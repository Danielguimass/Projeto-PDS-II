#include "sudokus.hpp"

void JOGO::imprimirTabuleiro(){
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
                auto posicao = find(casa->possiveis_valores.begin(), casa->possiveis_valores.end(), casa_original->valor);
        
                if(posicao != casa->possiveis_valores.end()){ //verdadeiro se casa->possiveis_valores conter casa_original->valor
            
                    if(casa->possiveis_valores.size() == 1){
                        return 0; //fazer backtracking
                    }

                    casa->possiveis_valores.erase(posicao);
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

void criarSolucao(vector<vector<CASA*>> tabuleiro_dinamico){
    //verifica se o tabuleiro está nas condições inicais apropriadas para criar a solução:
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(!(tabuleiro_dinamico[i][j]->valor == 0)){
                cout << "Tabuleiro inapropriado para criar uma solucao." << endl;
                return;
            }
        }
    }
    //algoritmo
    CASA *casa_atual;
    int etapa;
    vector<TABULEIRO_ESTATICO> tabuleiros(81);

    for(etapa = 0; etapa < 81; etapa++){
        casa_atual = escolheProximaCasa(tabuleiro_dinamico);

        if(casa_atual != nullptr){
            casa_atual->valor = casa_atual->possiveis_valores[rand() % casa_atual->possiveis_valores.size()]; //insere como valor da casa atual um item de indice aleatorio dentro do vetor de possiveis valores
            casa_atual->possiveis_valores = {};

            if(!limitaVizinhos(tabuleiro_dinamico, casa_atual)){
                //à implementar: desfazer passos caso não haja jogo possível (backtracking)
                tabuleiro_dinamico = dinamizaTabuleiro(tabuleiros[i-1]); //transforma tabuleiro_dinamico na sua iteração anterior

                auto posicao = find(tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.begin(), tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.end(), casa_atual->valor);
                tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.erase(posicao); //remove o valor escolhido aleatoriamente dos possiveis valores

                i--;
                continue; //retorna a mesma etapa (deveriam ser 2 etapas pra tras? pensar...)
            }

            

        } else{
            break;
        }

        tabuleiros[etapa] = *new TABULEIRO_ESTATICO(tabuleiro_dinamico, casa_atual);
    }
    
};


void criarTabuleiroInicial(vector<vector<CASA*>> tabuleiro_completo){

};

void JOGO::criarTabuleiro(){
    criarSolucao(tabuleiro);
    criarTabuleiroInicial(tabuleiro);
};