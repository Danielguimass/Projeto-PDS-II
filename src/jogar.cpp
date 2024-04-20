#include "jogar.hpp"
#include <iostream>

using namespace std;

void jogar() {
    int dificuldade = 0;
    MATRIZ_JOGO* matriz_jogo = new MATRIZ_JOGO();
    time_t tempo;

    while (dificuldade != 1 && dificuldade != 2 && dificuldade != 3) {
        cout << "Escolha a dificuldade: 1, 2 ou 3" << endl;
        cin >> dificuldade;
        if (dificuldade != 1 && dificuldade != 2 && dificuldade != 3)
            cout << "Dificuldade nao existente, tente de novo:" << endl;
    }

    matriz_jogo->criarMatriz(dificuldade);

    if (!matriz_jogo->jogando) {
        dificuldade = 0;
        return;
    }

    cout << "Inicio de jogo." << endl;

    matriz_jogo->imprimirMatriz();

    iniciarCronometro(&tempo); //Inicia cronômetro

    int i, j, x;
    while (matriz_jogo->jogando) {
        cout << "Linha: " << endl;
        cin >> i;

        cout << "Coluna: " << endl;
        cin >> j;

        cout << "Valor: " << endl;
        cin >> x;
        if (x == -1) break;

        if (!(i > 0 && i < 10) || !(j > 0 && j < 10) || !(x > 0 && x < 10)) {
            cout << "Coordenada ou valor invalido, tente novamente." << endl;
            continue;
        }

        matriz_jogo->verificarMatriz(i - 1, j - 1, x);
    }

    cout << "Fim de jogo." << endl;
    cout << endl;

    imprimeTempo(&tempo); //Imprime tempo na tela
    cout << endl;

    dificuldade = 0;
}