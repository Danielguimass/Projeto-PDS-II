#include "sudokus.hpp"
using namespace std;

int main (){
    bool printar = true;
    JOGO* jogo1 = new JOGO();

    criarSolucao(jogo1->tabuleiro, printar);

    delete jogo1;
    return 0;
}
