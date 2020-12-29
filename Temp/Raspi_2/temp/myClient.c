#include "open62541.h"

#include <signal.h>
#include <stdlib.h>

UA_Boolean running = true;

static void stopHandler(int sign) 
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Received Ctrl-C");
    running = 0;
}

int main(void)
{
	signal(SIGINT, stopHandler); // catches ctrl-c 
	
	UA_Client *client = UA_Client_new();
    UA_ClientConfig *cc = UA_Client_getConfig(client);
    UA_ClientConfig_setDefault(cc);

    // default timeout is 5 seconds. Set it to 1 second here for demo 
   // cc->timeout = 1000;


 //   UA_Variant value; /* Variants can hold scalar values and arrays of any type */
 //   UA_Variant_init(&value);
	UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
	
//	printf("\t\t\t\t\t\t\tUser Name \tUser Id \tTime Stamp \t\tVariable\n");	
	// While loop that keeps reading the value from the server until it is disconnected 
    while(running) 
	{
        if(retval != UA_STATUSCODE_GOOD) 						// If status code not good then log time and try to reconect 
		{ 
			UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Not connected. Retrying to connect in 2 second");		
            UA_sleep_ms(2000);
			UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
            continue;
        }
	//	readNode(client, retval, value);
		
       // UA_sleep_ms(500);				// Just a delay to reduce the spam
    };

    // Clean up 
   // UA_Variant_clear(&value);
    UA_Client_delete(client); //Disconnects the client internally 
    return EXIT_SUCCESS;
}