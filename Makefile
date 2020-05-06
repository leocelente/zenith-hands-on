SOURCES = main.c engine.c interface.c
NAME = TerminalPaint
CC  = clang
all: 
	${CC} -o ${NAME} ${SOURCES}
debug:
	${CC} -ggdb3 -DDEBUG -o ${NAME}Debug ${SOURCES}
	rm -f test.pgm
	./${NAME}Debug
	xdg-open test.pgm
clean:
	rm -f ./${NAME} ./${NAME}Debug