FILES = main.c

CC = gcc

OUTPUT = program

all: versionfile program message
versionfile:
	@echo:#define VERSION "${shell git describe --dirty --tags --abbrev=0}"> version.h
program:
	@${CC} ${FILES} -o ${OUTPUT}
message:
	@echo:Don't forget to commit and tag. Latest commit was ${shell git describe --tags --abbrev=0}.