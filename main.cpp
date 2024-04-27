#include "sudokus.hpp"
using namespace std;

int main (){
    srand(0);

    bool printar = false;
    JOGO* jogo1 = new JOGO();

    jogo1->tabuleiro = criarSolucao(jogo1->tabuleiro, printar);

    imprimirTabuleiroGenerico(jogo1->tabuleiro);

    //checar se solução realmente é válida
    int i, j, k, l;
    CASA *casa1; 
    CASA *casa2;
    for(i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            casa1 = jogo1->tabuleiro[i][j];
            
            for(k = 0; k < 9; k++){
                for (l = 0; l < 9; l++){
                    if(i != k && j != l){
                        casa2 = jogo1->tabuleiro[k][l];

                        if(saoVizinhas(casa2, casa1) && casa1->valor == casa2->valor){
                            cout << "A SOLUCAO E INVALIDA" << endl;
                        }
                    }
                }
            }
        }
    }

    delete jogo1;
    return 0;
}
