myServer: 
	gcc -c ./Include/myEvents.c 
	gcc -c myNodes.c
	gcc -c mySettings.c
	gcc -c open62541.c 
	gcc -c specNodes.c 
	
	gcc -c myServer.c 
	
	gcc myEvents.o myNodes.o mySettings.o open62541.o specNodes.o myServer.o -o myServer
	
clean: 
	rm *.o myServer

run: 
	./myServer
