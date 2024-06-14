#include "../../include/game/sudoku.hpp"

//Classe Jogador:

Jogador::Jogador() : Usuario() {
    _vidas = 0;
    _pontos_obtidos = 0;
    _vitoria_obtida = 0;
}

Jogador::~Jogador() {}

void Jogador::mensagem() {
    cout << "objeto Jogador" << endl;
}

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

void Celula::mensagem() {
    cout << "objeto Celula" << endl;
}

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

void Tabuleiro::mensagem() {
    cout << "objeto Tabuleiro" << endl;
}

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
    bool printar = false;
    int i = 0, j = 0;
    ifstream arquivo(path);
    if (!arquivo) {
        cerr << "Arquivo inexistente." << endl;
        return false;
    }    

    //após abrir o arquivo, verifica se já existe um tabuleiro para o dia atual
    string data;
    bool existe_tabuleiro = false;
    while (getline(arquivo, data)) {
        if (printar){
            cout << "Procurando tabuleiro para a data atual..." << endl;
        }
        if (data == obtemData()) {
            existe_tabuleiro = true;
            if (printar){
                cout << "Tabuleiro para a data atual encontrado. Lendo..." << endl;
            }
            break;
        }
    }


    if(existe_tabuleiro){
        //começa a preencher linha adequada e para de preencher após 9 linhas.
        int numero; char ch; bool estado;
        i = 0; 
        j = 0;
        while (1) {
            if (printar){
                cout << "Lendo arquivo..." << endl;
            }
            arquivo >> numero;

            if (arquivo.eof()){
                break;
                if (printar){
                    cout << "Fim do arquivo!" << endl;
                }
            }

            arquivo >> ch;

            if (arquivo.eof()){
                break;
                if (printar){
                    cout << "Fim do arquivo!" << endl;
                }
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
    }
    arquivo.close();

    if (printar){
        cout << "Tabuleiro para a data atual nao encontrado. Gerando..." << endl;
    }

    //caso contrário, gera um tabuleiro aleatório:

    _matriz = criarSolucao(_matriz);
    if (printar){
        cout << "Solucao gerada" << endl;
    }
    _matriz = criarMatrizInicial(_matriz);
    if (printar){
        cout << "Tabuleiro incial gerado" << endl;
    }
    //escreve o tabuleiro aleatório no desafios.txt

    ofstream outfile(path, ios_base::app); //abrir arquivo no modo append ao invés de write
    
    if (!outfile) {
        cerr << "Arquivo inexistente." << endl;
        return false;
    }   

    outfile << obtemData() << endl;

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            outfile << _matriz[i][j]->getValor();
            if(_matriz[i][j]->getVisivel()){
                outfile << "t";
            }
            else{
                outfile << "f";
            }

            if(j != 8){
                outfile << " ";
            }
        }

        outfile << endl;
    }

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

Partida::Partida(shared_ptr<Jogador> jogador) {
    _tabuleiro = new Tabuleiro();
    _jogador = jogador;
    _jogando = false;
    _cronometro = new Cronometro();
}

Partida::~Partida() {
    delete _tabuleiro;
    delete _cronometro;
}

void Partida::mensagem() {
    cout << "objeto Partida" << endl;
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

shared_ptr<Jogador> Partida::getJogador(){
    return _jogador;
}

Cronometro* Partida::getCronometro(){
    return _cronometro;
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

PartidaNormal::PartidaNormal(int dificuldade, shared_ptr<Jogador> jogador) : Partida(jogador) {
    _dificuldade = dificuldade;
}

PartidaNormal::~PartidaNormal() {}

void PartidaNormal::mensagem() {
    cout << "objeto PartidaNormal" << endl;
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
        throw ArquivoSudokuNormalNaoExiste();
        return false;
    }

    setJogando(true);

    return true;
}

void PartidaNormal::calcularPontosObtidos(time_t tempo){
    
    int pontos_obtidos;
    if(getJogador()->getVidas() > 0){
        pontos_obtidos = (getJogador()->getVidas() + _dificuldade - 1) * (20000/(tempo + 100)) * _dificuldade;
    }
    else{
        pontos_obtidos = 0;
    }
    //adiciona os pontos ao jogador:
    getJogador()->setPontosObtidos(pontos_obtidos);
};


//Classe PartidaDesafio:

PartidaDesafio::PartidaDesafio(int tempo_limite, shared_ptr<Jogador> jogador) : Partida(jogador) {
    _tempo_limite = tempo_limite;
}

PartidaDesafio::~PartidaDesafio() {}

void PartidaDesafio::mensagem() {
    cout << "objeto PartidaDesafio criado." << endl;
}

bool PartidaDesafio::iniciarPartida() {
    
    string path = "src/game/desafios/desafios.txt";

    if(!getTabuleiro()->criarTabuleiroDesafio(path)){
        cout << "Nao foi possivel criar o tabuleiro." << endl;
        throw ArquivoDesafiosNaoExiste();
        return false;
    }

    getJogador()->setVidas(3);

    setJogando(true);

    return true;
}

void PartidaDesafio::calcularPontosObtidos(time_t tempo){
    
    int pontos_obtidos;
    int dificuldade_equivalente = 3;
    float minutos = _tempo_limite / 60;
    if(getJogador()->getVidas() > 0 && tempo < _tempo_limite){
        pontos_obtidos = ((getJogador()->getVidas() + dificuldade_equivalente - 1) * (20000/(tempo + 100)) * dificuldade_equivalente) + ((minutos+1250)/minutos);
    }else{
        pontos_obtidos = 0;
    }
    //adiciona os pontos ao jogador:
    getJogador()->setPontosObtidos(pontos_obtidos);
};