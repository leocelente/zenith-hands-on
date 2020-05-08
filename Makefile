SOURCES = main.c engine.c  slre.c interface.c
NAME = TerminalPaint
CC  = gcc
all: 
	${CC} -O3 -o ${NAME} ${SOURCES} 
debug:
	${CC} -ggdb3 -DDEBUG -o ${NAME}Debug ${SOURCES}  
	rm -f *.pgm
	./${NAME}Debug
	xdg-open *.pgm
clean:
	rm -f ./${NAME} ./${NAME}Debug