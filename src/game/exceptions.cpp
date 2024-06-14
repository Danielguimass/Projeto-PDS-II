#include "../../include/game/exceptions.hpp"

const char* ArquivoTabelaNaoExiste::what() const noexcept{
    return "Arquivo tabela.txt nao existe";
};

const char* ArquivoUsuariosNaoExiste::what() const noexcept{
    return "Arquivo usuarios.txt nao existe";
};

const char *ArquivoDesafiosNaoExiste::what() const noexcept{
    return "Arquivo desafios.txt nao existe";
}

const char *ArquivoSudokuNormalNaoExiste::what() const noexcept{
    return "Arquivo de sudokus para a dificuldade selecionada nao existe";
}