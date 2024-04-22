#include <sudokus.hpp>

void JOGO::imprimirTabuleiro(){
    int acertos = 0;
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(tabuleiro[i][j]->visivel){
                cout << " " << tabuleiro[i][j]->valor;
                acertos++;
            }else{
                cout << "  ";
            }
            if(j==2 || j==5){
                cout << " |";
            }
        }
        cout << endl;
        if(i==2 || i==5){
            cout << "-----------------------" << endl;
        }
    }
    cout << endl;
    if(acertos==81){
        cout << "Parabens, voce venceu!" << endl;
        jogando = false;
    }else{
        cout << "Vidas restantes: " << vidas << endl;
    }
};

void JOGO::criarTabuleiro(){
    criarSolucao(tabuleiro);
    criarTabuleiroInicial(tabuleiro);
};

void criarSolucao(vector<vector<CASA*>> tabuleiro_vazio){
    //verifica se o tabuleiro está nas condições inicais apropriadas para criar a solução:
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(!(tabuleiro_vazio[i][j]->valor == 0)){
                cout << "Tabuleiro inapropriado para criar uma solucao." << endl;
                return;
            }
        }
    }
    //algoritmo
};


void criarTabuleiroInicial(vector<vector<CASA*>> tabuleiro_completo){

};
