#include "open62541.h"

#include <signal.h>
#include <stdlib.h>

UA_Boolean running = true;


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

	//UA_Double variable;
	
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
	
	// Maybe add a latency check since I got a time stamp I can calculate the latency 
	UA_DateTime refTimeStamp;
	refTimeStamp = UA_DateTime_now();
	UA_DateTimeStruct dts_1 = UA_DateTime_toStruct(refTimeStamp);	
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "%u-%u-%u %u:%u:%u.%03u", dts_1.day, dts_1.month, dts_1.year, dts_1.hour, dts_1.min, dts_1.sec, dts_1.milliSec);
	

		
	
    //Read the variable 
//  retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(2, "testVariable"), &value);
//  if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE])) 
//  {
//		variable = *(UA_Double *) value.data;
//		//UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Variable Value : %f", variable);
//   }
	
	
	//UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "%.*s , %d , %u-%u-%u %u:%u:%u.%03u , %f °C, %f %%", variableName.length, variableName.data, serialNumber, dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec, sysTemp, sysIdle );


    // Segmentation fault? 

  //  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "%.*s , %d , %u-%u-%u %u:%u:%u.%03u , %f °C, %f %%", variableName.length, variableName.data, 
  //  serialNumber, 
  //  dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec, 
  //  sysTemp, 
   // sysIdle );

    printf("\n %.*s , %d \n" variableName.length, variableName.data);

}


// myClient main 
int main(void)
{
    
	signal(SIGINT, stopHandler); // catches ctrl-c 

	
	UA_Client *client = UA_Client_new();
    UA_ClientConfig *cc = UA_Client_getConfig(client);
    UA_ClientConfig_setDefault(cc);

    // default timeout is 5 seconds. Set it to 1 second here for demo 
    cc->timeout = 1000;

    // Read the value attribute of the node. UA_Client_readValueAttribute is a
    // wrapper for the raw read service available as UA_Client_Service_read. 
    UA_Variant value; // Variants can hold scalar values and arrays of any type 
    UA_Variant_init(&value);
	//UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
	UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.1.58:4840");
	

    
	// While loop that keeps reading the value from the server until it is disconnected 
    while(running) 
	{
        
        if(retval != UA_STATUSCODE_GOOD) 						// If status code not good then log time and try to reconect 
		{ 
			UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Not connected. Retrying to connect in 1 second");		
			UA_DateTime raw_date = *(UA_DateTime *) value.data;
            UA_DateTimeStruct dts = UA_DateTime_toStruct(raw_date);
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Re-Connected at : %02u-%02u-%04u %02u:%02u:%02u.%03u",
                        dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec);
						
            UA_sleep_ms(10000);
			UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.1.58:4840");
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

