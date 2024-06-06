#include "../../include/game/sudoku.hpp"

//Classe Jogador:
/*
Jogador::Jogador(int vidas,string nome) {
    _vidas = vidas;
    _nome = nome;
}

int Jogador::getVidas() {
    return _vidas;
}

void Jogador::setVidas(int vidas) {
    _vidas = vidas;
}

string Jogador::getNome(){
    return _nome;
}

void Jogador::setNome(string nome){
    _nome = nome;
}
*/

//Classe Jogador:

Jogador::Jogador() : Usuario() {
    _vidas = 0;
    _pontos_obtidos = 0;
    _vitoria_obtida = 0;
}

Jogador::~Jogador() {}

int Jogador::getVidas() {
    return _vidas;
}

int Jogador::getPontosObtidos() {
    return _pontos_obtidos;
}

int Jogador::getVitoriaObtida() {
    return _vitoria_obtida;
}

void Jogador::setVidas(int vidas) {
    _vidas = vidas;
}

void Jogador::setPontosObtidos(int pontos_obtidos) {
    _pontos_obtidos = pontos_obtidos;
}

void Jogador::setVitoriaObtida(int vitoria_obtida) {
    _vitoria_obtida = vitoria_obtida;
}

void Jogador::atualizarEstatisticas() {
    int pontuacao_total = getEstatisticas()->getPontuacaoTotal() + _pontos_obtidos;
    getEstatisticas()->setPontuacaoTotal(pontuacao_total);
    int vitorias = getEstatisticas()->getVitorias() + _vitoria_obtida;
    getEstatisticas()->setVitorias(vitorias);
    int partidas = getEstatisticas()->getPartidas() + 1;
    getEstatisticas()->setPartidas(partidas);
}

//Classe Celula:

Celula::Celula(int valor, bool visivel, int x, int y) {
    _valor = valor;
    _visivel = visivel;
    _x = x;
    _y = y;
    _possiveis_valores = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

Celula::Celula(const Celula& celula_original)
    : _valor(celula_original._valor), _x(celula_original._x), _y(celula_original._y), _possiveis_valores(celula_original._possiveis_valores), _visivel(celula_original._visivel) {}
Celula::~Celula(){}

int Celula::getValor() {
    return _valor;
}

int Celula::getX() {
    return _x;
}

int Celula::getY() {
    return _y;
}

vector<int> Celula::getVetor() {
    return _possiveis_valores;
}

bool Celula::getVisivel() {
    return _visivel;
}

void Celula::setValor(int valor) {
    _valor = valor;
}

void Celula::setVetor(vector<int> possiveis_valores) {
    _possiveis_valores = possiveis_valores;
}

void Celula::setVisivel(bool visivel) {
    _visivel = visivel;
}


//Classe Tabuleiro:

Tabuleiro::Tabuleiro() {
    _matriz = vector<vector<shared_ptr<Celula>>>(9, vector<shared_ptr<Celula>>(9));

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            _matriz[i][j] = make_shared<Celula>(0, true, i, j);
        }
    }
}
Tabuleiro::~Tabuleiro(){}

bool Tabuleiro::criarTabuleiroNormal(string path) {

    //abre o arquivo e conta quantos sudokus tem:
    ifstream arquivo(path);
    if (!arquivo) {
        cerr << "Arquivo inexistente." << endl;
        return false;
    }   

    int quantidade_linhas;
    quantidade_linhas = count(istreambuf_iterator<char>(arquivo), istreambuf_iterator<char>(), '\n') + 1;
    int quantidade_sudokus = quantidade_linhas/10;

    arquivo.close();

    //escolhe um sudoku aleatório e consome as linhas anteriores a ele:
    int linha_escolhida = (rand() % quantidade_sudokus)*10;

    arquivo.open(path);
    int contagem = 1;
    string linha;
    while (getline(arquivo, linha) && contagem < linha_escolhida) {
        contagem++;
    }

    //começa a preencher linha adequada e para de preencher após 9 linhas.
    int i = 0, j = 0;
    int numero; char ch; bool estado;
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

        shared_ptr<Celula> celula = make_shared<Celula>(numero, estado, i, j);
        _matriz[i][j] = celula;

        j++;
        if (j == 9) {
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

        if (arquivo.eof()){
            break;
        }
    }
                                    /*essa seção do código vai ser reescrita pra lidar com a incompatibilidade entre o novo construtor do Tabuleiro e a função push_back
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

            Celula* celula = new Celula(numero, estado, i, j);
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
    }*/

    //caso contrário, gera um tabuleiro aleatório:

    _matriz = criarSolucao(_matriz);
    _matriz = criarMatrizInicial(_matriz);

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

Partida::Partida(Jogador* jogador) {
    _tabuleiro = new Tabuleiro();
    _jogador = jogador;
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

PartidaNormal::PartidaNormal(int dificuldade, Jogador* jogador) : Partida(jogador) {
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

void PartidaNormal::calcularPontosObtidos(time_t tempo){
    
    int pontos_obtidos;
    int segundos = difftime(time(NULL), tempo);
    if(getJogador()->getVidas() > 0){
        pontos_obtidos = ((getJogador()->getVidas() + _dificuldade - 1)*1000) + (1000/segundos) * _dificuldade;
    }
    else{
        pontos_obtidos = 0;
    }
    //adiciona os pontos ao jogador:
    getJogador()->setPontosObtidos(pontos_obtidos);
};

//Classe PartidaDesafio:
//a implementar: