#ifndef TABELA_H
#define TABELA_H

#include "usuario.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Tabela {
    private:
        size_t maxUsuarios = 10; // Tamanho máximo da tabela
        string arquivo;
        vector<Usuario> usuarios;

    public:
        Tabela(string nomeArquivo);
        ~Tabela();

        void adicionarUsuario(Usuario novoUsuario);
        void exibirTabela();
        void carregarUsuarios();
        void salvarUsuarios();
};

#endif