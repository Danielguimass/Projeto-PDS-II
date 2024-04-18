#include "historias.hpp"
#include "sudoku.hpp"
#include "cronometro.hpp"

using namespace std;


int main (){

//inicialização de variáveis para o jogo:
int dificuldade = 0;
MATRIZ_JOGO* MatrizJogo = new MATRIZ_JOGO();
time_t tempo;

bool condicao = true;

while (condicao){
 
    cout <<"Escolha para ver uma historia ou para jogar:" << endl;
    cout <<"1-Historia 1:" << endl;
    cout <<"2-Historia 2:" << endl;
    cout <<"3-Historia 3:" << endl;
    cout <<"4-Historia 4:" << endl;
    cout <<"5-Historia 5:" << endl;
    cout <<"6-Historia 6:" << endl;
    cout <<"7-Jogar" << endl;
    cout <<"0-Sair" << endl;
    cout << endl;
    int escolha;
    cin >> escolha;
    cout << endl;

    switch (escolha){
        case 1:
            historiaUm(); //Historia 01
            break;

        case 2:
            historiaDois(); //Historia 02
            break;

        case 3:
            historiaTres(); //Historia 03
            break;

        case 4:
            historiaQuatro(); //Historia 04
            break;

        case 5:
            historiaCinco(); //Historia 05
            break;

        case 6:
            historiaSeis(); //Historia 06
            break;

        case 7:
            
            while(dificuldade!=1 && dificuldade!=2 && dificuldade!=3){
                cout << "Escolha a dificuldade: 1, 2 ou 3" << endl;
                cin >> dificuldade;
                if(dificuldade!=1 && dificuldade!=2 && dificuldade!=3)
                    cout << "Dificuldade nao existente, tente de novo:" << endl;
            }

            MatrizJogo->criaMatriz(dificuldade);

            if(!MatrizJogo->jogando){
                dificuldade = 0;
                break;
            }

            cout << "Inicio de jogo." << endl;

            MatrizJogo->imprime();
            
            iniciarCronometro(&tempo); //Inicia cronômetro

            int i, j, x;
            while(MatrizJogo->jogando){
                cout << "Linha: " << endl;
                cin >> i;

                cout << "Coluna: " << endl;
                cin >> j;

                cout << "Valor: " << endl;
                cin >> x;
                if(x==-1) break;

                if(!(i>0 && i<10) || !(j>0 && j<10) || !(x>0 && x<10)){
                    cout << "Coordenada ou valor invalido, tente novamente." << endl;
                    continue;
                }

                MatrizJogo->verifica(i-1, j-1, x);
            }

            cout << "Fim de jogo." << endl;
            cout << endl;

            imprimeTempo(&tempo);   //Imprime tempo na tela
            cout << endl;

            dificuldade = 0;

            break;

        case 0:
            condicao = false;
            break;

        default:
            cout << "Opcao invalida" << endl;
            cout << endl;
            break;
    }
}

return 0;
}
