#include "open62541.h"

#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include <inttypes.h>
#include <math.h>
#include <stdio.h>


UA_Boolean running = true;

// ---------------------------------------

// #define DISCOVERY_SERVER_ENDPOINT "opc.tcp://localhost:4840"


// ---------------------------------------

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
	

	
	UA_DateTime refTimeStamp;
	refTimeStamp = UA_DateTime_now();
	UA_DateTimeStruct dts_1 = UA_DateTime_toStruct(refTimeStamp);	
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "%u-%u-%u %u:%u:%u.%03u", dts_1.day, dts_1.month, dts_1.year, dts_1.hour, dts_1.min, dts_1.sec, dts_1.milliSec);
	

		
	/*
    //Read the variable 
    retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(2, "testVariable"), &value);
    if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE])) 
    {
		variable = *(UA_Double *) value.data;
		//UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Variable Value : %f", variable);
    }
	*/
	//UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "%.*s , %d , %u-%u-%u %u:%u:%u.%03u , %f . ", variableName.length, variableName.data, serialNumber, dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec, variable );
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "%.*s , %d , %u-%u-%u %u:%u:%u.%03u , %f °C, %f %%", variableName.length, variableName.data, serialNumber, dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec, sysTemp, sysIdle );
}

// myClient main 
int main(void)
{
	signal(SIGINT, stopHandler); // catches ctrl-c 
	
	UA_Client *client = UA_Client_new();
    UA_ClientConfig *cc = UA_Client_getConfig(client);
    UA_ClientConfig_setDefault(cc);

    /* default timeout is 5 seconds. Set it to 1 second here for demo */
    cc->timeout = 1000;

    /* Read the value attribute of the node. UA_Client_readValueAttribute is a
     * wrapper for the raw read service available as UA_Client_Service_read. */
    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&value);
	UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
	
	// While loop that keeps reading the value from the server until it is disconnected 
    while(running) 
	{
		//UA_Variant_clear(&value);
        if(retval != UA_STATUSCODE_GOOD) 						// If status code not good then log time and try to reconect 
		{ 
			UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Not connected. Retrying to connect in 1 second");		
			UA_DateTime raw_date = *(UA_DateTime *) value.data;
            UA_DateTimeStruct dts = UA_DateTime_toStruct(raw_date);
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Re-Connected at : %02u-%02u-%04u %02u:%02u:%02u.%03u",
                        dts.day, dts.month, dts.year, dts.hour, dts.min, dts.sec, dts.milliSec);
						
            UA_sleep_ms(1000);
			UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
            continue;
        }

        //UA_Variant_clear(&value);
		//{
		readNode(client, retval, value);
		//}
        UA_sleep_ms(500);				// Just a delay to reduce the spam
    };

    // Clean up 
    UA_Variant_clear(&value);
    UA_Client_delete(client); //Disconnects the client internally 
    return EXIT_SUCCESS;
	
}



// ---------------------------------

