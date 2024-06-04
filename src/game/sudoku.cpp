#include "../../include/game/sudoku.hpp"

//Classe Jogador:

Jogador::Jogador(int vidas) {
    _vidas = vidas;
}

int Jogador::getVidas() {
    return _vidas;
}

void Jogador::setVidas(int vidas) {
    _vidas = vidas;
}


//Classe Celula:

Celula::Celula(int valor, bool visivel) {
    _valor = valor;
    _visivel = visivel;
}

int Celula::getValor() {
    return _valor;
}

bool Celula::getVisivel() {
    return _visivel;
}

void Celula::setVisivel(bool visivel) {
    _visivel = visivel;
}


//Classe Tabuleiro:

Tabuleiro::Tabuleiro() {
    _matriz = {};
}

bool Tabuleiro::criarTabuleiroNormal(string path) {

    //IMPORTANTE: ainda falta atualizar essa função para escolher um sudoku aleatorio dentro de várias opções em um mesmo arquivo.

    ifstream arquivo(path);
    if (!arquivo) {
        cerr << "Arquivo inexistente." << endl;
        return false;
    }    

    //após abrir o arquivo, preenche o tabuleiro:
    int i = 0, j = 0;
    int numero; char ch; bool estado;
    vector<Celula*> linha = {};
    while (1) {
        arquivo >> numero;

        if (arquivo.eof()){
            break;
        }

        arquivo >> ch;

        if (arquivo.eof()){
            break;
        }

        if(ch == 't'){
            estado = true;
        }
        else{
            estado = false;
        }

        Celula* celula = new Celula(numero, estado);
        linha.push_back(celula);

        j++;
        if (j == 9) {
            _matriz.push_back(linha);
            linha = {};
            j = 0;
            i++;
            if(i==9){
                break;
            }
        }
    }

    arquivo.close();

    return true;
};

//a implementar:
bool Tabuleiro::criarTabuleiroDesafio(string path) {

    ifstream arquivo(path);
    if (!arquivo) {
        cerr << "Arquivo inexistente." << endl;
        return false;
    }    

    //após abrir o arquivo, verifica se já existe um tabuleiro para o dia atual
    int data;
    bool existe_tabuleiro = false;
    while(1){
        arquivo >> data;

        if(data == obtemData()){
            existe_tabuleiro = true;
        }
    }

    if(existe_tabuleiro){   //caso exista, lê esse tabuleiro
        int i = 0, j = 0;
        int numero; char ch; bool estado;
        vector<Celula*> linha = {};
        while (1) {
            arquivo >> numero;

            if (arquivo.eof()){
                break;
            }

            arquivo >> ch;

            if (arquivo.eof()){
                break;
            }

            if(ch == 't'){
                estado = true;
            }
            else{
                estado = false;
            }

            Celula* celula = new Celula(numero, estado);
            linha.push_back(celula);

            j++;
            if (j == 9) {
                _matriz.push_back(linha);
                linha = {};
                j = 0;
                i++;
                if(i==9){
                    break;
                }
            }
        }

        arquivo.close();

        return true;
    }

    //caso contrário, gera um tabuleiro aleatório:

    criarSolucao(_matriz);
    criarMatrizInicial(_matriz);

    //à implementar: escrever o tabuleiro aleatório no desafios.txt




    return true;

}

void Tabuleiro::exibirTabuleiro() {
    int i, j;
    for(i=0; i<9; i++){

        for(j=0; j<9; j++){

            if(_matriz[i][j]->getVisivel()){
                cout << " " << _matriz[i][j]->getValor();
            }
            else{
                cout << "  ";
            }

            if(j==2 || j==5){
                cout << " |";
            }

        }

        cout << endl;

        if(i==2 || i==5){
            cout << "-----------------------" << endl;
        }

    }
};

bool Tabuleiro::verificarJogada(int i, int j, int valor) {
    if(valor == _matriz[i][j]->getValor()){
        if(_matriz[i][j]->getVisivel()){
            cout << "Valor ja encontrado." << endl;
        }
        else{
            _matriz[i][j]->setVisivel(true);
        }
        return true; 
    }        
}

bool Tabuleiro::verificarVitoria() {
    int i, j;
    int acertos = 0;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(_matriz[i][j]->getVisivel()){
                acertos++;
            }
        }
    }
    if(acertos == 81)
        return true;
    else
        return false;
}


//Classe Partida:

Partida::Partida() {
    _tabuleiro = new Tabuleiro();
    _jogador = new Jogador(0);
    _jogando = false;
}

bool Partida::getJogando(){
    return _jogando;
}

void Partida::setJogando(bool jogando){
    _jogando = jogando;
}

Tabuleiro* Partida::getTabuleiro(){
    return _tabuleiro;
}

Jogador* Partida::getJogador(){
    return _jogador;
}

void Partida::fazerJogada(int i, int j, int valor){
    if(getTabuleiro()->verificarJogada(i, j, valor)){
        getTabuleiro()->exibirTabuleiro();
        if(getTabuleiro()->verificarVitoria()){
            cout << "Parabens, voce venceu!" << endl;
            _jogando = false;
            return;
        }
    }
    else{
        getJogador()->setVidas(getJogador()->getVidas() -1);
        if(getJogador()->getVidas() == 0){
            cout << "DERROTA: Vidas esgotadas." << endl;
            _jogando = false;
            return;
        }
        else{
            cout << "Errado, voce perdeu uma vida." << endl;
            cout << "Vidas restantes: " << getJogador()->getVidas() << endl;
        }
    }
};


//Classe PartidaNormal:

PartidaNormal::PartidaNormal(int dificuldade) : Partida() {
    _dificuldade = dificuldade;
}

bool PartidaNormal::iniciarPartida() {
    
    string path;

    switch (_dificuldade){
    case 1:
        getJogador()->setVidas(5);
        path = "src/game/niveis/nivel1.txt";
        break;
    case 2:
        getJogador()->setVidas(4);
        path = "src/game/niveis/nivel2.txt";
        break;
    case 3:
        getJogador()->setVidas(3);
        path = "src/game/niveis/nivel3.txt";
        break;
    default:
        cout << "Erro: Dificuldade inadequada." << endl;
        return false;
    }

    if(!getTabuleiro()->criarTabuleiroNormal(path)){
        cout << "Nao foi possivel criar o tabuleiro." << endl;
        return false;
    }

    setJogando(true);

    return true;
}


//Classe PartidaDesafio:
//a implementar: