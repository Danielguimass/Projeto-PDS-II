#include "sudokus.hpp"

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

void limitaVizinhos(vector<vector<CASA*>> tabuleiro, CASA *casa_original){
    //...
    CASA *casa;

    if(casa->valor == 0){
        auto posicao = find(casa->possiveis_valores.begin(), casa->possiveis_valores.end(), casa_original->valor);

        if(posicao == casa->possiveis_valores.end() && casa->possiveis_valores.size() != 0){
            //fazer backtracking
        }
        
        if(posicao != casa->possiveis_valores.end()){
            casa->possiveis_valores.erase(posicao);
        }
    }
    //...
}

CASA *escolheProximaCasa(vector<vector<CASA*>> tabuleiro){
    return nullptr;
}

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
    CASA *casa_atual;
    while(1){
        casa_atual = escolheProximaCasa(tabuleiro_vazio);

        if(casa_atual != nullptr){
            casa_atual->valor = casa_atual->possiveis_valores[rand() % casa_atual->possiveis_valores.size()]; //insere como valor da casa atual um item de indice aleatorio dentro do vetor de possiveis valores
            casa_atual->possiveis_valores = {};

            limitaVizinhos(tabuleiro_vazio, casa_atual);

            //à implementar: desfazer passos caso não haja jogo possível (backtracking)

        } else{
            break;
        }
    }
    
};


void criarTabuleiroInicial(vector<vector<CASA*>> tabuleiro_completo){

};

void JOGO::criarTabuleiro(){
    criarSolucao(tabuleiro);
    criarTabuleiroInicial(tabuleiro);
};