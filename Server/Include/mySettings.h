#include "mySettings.c"

static volatile UA_Boolean running = true;			// Server state

// Stop handler to watch for ctrl + c 
static void stopHandler(int sig);

// Argument check, is Host name and Port number default? 
static void checkArguments(UA_Server *server, int argc, char * argv[]);