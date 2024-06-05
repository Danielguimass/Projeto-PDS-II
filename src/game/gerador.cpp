#include "../../include/game/gerador.hpp"
#include "../../include/game/sudoku.hpp"

bool saoVizinhas(Celula *celula, Celula *celula_original){
    if(celula->getX() == celula_original->getX() || celula->getY() == celula_original->getY()){
        return true;
    }

    if(celula->getX() / 3 == celula_original->getX() / 3 && celula->getY() / 3 == celula_original->getY() / 3){
        return true;
    }

    return false;
}

Celula *escolherProximaCelula(vector<vector<Celula *>> matriz){
    int i, j, n;
    unsigned int menor = 10;
    vector<vector<int>> coords_menores;
    Celula *celula;

    for(i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            celula = matriz[i][j];

            if(celula->getVetor().size() < menor && celula->getVetor().size() != 0){
                menor = celula->getVetor().size();
                coords_menores = {{i , j}};
            }
            if(celula->getVetor().size() == menor){
                coords_menores.push_back({i , j});
            }
            if(celula->getVetor().size() > menor){
                continue;
            }
        }
    }
    if(menor == 10){ //somente possivel se todos casa->possiveis_valores.size() == 0
        return nullptr;
    }

    n = rand() % coords_menores.size();
    return matriz[coords_menores[n][0]][coords_menores[n][1]];
}

void copiarMatriz(const vector<vector<Celula *>> &matriz_original, vector<vector<Celula *>> &matriz_copia){
    int i, j;

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(matriz_copia[i][j] != nullptr){
                delete matriz_copia[i][j];
            }

            matriz_copia[i][j] = new Celula(*matriz_original[i][j]);

            if(!matriz_copia[i][j]->getVisivel()){                      //reseta alguns valores para celulas nao visiveis (isso nao deve alterar o uso dessa função dentro da função criarSolucao(), já que as celulas sempre são visíveis nela)
                matriz_copia[i][j]->setVetor({1,2,3,4,5,6,7,8,9});      //a utilidade de resetar esses valores só existe na função resolverMatriz(), talvez seja melhor implementar diretamente nela e manter essa fução com uso mais genérico
                matriz_copia[i][j]->setValor(0);                    //a função limitarVizinhos() checa se o valor da casa é 0 ao invés de checar se ela é invisível, então resetar os valores é necessário
                matriz_copia[i][j]->setVisivel(true);               //apenas para caso seja necessário imprimir na depuração
            }
        }
    }
}

int limitarVizinhos(vector<vector<Celula *>> matriz, Celula *celula_original){
    Celula *celula;
    int i, j;
    vector<int> possiveis_valores;
    
    for(i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            celula = matriz[i][j];
            possiveis_valores = celula->getVetor();
            
            if(celula->getValor() == 0 && saoVizinhas(celula, celula_original)){ //verdadeiro se a casa nao estiver preenchida e for vizinha
                auto indice = find(possiveis_valores.begin(), possiveis_valores.end(), celula_original->getValor());
        
                if(indice != possiveis_valores.end()){ //verdadeiro se casa->possiveis_valores conter casa_original->valor
            
                    if(possiveis_valores.size() == 1){
                        return 0; //fazer backtracking
                    }

                    possiveis_valores.erase(indice);
                    celula->setVetor(possiveis_valores);
                }
            }       
        }
    }

    return 1;
}

