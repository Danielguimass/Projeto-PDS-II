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
    CASA(){
        valor = 0;
        possiveis_valores = {1,2,3,4,5,6,7,8,9};
        visivel = false;
        x = -1;
        y = -1;
    };

    //construtor com argumentos:
    CASA(int i, int j){
        valor = 0;
        possiveis_valores = {1,2,3,4,5,6,7,8,9};
        visivel = false;
        x = i;
        y = j;
    };
}; 

struct TABULEIRO_ESTATICO{
    //atributos:
    vector<vector<CASA>> tabuleiro;
    CASA casa_alterada = *(new CASA());

    //construtor padrão:
    TABULEIRO_ESTATICO(){
        tabuleiro = vector<vector<CASA>>(9, vector<CASA>(9)); //define o tamanho do tabuleiro

        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                tabuleiro[i][j] = *(new CASA());
            }
        }
    };

    //construtor com argumentos:
    TABULEIRO_ESTATICO(vector<vector<CASA*>> tabuleiro_dinamico, CASA *casa){
        tabuleiro = vector<vector<CASA>>(9, vector<CASA>(9)); //define o tamanho do tabuleiro

        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                tabuleiro[i][j] = *tabuleiro_dinamico[i][j];
            }
        }

        casa_alterada = *casa;
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
bool saoVizinhas(CASA *casa, CASA *casa_original);
vector<vector<CASA*>> dinamizaTabuleiro(TABULEIRO_ESTATICO);
CASA *escolheProximaCasa(vector<vector<CASA*>> tabuleiro); //retorna um endereço de casa aleatório dentro do grupo de casas cujo casa->possiveis_valores.size() é minimo mas > 0
                                                           //retorna nullptr caso casa->possiveis_valores.size() = 0 para toda casa
                                                           //\\ [APOS A IMPLEMENTAÇÃO DO FOR LOOP EM criarSolucao() ISSO SE TORNOU REDUNDANTE]
int limitaVizinhos(vector<vector<CASA*>> tabuleiro, CASA *casa_original); //remove casa_original->valor de todos casa->possiveis_valores vizinhos a casa_original
                                                                          //retorna 1 caso tudo ocorra normalmente, retorna 0 caso seja necessário backtracking
void criarSolucao(vector<vector<CASA*>> tabuleiro_vazio);
void criarTabuleiroInicial(vector<vector<CASA*>> tabuleiro_completo);

#endif