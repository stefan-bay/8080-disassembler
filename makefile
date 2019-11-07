CC=gcc
CFLAGS=-c -Wall
EXE=dissasemble

all: main.o disassembler.o
	$(CC) obj/main.o obj/disassembler.o -o target/$(EXE)

main.o: src/main.c
	$(CC) $(CFLAGS) -o obj/main.o src/main.c

disassembler.o: src/disassembler.c src/include/disassembler.h
	$(CC) $(CFLAGS) -o obj/disassembler.o src/disassembler.c

clean:
	rm obj/*.o target/$(EXE)
