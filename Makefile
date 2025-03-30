CFLAGS = 
LIBS = 

build:
	$(CC) $(CFLAGS) -o dram src/main.c src/segment.h src/components/*.h $(LIBS)

run:
	./dram
clean:
	rm dram