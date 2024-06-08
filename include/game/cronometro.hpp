#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

class Cronometro {
    private:
        time_t* _t0;

    public:
        Cronometro();
        ~Cronometro();

        void mensagem();

        void zerarCronometro();
        time_t tempoAtual();
        void imprimeTempo();
        
};

string obtemData();

#endif