void criarSolucao(vector<vector<Celula *>> matriz_dinamica){
    
    //verifica se a matriz está nas condições inicais apropriadas para criar a solução:
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(!(matriz_dinamica[i][j]->getValor() == 0)){
                cout << "Tabuleiro inapropriado para criar uma solucao." << endl;
                return;
            }
        }
    }
    
    //algoritmo
    int etapa, valor;
    Celula *celula_atual;
    vector<int> vetor;
    vector<vector<vector<Celula*>>> matrizes(81);

    for(etapa = 0; etapa < 81; etapa++){

        matrizes[etapa] = vector<vector<Celula*>>(9, vector<Celula*>(9));
        copiarMatriz(matriz_dinamica, matrizes[etapa]); //preenche matrizes com a matriz_dinamica atual, na primeira iteração, preencherá matrizes[0] com uma matriz vazia

        celula_atual = escolherProximaCelula(matriz_dinamica);
        
        if(celula_atual != nullptr){  //checa se escolherProximaCelula() retornou uma celula (acontece exceto se todas as celulas tiverem valor diferente de 0)
            
            valor = celula_atual->getVetor()[rand() % celula_atual->getVetor().size()]; 
            celula_atual->setValor(valor);  //insere como valor da celula atual um item de indice aleatorio dentro do vetor de possiveis valores
            celula_atual->setVetor({});
            
            if(!limitarVizinhos(matriz_dinamica, celula_atual)){ //condição válida se a função limitarVizinhos encontrar uma operação inválida (remover do vetor de possiveis valores o unico valor possivel)

                copiarMatriz(matrizes[etapa], matriz_dinamica);
                etapa--;

                while(matriz_dinamica[celula_atual->getX()][celula_atual->getY()]->getVetor().size() == 1){ //se o unico valor possivel da celula é o valor que resultara em uma operação invalida da função limitarVizinhos, o backtracking continua  
                    
                    copiarMatriz(matrizes[etapa], matriz_dinamica);
                    etapa--;

                }//caso contrario, ele remove o valor que resultou em erro (seja lá quantos passos no futuro) do vetor de valores possíveis

                vetor = matriz_dinamica[celula_atual->getX()][celula_atual->getY()]->getVetor();
                auto indice = find(vetor.begin(), vetor.end(), valor);
                vetor.erase(indice);
                
                matriz_dinamica[celula_atual->getX()][celula_atual->getY()]->setVetor(vetor);
            }
        }else{     //caso nao existam mais casas com valores diferentes de 0, o loop para (redundante)
            break;
         }
        
    }

}

bool resolveMatriz(vector<vector<Celula *>> matriz_para_resolver){

    vector<vector<Celula*>> matriz(9, vector<Celula*>(9));
    int i, j, n;

    copiarMatriz(matriz_para_resolver, matriz);  //copia tabuleiro para nao alterar o original (nao sera usada a função copiarMatriz() pois é necessário alterar alguns )


    //limita os possiveis valores de todas as celulas

    Celula* celula;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            celula = matriz[i][j];
            if(celula->getValor() != 0){
                limitarVizinhos(matriz, celula);
            }
        }
    }

    //algoritmo para resolver

    n = 0;  //numero de casas preenchidas

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            celula = matriz[i][j];
            if(celula->getValor() != 0){
                n++;
                if(n == 81){
                    return true;
                }
                continue;   
            }
            
            if(celula->getVetor().size() == 1){    //so executa se celula->valor == 0 (por causa do continue;)

                celula->setValor(celula->getVetor()[0]);
                limitarVizinhos(matriz, celula);

                i = -1; //para recomeçar o loop de fora
                break;
            }
        }
    }

    return false;
}

void criarMatrizInicial(vector<vector<Celula *>> matriz_completa){
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
        matriz_completa[pares_nao_checados[n][0]][pares_nao_checados[n][1]]->setVisivel(false);
        matriz_completa[pares_nao_checados[n][2]][pares_nao_checados[n][3]]->setVisivel(false);


        if(!resolveMatriz(matriz_completa)){          //caso o tabuleiro não continuar solúvel, o par em questão se torna visível
            matriz_completa[pares_nao_checados[n][0]][pares_nao_checados[n][1]]->setVisivel(true);
            matriz_completa[pares_nao_checados[n][2]][pares_nao_checados[n][3]]->setVisivel(true);
        }

        pares_nao_checados.erase(pares_nao_checados.begin() + n);
    }
}
