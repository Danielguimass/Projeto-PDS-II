#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct CELULA{
    //atributos:
    int valor;
    bool visivel;

    //construtor:
    CELULA(int numero, bool estado){
        valor = numero;
        visivel = estado;
    };
};

struct MATRIZ_JOGO{
    //atributos:
    vector<vector<CELULA*>> matriz;
    int vidas;
    bool jogando = true;

    //construtor:
    MATRIZ_JOGO(){
        matriz = {
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
        {new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false), new CELULA(0,false) , new CELULA(0,false)},
    };

    }

    //métodos:
    void criarMatriz(int dificuldade);
        //dependendo da dificuldade, inicia uma das matrizes contidas no /src.
    void imprimirMatriz();
        //varre linhas e colunas imprimindo na tela o valor da célula se visivel = true, caso contrário, imprime " ".
        //ao varrer por todas as celulas, se nenhuma tiver visivel = false, o jogo termina como vitória.
    void verificarMatriz(int i, int j, int x);
        //se acertou, altera o visivel da célula para true, e chama a função imprime().
        //se errou, tira uma vida e verifica se vidas = 0, se sim, o jogo termina como derrota.
};


#endif