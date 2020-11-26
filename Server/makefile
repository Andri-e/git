myServer: myServer.o myEvent.o myNodes.o mySettings.o open62541.o
	gcc myServer.o myEvent.o myNodes.o mySettings.o open62541.o -o myServer

myServer.o: myServer.clean	
	gcc -c myServer.c 

myEvent.o: myEvent.c myEvent.h 
	gcc -c myEvent.c 
	
myNodes.o: myNodes.c myNodes.h 
	gcc -c myNodes.c 
	
mySettings.o: mySettings.c mySettings.h
	gcc -c mySettings.c 
	
open62541.o: open62541.c open62541.h 
	gcc -c open62541.c 
	
specNodes.o: specNodes.c specNodes.h 
	gcc -c specNodes.c 
	
#clean: 
#	rm *.o myServer

#run: 
#	./myServer
