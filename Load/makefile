mySLoad: ../Open62541/open62541.o myLoad.o
	gcc ../Open62541/open62541.o myLoad.o -o myLoad

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
myLoad.o: myLoad.c 
	gcc -c myLoad.c 

clean: 
	rm *.o myLoad

run: 
	./myLoad
