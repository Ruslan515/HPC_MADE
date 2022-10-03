TARGET = ./best
INCLUDE_DIRS = matmul
SOURCE_FILES = main.c \
			   matmul/*.c

.PHONY: all build rebuild run clean

build: ${TARGET}

rebuild: clean build

${TARGET}: ${INCLUDE_DIRS} ${SOURCE_FILES}
	gcc -I ${INCLUDE_DIRS} ${SOURCE_FILES} -o ${TARGET} -fPIC -O3 -march=haswell

run: ${TARGET}
	${TARGET}

clean:
	rm ${TARGET}
