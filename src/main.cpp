#include "../include/game/sudoku.hpp"
#include "../include/game/cronometro.hpp"
#include "../include/game/jogar.hpp"
#include "../include/game/gerador.hpp"
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
    cout <<"1-Como Jogar" << endl;
    cout <<"2-Estatisticas " << endl;
    cout <<"3-Jogar " << endl;
    cout <<"0-Sair" << endl;
    cout << endl;
    int escolha;
    cin >> escolha;
    cout << endl;

    switch (escolha){
        case 1:
            comoJogar(); //Mostra como Jogar
            break;

        case 2: {
            bool condicaoEstatistica =true;
            while (condicaoEstatistica){
                cout <<"Selecione uma opcao:" << endl;
                cout <<"1-Tabela de Classificacao " << endl;
                cout <<"2-Minhas Estatisticas " << endl;
                cout <<"0-Voltar " << endl;
                int escolhaEstatistica;
                cin >> escolhaEstatistica;
                cout << endl;

                switch(escolhaEstatistica){
                    case 1:
                        tabela.exibirTabela();    //Mostra a tabela de classificacao;
                        break;
                    case 2:
                        //Colocar aqui funcao para mostrar Estatisticas
                        break;
                    case 0:
                        condicaoEstatistica = false;
                        break;
                    default:
                        cout << "Opcao invalida" << endl;
                        cout << endl;
                        break;
                }
            }
            break;
        }

        case 3:
            jogarNormal(&tabela, usuario.getNome()); // Comecar o jogo normal
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

/* //teste do gerador:
srand(10);
Tabuleiro tabuleiro = Tabuleiro();
tabuleiro.criarTabuleiroDesafio("../src/game/desafios/desafios.txt");

tabuleiro.exibirTabuleiro();

return 0;*/
}
