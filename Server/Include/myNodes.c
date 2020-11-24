#include "myNodes.h"
#include "open62541.h"

UA_Double variable = 20.0;						
UA_DateTime timeStamp = 0;	
UA_Float systemp = 0; 
UA_Double sysidle = 0;

// Setting up the object node and its variables  asdasdasdasd
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
	
	//Add the time stamp to the server
    UA_VariableAttributes tsAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&tsAttr.value, &timeStamp, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testTimeStamp"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "timeStamp"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), tsAttr, NULL, NULL);					  
	
	//Add the cpu Temperature to the server
    UA_VariableAttributes sysTempAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&sysTempAttr.value, &systemp, &UA_TYPES[UA_TYPES_FLOAT]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testSysTemp"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "systemTemperature"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), sysTempAttr, NULL, NULL);
	
	//Add the Sys Idle to the server
    UA_VariableAttributes sysIdleAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&sysIdleAttr.value, &sysidle, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testSysIdle"), testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "sysIdlePercentage"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), sysIdleAttr, NULL, NULL);
	
	

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

// CPU Temperature Callback 
static void beforeReadTemperature(UA_Server *server,
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
    UA_Server_writeValue(server, UA_NODEID_STRING(2, "testSysTemp"), value);
}

static void addValueCallbackToCurrentTemerature(UA_Server *server) {
    UA_ValueCallback callback ;
    callback.onRead = beforeReadTemperature;
    callback.onWrite = NULL;
    UA_Server_setVariableNode_valueCallback(server, UA_NODEID_STRING(2, "testSysTemp"), callback);
}



// CPU Not idle Callback  - https://rosettacode.org/wiki/Linux_CPU_utilization - https://www.kgoettler.com/post/proc-stat/ for math n stuff 
static void beforeReadIdle(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeid, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data) 
{
	char str[100];
	const char d[2] = " ";
	char* token;
	int i = 0,times,lag;
	long int sum = 0, idle, lastSum = 0,lastIdle = 0;
	double sysIdleFraction;

	FILE* fp = fopen("/proc/stat","r");
	i = 0;
	fgets(str,100,fp);
	fclose(fp);
	token = strtok(str,d);
	sum = 0;
	while(token!=NULL)
	{
		token = strtok(NULL,d);
		if(token!=NULL)
		{
			sum += atoi(token);
			if(i==3)
			{
				idle = atoi(token);
			}
			i++;
		}
	}
	sysIdleFraction = 100 - (idle-lastIdle)*100.0/(sum-lastSum);
	lastIdle = idle;
	lastSum = sum;

	// Way to update the variable 
	UA_Variant value;
	UA_Variant_setScalar(&value, &sysIdleFraction, &UA_TYPES[UA_TYPES_DOUBLE]);
    UA_Server_writeValue(server, UA_NODEID_STRING(2, "testSysIdle"), value);
}

static void addValueCallbackToCurrentIdle(UA_Server *server) {
    UA_ValueCallback callback ;
    callback.onRead = beforeReadIdle;
    callback.onWrite = NULL;
    UA_Server_setVariableNode_valueCallback(server, UA_NODEID_STRING(2, "testSysIdle"), callback);
}