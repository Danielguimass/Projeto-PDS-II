#include "../include/game/sudoku.hpp"
#include "../include/game/cronometro.hpp"
#include "../include/game/jogar.hpp"
#include "../include/game/gerador.hpp"
#include "../include/users/usuario.hpp"
#include "../include/users/tabela.hpp"

using namespace std;


int main (){

Tabela tabela("src/users/dados/tabela.txt");

string nomeUsuario;
cout<<"Digite seu nome:"<< endl;
getline(cin, nomeUsuario);
Usuario usuario(nomeUsuario,"src/users/dados/estatisticas.txt");

cout<< "" << endl;
cout <<"Bem-vindo " << usuario.getNome() << endl;
cout<< "" << endl;

bool condicao = true;

while (condicao){
    cout <<"Selecione uma opcao:" << endl;
    cout <<"1-Como Jogar" << endl;
    cout <<"2-Estatisticas " << endl;
    cout <<"3-Jogar " << endl;
    cout <<"0-Sair" << endl;
    cout << endl;
    int escolha;
    cin >> escolha;

    switch (escolha){
        case 1:
            comoJogar(); //Mostra como Jogar
            break;

        case 2: {
            bool condicaoEstatistica = true;
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
                        usuario.mostrarEstatisticas(nomeUsuario); //Mostra as estatisticas do usuario
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

        case 3: {
            bool condicaoJogo = true;
            while(condicaoJogo){
                cout <<"Selecione um modo de jogo:" << endl;
                cout <<"1-Modo Normal" << endl;
                cout <<"2-Desafio Diario " << endl;
                cout <<"0-Voltar " << endl;    
                int escolhaJogo;
                cin >> escolhaJogo;
                cout << endl;
                switch(escolhaJogo){
                    case 1:
                        jogarNormal(&tabela, usuario.getNome()); //Inicia o Jogo Normal
                        break;
                    case 2:
                        jogarDesafio(); //Inicia o Desafio Diario
                        break;
                    case 0:
                        condicaoJogo = false;
                        break;
                    default:
                        cout << "Opcao invalida" << endl;
                        cout << endl;
                        break;                        
                }
            }
            break;
        }

        case 0:
            condicao = false; //Sair
            break;

        default:
            cout << "Opcao invalida" << endl;
            cout << endl;
            break;
    }
}

/* //teste do gerador:
int seed;

cout << "insira a seed: " << endl;
cin >> seed;
srand(seed);

Tabuleiro tabuleiro = Tabuleiro();
tabuleiro.criarTabuleiroDesafio("../src/game/desafios/desafios.txt");

tabuleiro.exibirTabuleiro();*/

return 0;
}
