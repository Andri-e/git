#include "open62541.h"

#include <signal.h>
#include <stdlib.h>


//#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>

// myServer main 
int main(int argc, char * argv[])
{
	long int i = 1; 
	
	for (int a = 0; a < 100; ++a)
	{
		i = a * i;
		i = (a * i) / 3.14;
	}



    return 0;
}
