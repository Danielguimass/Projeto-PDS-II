#ifndef TABELA_H
#define TABELA_H

#include "../../include/users/usuario.hpp"
#include "../../include/game/sudoku.hpp"
#include "../../include/game/exceptions.hpp"


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

/*
class Jogador;

class Tabela {
    private:
        size_t maxUsuarios = 10; // Tamanho máximo da tabela
        string arquivo;
        vector<Usuario> usuarios;

    public:
        Tabela(string nomeArquivo);
        ~Tabela();

        void adicionarUsuario(Usuario* novoUsuario);
        void exibirTabela();
        void carregarUsuarios();
        void salvarUsuarios();
};
*/

class Jogador;

class Tabela {
    private:
        size_t _max_jogadores = 10; // Tamanho máximo da tabela
        string _path_tabela;
        vector<shared_ptr<Jogador>> _jogadores;

    public:
        Tabela(string path_tabela);
        ~Tabela();

        void mensagem();

        void adicionarJogador(const shared_ptr<Jogador>& jogador);
        void exibirTabela();
        void carregarTabela();
        void enviarTabela();
};

#endif