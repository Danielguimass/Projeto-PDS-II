#include "../../include/users/usuario.hpp"

Usuario::Usuario(string nome, string arquivoEstatisticas)
    :_nome(nome), _estatisticas(arquivoEstatisticas) {}

Usuario::Usuario() : _nome(""), _estatisticas("") {}
    
Usuario::~Usuario(){};

string Usuario::getNome(){
    return _nome;
};


void Usuario::setNome(string nome){
    this->_nome = nome;
};


Estatisticas& Usuario::getEstatisticas(){
    return _estatisticas;
}


void Usuario::mostrarEstatisticas(string nome){
    _estatisticas.mostrarEstatisticas(nome);
};