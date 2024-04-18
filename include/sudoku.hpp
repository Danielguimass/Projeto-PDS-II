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
    void criaMatriz(int dificuldade);
        //
    void imprime();
        //varre linhas e colunas imprimindo na tela o valor da célula se visivel = true, caso contrário, imprime " ".
        //ao varrer por todas as celulas, se nenhuma tiver visivel = false, o jogo termina como vitória.
    void verifica(int i, int j, int x);
        //se acertou, altera o visivel da célula para true, e chama a função imprime().
        //se errou, tira uma vida e verifica se vidas = 0, se sim, o jogo termina como derrota.
};










/*
struct MATRIZES_GERAIS{
    //atributos: (todos serão matrizes pre definidas, que podemos pegar na internet)
    //m1:
    vector<vector<CELULA*>> m1 {
        {new CELULA(5,true), new CELULA(6,false), new CELULA(8,false), new CELULA(7,false), new CELULA(2,true), new CELULA(4,false), new CELULA(1,false), new CELULA(3,true) , new CELULA(9,true)},
        {new CELULA(3,false), new CELULA(4,true), new CELULA(2,true), new CELULA(5,false), new CELULA(1,true), new CELULA(9,false), new CELULA(8,false), new CELULA(7,false), new CELULA(6,false)},
        {new CELULA(1,true), new CELULA(9,false), new CELULA(7,true), new CELULA(3,true), new CELULA(8,false), new CELULA(6,true), new CELULA(5,true), new CELULA(4,false), new CELULA(2,false)},
        {new CELULA(7,true), new CELULA(3,false), new CELULA(4,false), new CELULA(8,true), new CELULA(9,true), new CELULA(5,true), new CELULA(6,false), new CELULA(2,true), new CELULA(1,true)},
        {new CELULA(6,true), new CELULA(8,false), new CELULA(5,false), new CELULA(2,true), new CELULA(3,false), new CELULA(1,false), new CELULA(7,true), new CELULA(9,true), new CELULA(4,true)},
        {new CELULA(2,true), new CELULA(1,true), new CELULA(9,false), new CELULA(4,true), new CELULA(6,true), new CELULA(7,false), new CELULA(3,false), new CELULA(8,false), new CELULA(5,true)},
        {new CELULA(9,false), new CELULA(2,false), new CELULA(6,false), new CELULA(1,true), new CELULA(7,false), new CELULA(8,true), new CELULA(4,false), new CELULA(5,false), new CELULA(3,true)},
        {new CELULA(8,false), new CELULA(5,false), new CELULA(1,true), new CELULA(9,false), new CELULA(4,true), new CELULA(3,false), new CELULA(2,true), new CELULA(6,true), new CELULA(7,false)},
        {new CELULA(4,false), new CELULA(7,false), new CELULA(3,true), new CELULA(6,false), new CELULA(5,false), new CELULA(2,false), new CELULA(9,true), new CELULA(1,false), new CELULA(8,true)},
    };
    //m2:
    vector<vector<CELULA*>> m2 {
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
    //m3:
    //...

    //métodos:
    vector<vector<CELULA*>> escolheMatriz(int dificuldade);
    //se dificuldade = 1, escolhe uma matriz aleatória de m1 a m5, se dificuldade = 2, uma matriz aleatória de m6 a m10, ...
};
*/
