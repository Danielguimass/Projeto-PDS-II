#ifndef JOGAR_H
#define JOGAR_H

#include "../../include/game/sudoku.hpp"
#include "../../include/users/tabela.hpp"
#include "../../include/game/cronometro.hpp"
#include "../../include/users/usuario.hpp"

#include <iostream>

using namespace std;

void jogarNormal(Tabela *tabela, string nomeJogador);
void jogarDesafio();
void comoJogar(); // Printa as regras de como jogar

#endif