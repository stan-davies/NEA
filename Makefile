FILES = main.c

CC = gcc

OUTPUT = program

all: program
program:
	@${CC} ${FILES} -o ${OUTPUT}