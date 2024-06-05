CC = g++
CFLAGS = -std=c++11
CFLAGS_DEBUG = -std=c++11 -Wall -g
TARGET = programa

BUILD = ./build
SRC = ./src
INCLUDE = ./include

${BUILD}/${TARGET}: ${BUILD}/bin/usuario.o ${BUILD}/bin/tabela.o ${BUILD}/bin/sudoku.o ${BUILD}/bin/cronometro.o ${BUILD}/bin/jogar.o ${BUILD}/bin/gerador.o ${BUILD}/bin/main.o
	${CC} ${CFLAGS} ${BUILD}/bin/usuario.o ${BUILD}/bin/tabela.o ${BUILD}/bin/sudoku.o ${BUILD}/bin/cronometro.o ${BUILD}/bin/jogar.o ${BUILD}/bin/gerador.o ${BUILD}/bin/main.o -o ${BUILD}/${TARGET}

${BUILD}/bin/usuario.o: ${INCLUDE}/users/usuario.hpp ${SRC}/users/usuario.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/users/usuario.cpp -o ${BUILD}/bin/usuario.o

${BUILD}/bin/tabela.o: ${INCLUDE}/users/tabela.hpp ${SRC}/users/tabela.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/users/tabela.cpp -o ${BUILD}/bin/tabela.o	

${BUILD}/bin/sudoku.o: ${INCLUDE}/game/sudoku.hpp ${SRC}/game/sudoku.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/game/sudoku.cpp -o ${BUILD}/bin/sudoku.o

${BUILD}/bin/cronometro.o: ${INCLUDE}/game/cronometro.hpp ${SRC}/game/cronometro.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/game/cronometro.cpp -o ${BUILD}/bin/cronometro.o
	
${BUILD}/bin/jogar.o: ${INCLUDE}/game/jogar.hpp ${SRC}/game/jogar.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/game/jogar.cpp -o ${BUILD}/bin/jogar.o	

${BUILD}/bin/gerador.o: ${INCLUDE}/game/gerador.hpp ${SRC}/game/gerador.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c ${SRC}/game/gerador.cpp -o ${BUILD}/bin/gerador.o	

${BUILD}/bin/main.o: ${INCLUDE}/users/usuario.hpp ${INCLUDE}/users/tabela.hpp ${INCLUDE}/game/sudoku.hpp ${INCLUDE}/game/cronometro.hpp ${INCLUDE}/game/jogar.hpp ${INCLUDE}/game/gerador.hpp  ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/users -I ${INCLUDE}/game -c ${SRC}/main.cpp -o ${BUILD}/bin/main.o

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