myServer: myServer.o myNodes.o mySettings.o open62541.o 
	gcc myServer.o myNodes.o mySettings.o open62541.o -o myServer

myServer.o: Src/myServer.c	
	gcc -c Src/myServer.c 

myNodes.o: Src/myNodes.c Include/myNodes.h 
	gcc -c Src/myNodes.c 

mySettings.o: Src/mySettings.c Include/mySettings.h
	gcc -c Src/mySettings.c 

open62541.o: Src/open62541.c Include/open62541.h 
	gcc -c Src/open62541.c 
	
clean: 
	rm *.o myServer

run: 
	./myServer
