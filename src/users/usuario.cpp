#include "../../include/users/usuario.hpp"

//--------------------------------------------------------
//Classe Estatisticas:

//construtor e destrutor:

Estatisticas::Estatisticas(){
    _pontuacao_total = 0;
    _partidas = 0;
    _vitorias = 0;
    _ultimo_desafio_diario = 0;
}

Estatisticas::~Estatisticas() {}

//gets e sets:
int Estatisticas::getPontuacaoTotal(){
    return _pontuacao_total;
}

int Estatisticas::getPartidas(){
    return _partidas;
}

int Estatisticas::getVitorias(){
    return _vitorias;
}

int Estatisticas::getUltimoDesafioDiario(){
    return _ultimo_desafio_diario;
}

void Estatisticas::setPontuacaoTotal(int pontuacao_total){
    _pontuacao_total = pontuacao_total;
}

void Estatisticas::setPartidas(int partidas){
    _partidas = partidas;
}

void Estatisticas::setVitorias(int vitorias){
    _vitorias = vitorias;
}

void Estatisticas::setUltimoDesafioDiario(int ultimo_desafio_diario){
    _ultimo_desafio_diario = ultimo_desafio_diario;
}

//carregar e enviar:
void Estatisticas::carregarEstatisticas(vector<int> estatisticas){
    cout << "Carregando estatisticas... " << endl;
    _pontuacao_total = estatisticas[0];
    cout << "pontos: " << _pontuacao_total << endl;
    _partidas = estatisticas[1];
    cout << "partidas: " << _partidas << endl;
    _vitorias = estatisticas[2];
    cout << "vitorias: " << _vitorias << endl;
    _ultimo_desafio_diario = estatisticas[3];
    cout << "ultimo desafio jogado em: " << _ultimo_desafio_diario << endl;
};

void Estatisticas::enviarEstatisticas() {


};


//--------------------------------------------------------
//Classe Usuario:

Usuario::Usuario(){
    _nome = "user";
    _estatisticas = new Estatisticas();
}

Usuario::~Usuario() {}

string Usuario::getNome(){
    return _nome;
}

Estatisticas* Usuario::getEstatisticas(){
    return _estatisticas;
}

void Usuario::setNome(string nome){
    _nome = nome;
}

void Usuario::setEstatisticas(Estatisticas* estatisticas){
    _estatisticas = estatisticas;
}

/*
bool Usuario::carregarUsuario(string nome, string senha){

    string linha;         // Armazena cada linha lida do arquivo
    vector<string> palavras; // Armazena as estatisticas em forma de palavras extraídas da linha desejada

    vector<int> estatisticas = {}; // Armazena as estatisticas

    // Abra o arquivo no modo leitura
    ifstream arquivo("src/users/tabelas/usuarios.txt");

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            // Verifique se a linha inicia com <nome>:
            if (linha.find(nome) == 0) { 
                // Verifique se a segunda palavra da linha é <senha>:
                size_t pos = linha.find(' '); // Encontre o primeiro espaço
                if (pos != string::npos && linha.substr(pos + 1, senha.size()) == senha) {
                    // Nome e senha batem! Extrai as palavras:
                    istringstream iss(linha); // Crie um fluxo de string a partir da linha
                    string palavra;
                    // Extraia cada palavra após as duas primeiras:
                    bool extrair = false; // Flag para controlar a extração
                    while (iss >> palavra) {
                        if (extrair) {
                            palavras.push_back(palavra);
                        }
                        if (palavra == senha) {
                            extrair = true; // A partir da terceira palavra, extraia
                        }
                    }
                    // Transforma as palavras em inteiros e adiciona ao vetor estatisticas:
                    for (const string& palavra : palavras) {
                    int palavra_int = stoi(palavra);
                    estatisticas.push_back(palavra_int);
                    }
                    // Atualiza o nome, carrega as estatisticas e finaliza o login:
                    _nome = nome;
                    _estatisticas->carregarEstatisticas(estatisticas);
                    cout << "Login bem sucedido." << endl;
                    arquivo.close();
                    return true;
                }
            }
        }
        // Não encontrou o par <nome> e <senha> em nenhuma linha:
        arquivo.close();
        return false;
    } else {
    cerr << "Erro ao abrir o arquivo usuarios.txt" << endl;
    }
    return false;
}
*/

bool Usuario::carregarUsuario(string nome, string senha) {

  string linha;
  vector<string> palavras;

  vector<int> estatisticas = {}; // Armazena as estatisticas

  ifstream arquivo("src/users/tabelas/usuarios.txt");

  if (arquivo.is_open()) {
    while (getline(arquivo, linha)) {
      istringstream iss(linha); // Create stringstream from line

      string palavra;
      while (iss >> palavra) { // Extract each word from line
        palavras.push_back(palavra);
      }

      // Verifica se as duas primeiras palavras são <nome> e <senha>:
      if (palavras.size() >= 2 && palavras[0] == nome && palavras[1] == senha) {
        // Nome e senha batem! Converte as demais palavras para inteiros e adiciona ao vetor estatisticas:
        int i = 0;
        for(i=0; i<6; i++){
            if(i>1){
                estatisticas.push_back(stoi(palavras[i]));
            }
        }

        // Atualiza o nome, carrega as estatisticas e finaliza o login:
        _nome = nome;
        _estatisticas->carregarEstatisticas(estatisticas);
        cout << "Login bem sucedido." << endl;
        arquivo.close();
        return true;
      }
      else {
        palavras.clear(); // Clear words vector for next line
      }

    }

    //Não encontrou o par <nome> e <senha>:
    arquivo.close();
    return false;

  } else {
    cerr << "Erro ao abrir o arquivo usuarios.txt" << endl;
  }

  return false;
}

bool Usuario::criarUsuario(string nome, string senha){
    return true;
}