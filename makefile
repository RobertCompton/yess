# @file		makefile
# @author	rhoadskj
# @brief	makefile for yess.

CC = gcc -g

# @makes	yess
# @author	rhoadskj
yess: main.o tools.o memory.o registers.o memoryStage.o fetchStage.o\
decodeStage.o executeStage.o writebackStage.o dump.o loader.o
	$(CC) main.o tools.o memory.o registers.o memoryStage.o fetchStage.o decodeStage.o executeStage.o writebackStage.o dump.o -o yess

# @makes	main.o
# @author	rhoadskj
main.o: main.c tools.h memory.h dump.h registers.h memoryStage.h fetchStage.h\
decodeStage.h executeStage.h writebackStage.h loader.h
	$(CC) -c main.c -o main.o

# @makes	tools.o
# @author	rhoadskj
tools.o: tools.c tools.h
	$(CC) -c tools.c -o tools.o

# @makes	memory.o
# @author	rhoadskj
memory.o: memory.c memory.h
	$(CC) -c memory.c -o memory.o

# @makes	registers.o
# @author	rhoadskj
registers.o: registers.c registers.h tools.h
	$(CC) -c registers.c -o registers.o

# @makes	memoryStage.o
# @author	rhoadskj
memoryStage.o: memoryStage.c memoryStage.h
	$(CC) -c memoryStage.c -o memoryStage.o

# @makes	fetchStage.o
# @author	rhoadskj
fetchStage.o: fetchStage.c fetchStage.h tools.h
	$(CC) -c fetchStage.c -o fetchStage.o

# @makes	decodeStage.o
# @author	rhoadskj
decodeStage.o: decodeStage.c decodeStage.h
	$(CC) -c decodeStage.c -o decodeStage.o

# @makes	executeStage.o
# @author	rhoadskj
executeStage.o: executeStage.c executeStage.h
	$(CC) -c executeStage.c -o executeStage.o

# @makes	writebackStage.o
# @author	rhoadskj
writebackStage.o: writebackStage.c writebackStage.h
	$(CC) -c writebackStage.c -o writebackStage.o

# @makes	dump.o
# @author	rhoadskj
dump.o: dump.c dump.h fetchStage.h decodeStage.h executeStage.h\
memoryStage.h writebackStage.h registers.h memory.h
	$(CC) -c dump.c -o dump.o

# @makes	loader.o
# @author	rhoadskj
loader.o: loader.c loader.h
	$(CC) -c loader.c -o loader.o

# @makes	clean
# @author	rhoadskj
clean:
	rm -f *.o
