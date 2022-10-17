TARGET = ./best
INCLUDE_DIRS = count_path
SOURCE_FILES = main.c \
			   count_path/*.c

.PHONY: all build rebuild run clean

build: ${TARGET}

rebuild: clean build

${TARGET}: ${INCLUDE_DIRS} ${SOURCE_FILES}
	gcc -I ${INCLUDE_DIRS} ${SOURCE_FILES} -o ${TARGET} -fopenmp
	# gcc -I ${INCLUDE_DIRS} ${SOURCE_FILES} -o ${TARGET} -fPIC -O3 -march=haswell


run: ${TARGET}
	${TARGET}

clean:
	rm ${TARGET}