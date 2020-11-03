myClient_2: ../Open62541/open62541.o myClient_2.o
	gcc ../Open62541/open62541.o myClient_2.o -o myClient_2

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myClient_2.o: myClient_2.c 
	gcc -c myClient_2.c 

clean: 
	rm *.o myClient_2

run: 
	./myClient_2
