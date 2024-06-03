#include "../../include/game/jogar.hpp"

void comoJogar(){
    cout<<"Escrever as regras de como jogar:" << endl;
    cout<< "" << endl;
};


void jogarNormal() {

    //Seleciona a dificuldade e inicia o tabuleiro:
    int dificuldade = 0;

    while (dificuldade < 1 || dificuldade > 3) {
        cout << "Escolha a dificuldade: 1, 2 ou 3" << endl;
        cin >> dificuldade;
        if (dificuldade < 1 || dificuldade > 3) {
            cout << "Dificuldade inexistente, tente de novo:" << endl;
        }
    }

    PartidaNormal* partida = new PartidaNormal(dificuldade);
    if(!partida->iniciarPartida()){
        cout << "Nao foi possivel iniciar a partida." << endl;
        return;
    }

    //Inicia cronômetro:
    time_t tempo;
    iniciarCronometro(&tempo); 

    //Inicia o jogo:
    cout << "Inicio de jogo." << endl;
    partida->getTabuleiro()->exibirTabuleiro();

    int linha, coluna, valor;
    while (partida->getJogando()) {
        cout << "Linha: " << endl;
        cin >> linha;

        cout << "Coluna: " << endl;
        cin >> coluna;

        cout << "Valor: " << endl;
        cin >> valor;

        if (!(linha > 0 && linha < 10) || !(coluna > 0 && coluna < 10) || !(valor > 0 && valor < 10)) {
            cout << "Coordenada ou valor invalido, tente novamente." << endl;
            continue;
        }

        partida->fazerJogada(linha-1, coluna-1, valor);
    }

    //Procedimentos de fim de jogo:
    cout << "Fim de jogo." << endl;
    cout << endl;

    //Imprime tempo na tela:
    imprimeTempo(&tempo); 
    cout << endl;
}


void jogarDesafio(){

}
