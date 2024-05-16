#include "usuario.hpp"

using namespace std;
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

void Usuario::calcularPontuacao(){

};