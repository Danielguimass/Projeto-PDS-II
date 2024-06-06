#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include "../../include/users/estatisticas.hpp"

using namespace std;

class Usuario{
    private:
        string _nome;
        Estatisticas _estatisticas;
    public:
        Usuario();
        Usuario(string nome, string arquivoEstatisticas);
        ~Usuario();

        string getNome();
        void setNome(string nome);
        Estatisticas& getEstatisticas();

        void mostrarEstatisticas(string nome);
};

#endif