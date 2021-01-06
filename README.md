# EA872

# Madrugada dos Mortos

É um jogo no estilo bomberman em que você anda pelo mapa com um item (pá) escavando espaços do mapa(tumbas) e coletando minions para lutar contra os minions de outros players.

Para a primeira parte do projeto o grupo pretende criar um jogo em que o player dispute contra exércitos pré-definidos, já deixando pronta a jogabilidade principal de montar o exército e lutar contra outro exército, e depois adicionar a possibilidade de outro player criando um exército simultaneamente para a disputa final.

# Como jogar

Para ativar instância como servidor aperte E e como cliente(que vai jogar) aperte R. O cliente precisa configurar o endereço do ip do servidor escolhido no arquivo 'config/ip_remoto.ini'. Para jogar use as setas para se movimentar e segure a barra de espaço perto de um túmulo até a vida dele zerar para invocar um zumbi.

# Planejamento

Primeiro criaremos as classes do model responsáveis por armazenar os dados dos players, do mapa e das criaturas minions.
Testado isso faremos o view para carregar esses elementos na tela de computador com se possivel sprites simples(penso no estilo dos personagens do among us, deve ter uns legais na internet para usar).

Depois faremos o controler com as classes necessarias para os players poderem controlar os seus personagens e com a IA dos minions para eles atacarem seus inimigos. Que  seguir o mais próximo e atacar.

# Dependencias
sdl2 ttf:

sudo apt-get install libsdl2-ttf-dev

#para doxygen
sudo apt install graphviz
