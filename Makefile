C_SOURCES = $(wildcard src/*.c res/*.c)
OBJ = ${C_SOURCES:.c=.o}

all : gb_snake.gb

run : all
	mgba-qt gb_snake.gb

gb_snake.gb : ${OBJ}
	~/Programs/gbdk/bin/lcc -o $@ $^

%.o : %.c
	~/Programs/gbdk/bin/lcc -c -o $@ $<

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
