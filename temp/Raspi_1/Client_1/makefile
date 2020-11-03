myClient_1: ../Open62541/open62541.o myClient_1.o
	gcc ../Open62541/open62541.o myClient_1.o -o myClient_1

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myClient_1.o: myClient_1.c 
	gcc -c myClient_1.c 

clean: 
	rm *.o myClient_1

run: 
	./myClient_1
