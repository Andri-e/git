myClient2: ../Open62541/open62541.o myClient2.o
	gcc ../Open62541/open62541.o myClient2.o -o myClient2

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myClient2.o: myClient2.c 
	gcc -c myClient2.c 

clean: 
	rm *.o myClient2

run: 
	./myClient2
