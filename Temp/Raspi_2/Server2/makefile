myServer2: ../Open62541/open62541.o myServer2.o
	gcc ../Open62541/open62541.o myServer2.o -o myServer2

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myServer2.o: myServer2.c 
	gcc -c myServer2.c 

clean: 
	rm *.o myServer2

run: 
	./myServer2
