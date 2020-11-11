#include "open62541.h"

#include <signal.h>
#include <stdlib.h>


//#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>

static volatile bool running = true;

// Stop handler to watch for ctrl + c 
static void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}


// myServer main 
int main(int argc, char * argv[])
{
	signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

	while (running == true)
	{
		long int i = 1; 
		for (int a = 0; a < 10000; ++a)
		{
			i = a * i;
			i = (a * i) / 3.14;
		}
	}


    return 0;
}
