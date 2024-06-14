#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>
#include <iostream>

using namespace std;

class ArquivoTabelaNaoExiste : public exception {
    public:
        const char* what() const noexcept override;
};

class ArquivoUsuariosNaoExiste : public exception {
    public:
        const char* what() const noexcept override;
};

class ArquivoDesafiosNaoExiste : public exception {
    public:
        const char* what() const noexcept override;
};

#endif