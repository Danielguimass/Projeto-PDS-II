#include "../../include/users/tabela.hpp"

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