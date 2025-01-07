MAIN = main.c

UTIL = util/cli/cli.c util/dispose/dispose.c util/file-handling/log-writer/log-writer.c util/file-handling/scene-files/scen-parser.c util/file-handling/shader-files/shad-parser.c util/file-handling/parse.c util/opengl/gl-init.c

TRCR = tracer/camera/camera.c tracer/image-writer/img-writer.c tracer/prog-log/prog-log.c tracer/shader-handling/comp-prog.c tracer/shader-handling/vid-mem.c tracer/core.c

CC = gcc

INCLUDE_PATHS = -I include -I util -I .

LIBRARY_PATHS = -L .

# -w : suppress all warning
# -v : output all commands run
# -g : include debug information in the executable (for use with gdb)
COMPILER_FLAGS = -w -g

LINKER_FLAGS = -l mingw32 -l opengl32 -l glew32 -l glfw3

OUTPUT = -o spt

all: versionfile compile message
versionfile:
	@echo:#define VERSION "${shell git describe --dirty --tags --abbrev=0}"> version.h
compile:
	@${CC} ${MAIN} ${UTIL} ${TRCR} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${LINKER_FLAGS} ${COMPILER_FLAGS} ${OUTPUT}
message:
	@echo:Don't forget to commit and tag. Latest commit was ${shell git describe --tags --abbrev=0}.