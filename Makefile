FILES = main.c util/opengl/gl_init.c

CC = gcc

INCLUDE_PATHS = -I include -I util

LIBRARY_PATHS = -L lib

# suppress all warning
COMPILER_FLAGS = -w

LINKER_FLAGS = -l mingw32 -l opengl32 -l glew32 -l glfw3

OUTPUT = program

all: versionfile program message
versionfile:
	@echo:#define VERSION "${shell git describe --dirty --tags --abbrev=0}"> version.h
program:
	${CC} ${FILES} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${LINKER_FLAGS} ${COMPILER_FLAGS} -o ${OUTPUT}
message:
	@echo:Don't forget to commit and tag. Latest commit was ${shell git describe --tags --abbrev=0}.