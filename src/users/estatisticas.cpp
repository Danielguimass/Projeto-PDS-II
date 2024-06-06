#include "../../include/users/estatisticas.hpp"

#include <ctime>

Estatisticas::Estatisticas(string arquivoEstatisticas) : _arquivoEstatisticas(arquivoEstatisticas) {
    carregarEstatisticas();
}

Estatisticas::~Estatisticas(){}

//Metodos Get e Set
    int Estatisticas::getVitorias(){
        return _vitorias;
    };

    int Estatisticas::getPartidas(){
        return _partidas;
    };

    int Estatisticas::getPontuacao(){
        return _pontuacao;
    };

    int Estatisticas::getMaiorPontuacao(){
        return _maiorPontuacao;
    };

    void Estatisticas::setPontuacao(double pontuacao){
        _pontuacao=pontuacao;
    };

    void Estatisticas::setMaiorPontuacao(double pontuacao){
        _maiorPontuacao = pontuacao;
    };

    void Estatisticas::adicionarVitorias(){
        _vitorias++;
    };

    void Estatisticas::adicionarPartidas(){
        _partidas++;
    };

    void Estatisticas::compararPontuacao(double novaPontuacao){
        if(novaPontuacao>_maiorPontuacao){
            setMaiorPontuacao(novaPontuacao);
            setPontuacao(novaPontuacao);
        }
        else{
            setPontuacao(novaPontuacao);
        }
    };

    void Estatisticas::calcularPontuacao(time_t tempo, int dificuldade, int vidas){
    int pontuacaoFinal;
    int segundos = difftime(time(NULL), tempo);
    if(vidas >0){
        pontuacaoFinal = ((vidas+dificuldade-1)*100) + (1000/segundos) * dificuldade;
    }
    else{
        pontuacaoFinal=0;
    }
    
    compararPontuacao(pontuacaoFinal);

};

    void Estatisticas::mostrarEstatisticas(string nomeUsuario) {
    carregarEstatisticas();
    auto it = _dadosUsuarios.find(nomeUsuario);
    if (it != _dadosUsuarios.end()) {
        cout << "Estatísticas do jogador " << nomeUsuario << ":" << endl;
        cout << "Quantidade de partidas: " << get<1>(it->second) << endl;
        cout << "Quantidade de vitorias: " << get<0>(it->second) << endl;
        cout << "Maior pontuacao: " << get<2>(it->second) << endl;
        cout << endl;
    } else {
        cout << "Estatísticas nao encontradas para o usuario " << nomeUsuario << endl;
    }
    }

    void Estatisticas::atualizarEstatisticas(string nomeUsuario) {
    auto& estatisticasUsuario = _dadosUsuarios[nomeUsuario];
    get<1>(estatisticasUsuario) = _partidas;
    get<0>(estatisticasUsuario) = _vitorias;
    get<2>(estatisticasUsuario) = _maiorPontuacao;
    salvarEstatisticas();
    }

    void Estatisticas::salvarEstatisticas(){
    ofstream arquivo(_arquivoEstatisticas);
    if (arquivo.is_open()) {
        for (const auto& dados : _dadosUsuarios) {
            arquivo << dados.first << " " << get<0>(dados.second) << " " << get<1>(dados.second) << " " << get<2>(dados.second) << endl;
        }
        arquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo para salvar estatisticas." << endl;
    }
    };

    void Estatisticas::carregarEstatisticas(){
    ifstream arquivo(_arquivoEstatisticas);
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            istringstream iss(linha);
            string nomeUsuario;
            int vitorias, partidas;
            double maiorPontuacao;
            if (iss >> nomeUsuario >> vitorias >> partidas >> maiorPontuacao) {
                _dadosUsuarios[nomeUsuario] = make_tuple(vitorias, partidas, maiorPontuacao);
            }
        }
        arquivo.close();
    } else {
        cerr << "Arquivo de estatisticas nao encontrado." << endl;
    }
    };