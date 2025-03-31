CC=gcc
LN=ld
CFLAGS=-Wall -std=c99

HEADERS= bitutil.h bloom.h hashf.h MPlex.h cell.h DEMPlex.h RADecoder.h
SOURCES= bitutil.c bloom.c hashf.c
OBJECTS= bitutil.o bloom.o hashf.o 

.PHONY: default
default: build link
	
build: $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)
link: $(OBJECTS)
	$(LN) -r $(OBJECTS) -o components.o
clean:
	rm -f *.o *.i *.s