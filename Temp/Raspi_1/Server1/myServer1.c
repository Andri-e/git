#include "open62541.h"

#include <signal.h>
#include <stdlib.h>

#define SERVER_ENDPOINT "opc.tcp://localhost:4841"

static volatile UA_Boolean running = true;			// Server state

UA_Double variable = 20.0;						
UA_DateTime timeStamp = 0;	

// Stop handler to watch for ctrl + c 
static void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

// Argument check, is Host name and Port number default? 
static void checkArguments(UA_Server *server, int argc, char * argv[] )
{
	//Check for Arguments, host name and port number
    if(argc > 2)
    {
		UA_Int16 port_number = atoi(argv[2]);
		UA_ServerConfig_setMinimal(UA_Server_getConfig(server), port_number, 0);
    } 
    else
    {	
		UA_Int16 port_number = 4841; 
		UA_ServerConfig_setMinimal(UA_Server_getConfig(server), port_number, 0);
		//UA_ServerConfig_setDefault(UA_Server_getConfig(server));
    }

    if(argc > 1)
    {
		//Copy the hostname from char * to an open62541 Variable
		UA_String hostname;
		UA_String_init(&hostname);
		hostname.length = strlen(argv[1]);
		hostname.data = (UA_Byte *) argv[1];

		//Change the configuration 
		UA_ServerConfig_setCustomHostname(UA_Server_getConfig(server), hostname);
    }
}

// Setting up the object node and its variables 
static void nodeSetup(UA_Server *server)
{
 //Add a new namespace to the server
    UA_Int16 ns_1 = UA_Server_addNamespace(server, "Namespace_1");
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "New Namespace added with Nr. %d", ns_1);

    //Add a new object called testObject 
    UA_NodeId testObjectId;
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    UA_Server_addObjectNode(server, UA_NODEID_STRING(2, "testObject"),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(2, "Test Object"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &testObjectId);

    //
    UA_VariableAttributes vnAttr = UA_VariableAttributes_default;
    UA_String variableName = UA_STRING("nameOfUser");
    UA_Variant_setScalar(&vnAttr.value, &variableName, &UA_TYPES[UA_TYPES_STRING]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testUserName"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "User Name"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), vnAttr, NULL, NULL);

    //
    UA_VariableAttributes userIdAttr = UA_VariableAttributes_default;
    UA_Int32 userId = 654321;
    UA_Variant_setScalar(&userIdAttr.value, &userId, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testUserId"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "User Identification"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), userIdAttr, NULL, NULL);
	
	//
    UA_VariableAttributes tsAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&tsAttr.value, &timeStamp, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testTimeStamp"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "timeStamp"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), tsAttr, NULL, NULL);					  
	
	//Add the Variable to the server
    UA_VariableAttributes variableAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&variableAttr.value, &variable, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testVariable"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Variable"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), variableAttr, NULL, NULL);

/*
    //Add the Variable to the server
    UA_VariableAttributes variableAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&variableAttr.value, &variable, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testVariable"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Variable"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), variableAttr, NULL, NULL);
*/
}

// Time Stamp callback 
static void beforeReadTime(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeid, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data) 
{
    timeStamp = UA_DateTime_now();
    UA_Variant value;
    UA_Variant_setScalar(&value, &timeStamp, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_Server_writeValue(server, UA_NODEID_STRING(2, "testTimeStamp"), value);
}

static void addValueCallbackToCurrentTimeVariable(UA_Server *server) {
    UA_ValueCallback callback ;
    callback.onRead = beforeReadTime;
    callback.onWrite = NULL;
    UA_Server_setVariableNode_valueCallback(server, UA_NODEID_STRING(2, "testTimeStamp"), callback);
}

// Variable callback 
static void beforeReadVariable(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeid, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data) 
{

	variable = variable + 1 ; 

    UA_Variant value;
    UA_Variant_setScalar(&value, &variable, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_Server_writeValue(server, UA_NODEID_STRING(2, "testVariable"), value);
}

static void addValueCallbackVariable(UA_Server *server) {
    UA_ValueCallback callback ;
    callback.onRead = beforeReadVariable;
    callback.onWrite = NULL;
    UA_Server_setVariableNode_valueCallback(server, UA_NODEID_STRING(2, "testVariable"), callback);
}


// myServer main 
int main(int argc, char * argv[])
{
	// Setting up the signals for the stop signal (ctrl + c)
    signal(SIGINT, stopHandler);
   // signal(SIGTERM, stopHandler);
	

	// Creating a new server 
    UA_Server *server = UA_Server_new();

	// Check for Arguments and setup host name and port number
	checkArguments(server, argc, argv);

	// Setup the nodes used 
	nodeSetup(server);
	
	// Add callback for updating the TimeStamp / Variable
	addValueCallbackToCurrentTimeVariable(server);
	addValueCallbackVariable(server);

	
	// Server start up 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting server...");
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Shuting down server....");

	// Clean up after shut down 
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
