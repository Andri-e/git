myServer1: ../Open62541/open62541.o myServer1.o
	gcc ../Open62541/open62541.o myServer1.o -o myServer1

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myServer1.o: myServer1.c 
	gcc -c myServer1.c 

clean: 
	rm *.o myServer1

run: 
	./myServer1
