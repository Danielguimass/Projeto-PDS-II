#ifndef GERADOR_H
#define GERADOR_H

#include <vector>

class Celula;
class Tabuleiro;


bool saoVizinhas(Celula *celula, Celula *celula_original);

Celula *escolherProximaCelula(std::vector<std::vector<Celula*>> matriz); 

void copiarMatriz(const std::vector<std::vector<Celula*>>& matriz_original, std::vector<std::vector<Celula*>>& matriz_copia);

int limitarVizinhos(std::vector<std::vector<Celula*>> matriz, Celula *celula_original); 

void criarSolucao(std::vector<std::vector<Celula*>> matriz_dinamica);

bool resolveMatriz(std::vector<std::vector<Celula*>> matriz_para_resolver);

void criarMatrizInicial(std::vector<std::vector<Celula*>> matriz_completa);


#endif