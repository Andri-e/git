myServer: 
	gcc -c ./Include/myEvent.c 
	gcc -c ./Include/myNodes.c
	gcc -c ./Include/mySettings.c
	gcc -c ./Include/open62541.c 
	gcc -c ./Include/specNodes.c 
	gcc -c myServer.c 
	
	gcc -o Mainfile func_1.o func_2.o func_3.o func_4.o func_5.o Mainfile.o
	

	
clean: 
	rm *.o myServer

run: 
	./myServer
