myClient: myClient.o myRead.o 
	gcc myClient.o myRead.o -o myClient

myClient.o: Src/myClient.c	
	gcc -c myClient.c 

myEvent.o: Src/myRead.c Include/myRead.h 
	gcc -c Src/myRead.c  
	
clean: 
	rm *.o myClient

run: #adasdasdas
	./myClient  
