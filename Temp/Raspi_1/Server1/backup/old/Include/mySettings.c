#include "open62541.h"
#include "mySettings.h"

// Argument check, is Host name and Port number default? 
void checkArguments(UA_Server *server, int argc, char * argv[] )
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

