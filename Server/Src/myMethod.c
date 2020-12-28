#include "../Include/open62541.h"
#include "../Include/myMethod.h"

UA_StatusCode MethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) 
{
    /*
    UA_String *inputStr = (UA_String*)input->data;
    UA_String response = UA_STRING_ALLOC("Undefined");

    if(inputStr->length == 1)
    {
        switch(inputStr->data[0])
        {
            */
    UA_String inputStr = *(UA_String*)input->data;
    UA_String response = UA_STRING_ALLOC("Undefined");

    if(inputStr.length == 1)
    {
        switch(inputStr.data[0])
        {          
            case '1' :
                printf("Case 1 \n");
                response = UA_STRING_ALLOC("Case 1 selected.");
                break;
            case '2' :
                printf("Case 2 \n");
                response = UA_STRING_ALLOC("Case 2 selected.");
                break;
            case '3' :
                printf("Case 3 \n");
                response = UA_STRING_ALLOC("Case 3 selected.");
                break;
            default : 
                printf("Incorect value picked. \n");
                response = UA_STRING_ALLOC("Incorect value picked.");
                break;
        }
    } 
    else 
    {
        printf("Incorrect value selected, please try again.\n");
        response = UA_STRING_ALLOC("Incorrect value selected, please try again.");
    }

    response.data = (UA_Byte *)UA_realloc(response.data, response.length);
    UA_Variant_setScalarCopy(output, &response, &UA_TYPES[UA_TYPES_STRING]);
    
    // Cleanup 
    UA_String_clear(&response);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Method was called");
    return UA_STATUSCODE_GOOD;
}

void addMethodNode(UA_Server *server) 
{
    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);
    inputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
    inputArgument.name = UA_STRING("Input");
    inputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputArgument.valueRank = UA_VALUERANK_SCALAR;

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);
    outputArgument.description = UA_LOCALIZEDTEXT("en-US", "A String");
    outputArgument.name = UA_STRING("Output");
    outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    outputArgument.valueRank = UA_VALUERANK_SCALAR;

    UA_MethodAttributes mtdAttr = UA_MethodAttributes_default;
    mtdAttr.description = UA_LOCALIZEDTEXT("en-US","Select : \t1 for xx \n\t2 for xy\n\t3 for yx\n\t4 for ... ");
    mtdAttr.displayName = UA_LOCALIZEDTEXT("en-US","Method Node");
    mtdAttr.executable = true;
    mtdAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1,62541),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "MethodNode"),
                            mtdAttr, &MethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
}
