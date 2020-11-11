myClient1: ../Open62541/open62541.o myClient1.o
	gcc ../Open62541/open62541.o myClient1.o -o myClient1

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myClient1.o: myClient1.c 
	gcc -c myClient1.c 

clean: 
	rm *.o myClient1

run: 
	./myClient1
