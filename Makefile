CC = g++
CFLAGS = -std=c++11 -Wall -g
TARGET = programa

BUILD = ./build
SRC = ./src
INCLUDE = ./include

${TARGET}: ${BUILD}/sudokus.o ${BUILD}/cronometro.o ${BUILD}/main.o
	${CC} ${CFLAGS} ${BUILD}/sudokus.o ${BUILD}/cronometro.o ${BUILD}/main.o -o ${TARGET}

${BUILD}/sudokus.o: ${INCLUDE}/sudokus.hpp ${SRC}/sudokus.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/sudokus.cpp -o ${BUILD}/sudokus.o

${BUILD}/cronometro.o: ${INCLUDE}/cronometro.hpp ${SRC}/cronometro.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/cronometro.cpp -o ${BUILD}/cronometro.o

${BUILD}/main.o: ${INCLUDE}/sudokus.hpp ${INCLUDE}/cronometro.hpp main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c main.cpp -o ${BUILD}/main.o