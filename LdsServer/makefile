server_lds: ../Open62541/open62541.o server_lds.o
	gcc ../Open62541/open62541.o server_lds.o -o server_lds

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
server_lds.o: server_lds.c 
	gcc -c server_lds.c 

clean: 
	rm *.o server_lds

run: 
	./server_lds
