#ifndef USUARIO_H
#define USUARIO_H

#include "../../include/game/exceptions.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <memory>

//#include <ctime>

using namespace std;

/*
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

        void calcularPontuacao(time_t tempo, int dificuldade, int vidas);
};
*/

class Estatisticas {
    private:
        int _pontuacao_total;
        int _partidas;
        int _vitorias;
        int _ultimo_desafio_diario;
        
    public:
        Estatisticas();
        ~Estatisticas();

        int getPontuacaoTotal();
        int getPartidas();
        int getVitorias();
        int getUltimoDesafioDiario();
        void setPontuacaoTotal(int pontuacao_total);
        void setPartidas(int partidas);
        void setVitorias(int vitorias);
        void setUltimoDesafioDiario(int ultimo_desafio_diario);

        void mensagem();

        void carregarEstatisticas(vector<int> estatisticas);
            //carrega as estatisticas (quando o login é efetuado)
        void enviarEstatisticas(string nome, string senha);        
            //envia as estatisticas para o usuarios.txt
};

class Usuario {
    private:
        string _nome;
        string _senha;
        shared_ptr<Estatisticas> _estatisticas;

    public:
        Usuario();
        ~Usuario();

        string getNome();
        string getSenha();
        shared_ptr<Estatisticas> getEstatisticas();
        void setNome(string nome);
        void setEstatisticas(shared_ptr<Estatisticas> estatisticas);

        void mensagem();

        bool carregarUsuario(string nome, string senha);
            //retorne true se o login foi bem sucessido, false caso contrário
        bool criarUsuario(string nome, string senha);
            //retorne true se a conta foi criada, false caso contrário
};

#endif