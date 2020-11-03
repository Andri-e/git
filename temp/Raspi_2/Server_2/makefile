myServer_2: ../Open62541/open62541.o myServer_2.o
	gcc ../Open62541/open62541.o myServer_2.o -o myServer_2

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myServer_2.o: myServer_2.c 
	gcc -c myServer_2.c 

clean: 
	rm *.o myServer_2

run: 
	./myServer_2
