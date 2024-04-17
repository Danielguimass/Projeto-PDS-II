#include "cronometro.hpp"

using namespace std;

void iniciarCronometro(time_t *tempo){
    time(tempo);
}

void imprimeTempo(time_t *tempo){
    int segundos = difftime(time(NULL), *tempo);
    if (segundos < 100*60){
        cout << "Tempo de jogo: " <<
        setw(2) << setfill('0') << segundos / 60 << ":" << 
        setw(2) << setfill('0') << segundos % 60 << endl;
    }else{
        cout << "Tempo de jogo: " <<
        setw(3) << setfill('0') << segundos / 60 << ":" << 
        setw(2) << setfill('0') << segundos % 60 << endl;
    }
}