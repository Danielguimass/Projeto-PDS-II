#include "jogar.hpp"

using namespace std;

void jogar() {
    int dificuldade = 0;
    MATRIZ_JOGO* matriz_jogo = new MATRIZ_JOGO();
    time_t tempo;

    while (dificuldade < 1 || dificuldade > 3) {
        cout << "Escolha a dificuldade: 1, 2 ou 3" << endl;
        cin >> dificuldade;
        if (dificuldade < 1 || dificuldade > 3) {
            cout << "Dificuldade nao existente, tente de novo:" << endl;
        }
    }

    matriz_jogo->criarMatriz(dificuldade);

    if (!matriz_jogo->jogando) {
        dificuldade = 0;
        return;
    }

    cout << "Inicio de jogo." << endl;

    matriz_jogo->imprimirMatriz();

    iniciarCronometro(&tempo); //Inicia cronômetro

    int linha, coluna, valor;
    while (matriz_jogo->jogando) {
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

        matriz_jogo->verificarMatriz(linha-1, coluna-1, valor);
    }

    cout << "Fim de jogo." << endl;
    cout << endl;

    imprimeTempo(&tempo); //Imprime tempo na tela
    cout << endl;
}