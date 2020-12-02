#include "open62541.h"

#include <signal.h>
#include <stdlib.h>


// mySettings.h
#include "./Include/mySettings.h"
// myEvent.h 
#include "./Include/myEvent.h"
// myNodes.h 
#include "./Include/myNodes.h"
// specNodes.h
#include "./Include/specNodes.h"

// Want to add 
        // Methods 
            // Below 
        // Security 
            // see : https://github.com/open62541/open62541/issues/3002
        // Pub/sub? 
            // see : https://stackoverflow.com/questions/58855146/opcua-open62541-pubsub-how-to-publish-value-change
            //       https://github.com/open62541/open62541/issues/2363 
        // Conditions? 
            //
        


UA_StatusCode MethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) 
{
    UA_String *inputStr = (UA_String*)input->data;
   UA_String tmp = UA_STRING_ALLOC(" ");
   // printf("%s", inputStr->length, inputStr->data);
 //  printf("%s", &tmp.length, &tmp.data);
 
    if(inputStr->length > 0) 
   {
        printf("%s", &tmp.length, &tmp.data);


       tmp.data = (UA_Byte *)UA_realloc(tmp.data, tmp.length + inputStr->length);
        memcpy(&tmp.data[tmp.length], inputStr->data, inputStr->length);
       tmp.length += inputStr->length;
   }

UA_Variant_setScalarCopy(output, &tmp, &UA_TYPES[UA_TYPES_STRING]);


    printf("\tOutput data: %x\n", output[0].data);
    printf("\tOutput: %x\n", output);


  //  printf("\tOutput int: %x\n", *(UA_Int32*)output[0].data);
 //   UA_String value = *(UA_String*) output[0].data;
 //   printf("\tOutput : %x\n", value);


 //   printf("\tOutput type: %s\n", output[0].type->typeName);
    //printf("\t  Output string: %s\n", *(UA_String*)output[0].data);           // segmentation error argg .. 
 //   if(output[0].type == &UA_TYPES[UA_TYPES_STRING])
  //  {
  //      value = *(UA_String*)output[0].data;
  //     printf("\tOutput : %x\n", value);
//}

 //   printf("Drasl : %.*s\" ", (int)(value).length, (value).data);

    // virkar ekki 
 //   long drasl = strtol((value).data, NULL,  10 );
 //   printf("drasl prent : %ld\n", drasl);
 
    // ?? 
    //UA_Int32 value2 = *(UA_Int32*) output->data[0];
    //printf("\tOutput: %x\n", value2);


    UA_String strval = *(UA_String*)output[0].data;
 //   printf("\tOutput UAstring: " UA_PRINTF_STRING_FORMAT "\n", UA_PRINTF_STRING_DATA(strval));      // prentar 
    long int intval = strtol(strval.data, NULL, 10);
 //   printf("\tOutput int: %ld\n", intval);          // prentar ekki 


    
    switch(intval)
    {
        case '1' :
            printf("Case 1 \n");
            break;
        case '2' :
            printf("Case 2 \n");
            break;
        case '3' :
            printf("Case 3 \n");
            break;
        default : 
            printf("Incorect value picked. \n");
            break;

    }


    


    //printf("\tOutput: %s\n", value);          // get segmentation error.. hmm 

 //   UA_String_clear(&tmp);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Method was called");
    return UA_STATUSCODE_GOOD;
}

void addMethodNode(UA_Server *server) 
{
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
    inputArgument.name = UA_STRING("MyInput");
    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputArgument.valueRank = UA_VALUERANK_SCALAR;

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
    outputArgument.name = UA_STRING("MyOutput");
    outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    outputArgument.valueRank = UA_VALUERANK_SCALAR;

    UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
    helloAttr.description = UA_LOCALIZEDTEXT("en-US","Select : \t1 for xx \n\t2 for xy\n\t3 for yx\n\t4 for ... ");
    helloAttr.displayName = UA_LOCALIZEDTEXT("en-US","Method Node");
    helloAttr.executable = true;
    helloAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,62541),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "MethodNode"),
                            helloAttr, &MethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
}

static volatile UA_Boolean running = true;			// Server state

// Stop handler to watch for ctrl + c 
static void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

// myServer main 
int main(int argc, char * argv[])
{
	// Setting up the signals for the stop signal (ctrl + c)
    signal(SIGINT, stopHandler);

	// Creating a new server 
    UA_Server *server = UA_Server_new();

	// Check for Arguments, host name and port number
	checkArguments(server, argc, argv);

	// Setup the nodes used 
	nodeSetup(server);
    powerlinkNode(server);
	
	// Add callback for updating the variables 
	addValueCallbackToCurrentTimeVariable(server);
	addValueCallbackToCurrentTemerature(server);
	addValueCallbackToCurrentIdle(server);

    // Add a event to trigger a response 
    addNewEventType(server);
    addGenerateEventMethod(server);
	


// -- 

    addMethodNode(server);
// -- 


	// Server start up 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting server...");
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Shuting down server....");

	// Clean up after shut down 
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
