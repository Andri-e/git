#include "open62541.h"

#include <signal.h>
#include <stdlib.h>

#include "./Include/mySettings.h"
#include "./Include/myEvent.h"
#include "./Include/myNodes.h"
#include "./Include/specNodes.h"
#include "./Include/myMethod.h"

// Want to add 
        // Security 
            // see : https://github.com/open62541/open62541/issues/3002
        // Pub/sub? 
            // see : https://stackoverflow.com/questions/58855146/opcua-open62541-pubsub-how-to-publish-value-change
            //       https://github.com/open62541/open62541/issues/2363 
        // Conditions? 
            //
        
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

    // Set security 
    //UA_ServerConfig_setDefault(UA_Server_getConfig(server));

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
	
    // Method node 
    addMethodNode(server);

	// Server start up 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting server...");
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Shuting down server....");

	// Clean up after shut down 
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
