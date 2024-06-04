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

void copiarTabuleiro(const vector<vector<CASA*>>& tabuleiro_original, vector<vector<CASA*>>& tabuleiro_copia){
    int i, j;

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(tabuleiro_copia[i][j] == nullptr){
                tabuleiro_copia[i][j] = new CASA(i, j);
            }

            *tabuleiro_copia[i][j] = *tabuleiro_original[i][j];
        }
    }
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
    int etapa, valor;
    CASA *casa_atual;
    vector<vector<vector<CASA*>>> tabuleiros(81);

    if(printar){
        cout << "Iniciando loop." << endl;
    }
    for(etapa = 0; etapa < 81; etapa++){

        tabuleiros[etapa] = vector<vector<CASA*>>(9, vector<CASA*>(9));
        copiarTabuleiro(tabuleiro_dinamico, tabuleiros[etapa]); //preenche tabuleiros com o tabuleiro_dinamico atual, na primeira iteração, preencherá tabuleiros[0] com um tabuleiro vazio

        if(printar){
            cout << "Tabuleiro da etapa " << etapa << ":" << endl;
            imprimirTabuleiroGenerico(tabuleiros[etapa]); 
            system("pause");
        }

        casa_atual = escolheProximaCasa(tabuleiro_dinamico);
        
        if(printar){
            cout << "Coordenadas da casa escolhida: (" << casa_atual->x + 1<< ", " << casa_atual->y + 1<< ")." << endl;
        }

        if(casa_atual != nullptr){  //checa se escolheProximaCasa() retornou uma casa (acontece exceto se todas as casas tiverem valor diferente de 0)
            
            valor = casa_atual->possiveis_valores[rand() % casa_atual->possiveis_valores.size()]; 
            casa_atual->valor = valor;  //insere como valor da casa atual um item de indice aleatorio dentro do vetor de possiveis valores
            casa_atual->possiveis_valores = {};

            if(printar){
                cout << "Valor alterado para: " << casa_atual->valor << "." << endl;
                imprimirTabuleiroGenerico(tabuleiro_dinamico); 
                system("pause");
            }

            if(!limitaVizinhos(tabuleiro_dinamico, casa_atual)){ //condição válida se a função limitaVizinhos encontrar uma operação inválida (remover do vetor de possiveis valores o unico valor possivel)
                
                if(printar){
                    cout << "Casa causou um vizinho invalido, retornando o tabuleiro para antes das modificacoes" << endl; 
                }
                
                copiarTabuleiro(tabuleiros[etapa], tabuleiro_dinamico);
                etapa--;

                while(tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.size() == 1){ //se o unico valor possivel da casa é o valor que resultara em uma operação invalida da função limitaVizinhos, o backtracking continua  
                    
                    if(printar){
                        cout << "A unica possibilidade da casa causa erros, retornando mais uma etapa" << endl; 
                    }
                    
                    copiarTabuleiro(tabuleiros[etapa], tabuleiro_dinamico);
                    etapa--;


                }//caso contrario, ele remove o valor que resultou em erro (seja lá quantos passos no futuro) do vetor de valores possíveis
                auto indice = find(tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.begin(), tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.end(), valor);
                tabuleiro_dinamico[casa_atual->x][casa_atual->y]->possiveis_valores.erase(indice);

                if(printar){
                    cout << "Valor " << valor << " removido das possibilidades de valores da casa." << endl;
                }

            }
        }else{     //caso nao existam mais casas com valores diferentes de 0, o loop para (redundante)
            break;
          }
    }

    return tabuleiro_dinamico;
};

bool resolveTabuleiro(vector<vector<CASA*>> tabuleiro_para_resolver){
    vector<vector<CASA*>> tabuleiro(9, vector<CASA*>(9));
    int i, j, n;

    for(i = 0; i < 9; i++){                     //copia tabuleiro para nao alterar o original
        for(j = 0; j < 9; j++){
            tabuleiro[i][j] = new CASA(i, j);   //nao sei se essa linha é necessária
            *tabuleiro[i][j] = *tabuleiro_para_resolver[i][j];

            if(!tabuleiro[i][j]->visivel){
                tabuleiro[i][j]->possiveis_valores = {1,2,3,4,5,6,7,8,9};
                tabuleiro[i][j]->valor = 0;     //a função limitaVizinhos() checa se o valor da casa é 0 ao invés de checar se ela é invisível
                tabuleiro[i][j]->visivel = true; //apenas para caso seja necessário imprimir na depuração
            }
        }
    }
    
    //limita todas as casa->possiveis_valores de todas as casas

    CASA* casa;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            casa = tabuleiro[i][j];
            if(casa->valor != 0){
                if(!limitaVizinhos(tabuleiro, casa)){           
                    cout << "Algo de muito errado aconteceu" << endl;
                }
            }
        }
    }

    //algoritmo para resolver

    n = 0;          //numero de casas preenchidas

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            casa = tabuleiro[i][j];
            if(casa->valor != 0){
                n++;
                if(n == 81){
                    return true;
                }

                continue;   
            }
            
            if(casa->possiveis_valores.size() == 1){    //so executa se casa->valor == 0 (por causa do continue;)

                casa->valor = casa->possiveis_valores[0];
                if(!limitaVizinhos(tabuleiro, casa)){
                    cout << "Algo de muito errado aconteceu" << endl;
                    return false;
                }



                i = -1; //para recomeçar o loop de fora
                break;
            }
        }
    }

    return false;
};

void criarTabuleiroInicial(vector<vector<CASA*>> tabuleiro_completo){
    int i, j, n;
    int k = 0;
    vector<vector<int>> pares_nao_checados(41, vector<int>(4, 0));

    for(i = 0; i < 5; i++){         //essas condições de paradas sao desnecessárias, só a do k importa
        for(j = 0; j < 9; j++){
            if(k > 40){  //condição de parada
                break;
            }
            pares_nao_checados[k][0] = i;
            pares_nao_checados[k][1] = j;

            pares_nao_checados[k][2] = 8 - i;
            pares_nao_checados[k][3] = 8 - j;

            k++;
        }
    }
    
    while(!pares_nao_checados.empty()){     //checa, par à par, se o tabuleiro continua solúvel (sem chutes) após ocultar o par
        n = rand() % pares_nao_checados.size();
        tabuleiro_completo[pares_nao_checados[n][0]][pares_nao_checados[n][1]]->visivel = false;
        tabuleiro_completo[pares_nao_checados[n][2]][pares_nao_checados[n][3]]->visivel = false;


        if(!resolveTabuleiro(tabuleiro_completo)){          //caso o tabuleiro não continuar solúvel, o par em questão se torna visível
            tabuleiro_completo[pares_nao_checados[n][0]][pares_nao_checados[n][1]]->visivel = true;
            tabuleiro_completo[pares_nao_checados[n][2]][pares_nao_checados[n][3]]->visivel = true;
        }

        pares_nao_checados.erase(pares_nao_checados.begin() + n);
    }
};

void JOGO::criarTabuleiro(){
    criarSolucao(tabuleiro, false);
    criarTabuleiroInicial(tabuleiro);
};