#include "../../include/game/jogar.hpp"


void comoJogar(){
    cout<<"Escrever as regras de como jogar:" << endl;
    cout<< "" << endl;
};

/*

void jogarNormal(Tabela* tabela, string nomeJogador) {

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
    PartidaNormal* partida = new PartidaNormal(dificuldade, nomeJogador);
    if(!partida->iniciarPartida()){
        cout << "Nao foi possivel iniciar a partida." << endl;
        return;
    }

    //Inicia cronômetro:
    time_t tempo;
    iniciarCronometro(&tempo); 

    //Inicia o jogo:
    cout << "Inicio de jogo." << endl;
    partida->getTabuleiro()->exibirTabuleiro();

    int linha, coluna, valor;
    while (partida->getJogando()) {
        cout << "Linha: " << endl;
        cin >> linha;

        cout << "Coluna: " << endl;
        cin >> coluna;

        cout << "Valor: " << endl;
        cin >> valor;

        if(valor == -1){
            break;
        }

        if (!(linha > 0 && linha < 10) || !(coluna > 0 && coluna < 10) || !(valor > 0 && valor < 10)) {
            cout << "Coordenada ou valor invalido, tente novamente." << endl;
            continue;
        }

        partida->fazerJogada(linha-1, coluna-1, valor);
    }

    //Procedimentos de fim de jogo:
    cout << "Fim de jogo." << endl;
    cout << endl;

    //Imprime tempo na tela:
    imprimeTempo(&tempo); 
    cout << endl;

    //Calcula a Pontuacao do Jogador
    partida->getJogador()->calcularPontuacao(tempo, dificuldade, partida->getJogador()->getVidas());

    //Acessa a pontuação do jogador
    cout << "Sua pontuacao nesta partida: " << partida->getJogador()->getPontuacao() << endl;
    cout << endl;

    //Adiciona a pontuacao do jogador na tabela
    Usuario usuario(partida->getJogador()->getNome(), partida->getJogador()->getPontuacao());
    tabela->adicionarUsuario(&usuario);

}

*/

void jogarNormal(Jogador* jogador, Tabela* tabela) {

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
    partida->getJogador()->getEstatisticas()->enviarEstatisticas();

    //Submete o jogador à tabela de classificação e, se ele for apto ao top 10, é adicionado:
    tabela->adicionarJogador(make_shared<Jogador>(*jogador));

    //Desaloca a memoria do objeto partida:
    delete partida;
}

void jogarDesafio(Jogador* jogador, Tabela* tabela){

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

    //Envia as novas estatísticas do jogador para o usuarios.txt:
    partida->getJogador()->getEstatisticas()->enviarEstatisticas();

    //Submete o jogador à tabela de classificação e, se ele for apto ao top 10, é adicionado:
    auto ptrJogador = make_shared<Jogador>(*jogador);
    tabela->adicionarJogador(ptrJogador);

    //Desaloca a memoria do objeto partida:
    delete partida;
}
