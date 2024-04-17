CC = g++
CFLAGS = -std=c++11 -Wall -g
TARGET = programa

BUILD = ./build
SRC = ./src
INCLUDE = ./include

${BUILD}/${TARGET}: ${BUILD}/historias.o ${BUILD}/cronometro.o ${BUILD}/main.o
	${CC} ${CFLAGS} ${BUILD}/historias.o ${BUILD}/cronometro.o ${BUILD}/main.o -o ${BUILD}/${TARGET}

${BUILD}/historias.o: ${INCLUDE}/historias.hpp ${SRC}/historias.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/historias.cpp -o ${BUILD}/historias.o

${BUILD}/cronometro.o: ${INCLUDE}/cronometro.hpp ${SRC}/cronometro.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/cronometro.cpp -o ${BUILD}/cronometro.o

${BUILD}/main.o: ${INCLUDE}/historias.hpp ${INCLUDE}/cronometro.hpp  main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c main.cpp -o ${BUILD}/main.o