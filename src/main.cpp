#include "../include/game/sudoku.hpp"
#include "../include/game/cronometro.hpp"
#include "../include/game/jogar.hpp"
#include "../include/game/gerador.hpp"
#include "../include/users/usuario.hpp"
#include "../include/users/tabela.hpp"
#include "../../include/game/exceptions.hpp"

using namespace std;

int main (){
try{
srand(time(NULL));
cout << endl;
cout << R"(
  ___           _       _           ___  __  __  ___  
 / __| _  _  __| | ___ | |__ _  _  / __||  \/  ||   \ 
 \__ \| || |/ _` |/ _ \| / /| || || (__ | |\/| || |) |
 |___/ \_,_|\__,_|\___/|_\_\ \_,_| \___||_|  |_||___/ 
                                                      )" << endl;

cout << "Seja bem vindo ao SudokuCMD." << endl;

Jogador* jogador = new Jogador();
Tabela* tabela = new Tabela("src/users/tabelas/ranking.txt");

bool login = false;
while(!login){
    cout << "" << endl;
    cout << "Para entrar, selecione:" << endl;
    cout << "1-Logar com a sua conta" << endl;
    cout << "2-Criar uma nova conta" << endl;
    cout << "0-Sair do programa" << endl;
    cout << "" << endl;
    string nome;
    string senha;
    int escolha;
    cin >> escolha;
    switch(escolha){
        case 1:{
            cout << "Nome: ";
            cin >> nome;
            cout << "Senha: ";
            cin >> senha;
            cout << endl;
            if(jogador->carregarUsuario(nome, senha)){
                login = true;
                break;
            }
            else{
                int tentativas = 0;
                while(!jogador->carregarUsuario(nome, senha)){
                    cout << "Nome ou senha incorretos, tente novamente." << endl;
                    tentativas++;
                    cout << "Nome: ";
                    cin >> nome;
                    cout << "Senha: ";
                    cin >> senha;
                    cout << endl;
                    if(tentativas == 4){
                        cout << "Limite de tentativas excedido. Tente novamente mais tarde ou opte por criar uma nova conta." << endl;
                        break;
                    }
                }
                if(tentativas < 4){
                    login = true;
                }
                break;
            }
        }

        case 2:{
            cout << "Nome: ";
            cin >> nome;
            cout << "Senha: ";
            cin >> senha;
            cout << endl;
            if(jogador->criarUsuario(nome, senha)){
                login = true;
                break;
            }
            else{
                int tentativas = 0;
                while(!jogador->criarUsuario(nome, senha)){
                    cout << "Nome ja existente, tente outro nome." << endl;
                    tentativas++;
                    cout << "Nome: ";
                    cin >> nome;
                    cout << "Senha: ";
                    cin >> senha;
                    cout << endl;
                    if(tentativas == 4){
                        cout << "Limite de tentativas excedido. Tente novamente mais tarde ou opte por logar com uma conta." << endl;
                        break;
                    }
                }
                if(tentativas < 4){
                    login = true;
                }
                break;
            }
        }

        case 0:
            return 0; //terminar o programa.
    }
}


cout<< "" << endl;
cout <<"Bem-vindo, " << jogador->getNome() << "!" << endl;
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
            bool condicao_estatisticas = true;
            while (condicao_estatisticas){
                cout <<"Selecione uma opcao:" << endl;
                cout <<"1-Tabela de Classificacao " << endl;
                cout <<"2-Minhas Estatisticas " << endl;
                cout <<"0-Voltar " << endl;
                int escolha_estatisticas;
                cin >> escolha_estatisticas;
                cout << endl;
                switch(escolha_estatisticas){
                    case 1:
                        tabela->exibirTabela();    //Mostra a tabela de classificacao;
                        break;
                    case 2:
                        jogador->getEstatisticas()->exibirEstatisticas();     //Mostra as estatisticas do usuario;
                        break;
                    case 0:
                        condicao_estatisticas = false;
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
            bool condicao_jogo = true;
            while(condicao_jogo){
                cout <<"Selecione um modo de jogo:" << endl;
                cout <<"1-Modo Normal" << endl;
                cout <<"2-Desafio Diario " << endl;
                cout <<"0-Voltar " << endl;    
                int escolha_jogo;
                cin >> escolha_jogo;
                cout << endl;
                switch(escolha_jogo){
                    case 1:
                        jogarNormal(jogador, tabela); //Inicia o Jogo Normal
                        condicao_jogo = false;
                        break;
                    case 2:
                        if(jogador->getEstatisticas()->getUltimoDesafioDiario() == stoi(obtemData())){
                            cout << "Voce ja jogou o desafio diario de hoje, volte novamente mais tarde." << endl;
                            break;
                        }

                        try{
                            jogarDesafio(jogador, tabela); //Inicia o Desafio Diario
                        } catch (const ArquivoDesafiosNaoExiste& e) {
                            cerr << e.what() << endl;
                            return 1;   // Terminar o programa com código de erro
                        }
                        
                        condicao_jogo = false;
                        break;
                    case 0:
                        condicao_jogo = false;
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

delete jogador;
delete tabela;
}catch (const ArquivoTabelaNaoExiste& e) {
        cerr << e.what() << endl;
        return 1; // Terminar o programa com código de erro
    } catch (const ArquivoUsuariosNaoExiste& e) {
        cerr << e.what() << endl;
        return 1; // Terminar o programa com código de erro
    }
return 0;
}
