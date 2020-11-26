myServer: myServer.o myEvent.o myNodes.o mySettings.o open62541.o
	gcc myServer.o myEvent.o myNodes.o mySettings.o open62541.o -o myServer

myServer.o: myServer.c	
	gcc -c myServer.c 

myEvent.o: Include/myEvent.c Include/myEvent.h 
	gcc -c Include/myEvent.c  
	
myNodes.o: Include/myNodes.c Include/myNodes.h 
	gcc -c Include/myNodes.c 
	
mySettings.o: Include/mySettings.c Include/mySettings.h
	gcc -c Include/mySettings.c 
	
open62541.o: Include/open62541.c Include/open62541.h 
	gcc -c Include/open62541.c 
	
specNodes.o: Include/specNodes.c Include/specNodes.h 
	gcc -c Include/specNodes.c 
	
clean: 
	rm *.o myServer

run: 
	./myServer
