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

}

int Estatisticas::getVitorias(){

}

int Estatisticas::getUltimoDesafioDiario(){

}

void Estatisticas::setPontuacaoTotal(int pontuacao_total){
    _pontuacao_total = pontuacao_total;
}

void Estatisticas::setPartidas(int partidas){

}

void Estatisticas::setVitorias(int vitorias){

}

void Estatisticas::setUltimoDesafioDiario(int ultimo_desafio_diario){

}

//carregar e enviar:
void Estatisticas::carregarEstatisticas(){

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

bool Usuario::carregarUsuario(string nome, string senha){
    return true;
}

bool Usuario::criarUsuario(string nome, string senha){
    return true;
}