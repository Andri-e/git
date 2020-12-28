myServer: 
	gcc -c ./Src/myEvent.c 
	gcc -c ./Src/myNodes.c
	gcc -c ./Src/mySettings.c
	gcc -c ./Src/open62541.c 
	gcc -c ./Src/specNodes.c 
	gcc -c ./Src/myServer.c 
	
	gcc -o myServer myEvent.o myNodes.o mySettings.o open62541.o specNodes.o myServer.o
	

	
clean: 
	rm *.o myServer

run: 
	./myServer
