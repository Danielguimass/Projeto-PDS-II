#ifndef SUDOKU_H
#define SUDOKU_H

/*
Este módulo implementa todas as classes que fazem parte de um jogo de sudoku, tanto para a modalidade normal quanto para o desafio diário.
Faz uso dos módulos "usuario" e "tabela".
*/

#include "../users/usuario.hpp"
#include "../users/tabela.hpp"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Jogador : public Usuario {
    private:
    int _vidas;

    public:
    Jogador(int vidas);
    ~Jogador();

    int getVidas();
    void setVidas(int vidas);
};

class Celula {
    private:
    int _valor;
    bool _visivel;

    public:
    Celula(int valor, bool visivel);
    ~Celula();

    int getValor();
    bool getVisivel();
    void setVisivel(bool visivel);
};

class Tabuleiro {
    private:
    vector<vector<Celula*>> _matriz;

    public:
    Tabuleiro();
    ~Tabuleiro();

    bool criarTabuleiroNormal(string path);
        //retorna false se não conseguiu criar o tabuleiro.
    bool criarTabuleiroDesafio();
        //retorna false se não conseguiu criar o tabuleiro.

    void exibirTabuleiro();
        //apenas exibe o tabuleiro na tela.
    bool verificarJogada(int i, int j, int valor);
        //se a jogada foi um acerto, atualiza o tabuleiro e retorna true, se errou retorna false.
    bool verificarVitoria();
        //se o tabuleiro estiver completo, retorna true.
};

class Partida {
    private:
    Tabuleiro* _tabuleiro;
    Jogador* _jogador;
    bool _jogando;

    public:
    Partida();
    ~Partida();

    bool getJogando();
    void setJogando(bool jogando);
    Tabuleiro* getTabuleiro();
    Jogador* getJogador();

    bool virtual iniciarPartida() = 0;

    void fazerJogada(int i, int j, int valor);
        //se acertou, atualiza o tabuleiro, exibe ele novamente e verifica se o jogo terminou.
        //se errou, tira uma vida e verifica se vidas = 0, caso afirmativo, o jogo termina como derrota.
};

class PartidaNormal : public Partida {
    private:
    int _dificuldade;

    public:
    PartidaNormal(int dificuldade);

    bool iniciarPartida() override;
        //retorna false se não conseguiu iniciar a partida.
};

class PartidaDesafio : public Partida {

};


#endif