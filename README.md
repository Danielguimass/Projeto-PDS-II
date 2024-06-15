Neste projeto decidimos criar uma plataforma para se jogar o famoso jogo de quebra-cabeça Sudoku, que se baseia na colocação lógica de números em uma grande tabela 9x9.

Histórias de usuário que nos levaram a criar essa plataforma:
1. Como jogador, gostaria que existisse um menu com a possibilidade de escolher entre diferentes dificuldades.
2. Como jogador, gostaria que o tabuleiro do jogo fosse como uma matriz 9x9.
3. Como jogador, gostaria que ao final de uma partida mostrasse na tela o tempo total gasto na partida.
4. Como jogador, gostaria que o jogo guardasse e atualizasse as minhas estatísticas ao final de cada partida.
5. Como jogador, ao realizar uma jogada, gostaria que o jogo me informasse se a resposta está certa ou errada e, caso esteja errada, me informe quantas tentativas ainda me restam.
6. Como jogador, gostaria que tivesse um modo no qual eu corresse contra o tempo para finalizar corretamente o tabuleiro.

Hoje, além das funcionalidades descritas acima, nós já criamos muito mais!
Entre outros, o nosso programa já comporta um sistema de login e criar contas, um sistema de pontuação, que adiciona pontos a conta de um jogador ao final de cada partida, e um sistema de ranking, que durante o jogo é possível se consultar para ver quem são os 10 jogadores com a maior pontuação do momento!

Durante o desenvolvimento do nosso programa, nós também percebemos que, além de criar uma simples plataforma de jogos de Sudoku baseada em um estoque limitado de jogos de Sudoku, que nós conseguimos através de outras fontes, nós poderíamos deixar o nosso projeto muito maior, mais completo e mais divertido com a implementação de um gerador de Sudokus próprio.

Para isso, após estudarmos a respeito dos algoritmos na criação de uma partida de Sudoku, nós conseguimos com sucesso desenvolver um gerador completo. Este gerador é capaz de, primeiramente, criar uma solução completamente aleatória para uma grade 9x9 e, em seguida, remover uma quantidade específica de números da grade para formar um tabuleiro inicial, no qual terá uma quantidade de dicas suficiente para que o jogador consiga chegar na solução final esperada. Tal gerador de Sudokus atualmente está sendo utilizado na funcionalidade de Desafio Diário, que cria um Sudoku completamente novo a cada dia, que é disponibilizado igualmente para todos os jogadores que queiram jogá-lo.

Com isso, para o futuro, acreditamos que o nosso projeto ainda pode ser atualizado para comportar muito mais, como por exemplo, aumentar o estoque de jogos de Sudokus para cada dificuldade, criar sistemas de segurança e anti-trapaça para os jogadores, e criar uma interface gráfica para melhorar a jogabilidade do nosso programa.

Por fim, para começar a jogar no nosso programa agora mesmo, clone este repositório e digite os comandos "make builder", "make" e "make run" no seu terminal. Espero que goste do nosso projeto, e muito obrigado por ter lido até aqui!