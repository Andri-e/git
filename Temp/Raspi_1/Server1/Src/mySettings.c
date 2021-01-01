#include "../Include/open62541.h"
#include "../Include/mySettings.h"

// Argument check, is Port number default? 
void checkArguments(UA_Server *server, int argc, char * argv[] )
{
    if(argc != 0)
    {
		UA_Int16 port_number = atoi(argv[1]);
		UA_ServerConfig_setMinimal(UA_Server_getConfig(server), port_number, 0);
    }
	else
    {	
		UA_ServerConfig_setDefault(UA_Server_getConfig(server));
    }
}

