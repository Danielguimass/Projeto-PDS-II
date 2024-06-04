#include "../../include/users/usuario.hpp"

#include <ctime>

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