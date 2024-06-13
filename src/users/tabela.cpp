#include "../../include/users/tabela.hpp"


/*

Tabela::Tabela(string nomeArquivo) : arquivo(nomeArquivo) {
    carregarUsuarios();
}

Tabela::~Tabela(){};

// Adiciona novo usuário na posição correta, garantindo que a tabela não tenha mais que 10 usuários
void Tabela::adicionarUsuario(Usuario* novoUsuario) {
    bool inserido = false;
    for (size_t i = 0; i < usuarios.size() && i < maxUsuarios; i++) {
        if (novoUsuario->getPontuacao() > usuarios[i].getPontuacao()) {
            usuarios.insert(usuarios.begin() + i, *novoUsuario);
            inserido = true;
            break;
        }
    }

    // Se o novo usuário não foi inserido na iteração anterior, adicioná-lo no final, se há espaço
    if (!inserido && usuarios.size() < maxUsuarios) {
        usuarios.push_back(*novoUsuario);
    }

    // Se a tabela exceder o tamanho máximo, remover o último usuário
    if (usuarios.size() > maxUsuarios) {
        usuarios.pop_back();
    }

    salvarUsuarios();
}

//Exibe a Tabela
void Tabela::exibirTabela() {
    cout << "Tabela de Classificacao:" << endl;
    for (size_t i = 0; i < usuarios.size(); i++) {
        cout << i + 1 << ". " << usuarios[i].getNome() << " - " << usuarios[i].getPontuacao() << endl;
    }
    cout << "" << endl;
}

//Envia os dados do arquivo para um vector
void Tabela::carregarUsuarios() {
    ifstream input(arquivo);
    if (!input) {
        cerr << "Erro ao abrir arquivo." << endl;
        return;
    }

    string nome;
    double pontuacao;
    while (input >> nome >> pontuacao) {
        Usuario usuario(nome, pontuacao);
        usuarios.push_back(usuario);
    }
    input.close();

    // Ordenar a tabela e garantir que não ultrapasse 10 entradas
    sort(usuarios.begin(), usuarios.end(), [](Usuario& u1, Usuario& u2) {
        return u1.getPontuacao() > u2.getPontuacao();
    });

    if (usuarios.size() > maxUsuarios) {
        usuarios.resize(maxUsuarios);
    }
}

//Envie os dados do vector para o arquivo
void Tabela::salvarUsuarios() {
    ofstream output(arquivo);
    if (!output) {
        cerr << "Erro ao abrir arquivo." << endl;
        return;
    }

    for (Usuario& usuario : usuarios) {
        output << usuario.getNome() << " " << usuario.getPontuacao() << endl;
    }
    output.close();
}

*/


//--------------------------------------------------------
//Classe Tabela:

//construtor e destrutor:

Tabela::Tabela(string path_tabela) {
    _path_tabela = path_tabela;
    carregarTabela();
}

Tabela::~Tabela() {}

void Tabela::mensagem() {
    cout << "objeto Tabela" << endl;
}

// Adiciona novo jogador na posição correta, garantindo que a tabela não tenha mais que 10 jogadores:
void Tabela::adicionarJogador(const shared_ptr<Jogador>& jogador) {
    
    // Itera pelo vetor de jogadores:
    bool inserido = false;
    for (size_t i = 0; i < _jogadores.size() && i < _max_jogadores; i++) {
        // Se o jogador tem pontuação suficiente para entrar para o top10:
        if (jogador->getEstatisticas()->getPontuacaoTotal() > _jogadores[i]->getEstatisticas()->getPontuacaoTotal()) {
            _jogadores.insert(_jogadores.begin() + i, jogador);
            inserido = true;
            break;
        }
    }

    // Se foi adicionado, verifica se ele já estava na tabela para remover a(s) sua(s) inscrição(ões) antiga(s):
    int count = 0;
    if(inserido){
        for (size_t i = 0; i < _jogadores.size(); i++){
            if(_jogadores[i]->getNome() == jogador->getNome()){
                count++;
                if(count > 1){
                    _jogadores.erase(_jogadores.begin() + i);
                    i--;
                }
            }
        }
    }

    // Se o novo usuário não foi inserido na iteração anterior, adicioná-lo no final, se há espaço
    if (!inserido && _jogadores.size() < _max_jogadores) {
        _jogadores.push_back(jogador);
    }

    // Se a tabela exceder o tamanho máximo, remover o último usuário
    if (_jogadores.size() > _max_jogadores) {
        _jogadores.pop_back();
    }

    enviarTabela();
}

//Exibe a Tabela:
void Tabela::exibirTabela() {
    cout << "Tabela de Classificacao:" << endl;
    for (size_t i = 0; i < _jogadores.size(); i++) {
        cout << i + 1 << ". " << _jogadores[i]->getNome() << " - " << _jogadores[i]->getEstatisticas()->getPontuacaoTotal() << " pontos." << endl;
    }
    cout << "" << endl;
}

//Envia os dados do arquivo para um vector:
void Tabela::carregarTabela() {
    ifstream input(_path_tabela);
    try{
    if (!input) {
        throw ArquivoTabelaNaoExiste();
    }

    string nome;
    int pontuacao_total;
    while (input >> nome >> pontuacao_total) {
        shared_ptr<Jogador> jogador = make_shared<Jogador>();
        jogador->setNome(nome);
        jogador->getEstatisticas()->setPontuacaoTotal(pontuacao_total);
        _jogadores.push_back(jogador);
    }
    input.close();

    /*
    // Ordenar a tabela e garantir que não ultrapasse 10 entradas
    sort(_jogadores.begin(), _jogadores.end(), [](Jogador* p1, Jogador* p2) {
        return p1->getEstatisticas()->getPontuacaoTotal() > p2->getEstatisticas()->getPontuacaoTotal();
    });

    if (_jogadores.size() > _max_jogadores) {
        _jogadores.resize(_max_jogadores);
    }
    */
    }catch(const ArquivoTabelaNaoExiste& e){
        cerr << e.what() << endl;
        throw;
    }
}

//Envie os dados do vector para o arquivo:
void Tabela::enviarTabela() {
    ofstream output(_path_tabela);
    if (!output) {
        cerr << "Erro ao abrir tabela." << endl;
        return;
    }

    for (auto& jogador: _jogadores) {
        output << jogador->getNome() << " " << jogador->getEstatisticas()->getPontuacaoTotal() << endl;
    }
    output.close();
}