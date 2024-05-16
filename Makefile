CC = g++
CFLAGS = -std=c++11 -Wall -g
TARGET = programa

BUILD = ./build
SRC = ./src
INCLUDE = ./include

${TARGET}: ${BUILD}/usuario.o ${BUILD}/sudoku.o ${BUILD}/cronometro.o ${BUILD}/jogar.o ${BUILD}/tabela.o ${BUILD}/main.o
	${CC} ${CFLAGS} ${BUILD}/usuario.o ${BUILD}/sudoku.o ${BUILD}/cronometro.o ${BUILD}/jogar.o ${BUILD}/tabela.o ${BUILD}/main.o -o ${TARGET}

${BUILD}/usuario.o: ${INCLUDE}/usuario.hpp ${SRC}/usuario.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/usuario.cpp -o ${BUILD}/usuario.o

${BUILD}/sudoku.o: ${INCLUDE}/sudoku.hpp ${SRC}/sudoku.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/sudoku.cpp -o ${BUILD}/sudoku.o

${BUILD}/cronometro.o: ${INCLUDE}/cronometro.hpp ${SRC}/cronometro.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/cronometro.cpp -o ${BUILD}/cronometro.o
	
${BUILD}/jogar.o: ${INCLUDE}/jogar.hpp ${SRC}/jogar.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/jogar.cpp -o ${BUILD}/jogar.o
	
${BUILD}/tabela.o: ${INCLUDE}/tabela.hpp ${SRC}/tabela.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/tabela.cpp -o ${BUILD}/tabela.o		

${BUILD}/main.o: ${INCLUDE}/usuario.hpp ${INCLUDE}/sudoku.hpp ${INCLUDE}/cronometro.hpp ${INCLUDE}/jogar.hpp  ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/main.cpp -o ${BUILD}/main.o