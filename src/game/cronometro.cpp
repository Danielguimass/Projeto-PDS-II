#include "../../include/game/cronometro.hpp"

Cronometro::Cronometro(){
    time(_t0);
}
Cronometro::~Cronometro(){}

void Cronometro::zerarCronometro(){
    time(_t0);
}

time_t Cronometro::tempoAtual(){
    return difftime(time(NULL), *_t0);
}

void Cronometro::imprimeTempo(){
    int segundos = difftime(time(NULL), *_t0);
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

string obtemData(){
    time_t tempo = time(NULL);
    tm *tempo_tm = gmtime(&tempo);
    stringstream ss;

    ss << setw(4) << setfill('0') << tempo_tm->tm_year + 1900
       << setw(2) << setfill('0') << tempo_tm->tm_mon + 1
       << setw(2) << setfill('0') << tempo_tm->tm_mday;

    return ss.str();
}