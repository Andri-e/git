#include "open62541.h"

#include <signal.h>
#include <stdlib.h>


//#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>



static volatile UA_Boolean running = true;			// Server state

UA_Double variable = 20.0;						
UA_DateTime timeStamp = 0;	

UA_Float systemp = 0; 

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
    UA_Int32 serialNumber = 123456;
    UA_Variant_setScalar(&snAttr.value, &serialNumber, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testSerial"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Serial Number"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), snAttr, NULL, NULL);
	
	//Add the Variable to the server
    UA_VariableAttributes tsAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&tsAttr.value, &variable, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testTimeStamp"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "timeStamp"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), tsAttr, NULL, NULL);					  
	
	//Add the cpu Temperature to the server
    UA_VariableAttributes variableAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&variableAttr.value, &systemp, &UA_TYPES[UA_TYPES_FLOAT]);
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

// Variable Callback 
static void beforeReadVariable(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeid, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data) 
{
	// Read cpu Temp 
	float millideg;
	FILE *thermal;
	int n;

	thermal = fopen("/sys/class/thermal/thermal_zone0/temp","r");
	n = fscanf(thermal,"%f",&millideg);
	fclose(thermal);
	systemp = millideg / 1000;

	// Way to update the variable 
	UA_Variant value;
	UA_Variant_setScalar(&value, &systemp, &UA_TYPES[UA_TYPES_FLOAT]);
    //UA_Variant_setScalar(&value, &variable, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_writeValue(server, UA_NODEID_STRING(2, "testVariable"), value);
}

static void addValueCallbackToCurrentVariable(UA_Server *server) {
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
    signal(SIGTERM, stopHandler);
	
	
	
	
	char str[100];
	const char d[2] = " ";
	char* token;
	int i = 0,times,lag;
	long int sum = 0, idle, lastSum = 0,lastIdle = 0;
	long double idleFraction;
 
	if(argC!=3)
		printf("Usage : %s <number of times /proc/stat should be polled followed by delay in seconds.>",argV[0]);
 
	else{
		times = atoi(argV[1]);
		lag = atoi(argV[2]);
 
		while(times>0){
			FILE* fp = fopen("/proc/stat","r");
	                i = 0;
			fgets(str,100,fp);
			fclose(fp);
			token = strtok(str,d);
	                sum = 0;
			while(token!=NULL){
				token = strtok(NULL,d);
				if(token!=NULL){
					sum += atoi(token);
 
				if(i==3)
					idle = atoi(token);
 
				i++;
			        }
		        }
	                idleFraction = 100 - (idle-lastIdle)*100.0/(sum-lastSum);
		        printf("Busy for : %lf %% of the time.", idleFraction);
 
		        lastIdle = idle;
		        lastSum = sum;
 
 
		        times--;
		        sleep(lag);
		}	
	}
	
	
	
	
	

	
	
	
	
	// Creating a new server 
    UA_Server *server = UA_Server_new();

	// Check for Arguments, host name and port number
	checkArguments(server, argc, argv);

	// Setup the nodes used 
	nodeSetup(server);
	
	// Add callback for updating the TimeStamp / Variable
	addValueCallbackToCurrentTimeVariable(server);
	addValueCallbackToCurrentVariable(server);

	// Server start up 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting server...");
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Shuting down server....");

	// Clean up after shut down 
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
