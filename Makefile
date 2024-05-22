CC = g++
CFLAGS = -std=c++11
CFLAGS_DEBUG = -std=c++11 -Wall -g
TARGET = programa

BUILD = ./build
SRC = ./src
INCLUDE = ./include

${BUILD}/${TARGET}: ${BUILD}/bin/usuario.o ${BUILD}/bin/sudoku.o ${BUILD}/bin/cronometro.o ${BUILD}/bin/jogar.o ${BUILD}/bin/tabela.o ${BUILD}/bin/main.o
	${CC} ${CFLAGS} ${BUILD}/bin/usuario.o ${BUILD}/bin/sudoku.o ${BUILD}/bin/cronometro.o ${BUILD}/bin/jogar.o ${BUILD}/bin/tabela.o ${BUILD}/bin/main.o -o ${BUILD}/${TARGET}

${BUILD}/bin/usuario.o: ${INCLUDE}/usuario.hpp ${SRC}/usuario.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/usuario.cpp -o ${BUILD}/bin/usuario.o

${BUILD}/bin/sudoku.o: ${INCLUDE}/sudoku.hpp ${SRC}/sudoku.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/sudoku.cpp -o ${BUILD}/bin/sudoku.o

${BUILD}/bin/cronometro.o: ${INCLUDE}/cronometro.hpp ${SRC}/cronometro.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/cronometro.cpp -o ${BUILD}/bin/cronometro.o
	
${BUILD}/bin/jogar.o: ${INCLUDE}/jogar.hpp ${SRC}/jogar.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/jogar.cpp -o ${BUILD}/bin/jogar.o
	
${BUILD}/bin/tabela.o: ${INCLUDE}/tabela.hpp ${SRC}/tabela.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/tabela.cpp -o ${BUILD}/bin/tabela.o		

${BUILD}/bin/main.o: ${INCLUDE}/usuario.hpp ${INCLUDE}/sudoku.hpp ${INCLUDE}/cronometro.hpp ${INCLUDE}/jogar.hpp  ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/main.cpp -o ${BUILD}/bin/main.o

builder:
	if not exist build mkdir build
	if not exist build\bin mkdir build\bin

run:
	${BUILD}/${TARGET}

clean:
	del build\*.exe
	del build\bin\*.o

test:
	g++ -std=c++11 -Wall -g test.cpp -o programaTeste
	.\programaTeste.exe

cleanTest:
	del programaTeste.exe