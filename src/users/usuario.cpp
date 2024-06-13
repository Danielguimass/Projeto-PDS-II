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

void Estatisticas::mensagem() {
    cout << "objeto Estatisticas" << endl;
}

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
    //considerando que o vetor estatisticas tem 4 inteiros.
    cout << "Carregando suas estatisticas... " << endl;
    _pontuacao_total = estatisticas[0];
    cout << "pontos: " << _pontuacao_total << endl;
    _partidas = estatisticas[1];
    cout << "partidas: " << _partidas << endl;
    _vitorias = estatisticas[2];
    cout << "vitorias: " << _vitorias << endl;
    _ultimo_desafio_diario = estatisticas[3];
    cout << "ultimo desafio jogado em: " << _ultimo_desafio_diario << endl;
};

void Estatisticas::enviarEstatisticas(string nome, string senha) {
    //Cria string com as estatísticas atuais:
    string nova_linha = nome + " " + senha + " " + to_string(_pontuacao_total) + " " + to_string(_partidas) + " " + to_string(_vitorias) + " " + to_string(_ultimo_desafio_diario);

    fstream arquivo;
    string linha_lida; // Variável para armazenar cada linha lida do arquivo

    arquivo.open("src/users/tabelas/usuarios.txt", ios::in);

    string conteudo;

    //Armazena na variável conteúdo todas as linhas exceto a que contém <nome>:
    while(getline(arquivo, linha_lida)){
        if (!linha_lida.find(nome + " " + senha + " ") == 0) {
            conteudo += linha_lida + '\n';
        }
    }
        
    arquivo.close();

    arquivo.open("src/users/tabelas/usuarios.txt", ios::out);

    arquivo << conteudo;
    arquivo << nova_linha;

    arquivo.close();
};


//--------------------------------------------------------
//Classe Usuario:

Usuario::Usuario(){
    _nome = "user";
    _senha = "password";
    _estatisticas = shared_ptr<Estatisticas>(new Estatisticas());
}

Usuario::~Usuario() {}

void Usuario::mensagem() {
    cout << "objeto Usuario" << endl;
}

string Usuario::getNome(){
    return _nome;
}

string Usuario::getSenha(){
    return _senha;
}

shared_ptr<Estatisticas> Usuario::getEstatisticas(){
    return _estatisticas;
}

void Usuario::setNome(string nome){
    _nome = nome;
}

void Usuario::setEstatisticas(shared_ptr<Estatisticas> estatisticas){
    _estatisticas = move(estatisticas);
}

bool Usuario::carregarUsuario(string nome, string senha) {

  string linha;
  vector<string> palavras;

  vector<int> estatisticas = {}; // Armazena as estatisticas

  ifstream arquivo("src/users/tabelas/usuarios.txt");

try{
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
        _senha = senha;
        _estatisticas->carregarEstatisticas(estatisticas);
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
        throw ArquivoUsuariosNaoExiste();
  }
}catch(const ArquivoUsuariosNaoExiste& e){
    cerr << e.what() << endl;
    throw;
}

  return false;
    
}

bool Usuario::criarUsuario(string nome, string senha){

  string linha;
  fstream arquivo;

  //Abre para leitura:
  arquivo.open("src/users/tabelas/usuarios.txt", ios::in);
try{
  if (arquivo.is_open()) {
    while (getline(arquivo, linha)) {
      istringstream iss(linha); // Create stringstream from line
      string nome_da_linha;
      iss >> nome_da_linha;

      // Verifica se o nome da linha é igual a <nome>:
      if (nome_da_linha == nome) {
        arquivo.close();
        return false;
      }
    }
    arquivo.close();

  } else {
        throw ArquivoUsuariosNaoExiste();
        return false;
  }
}catch(const ArquivoUsuariosNaoExiste& e){
    cerr << e.what() << endl;
    throw;
}

  //Não tendo encontrado nenhuma linha com o nome <nome>, abre para escrita:

  arquivo.open("src/users/tabelas/usuarios.txt", ios::app);

  string usuario = nome + " " + senha + " 0 0 0 0"; 
  arquivo << endl << usuario;

  arquivo.close();

  //Carrega o usuário que acabou de criar:
  carregarUsuario(nome, senha);
    
  return true;
}