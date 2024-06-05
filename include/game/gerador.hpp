#ifndef GERADOR_H
#define GERADOR_H

#include <vector>
#include <memory>

class Celula;
class Tabuleiro;


bool saoVizinhas(std::shared_ptr<Celula> celula, std::shared_ptr<Celula> celula_original);

std::shared_ptr<Celula> escolherProximaCelula(std::vector<std::vector<std::shared_ptr<Celula>>> matriz); 

void copiarMatriz(const std::vector<std::vector<std::shared_ptr<Celula>>>& matriz_original, std::vector<std::vector<std::shared_ptr<Celula>>>& matriz_copia);

int limitarVizinhos(std::vector<std::vector<std::shared_ptr<Celula>>> matriz, std::shared_ptr<Celula> celula_original); 

std::vector<std::vector<std::shared_ptr<Celula>>> criarSolucao(std::vector<std::vector<std::shared_ptr<Celula>>> matriz_dinamica);

bool resolveMatriz(std::vector<std::vector<std::shared_ptr<Celula>>> matriz_para_resolver);

std::vector<std::vector<std::shared_ptr<Celula>>> criarMatrizInicial(std::vector<std::vector<std::shared_ptr<Celula>>> matriz_completa);


#endif