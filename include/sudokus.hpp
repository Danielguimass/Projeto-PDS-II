#ifndef SUDOKUS_H
#define SUDOKUS_H

#include <vector> //para criar matrizes
#include <iostream> //para imprimir mensagens na tela
#include <fstream> //para armazenar tabuleiros em um arquivo .txt
#include <stdlib.h> //para criar números aleatórios
#include <time.h> //para criar números aleatórios

using namespace std;

//structs:

struct CASA{
    //atributos:
    int valor;
    vector<int> possiveis_valores;
    bool visivel;

    //construtor padrão:
    CASA(){
        valor = 0;
        possiveis_valores = {1,2,3,4,5,6,7,8,9};
        visivel = false;
    };
};

struct JOGO{
    //atributos:
    vector<vector<CASA*>> tabuleiro;
    int vidas;
    bool jogando;

    //construtor padrão:
    JOGO(){
        tabuleiro = {
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
            {new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA(), new CASA()},
        };
        vidas = 5;
        jogando = true;
    };   

    //métodos:
    void criarTabuleiro();

    void imprimirTabuleiro();
};

//funções auxiliares para a função criarTabuleiro():
void criarSolucao(vector<vector<CASA*>> tabuleiro_vazio);
void criarTabuleiroInicial(vector<vector<CASA*>> tabuleiro_completo);

#endif