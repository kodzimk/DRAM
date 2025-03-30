CFLAGS = 
LIBS = 

build:
	$(CC) $(CFLAGS) -o dram src/main.c src/components/MPlex.h src/components/DEMPlex.h src/components/cell.h $(LIBS)

run:
	./dram
clean:
	rm dram