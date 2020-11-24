#include "open62541.h"

#include <signal.h>
#include <stdlib.h>


// mySettings.h
#include "./Include/mySettings.h"


// Want to add 
        // Security 
        // Pub/sub? 
        // Conditions? 


// myServer main 
int main(int argc, char * argv[])
{
    // Creating a new server 
    UA_Server *server = UA_Server_new();

    setupServer(server);
	
	// Server start up 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting server...");
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Shuting down server....");

	// Clean up after shut down 
    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
