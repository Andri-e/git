myServer: 
	gcc -c ./Include/myEvent.c 
	gcc -c ./Include/myNodes.c
	gcc -c ./Include/mySettings.c
	gcc -c ./Include/open62541.c 
	gcc -c ./Include/specNodes.c 
	
	gcc -c myServer.c 
	
	gcc myEvents.o myNodes.o mySettings.o open62541.o specNodes.o myServer.o -o myServer
	
clean: 
	rm *.o myServer

run: 
	./myServer
