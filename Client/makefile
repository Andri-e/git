myClient: myClient.o myRead.o open62541.o 
	gcc myClient.o myRead.o open62541.o  -o myClient

myClient.o: src/myClient.c	
	gcc -c src/myClient.c 

myRead.o: src/myRead.c include/myRead.h 
	gcc -c src/myRead.c  

open62541.o: src/open62541.c include/open62541.h 
	gcc -c src/open62541.c 
	
clean: 
	rm *.o myClient

run: #adasdasdasasdasd asdasd 
	./myClient  
