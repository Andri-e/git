myServer: ../Open62541/open62541.o myServer.o
	gcc ../Open62541/open62541.o myServer.o -o myServer

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myServer.o: myServer.c 
	gcc -c myServer.c 

clean: 
	rm *.o myServer

run: 
	./myServer
