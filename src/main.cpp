#include "../include/game/sudoku.hpp"
//#include "../include/game/cronometro.hpp"
#include "../include/game/jogar.hpp"
#include "../include/users/usuario.hpp"
#include "../include/users/tabela.hpp"

using namespace std;


int main (){

Usuario usuario;
string nomeArquivo = "src/users/tabela/tabela.txt";
Tabela tabela(nomeArquivo);

string nomeUsuario;
cout<<"Digite seu nome:"<< endl;
getline(cin, nomeUsuario);
usuario.setNome(nomeUsuario);

bool condicao = true;

while (condicao){
    cout<< "" << endl;
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
            jogarNormal(); // Comecar o jogo normal
            break;

        case 2:
            comoJogar(); //Mostra como jogar;
            break;

        case 3:
            tabela.exibirTabela();    //Mostra a tabela de classificacao;
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
