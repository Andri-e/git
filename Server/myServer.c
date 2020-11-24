#include "open62541.h"

#include <signal.h>
#include <stdlib.h>


// mySettings.h
#include "./Include/mySettings.h"
// myEvent.h 
#include "./Include/myEvent.h"
// myNodes.h 
#include "./Include/myNodes.h"
// specNodes.h
#include "./Include/specNodes.h"

// Want to add 
        // Security 
        // Pub/sub? 
        // Conditions? 


// myServer main 
int main(int argc, char * argv[])
{
	// Setting up the signals for the stop signal (ctrl + c)
    signal(SIGINT, stopHandler);
   // signal(SIGTERM, stopHandler);


	// Creating a new server 
    UA_Server *server = UA_Server_new();

	// Check for Arguments, host name and port number
	checkArguments(server, argc, argv);

	// Setup the nodes used 
	nodeSetup(server);
	
	// Add callback for updating the variables 
	addValueCallbackToCurrentTimeVariable(server);
	addValueCallbackToCurrentTemerature(server);
	addValueCallbackToCurrentIdle(server);

    // Add a event to trigger a response 
    addNewEventType(server);
    addGenerateEventMethod(server);
	
	// Server start up 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting server...");
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Shuting down server....");

	// Clean up after shut down 
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
