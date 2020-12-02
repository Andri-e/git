myServer: myServer.o myEvent.o myNodes.o mySettings.o open62541.o specNodes.o myMethod.o
	gcc myServer.o myEvent.o myNodes.o mySettings.o open62541.o specNodes.o myMethod.o -o myServer

myServer.o: Src/myServer.c	
	gcc -c myServer.c 

myEvent.o: Src/myEvent.c Include/myEvent.h 
	gcc -c Src/myEvent.c  
	
myNodes.o: Src/myNodes.c Include/myNodes.h 
	gcc -c Src/myNodes.c 
	
mySettings.o: Src/mySettings.c Include/mySettings.h
	gcc -c Src/mySettings.c 
	
open62541.o: Src/open62541.c Include/open62541.h 
	gcc -c Src/open62541.c 
	
specNodes.o: Src/specNodes.c Include/specNodes.h 
	gcc -c Src/specNodes.c 
	
myMethod.o: Src/myMethod.c Include/myMethod.h
	gcc -c Src/myMethod.c
	
clean: 
	rm *.o myServer

run: 
	./myServer