/*
    {
        UA_ServerOnNetwork *serverOnNetwork = NULL;
        size_t serverOnNetworkSize = 0;

        UA_Client *client = UA_Client_new();
        UA_ClientConfig_setDefault(UA_Client_getConfig(client));
        UA_StatusCode retval = UA_Client_findServersOnNetwork(client, DISCOVERY_SERVER_ENDPOINT, 0, 0,
                                                              0, NULL, &serverOnNetworkSize, &serverOnNetwork);
        if(retval != UA_STATUSCODE_GOOD) {
            UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                         "Could not call FindServersOnNetwork service. "
                         "Is the discovery server started? StatusCode %s",
                         UA_StatusCode_name(retval));
            UA_Client_delete(client);
            return EXIT_FAILURE;
        }

        // output all the returned/registered servers
        for(size_t i = 0; i < serverOnNetworkSize; i++) {
            UA_ServerOnNetwork *server = &serverOnNetwork[i];
            printf("Server[%lu]: %.*s", (unsigned long) i,
                   (int) server->serverName.length, server->serverName.data);
            printf("\n\tRecordID: %d", server->recordId);
            printf("\n\tDiscovery URL: %.*s", (int) server->discoveryUrl.length,
                   server->discoveryUrl.data);
            printf("\n\tCapabilities: ");
            for(size_t j = 0; j < server->serverCapabilitiesSize; j++) {
                printf("%.*s,", (int) server->serverCapabilities[j].length,
                       server->serverCapabilities[j].data);
            }
            printf("\n\n");
        }

        UA_Array_delete(serverOnNetwork, serverOnNetworkSize,
                        &UA_TYPES[UA_TYPES_SERVERONNETWORK]);
    }
	

    // Example for calling FindServers 
    UA_ApplicationDescription *applicationDescriptionArray = NULL;
    size_t applicationDescriptionArraySize = 0;

    UA_StatusCode retval;
    {
        UA_Client *client = UA_Client_new();
        UA_ClientConfig_setDefault(UA_Client_getConfig(client));
        retval = UA_Client_findServers(client, DISCOVERY_SERVER_ENDPOINT, 0, NULL, 0, NULL,
                                       &applicationDescriptionArraySize, &applicationDescriptionArray);
        UA_Client_delete(client);
    }
    if(retval != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not call FindServers service. "
                "Is the discovery server started? StatusCode %s", UA_StatusCode_name(retval));
        return EXIT_FAILURE;
    }

    // output all the returned/registered servers
    for(size_t i = 0; i < applicationDescriptionArraySize; i++) {
        UA_ApplicationDescription *description = &applicationDescriptionArray[i];
        printf("Server[%lu]: %.*s", (unsigned long) i, (int) description->applicationUri.length,
               description->applicationUri.data);
        printf("\n\tName: %.*s", (int) description->applicationName.text.length,
               description->applicationName.text.data);
        printf("\n\tApplication URI: %.*s", (int) description->applicationUri.length,
               description->applicationUri.data);
        printf("\n\tProduct URI: %.*s", (int) description->productUri.length,
               description->productUri.data);
        printf("\n\tType: ");
        switch(description->applicationType) {
            case UA_APPLICATIONTYPE_SERVER:
                printf("Server");
                break;
            case UA_APPLICATIONTYPE_CLIENT:
                printf("Client");
                break;
            case UA_APPLICATIONTYPE_CLIENTANDSERVER:
                printf("Client and Server");
                break;
            case UA_APPLICATIONTYPE_DISCOVERYSERVER:
                printf("Discovery Server");
                break;
            default:
                printf("Unknown");
        }
        printf("\n\tDiscovery URLs:");
        for(size_t j = 0; j < description->discoveryUrlsSize; j++) {
            printf("\n\t\t[%lu]: %.*s", (unsigned long) j,
                   (int) description->discoveryUrls[j].length,
                   description->discoveryUrls[j].data);
        }
        printf("\n\n");
    }


    
    // Now that we have the list of available servers, call get endpoints on all of them
     

    printf("-------- Server Endpoints --------\n");

    for(size_t i = 0; i < applicationDescriptionArraySize; i++) {
        UA_ApplicationDescription *description = &applicationDescriptionArray[i];
        if(description->discoveryUrlsSize == 0) {
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT,
                        "[GetEndpoints] Server %.*s did not provide any discovery urls. Skipping.",
                        (int)description->applicationUri.length, description->applicationUri.data);
            continue;
        }

        printf("\nEndpoints for Server[%lu]: %.*s\n", (unsigned long) i,
               (int) description->applicationUri.length, description->applicationUri.data);

        UA_Client *client = UA_Client_new();
        UA_ClientConfig_setDefault(UA_Client_getConfig(client));

        char *discoveryUrl = (char *) UA_malloc(sizeof(char) * description->discoveryUrls[0].length + 1);
        memcpy(discoveryUrl, description->discoveryUrls[0].data, description->discoveryUrls[0].length);
        discoveryUrl[description->discoveryUrls[0].length] = '\0';

        UA_EndpointDescription *endpointArray = NULL;
        size_t endpointArraySize = 0;
        //TODO: adapt to the new async getEndpoint
        retval = UA_Client_getEndpoints(client, discoveryUrl, &endpointArraySize, &endpointArray);
        UA_free(discoveryUrl);
        if(retval != UA_STATUSCODE_GOOD) {
            UA_Client_disconnect(client);
            UA_Client_delete(client);
            break;
        }

        for(size_t j = 0; j < endpointArraySize; j++) {
            UA_EndpointDescription *endpoint = &endpointArray[j];
            printf("\n\tEndpoint[%lu]:", (unsigned long) j);
            printf("\n\t\tEndpoint URL: %.*s", (int) endpoint->endpointUrl.length, endpoint->endpointUrl.data);
            printf("\n\t\tTransport profile URI: %.*s", (int) endpoint->transportProfileUri.length,
                   endpoint->transportProfileUri.data);
            printf("\n\t\tSecurity Mode: ");
            switch(endpoint->securityMode) {
            case UA_MESSAGESECURITYMODE_INVALID:
                printf("Invalid");
                break;
            case UA_MESSAGESECURITYMODE_NONE:
                printf("None");
                break;
            case UA_MESSAGESECURITYMODE_SIGN:
                printf("Sign");
                break;
            case UA_MESSAGESECURITYMODE_SIGNANDENCRYPT:
                printf("Sign and Encrypt");
                break;
            default:
                printf("No valid security mode");
                break;
            }
            printf("\n\t\tSecurity profile URI: %.*s", (int) endpoint->securityPolicyUri.length,
                   endpoint->securityPolicyUri.data);
            printf("\n\t\tSecurity Level: %d", endpoint->securityLevel);
        }

        UA_Array_delete(endpointArray, endpointArraySize, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
        UA_Client_delete(client);
    }

    printf("\n");

    UA_Array_delete(applicationDescriptionArray, applicationDescriptionArraySize,
                    &UA_TYPES[UA_TYPES_APPLICATIONDESCRIPTION]);
					
					
*/











// -------------------------------------------------------
