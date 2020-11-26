myServer: 
	gcc -c ./Include/myEvent.c 
	gcc -c ./Include/myNodes.c
	gcc -c ./Include/mySettings.c
	gcc -c ./Include/open62541.c 
	gcc -c ./Include/specNodes.c 
	gcc -c myServer.c 
	
	gcc -o myServer myEvent.o myNodes.o mySettings.o open62541.o specNodes.o myServer.o
	

	
clean: 
	rm *.o myServer

run: 
	./myServer
