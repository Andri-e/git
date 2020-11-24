myServer: 
	gcc -c ./Include/myEvent.c 
	gcc -c ./Include/myNodes.c
	gcc -c ./Include/mySettings.c
	gcc -c ./Include/open62541.c 
	gcc -c ./Include/specNodes.c 
	gcc -c myServer.c 
	
	gcc -o myServer myServer.c ./Include/myEvent.c ./Include/myNodes.c ./Include/mySettings.c ./Include/open62541.c ./Include/specNodes.c 
	

	
clean: 
	rm *.o myServer

run: 
	./myServer
