FILES = main.c

UTIL = util/opengl/gl-init.c util/file-handling/log-writer/log-writer.c util/cli/cli.c util/file-handling/shader-files/shad-parser.c util/file-handling/parse.c util/file-handling/scene-files/scen-parser.c

TRACER = tracer/core.c tracer/image-writer/img-writer.c tracer/shader-handling/comp-prog.c tracer/shader-handling/vid-mem.c tracer/prog-log/prog-log.c


CC = gcc

INCLUDE_PATHS = -I include -I util -I .

LIBRARY_PATHS = -L .

# -w : suppress all warning
# -v : output all commands run
# -g : include debug information in .exe
COMPILER_FLAGS = -w -g

LINKER_FLAGS = -l mingw32 -l opengl32 -l glew32 -l glfw3

OUTPUT = -o sdpt

all: versionfile compile message
versionfile:
	@echo:#define VERSION "${shell git describe --dirty --tags --abbrev=0}"> version.h
compile:
	@${CC} ${FILES} ${UTIL} ${TRACER} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${LINKER_FLAGS} ${COMPILER_FLAGS} ${OUTPUT}
message:
	@echo:Don't forget to commit and tag. Latest commit was ${shell git describe --tags --abbrev=0}.