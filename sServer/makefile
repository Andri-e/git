myServer: myServer.o myNodes.o mySettings.o open62541.o 
	gcc myServer.o myNodes.o mySettings.o open62541.o -o myServer

myServer.o: Src/myServer.c	
	gcc -c Src/myServer.c 

myNodes.o: Src/myNodes.c Include/myNodes.h 
	gcc -c Src/myNodes.c 
	

	
clean: 
	rm *.o myServer

run: 
	./myServer
