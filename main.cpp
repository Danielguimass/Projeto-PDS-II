#include "sudokus.hpp"
using namespace std;

int main (){
    JOGO* jogo1 = new JOGO();
    jogo1->imprimirTabuleiro();
    int x1, y1, x2, y2;
    x1 = 6;
    y1 = 7;
    x2 = 8;
    y2 = 8;
    cout << "Testando vizinhanca entre " << x1 << "," << y1 << " e " << x2 << "," << y2 << ": " << saoVizinhas(jogo1->tabuleiro[x1][y1],jogo1->tabuleiro[x2][y2] );

    delete jogo1;
    return 0;
}
