CFLAGS = 
LIBS = 

build:
	$(CC) $(CFLAGS) -o dram src/dram.c src/*.h src/components/*.h -lm $(LIBS)

run:
	./dram
clean:
	rm dram