#include "sudokus.hpp"

int imprimirTabuleiroGenerico(vector<vector<CASA*>> tabuleiro){
    int acertos = 0;
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(tabuleiro[i][j]->visivel){
                cout << " " << tabuleiro[i][j]->valor;
                acertos++;
            }else{
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

    return acertos;
}

void JOGO::imprimirTabuleiro(){
    int acertos = imprimirTabuleiroGenerico(tabuleiro);

    if(acertos==81){
        cout << "Parabens, voce venceu!" << endl;
        jogando = false;
    }else{
        cout << "Vidas restantes: " << vidas << endl;
    }
};

bool saoVizinhas(CASA *casa, CASA *casa_original){
    if(casa->x == casa_original->x || casa->y == casa_original->y){ //se estiverem na mesma linha ou na mesma coluna
        return 1;
    }

    if(casa->x / 3 == casa_original->x / 3 && casa->y / 3 == casa_original->y / 3){ //se estiverem no mesmo 3x3
        return 1;
    }

    return 0;
}

int limitaVizinhos(vector<vector<CASA*>> tabuleiro, CASA *casa_original){
    CASA *casa;
    int i, j;
    for(i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            casa = tabuleiro[i][j];

            if(casa->valor == 0 && saoVizinhas(casa, casa_original)){ //verdadeiro se a casa nao estiver preenchida e for vizinha
                auto indice = find(casa->possiveis_valores.begin(), casa->possiveis_valores.end(), casa_original->valor);
        
                if(indice != casa->possiveis_valores.end()){ //verdadeiro se casa->possiveis_valores conter casa_original->valor
            
                    if(casa->possiveis_valores.size() == 1){
                        return 0; //fazer backtracking
                    }

                    casa->possiveis_valores.erase(indice);
                }
            }       
        }
    }

    return 1;
}

CASA *escolheProximaCasa(vector<vector<CASA*>> tabuleiro){
    int i, j, n;
    unsigned int menor = 10;
    vector<vector<int>> coords_menores;
    CASA *casa;

    for(i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            casa = tabuleiro[i][j];

            if(casa->possiveis_valores.size() < menor && casa->possiveis_valores.size() != 0){
                menor = casa->possiveis_valores.size();
                coords_menores = {{i , j}};
            }
            if(casa->possiveis_valores.size() == menor){
                coords_menores.push_back({i , j});
            }
            if(casa->possiveis_valores.size() > menor){
                continue;
            }
        }
    }
    if(menor == 10){ //somente possivel se todos casa->possiveis_valores.size() == 0
        return nullptr;
    }

    n = rand() % coords_menores.size();
    return tabuleiro[coords_menores[n][0]][coords_menores[n][1]];
}

vector<vector<CASA*>> dinamizaTabuleiro(TABULEIRO_ESTATICO tabuleiro_estatico){
    int i, j;
    CASA casa;
    vector<vector<CASA*>> tabuleiro_dinamico;
    tabuleiro_dinamico = vector<vector<CASA*>>(9, vector<CASA*>(9)); //define o tamanho do tabuleiro

    for(i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            casa = tabuleiro_estatico.tabuleiro[i][j];
            tabuleiro_dinamico[i][j] = new CASA(i ,j);

            tabuleiro_dinamico[i][j]->valor = casa.valor;
            tabuleiro_dinamico[i][j]->possiveis_valores = casa.possiveis_valores;
        }
    }
    return tabuleiro_dinamico;
}

vector<vector<CASA*>> criarSolucao(vector<vector<CASA*>> tabuleiro_dinamico, bool printar){
    //verifica se o tabuleiro está nas condições inicais apropriadas para criar a solução:
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(!(tabuleiro_dinamico[i][j]->valor == 0)){
                cout << "Tabuleiro inapropriado para criar uma solucao." << endl;
                return tabuleiro_dinamico;
            }
        }
    }
    if(printar){
        cout << "Tabuleiro apropriado para criar uma solucao." << endl;
    }
    
    //algoritmo
    int etapa, n;
    CASA *casa_atual;
    vector<TABULEIRO_ESTATICO> tabuleiros(81);

    if(printar){
        cout << "Iniciando loop." << endl;
    }
    for(etapa = 0; etapa < 81; etapa++){

        if(printar){
            cout << "Tabuleiro da etapa " << etapa << ":" << endl;
            n = imprimirTabuleiroGenerico(tabuleiro_dinamico); 
            system("pause");
        }

        casa_atual = escolheProximaCasa(tabuleiro_dinamico);
        
        if(printar){
            cout << "Coordenadas da casa escolhida: (" << casa_atual->x + 1<< ", " << casa_atual->y + 1<< ")." << endl;
        }

        tabuleiros[etapa] = *new TABULEIRO_ESTATICO(tabuleiro_dinamico, casa_atual); //preenche tabuleiros com o tabuleiro_dinamico atual, na primeira iteração, preencherá tabuleiros[0] com um tabuleiro vazio

        if(casa_atual != nullptr){  //checa se escolheProximaCasa() retornou uma casa (acontece exceto se todas as casas tiverem valor diferente de 0)
            
            casa_atual->valor = casa_atual->possiveis_valores[rand() % casa_atual->possiveis_valores.size()]; //insere como valor da casa atual um item de indice aleatorio dentro do vetor de possiveis valores
            casa_atual->possiveis_valores = {};

            if(printar){
                cout << "Valor alterado para: " << casa_atual->valor << "." << endl;
                n = imprimirTabuleiroGenerico(tabuleiro_dinamico); 
                system("pause");
            }

            if(!limitaVizinhos(tabuleiro_dinamico, casa_atual)){ //condição válida se a função limitaVizinhos encontrar uma operação inválida (remover do vetor de possiveis valores o unico valor possivel)
                
                if(printar){
                    cout << "Casa causou um vizinho invalido, retornando o tabuleiro para antes das modificacoes" << endl; 
                }
                
                tabuleiro_dinamico = dinamizaTabuleiro(tabuleiros[etapa]); //desfaz as mudanças dessa etapa
                etapa--;

                while(tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.size() == 1){ //se o unico valor possivel da casa é o valor que resultara em uma operação invalida da função limitaVizinhos, o backtracking continua  
                    
                    if(printar){
                        cout << "A unica possibilidade da casa causa erros, retornando mais uma etapa" << endl; 
                    }
                    
                    tabuleiro_dinamico = dinamizaTabuleiro(tabuleiros[etapa]);
                    etapa--;


                }//caso contrario, ele remove o valor que resultou em erro (seja lá quantos passos no futuro) do vetor de valores possíveis
                auto indice = find(tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.begin(), tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.end(), casa_atual->valor);
                tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.erase(indice);

                if(printar){
                    cout << "Valor " << casa_atual->valor << " removido das possibilidades de valores da casa." << endl;
                }

            }
        }else{     //caso nao existam mais casas com valores diferentes de 0, o loop para (redundante)
            break;
          }
    }

    return tabuleiro_dinamico;
};

void criarTabuleiroInicial(vector<vector<CASA*>> tabuleiro_completo){

};

void JOGO::criarTabuleiro(){
    criarSolucao(tabuleiro, false);
    criarTabuleiroInicial(tabuleiro);
};