#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

    void iniciarCronometro(time_t *tempo);
    void imprimeTempo(time_t *tempo);
    int obtemData();

#endif