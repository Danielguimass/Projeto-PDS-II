#include <sudoku.hpp>

void MATRIZ_JOGO::criarMatriz(int dificuldade) {

    fstream arquivo;

    switch (dificuldade){
    case 1:
        vidas = 5;
        jogando = true;
        arquivo.open("src/niveis/nivel1.txt", ios::in);
        break;
    case 2:
        vidas = 3;
        jogando = true;
        arquivo.open("src/niveis/nivel2.txt", ios::in);
        break;
    case 3:
        vidas = 1;
        jogando = true;
        arquivo.open("src/niveis/nivel3.txt", ios::in);
        break;
    default:
        cout << "Dificuldade inexistente." << endl;
        jogando = false;
        return;
    }

    if (!arquivo){
        cout << "Arquivo inexistente." << endl;
        jogando = false;
        return;
    }

    int i = 0, j = 0;
    int numero; char ch; bool estado;
    while (1) {
        arquivo >> numero;
        if (arquivo.eof()){
            break;
        }

        arquivo >> ch;
        if (arquivo.eof()){
            break;
        }

        if(ch == 't'){
            estado = true;
        }
        else{
            estado = false;
        }
        
        CELULA* celula = new CELULA(numero, estado);
        matriz[i][j] = celula;

        j++;
        if (j == 9) {
            j = 0;
            i++;
        }
    }

    arquivo.close();
};


void MATRIZ_JOGO::imprimirMatriz(){
    int acertos = 0;
    int i, j;
    for(i=0; i<9; i++){

        for(j=0; j<9; j++){

            if(matriz[i][j]->visivel){
                cout << " " << matriz[i][j]->valor;
                acertos++;
            }
            else{
                cout << "  ";
            }

            if(j==2 || j==5){
                cout << " |";
            }

        }

        cout << endl;

        if(i==2 || i==5){
            cout << "-----------------------" << endl;
        }

    }

    cout << endl;

    if(acertos==81){
        cout << "Parabens, voce venceu!" << endl;
        jogando = false;
    }
    else{
        cout << "Vidas restantes: " << vidas << endl;
    }
};


void MATRIZ_JOGO::verificarMatriz(int i, int j, int x){
    if(x == matriz[i][j]->valor){
        if(matriz[i][j]->visivel){
            cout << "Valor ja encontrado." << endl;
        }
        else{
            matriz[i][j]->visivel = true;
            imprimirMatriz();
        } 
    }
    else{
        vidas--;
        if(vidas==0){
            cout << "DERROTA: Vidas esgotadas." << endl;
            jogando = false;
        }
        else{
            cout << "Errado, voce perdeu uma vida." << endl;
            cout << "Vidas restantes: " << vidas << endl;
        }
    }
};