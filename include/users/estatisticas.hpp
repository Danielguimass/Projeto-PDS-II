#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Estatisticas {
private:
    string _arquivoEstatisticas;
    int _vitorias;
    int _partidas;
    int _pontuacao;
    int _maiorPontuacao;
    map<string, tuple<int, int, double>> _dadosUsuarios;

public:
    Estatisticas(string arquivoEstatisticas);
    ~Estatisticas();

//Metodos Get 
    int getVitorias();
    int getPartidas();
    int getPontuacao();
    int getMaiorPontuacao();

    void setPontuacao(double pontuacao);
    void setMaiorPontuacao(double pontuacao);

    void adicionarVitorias();
    void adicionarPartidas();
    void compararPontuacao(double pontuacao);
    void calcularPontuacao(time_t tempo, int dificuldade, int vidas);

    void atualizarEstatisticas(string nomeUsuario);
    void mostrarEstatisticas(string nome);
    void salvarEstatisticas();
    void carregarEstatisticas();



};

#endif