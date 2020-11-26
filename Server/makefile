# Tell the compiler about the headers directory
CFLAGS += -I./Includes

# Find all C source files
SRCS := $(wildcard Src/*.c)

# Compute object file names from source file names
OBJS := $(patsubst Src/%.c,%.o,$(SRCS))

# Static pattern rule to tell make how to build an
# object file from its source file
$(OBJS): %.o: Src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Tell make that `funcXX.o` depends on the `Includes/funcXX.h`
# such that it rebuilds the former if the latter changes
#myEvent.o: Includes/myEvent.h
#	gcc -c ./Src/myEvent.c 
 
#myNodes.o: Includes/myNodes.h 
#	gcc -c ./Src/myNodes.c
 
#mySettings.o: Includes/mySettings.h 
#	gcc -c ./Src/mySettings.c
 
#open62541.o: Includes/open62541.h 
#	gcc -c ./Src/open62541.c
 
#specNodes.o: Includes/specNodes.h 
#	gcc -c ./Src/specNodes.c

 %.o: Includes/%.h


# Tell make that `Mainfile.o` depends on all `Includes/funcXX.h`
# files such that it rebuilds the former if any of the latter
# changes
myServer.o: $(wildcard Includes/*.h)
	gcc -c myServer.c

# Tell make how to build the executable from the object files
#myServer: $(OBJS)
#	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	
clean: 
	rm *.o myServer

# Might have to do chmod 777 -R yourDir to make the run file run
run: 
	./myServer
