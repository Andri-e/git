#include "open62541.h"

#include <signal.h>
#include <stdlib.h>

UA_Boolean running = true;

#define SERVER_ENDPOINT "opc.tcp://192.168.1.59:4840"

static void stopHandler(int sign) 
{
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Received Ctrl-C");
  running = 0;
}


// read out the nodes 
static void readNode(UA_Client *client, UA_StatusCode retval, UA_Variant value)
{
  //Variables for read access 
  UA_String variableName;
  UA_Int32 serialNumber;
	UA_DateTime timeStamp;
	UA_Float sysTemp;
	UA_Double sysIdle;
	
	UA_Variant_clear(&value);
	UA_DateTimeStruct dts = UA_DateTime_toStruct(timeStamp);	

  //Read Variable name
  retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(2, "testVariableName"), &value);
  if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_STRING])) 
  {
		variableName = *(UA_String *) value.data;
  }

  //Read Serial Number 
  retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(2, "testSerial"), &value);
  if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32])) 
  {
		serialNumber = *(UA_Int32 *) value.data;
  }
	
	//Read the time stamp
  retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(2, "testTimeStamp"), &value);
  if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DATETIME])) 
  {
		timeStamp = *(UA_DateTime *) value.data;
		UA_DateTimeStruct dts = UA_DateTime_toStruct(timeStamp);	
  }

	//Read the cpu temp
  retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(2, "testSysTemp"), &value);
  if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_FLOAT])) 
  {
		sysTemp = *(UA_Float *) value.data;
  }
	
	
	//Read the cpu idle time
  retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(2, "testSysIdle"), &value);
  if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE])) 
  {
		sysIdle = *(UA_Double*) value.data;
  }
	
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "%.*s , %d , %u-%u-%u %u:%u:%u.%03u , %f °C, %f %%", variableName.length, variableName.data, serialNumber, dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec, sysTemp, sysIdle );
}


// myClient main 
int main(void)
{
	signal(SIGINT, stopHandler); // catches ctrl-c 
	
	UA_Client *client = UA_Client_new();
  UA_ClientConfig *cc = UA_Client_getConfig(client);
  UA_ClientConfig_setDefault(cc);

  UA_StatusCode retval = UA_Client_connect(client, SERVER_ENDPOINT);
  if(retval != UA_STATUSCODE_GOOD) 
  {
    UA_Client_delete(client);
    return retval;
  }

  UA_Variant value; 
  UA_Variant_init(&value);

  while(running) 
	{
    // Check if Client is still connected 
    if(retval != UA_STATUSCODE_GOOD) 						
		{ 
			UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Not connected. Retrying to connect in 2 second");	
      UA_StatusCode retval = UA_Client_connect(client, SERVER_ENDPOINT);	
      UA_sleep_ms(2000);
      continue;
    }
		readNode(client, retval, value);
		
    UA_sleep_ms(500);				// Just a delay to reduce the spam
  };

  // Clean up 
  UA_Variant_clear(&value);
  UA_Client_delete(client); //Disconnects the client internally 
  return EXIT_SUCCESS;
}