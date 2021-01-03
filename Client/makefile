myClient: myClient.o myRead.o open62541.o 
	gcc myClient.o myRead.o open62541.o  -o myClient

myClient.o: src/myClient.c	
	gcc -c src/myClient.c 

myRead.o: src/myRead.c include/myRead.h 
	gcc -c src/myRead.c  
	
clean: 
	rm *.o myClient

run: #adasdasdas
	./myClient  
