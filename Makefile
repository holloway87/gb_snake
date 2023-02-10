C_SOURCES = $(wildcard src/*.c res/*.c)
OBJ = ${C_SOURCES:.c=.o}
CC=~/Programs/gbdk/bin/lcc

all : gb_snake.gb

run : all
	mgba-qt gb_snake.gb

gb_snake.gb : $(OBJ)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) -c -o $@ $<

clean:
	rm res/*.asm
	rm res/*.lst
	rm res/*.sym
	rm res/*.o
	rm src/*.asm
	rm src/*.lst
	rm src/*.sym
	rm src/*.o
	rm *.gb
	rm *.ihx
