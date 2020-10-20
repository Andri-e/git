myClient: ../Open62541/open62541.o myClient.o
	gcc ../Open62541/open62541.o myClient.o -o myClient

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myServer.o: myClient.c 
	gcc -c myClient.c 

clean: 
	rm *.o myClient

run: 
	./myClient
