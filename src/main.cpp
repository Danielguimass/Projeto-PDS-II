#include "sudoku.hpp"
#include "cronometro.hpp"
#include "jogar.hpp"
#include "usuario.hpp"
#include "tabela.hpp"

using namespace std;


int main (){

Usuario usuario;
Tabela tabela;

string nomeUsuario;
cout<<"Digite seu nome:"<< endl;
getline(cin, nomeUsuario);
usuario.setNome(nomeUsuario);
cout<< "" << endl;

bool condicao = true;

while (condicao){
    cout <<"Bem-vindo " << usuario.getNome() << endl;
    cout<< "" << endl;
    cout <<"Selecione uma opcao:" << endl;
    cout <<"1-Jogar:" << endl;
    cout <<"2-Como Jogar:" << endl;
    cout <<"3-Tabela de classificacao:" << endl;
    cout <<"0-Sair" << endl;
    cout << endl;
    int escolha;
    cin >> escolha;
    cout << endl;

    switch (escolha){
        case 1:
            jogar(); // Comecar o jogo
            break;

        case 2:
            comoJogar(); //Mostra como jogar;
            break;

        case 3:
            tabela.mostrarTabela();    //Mostra a tabela de classificacao;
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
