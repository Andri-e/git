myClient2: ./Open62541/open62541.o myClient2.o
	gcc ./Open62541/open62541.o myClient2.o -o myClient2

./Open62541/open62541.o: ./Open62541/open62541.c
	gcc -c ./Open62541/open62541.c -o ./Open62541/open62541.o
	
myClient2.o: myClient.c 
	gcc -c myClient.c 

clean: 
	rm *.o myClient

run: 
	./myClient2
