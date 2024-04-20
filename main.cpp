#include "historias.hpp"
#include "sudoku.hpp"
#include "cronometro.hpp"
#include "jogar.hpp"

using namespace std;


int main (){

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
            jogar();
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
