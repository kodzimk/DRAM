CFLAGS = 
LIBS = 

build:
	$(CC) $(CFLAGS) -o dram src/dram.c src/*.h src/components/components.o -lm $(LIBS)

run:
	./dram
clean:
	rm dram