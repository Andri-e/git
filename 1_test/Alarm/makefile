alarm: ../Open62541/open62541.o alarm.o
	gcc ../Open62541/open62541.o alarm.o -o alarm

../Open62541/open62541.o: ../Open62541/open62541.c
	gcc -c -std=c99 ../Open62541/open62541.c -o ../Open62541/open62541.o
	
alarm.o: alarm.c 
	gcc -c alarm.c 

clean: 
	rm *.o alarm

run: 
	./alarm
