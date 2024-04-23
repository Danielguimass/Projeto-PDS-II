#ifndef SUDOKUS_H
#define SUDOKUS_H

#include <vector> //para criar matrizes
#include <iostream> //para imprimir mensagens na tela
#include <fstream> //para armazenar tabuleiros em um arquivo .txt
#include <stdlib.h> //para criar números aleatórios
#include <time.h> //para criar números aleatórios
#include <algorithm> //para encontrar elementos em vetores

using namespace std;

//structs:

struct CASA{
    //atributos:
    int valor, x, y;
    vector<int> possiveis_valores;
    bool visivel;

    //construtor padrão:
    CASA(int i, int j){
        valor = 0;
        possiveis_valores = {1,2,3,4,5,6,7,8,9};
        visivel = false;
        x = i;
        y = j;
    };
}; 

struct JOGO{
    //atributos:
    vector<vector<CASA*>> tabuleiro;
    int vidas;
    bool jogando;

    //construtor padrão:
    JOGO(){
        tabuleiro = vector<vector<CASA*>>(9, vector<CASA*>(9)); //define o tamanho do tabuleiro

        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                tabuleiro[i][j] = new CASA(i, j);
            }
        }
        vidas = 5;
        jogando = true;
    };   

    //métodos:
    void criarTabuleiro();

    void imprimirTabuleiro();
};

//funções auxiliares para a função criarTabuleiro():
CASA *escolheProximaCasa(vector<vector<CASA*>> tabuleiro); //retorna um endereço de casa aleatório dentro do grupo de casas cujo casa->possiveis_valores.size() é minimo mas > 0
                                                           //retorna nullptr caso casa->possiveis_valores.size() = 0 para toda casa
void limitaVizinhos(vector<vector<CASA*>> tabuleiro, CASA *casa_original); //remove casa_original->valor de todos casa->possiveis_valores vizinhos a casa_original

void criarSolucao(vector<vector<CASA*>> tabuleiro_vazio);
void criarTabuleiroInicial(vector<vector<CASA*>> tabuleiro_completo);

#endif