myServer_1: ../Open62541/open62541.o myServer_1.o
	gcc ../Open62541/open62541.o myServer_1.o -o myServer_1

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myServer_1.o: myServer_1.c 
	gcc -c myServer_1.c 

clean: 
	rm *.o myServer_1

run: 
	./myServer_1
