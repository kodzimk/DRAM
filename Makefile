CFLAGS = 
LIBS = 

dram: src/main.c 
	$(CC) $(CFLAGS) -o dram src/main.c $(LIBS)