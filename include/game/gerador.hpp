#ifndef GERADOR_H
#define GERADOR_H

#include <vector>

class Celula;
class Tabuleiro;


bool saoVizinhas(Celula *celula, Celula *celula_original);

Celula *escolherProximaCelula(vector<vector<Celula*>> matriz); 

void copiarMatriz(const vector<vector<Celula*>>& matriz_original, vector<vector<Celula*>>& matriz_copia);

int limitarVizinhos(vector<vector<Celula*>> matriz, Celula *celula_original); 

void criarSolucao(vector<vector<Celula*>> matriz_dinamica);

bool resolverMatriz(vector<vector<Celula*>> matriz_para_resolver);

void criarMatrizInicial(vector<vector<Celula*>> matriz_completa);


#endif