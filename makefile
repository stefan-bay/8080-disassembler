CC=clang
CFLAGS=-c -Wall
EXE=dissasemble

all: main.o disassembler.o
	$(CC) obj/main.o obj/disassembler.o -o $(EXE)

main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c
	mv main.o obj/

disassembler.o: src/disassembler.c src/disassembler.h
	$(CC) $(CFLAGS) src/disassembler.c
	mv disassembler.o obj/

clean:
	rm *.o $(EXE)
