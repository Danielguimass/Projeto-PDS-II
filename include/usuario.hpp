#ifndef USUARIO_H
#define USUARIO_h
#include <iostream>

using namespace std;

class Usuario{
    private:
        string _nome;
        double _pontuacao;
    public:
        Usuario();
        Usuario(string nome, double pontuacao);
        ~Usuario();

        string getNome();
        double getPontuacao();
        void setNome(string nome);
        void setPontuacao(double pontuacao);

        void calcularPontuacao();
};

#endif