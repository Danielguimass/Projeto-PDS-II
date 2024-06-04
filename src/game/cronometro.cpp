#include "../../include/game/cronometro.hpp"

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

int obtemData(){
    time_t tempo = time(NULL);
    tm *tempo_tm = gmtime(&tempo);
    stringstream ss;

    ss << setw(4) << setfill('0') << tempo_tm->tm_year + 1900
       << setw(2) << setfill('0') << tempo_tm->tm_mon + 1
       << setw(2) << setfill('0') << tempo_tm->tm_mday;

    return stoi(ss.str());
}