#include "open62541.h"

#include <signal.h>
#include <stdlib.h>

static volatile UA_Boolean running = true;
static void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

//Global variable to print out in test Variable
UA_Double variable = 20.0;

// myServer with Hostname and Portnumber
int main(int argc, char * argv[])
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server *server = UA_Server_new();
   // UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    //Check for Arguments
    if(argc > 2)
    {
	UA_Int16 port_number = atoi(argv[2]);
	UA_ServerConfig_setMinimal(UA_Server_getConfig(server), port_number, 0);
    } 
    else
    {	
   	 UA_ServerConfig_setDefault(UA_Server_getConfig(server));
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

    //Add the variable name to the server
    UA_VariableAttributes vnAttr = UA_VariableAttributes_default;
    UA_String variableName = UA_STRING("nameOfVariable");
    UA_Variant_setScalar(&vnAttr.value, &variableName, &UA_TYPES[UA_TYPES_STRING]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testVariableName"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Vendor Name"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), vnAttr, NULL, NULL);

    //Add the variable serial number to the server 
    UA_VariableAttributes snAttr = UA_VariableAttributes_default;
    UA_Int32 serialNumber = Ua_Int32(123456);
    UA_Variant_setScalar(&snAttr.value, &serialNumber, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testSerial"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Serial Number"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), snAttr, NULL, NULL);

    //Add the Variable to the server
    UA_VariableAttributes variableAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&variableAttr.value, &variable, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testVariable"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Variable"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), variableAttr, NULL, NULL);




    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting server...");
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Shuting down server....");



    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
