#include "../../include/game/exceptions.hpp"

const char* ArquivoTabelaNaoExiste::what() const noexcept{
    return "Arquivo tabela.txt nao existe";
};

const char* ArquivoUsuariosNaoExiste::what() const noexcept{
    return "Arquivo usuarios.txt nao existe";
};