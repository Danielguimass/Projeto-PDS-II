#ifndef JOGAR_H
#define JOGAR_H

#include "../../include/game/sudoku.hpp"
#include "../../include/users/tabela.hpp"
#include "../../include/game/cronometro.hpp"
#include "../../include/users/usuario.hpp"

#include <iostream>
#include <memory>

using namespace std;

//void jogarNormal(Tabela *tabela, string nomeJogador);

void jogarNormal(shared_ptr<Jogador> jogador, Tabela* tabela);
void jogarDesafio(shared_ptr<Jogador> jogador, Tabela* tabela);
void comoJogar(); // Printa as regras de como jogar

#endif