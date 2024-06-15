#include "../../include/game/jogar.hpp"


void comoJogar(){
    cout << "O Sudoku eh um jogo de raciocinio e logica que te desafia a preencher toda uma grade de 9x9 quadrados, com numeros de 1 a 9, seguindo uma regra simples:" << endl;
    cout << "Voce nao pode repetir nenhum numero em nenhuma linha, coluna ou bloco 3x3!" << endl;
    cout << "O jogo termina quando voce conseguir preencher todos os numeros, ou, se voce errar o suficiente, as suas vidas acabarem!" << endl;
    cout << "Neste programa nos disponibilizamos diversos jogos de sudokus para todos tipos de jogadores." << endl;
    cout << "Comece a jogar agora mesmo e descubra todas as funcionalidades do nosso programa!" << endl;
    cout << "" << endl;
};

void jogarNormal(shared_ptr<Jogador> jogador, Tabela* tabela) {

    //Seleciona a dificuldade:
    int dificuldade = 0;
    while (dificuldade < 1 || dificuldade > 3) {
        cout << "Escolha a dificuldade: 1, 2 ou 3" << endl;
        cin >> dificuldade;
        if (dificuldade < 1 || dificuldade > 3) {
            cout << "Dificuldade inexistente, tente de novo:" << endl;
        }
    }

    //Inicia a Partida Normal:
    PartidaNormal* partida = new PartidaNormal(dificuldade, jogador);
    if(!partida->iniciarPartida()){
        cout << "Nao foi possivel iniciar a partida." << endl;
        return;
    }

    //Inicia cronômetro:
    partida->getCronometro()->zerarCronometro();

    //Inicia o jogo:
    cout << "Inicio de jogo." << endl;
    partida->getTabuleiro()->exibirTabuleiro();

    int linha, coluna, valor;

    while (partida->getJogando()) {
        cout << "Linha: " << endl;
        if ((cin >> linha) && (linha > 0 && linha < 10)) {
            // Leitura bem-sucedida
        } else {
            // Erro na leitura
            cin.clear(); // Função para limpar o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres até a quebra de linha
            cout << "Entrada invalida. Tente novamente." << endl;
            continue;
        }

        cout << "Coluna: " << endl;
        if ((cin >> coluna) && (coluna > 0 && coluna < 10)) {
            // Leitura bem-sucedida
        } else {
            // Erro na leitura
            cin.clear(); // Função para limpar o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres até a quebra de linha
            cout << "Entrada invalida. Tente novamente." << endl;
            continue;
        }

        cout << "Valor: " << endl;
        if ((cin >> valor) && (valor > 0 && valor < 10)) {
            // Leitura bem-sucedida
        } else {
            //condicao de parada:
            if(valor == -1){
                break;
            }
            // Erro na leitura
            cin.clear(); // Função para limpar o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres até a quebra de linha
            cout << "Entrada invalida. Tente novamente." << endl;
            continue;
        }

        partida->fazerJogada(linha-1, coluna-1, valor);
    }

    //Procedimentos de fim de jogo:
    cout << "Fim de jogo." << endl;
    cout << endl;

    //Imprime tempo na tela:
    partida->getCronometro()->imprimeTempo(); 
    cout << endl;

    //Calcula e atribui a Pontuacao desta partida ao jogador:
    partida->calcularPontosObtidos(partida->getCronometro()->tempoAtual());

    //Acessa a pontuação desta partida
    cout << "Sua pontuacao nesta partida: " << partida->getJogador()->getPontosObtidos() << endl;
    cout << endl;

    //Adiciona as estatísticas desta partida às estatísticas totais do jogador:
    partida->getJogador()->atualizarEstatisticas();

    //Envia as novas estatísticas do jogador para o usuarios.txt:
    partida->getJogador()->getEstatisticas()->enviarEstatisticas(partida->getJogador()->getNome(), partida->getJogador()->getSenha());

    //Submete o jogador à tabela de classificação e, se ele for apto ao top 10, é adicionado:
    tabela->adicionarJogador(make_shared<Jogador>(*jogador));

    //Desaloca a memoria do objeto partida:
    delete partida;
}

void jogarDesafio(shared_ptr<Jogador> jogador, Tabela* tabela){

    //Seleciona a dificuldade:
    int tempo_limite = 0;
    while (tempo_limite < 1 || tempo_limite > 60) {
        cout << "Escolha um tempo limite entre 1 e 60 minutos" << endl;
        cin >> tempo_limite;
        if (tempo_limite < 1 || tempo_limite > 60) {
            cout << "Tempo limite invalido, tente de novo:" << endl;
        }
    }
    tempo_limite *= 60;

    //Inicia a Partida Desafio:
    PartidaDesafio* partida = new PartidaDesafio(tempo_limite, jogador);
    if(!partida->iniciarPartida()){
        cout << "Nao foi possivel iniciar a partida." << endl;
        return;
    }

    //Inicia cronômetro:
    partida->getCronometro()->zerarCronometro(); 

    //Inicia o jogo:
    cout << "Inicio de jogo." << endl;
    partida->getTabuleiro()->exibirTabuleiro();

    int linha, coluna, valor;
    while (partida->getJogando()) {
        cout << "Linha: " << endl;
        if ((cin >> linha) && (linha > 0 && linha < 10)) {
            // Leitura bem-sucedida
        } else {
            // Erro na leitura
            cin.clear(); // Função para limpar o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres até a quebra de linha
            cout << "Entrada invalida. Tente novamente." << endl;
            continue;
        }

        cout << "Coluna: " << endl;
        if ((cin >> coluna) && (coluna > 0 && coluna < 10)) {
            // Leitura bem-sucedida
        } else {
            // Erro na leitura
            cin.clear(); // Função para limpar o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres até a quebra de linha
            cout << "Entrada invalida. Tente novamente." << endl;
            continue;
        }

        cout << "Valor: " << endl;
        if ((cin >> valor) && (valor > 0 && valor < 10)) {
            // Leitura bem-sucedida
        } else {
            //condicao de parada:
            if(valor == -1){
                break;
            }
            // Erro na leitura
            cin.clear(); // Função para limpar o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar caracteres até a quebra de linha
            cout << "Entrada invalida. Tente novamente." << endl;
            continue;
        }

        partida->fazerJogada(linha-1, coluna-1, valor);
    }

    //Procedimentos de fim de jogo:
    cout << "Fim de jogo." << endl;
    cout << endl;

    //Imprime tempo na tela:
    partida->getCronometro()->imprimeTempo(); 
    cout << endl;

    //Calcula e atribui a Pontuacao desta partida ao jogador:
    partida->calcularPontosObtidos(partida->getCronometro()->tempoAtual());

    //Acessa a pontuação desta partida
    cout << "Sua pontuacao nesta partida: " << partida->getJogador()->getPontosObtidos() << endl;
    cout << endl;

    //Adiciona as estatísticas desta partida às estatísticas totais do jogador:
    partida->getJogador()->atualizarEstatisticas();
    jogador->getEstatisticas()->setUltimoDesafioDiario(stoi(obtemData()));

    //Envia as novas estatísticas do jogador para o usuarios.txt:
    partida->getJogador()->getEstatisticas()->enviarEstatisticas(partida->getJogador()->getNome(), partida->getJogador()->getSenha());

    //Submete o jogador à tabela de classificação e, se ele for apto ao top 10, é adicionado:
    auto ptrJogador = make_shared<Jogador>(*jogador);
    tabela->adicionarJogador(ptrJogador);

    //Desaloca a memoria do objeto partida:
    delete partida;
}
