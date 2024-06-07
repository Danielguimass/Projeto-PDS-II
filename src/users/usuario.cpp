#include "../../include/users/usuario.hpp"

/*
Usuario::Usuario(){
    _nome = "";
    _pontuacao = 0;
};
Usuario::Usuario(string nome, double pontuacao)
    :_nome(nome), _pontuacao(pontuacao) {}
Usuario::~Usuario(){};

string Usuario::getNome(){
    return _nome;
};

double Usuario::getPontuacao(){
    return _pontuacao;
};

void Usuario::setNome(string nome){
    this->_nome = nome;
};

void Usuario::setPontuacao(double pontuacao){
    this->_pontuacao = pontuacao;
};

void Usuario::calcularPontuacao(time_t tempo, int dificuldade, int vidas){
    int pontuacaoFinal;
    int segundos = difftime(time(NULL), tempo);
    if(vidas >0){
        pontuacaoFinal = ((vidas+dificuldade-1)*100) + (1000/segundos) * dificuldade;
    }
    else{
        pontuacaoFinal=0;
    }
    setPontuacao(pontuacaoFinal);
};
*/


//--------------------------------------------------------
//Classe Estatisticas:

//construtor e destrutor:

Estatisticas::Estatisticas(string path_usuarios){
    _path_usuarios = path_usuarios;
    _pontuacao_total = 0;
    _partidas = 0;
    _vitorias = 0;
    _ultimo_desafio_diario = 0;
}

Estatisticas::Estatisticas() {}

Estatisticas::~Estatisticas() {}

//gets e sets:
int Estatisticas::getPontuacaoTotal(){
    return _pontuacao_total;
};

int Estatisticas::getPartidas(){

};

int Estatisticas::getVitorias(){

};

int Estatisticas::getUltimoDesafioDiario(){

};

void Estatisticas::setPontuacaoTotal(int pontuacao_total){
    _pontuacao_total = pontuacao_total;
};

void Estatisticas::setPartidas(int partidas){

};

void Estatisticas::setVitorias(int vitorias){

};

void Estatisticas::setUltimoDesafioDiario(int ultimo_desafio_diario){

};

//carregar e enviar:
void Estatisticas::carregarEstatisticas(){

};

void Estatisticas::enviarEstatisticas() {


};


//--------------------------------------------------------
//Classe Usuario:

Usuario::Usuario(string path_usuarios){
    _nome = "user";
    _estatisticas = new Estatisticas(path_usuarios);
}

Usuario::Usuario() {}

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

bool Usuario::carregarUsuario(string nome, string senha){
    return true;
}

bool Usuario::criarUsuario(string nome, string senha){
    return true;
}