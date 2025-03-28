CFLAGS = 
LIBS = 

build:
	$(CC) $(CFLAGS) -o dram src/main.c src/components/MPlex.h src/components/DEMPlex.h $(LIBS)

run:
	./dram
clean:
	rm dram