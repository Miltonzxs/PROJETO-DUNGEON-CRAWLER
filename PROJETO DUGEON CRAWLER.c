//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int vida = 3;

void limpartela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//void para inserir variaveis do mapa,player e texto.
void criarmapa(char **mapa, int vertical, int horizontal, int playerX, int playerY, char *nomemapa, int monstroX, int monstroY, int monstro2X, int monstro2Y, int aldeaoX, int aldeaoY){
    //codigo para centralizar o nome do mapa a partir do tamanho do mesmo.
    int comprimentonome = strlen(nomemapa);
    int espacototal = (horizontal * 3 - comprimentonome) / 2;
    int i;
    int j;
    for(i = 0; i < espacototal; i++) {
        printf(" ");
    }
        printf("%s\n\n", nomemapa);
        
        //código para imprimir o mapa na tela, linha por linha, e colocar o player no mapa.
        //função para desenhar mapa.
        for( i = 0; i < vertical; i++){
            for( j = 0; j < horizontal; j++){
                if(i == playerX && j == playerY) //verificar e imprimir posiçao do jogado.
                printf("@  ");//player
                else 
                if (i == monstroX && j == monstroY)
                printf("M  "); //primeiro monstro
                else
                if (i == monstro2X && j == monstro2Y)
                printf("N  "); //segundo monstro
                else
                if (i == aldeaoX && j == aldeaoY)
                printf("A  "); // aldeão
                else
                printf("%c  ", mapa[i][j]); //verificar e imprimir posiçao do mapa.
            }
            printf("\n"); //pular uma linha e comecar outra.
        }
}

//gerar paredes internas
void gerarParedeInterna(char **mapa, int inicioX, int inicioY, int tamanho, char direcao) {
	int i;
    for (i = 0; i < tamanho; i++) {
        if (direcao == 'H') { // Horizontal
            mapa[inicioX][inicioY + i] = '*';
        } else if (direcao == 'V') { // Vertical
            mapa[inicioX + i][inicioY] = '*';
        }
    }
}

//gerar espinhos
void gerarEspinhos(char **mapa, int inicioX, int inicioY, int quantidade, char direcao) {
	int i;
    for (i = 0; i < quantidade; i++) {
        if (direcao == 'H') { // Horizontal
            mapa[inicioX][inicioY + i] = '^';
        } else if (direcao == 'V') { // Vertical
            mapa[inicioX + i][inicioY] = '^';
        }
    }
}


//liberar da memória o mapa //função de limpeza
void liberarmapa(char **mapa, int vertical){
	int i;
    for( i = 0; i < vertical; i++){
    free(mapa[i]); //liberar cada linha do mapa de maneira individual
    }
    free(mapa); //liberar ponteiro principal
}


 //apenas para informa que em algum momemnto vai ter o mapa caverna.
void mapacaverna(int startX, int startY); 

void mapacaverna2(int startX, int startY);

void mapacaverna3(int startX, int startY);

//start(X e Y) são a posição V/H inicial do jogador.
//para desenhar e gerenciar o mapa da vila do jogo.
void mapavila(int startX, int startY){
    
//tamanho do mapa.
    int vertical = 10;
    int horizontal = 10;
    
    //alocar de maneira dinamica
    char **mapa = malloc(vertical * sizeof(char *));
    int i;
    for( i = 0; i < vertical; i++)
    mapa[i] = malloc(horizontal * sizeof(char));
    
    //preencher mapa. //função que cria paredes ao redor.
    int j;
    for( i = 0; i < vertical; i++){
        for( j = 0; j < horizontal; j++){
            if(i == 0 || i == vertical - 1 || j == 0 || j == horizontal - 1)
            mapa[i][j] = '*'; //preencher com asterisco
            else
            mapa[i][j] = ' '; //preencher com espaço
        }
    }
    
    int aldeaoX = 4;
    int aldeaoY = 4;
    
    //criar porta no mapa.
    mapa[0][5] = 'C';
    //definir posição inicial do jogador.
    int playerX = startX, playerY = startY;
    //guarda comando.
    char comando;
    
    while(1){
        //limpar o terminal para atualizar a tela conforme se move.
        limpartela();
        criarmapa(mapa, vertical, horizontal, playerX, playerY, "vila", -1, -1, -1, -1, aldeaoX, aldeaoY);
        
        scanf(" %c", &comando);
        
        //transformar letras minusculas em maiusculas.
        if(comando >= 'a') comando -= 32;
        //fechar jogo/sair do loop.
        if(comando == 'F') break;
        
        //movimentação do jogador.
        switch(comando){
    case 'W':
        if (playerX > 0 && mapa[playerX - 1][playerY] != '*' && !(playerX - 1 == aldeaoX && playerY == aldeaoY))
            playerX--;
        break;
    case 'S':
        if (playerX < vertical - 1 && mapa[playerX + 1][playerY] != '*' && !(playerX + 1 == aldeaoX && playerY == aldeaoY))
            playerX++;
        break;
    case 'A':
        if (playerY > 0 && mapa[playerX][playerY - 1] != '*' && !(playerX == aldeaoX && playerY - 1 == aldeaoY))
            playerY--;
        break;
    case 'D':
        if (playerY < horizontal - 1 && mapa[playerX][playerY + 1] != '*' && !(playerX == aldeaoX && playerY + 1 == aldeaoY))
            playerY++;
        break;
}
        
       if ((abs(playerX - aldeaoX) + abs(playerY - aldeaoY)) == 1) {
    printf("\nO aldeão diz: 'Bem-vindo à nossa vila! Tenha cuidado nas cavernas...'\n");
    printf("Pressione Enter para continuar...\n");
    while(getchar() != '\n');
    getchar();
}
        
        //verificar se o jogador interagiu com a porta.
        if(mapa[playerX][playerY] == 'C'){
            liberarmapa(mapa, vertical);
            mapacaverna(8, 1); //entrar pela parte inferior, pode mudar conforme prosegue o jogo.
            return;
        }
    }
    liberarmapa(mapa, vertical);
    printf("saindo do jogo\n");
}

//mapa 2

void mapacaverna(int startX, int startY){

int vertical = 10;
int horizontal = 10;

char **mapa = malloc(vertical * sizeof(char *));
int i,j;
for( i = 0; i < vertical; i++)
mapa[i] = malloc(horizontal * sizeof(char));

for( i = 0; i < vertical; i++){
    for( j = 0; j < horizontal; j++){
        if(i == 0 || i == vertical - 1 || j == 0 || j == horizontal - 1)
        mapa[i][j] = '*';
        else
        mapa[i][j] = ' ';
    }
}

//paredes internas horizontais
gerarParedeInterna(mapa, 3, 2, 6, 'H');
gerarParedeInterna(mapa, 6, 5, 3, 'H'); 

//paredes internas verticais
gerarParedeInterna(mapa, 2, 4, 1, 'V'); 
gerarParedeInterna(mapa, 7, 5, 2, 'V'); 
gerarParedeInterna(mapa, 4, 7, 2, 'V'); 

mapa[5][6] = 'C';
mapa[7][7] = 'P';

int playerX = startX, playerY = startY;
int chaveadquirida = 0;
char comando;

 while(1){
     
        limpartela();
        criarmapa(mapa, vertical, horizontal, playerX, playerY, "caverna", -1, -1, -1, -1, -1, -1);
        
        scanf(" %c", &comando);
        
        if(comando >= 'a') comando -= 32;
        if(comando == 'F') break;
        
        switch(comando){
            
           case 'W':
    if (playerX > 0 && mapa[playerX - 1][playerY] != '*') playerX--;
    break;
// Faça o mesmo para S, A, D:
case 'S':
    if (playerX < vertical - 1 && mapa[playerX + 1][playerY] != '*') playerX++;
    break;
case 'A':
    if (playerY > 0 && mapa[playerX][playerY - 1] != '*') playerY--;
    break;
case 'D':
    if (playerY < horizontal - 1 && mapa[playerX][playerY + 1] != '*') playerY++;
    break;
    
        }
        
        //interação com a chave e porta
        if(mapa[playerX][playerY] == 'C'){
            chaveadquirida = 1;
            mapa[playerX][playerY] = ' ';
            printf("voce adquiriu a chave\n");
            while(getchar() != '\n'); // limpa o buffer
            getchar(); // aguarda Enter do jogador
        }
        
        if(mapa[playerX][playerY] == 'P'){
            if(chaveadquirida){
                printf("voce conseguiu abrir a porta com a chave antiga\n");
                while(getchar() != '\n'); // limpa o buffer
                getchar(); // aguarda Enter do jogador
                liberarmapa(mapa, vertical);
                mapacaverna2(3, 4);
                return;
            }else{
                printf("voce precisará de uma chave para destrancar essa porta\n");
                while(getchar() != '\n'); // limpa o buffer
                getchar(); // aguarda Enter do jogador
            }
            
        }
        
    }
    
    liberarmapa(mapa, vertical);
    printf("saindo do jogo\n");
}

//mapa 3
void mapacaverna2(int startX, int startY){

int vertical = 20;
int horizontal = 20;
srand(time(NULL)); // gerador de números aleatórios

// posição inicial do monstro
int monstroX = 1, monstroY = 1;

char **mapa = malloc(vertical * sizeof(char *));
int i,j;
for( i = 0; i < vertical; i++)
mapa[i] = malloc(horizontal * sizeof(char));

for( i = 0; i < vertical; i++){
    for( j = 0; j < horizontal; j++){
        if(i == 0 || i == vertical - 1 || j == 0 || j == horizontal - 1)
        mapa[i][j] = '*';
        else
        mapa[i][j] = ' ';
    }
}

//paredes internas horizontais
gerarParedeInterna(mapa, 3, 1, 2, 'H');
gerarParedeInterna(mapa, 7, 3, 9, 'H');
gerarParedeInterna(mapa, 13, 3, 6, 'H');
gerarParedeInterna(mapa, 16, 5, 4, 'H');
gerarParedeInterna(mapa, 12, 10, 4, 'H');
gerarParedeInterna(mapa, 8, 14, 4, 'H');


//paredes internas verticais
gerarParedeInterna(mapa, 1, 17, 2, 'V'); 
gerarParedeInterna(mapa, 17, 14, 2, 'V');
gerarParedeInterna(mapa, 4, 12, 6, 'V');
gerarParedeInterna(mapa, 8, 4, 5, 'V');
gerarParedeInterna(mapa, 14, 3, 3, 'V');
gerarParedeInterna(mapa, 5, 16, 7, 'V');
gerarParedeInterna(mapa, 15, 10, 5, 'V');


//espinhos horizontais
gerarEspinhos(mapa, 16, 14, 5, 'H');
gerarEspinhos(mapa, 5, 7, 1, 'H');
gerarEspinhos(mapa, 3, 9, 1, 'H');
gerarEspinhos(mapa, 2, 4, 1, 'H');
gerarEspinhos(mapa, 16, 1, 1, 'H');
gerarEspinhos(mapa, 11, 2, 1, 'H');
gerarEspinhos(mapa, 12, 18, 1, 'H');
gerarEspinhos(mapa, 16, 12, 1, 'H');
gerarEspinhos(mapa, 5, 14, 1, 'H');
gerarEspinhos(mapa, 2, 12, 1, 'H');
gerarEspinhos(mapa, 14, 15, 1, 'H');
gerarEspinhos(mapa, 10, 6, 1, 'H');
gerarEspinhos(mapa, 10, 10, 1, 'H');
gerarEspinhos(mapa, 8, 8, 1, 'H');

mapa[18][16] = 'P';
mapa[15][4] = 'B';
mapa[5][18] = 'C';

int playerX = startX, playerY = startY;
int chaveadquirida = 0;
int botaoAtivado = 0; //variavel para o botão
char comando;

 while(1){
     
        limpartela();
        criarmapa(mapa, vertical, horizontal, playerX, playerY, "caverna2", monstroX, monstroY, -1, -1, -1, -1);
        
        scanf(" %c", &comando);
        
        if(comando >= 'a') comando -= 32;
        if(comando == 'F') break;
        
        switch(comando){
            
            case 'W':
    if (playerX > 0 && mapa[playerX - 1][playerY] != '*') playerX--;
    break;
case 'S':
    if (playerX < vertical - 1 && mapa[playerX + 1][playerY] != '*') playerX++;
    break;
case 'A':
    if (playerY > 0 && mapa[playerX][playerY - 1] != '*') playerY--;
    break;
case 'D':
    if (playerY < horizontal - 1 && mapa[playerX][playerY + 1] != '*') playerY++;
    break;
        }
        
        // MOVIMENTO DO MONSTRO (mais esperto e ainda bêbado)
int novoX = monstroX, novoY = monstroY;

if (rand() % 3 == 0) {
    // 1/3 das vezes: persegue o jogador com chance de erro
    int dx = playerX - monstroX;
    int dy = playerY - monstroY;

    if (abs(dx) > abs(dy)) {
        novoX += (dx > 0) ? 1 : -1;
        if (rand() % 4 == 0) novoY += (rand() % 3) - 1;
    } else {
        novoY += (dy > 0) ? 1 : -1;
        if (rand() % 4 == 0) novoX += (rand() % 3) - 1;
    }
} else {
    // 2/3 das vezes: anda aleatoriamente
    switch (rand() % 4) {
        case 0: novoX--; break;
        case 1: novoX++; break;
        case 2: novoY--; break;
        case 3: novoY++; break;
    }
}

// Só anda se não for parede e não for a posição do jogador
if (novoX >= 0 && novoX < vertical && novoY >= 0 && novoY < horizontal &&
    mapa[novoX][novoY] != '*') {
    monstroX = novoX;
    monstroY = novoY;
}

   // VERIFICA SE O MONSTRO MATOU O JOGADOR
if (monstroX == playerX && monstroY == playerY) {
    vida--;
    if (vida > 0) {
        printf("O monstro te pegou! Vidas restantes: %d\n", vida);
        playerX = startX;
        playerY = startY;
        while(getchar() != '\n'); getchar();
    } else {
        printf("Game Over!\n");
        exit(0);
    }
}

// Dentro do loop de jogo, após o movimento do jogador, verificar colisão:
if (mapa[playerX][playerY] == '^') { // se pisar em espinho
    vida--;
    if (vida > 0) {
        printf("Você pisou em um espinho! Vidas restantes: %d\n", vida);
        playerX = startX;
        playerY = startY;
        // opcional: pausa para o jogador ver a mensagem
        while(getchar() != '\n');
        getchar();
    } else {
        printf("Game Over!\n");
        exit(0);
    }
}
   
        //ir para a caverna 4.
        if(mapa[playerX][playerY] == 'C'){
            chaveadquirida = 1;
            mapa[playerX][playerY] = ' ';
            printf("voce adquiriu a chave\n");
            while(getchar() != '\n'); // limpa o buffer
            getchar(); // aguarda Enter do jogador
        }
        
        //interação com o botão
        if (mapa[playerX][playerY] == 'B' && !botaoAtivado) {
    botaoAtivado = 1;
    printf("Você apertou o botão. Algo se move ao longe...\n");
    mapa[playerX][playerY] = ' '; // para remover o B do mapa

    mapa[16][15] = ' '; // para liberar parede
    while(getchar() != '\n');
    getchar();
}

        if(mapa[playerX][playerY] == 'P'){
            if(chaveadquirida){
                printf("voce conseguiu abrir a porta com a chave antiga\n");
                 while(getchar() != '\n');
                 getchar();
                liberarmapa(mapa, vertical);
                mapacaverna3(3, 2);
                return;
            }else{
                printf("voce precisará de uma chave para destrancar essa porta\n");
                while(getchar() != '\n');
                getchar();
            }
        }
        
    }
    
    liberarmapa(mapa, vertical);
    printf("saindo do jogo\n");
}

//mapa 4
void mapacaverna3(int startX, int startY){

int vertical = 40;
int horizontal = 40;

int monstro2X = 18, monstro2Y = 7; // exemplo de posição inicial

char **mapa = malloc(vertical * sizeof(char *));
int i,j;
for( i = 0; i < vertical; i++)
mapa[i] = malloc(horizontal * sizeof(char));

for( i = 0; i < vertical; i++){
    for( j = 0; j < horizontal; j++){
        if(i == 0 || i == vertical - 1 || j == 0 || j == horizontal - 1)
        mapa[i][j] = '*';
        else
        mapa[i][j] = ' ';
    }
}

//paredes internas horizontais
gerarParedeInterna(mapa, 5, 3, 6, 'H'); 
gerarParedeInterna(mapa, 27, 7, 7, 'H');
gerarParedeInterna(mapa, 11, 10, 7, 'H');
gerarParedeInterna(mapa, 14, 17, 7, 'H');
gerarParedeInterna(mapa, 33, 32, 4, 'H');
gerarParedeInterna(mapa, 17, 34, 7, 'H');
gerarParedeInterna(mapa, 27, 34, 7, 'H');

//paredes internas verticais
gerarParedeInterna(mapa, 6, 6, 4, 'V');  // parede de posição vertical (6,6) até (6,9)
gerarParedeInterna(mapa, 1, 4, 2, 'V');
gerarParedeInterna(mapa, 28, 13, 12, 'V');
gerarParedeInterna(mapa, 28, 7, 6, 'V');
gerarParedeInterna(mapa, 33, 3, 7, 'V');
gerarParedeInterna(mapa, 6, 27, 5, 'V');
gerarParedeInterna(mapa, 23, 8, 4, 'V');
gerarParedeInterna(mapa, 14, 24, 7, 'V');
gerarParedeInterna(mapa, 8, 21, 7, 'V');
gerarParedeInterna(mapa, 25, 21, 9, 'V');
gerarParedeInterna(mapa, 20, 31, 8, 'V');
gerarParedeInterna(mapa, 28, 29, 12, 'V');

//espinhos horizontais
gerarEspinhos(mapa, 33, 4, 3, 'H');
gerarEspinhos(mapa, 12, 27, 5, 'H');
gerarEspinhos(mapa, 27, 28, 7, 'H');
gerarEspinhos(mapa, 17, 1, 5, 'H');
gerarEspinhos(mapa, 23, 4, 4, 'H');
gerarEspinhos(mapa, 33, 18, 7, 'H');
gerarEspinhos(mapa, 8, 3, 1, 'H');
gerarEspinhos(mapa, 12, 3, 1, 'H');
gerarEspinhos(mapa, 10, 5, 1, 'H');
gerarEspinhos(mapa, 6, 1, 1, 'H');
gerarEspinhos(mapa, 12, 6, 1, 'H');
gerarEspinhos(mapa, 15, 7, 1, 'H');
gerarEspinhos(mapa, 3, 6, 1, 'H');
gerarEspinhos(mapa, 4, 8, 1, 'H');
gerarEspinhos(mapa,3, 10, 1, 'H');
gerarEspinhos(mapa,6, 10, 1, 'H');
gerarEspinhos(mapa, 3, 12, 1, 'H');
gerarEspinhos(mapa, 4, 14, 1, 'H');
gerarEspinhos(mapa, 7, 15, 1, 'H');
gerarEspinhos(mapa, 15, 10, 1, 'H');
gerarEspinhos(mapa, 15, 12, 1, 'H');
gerarEspinhos(mapa, 17, 11, 1, 'H');
gerarEspinhos(mapa, 20, 14, 1, 'H');
gerarEspinhos(mapa, 5, 20, 1, 'H');
gerarEspinhos(mapa, 3, 22, 1, 'H');
gerarEspinhos(mapa, 7, 24, 1, 'H');
gerarEspinhos(mapa, 3, 27, 1, 'H');
gerarEspinhos(mapa, 7, 29, 1, 'H');
gerarEspinhos(mapa, 9, 31, 1, 'H');
gerarEspinhos(mapa, 8, 34, 1, 'H');
gerarEspinhos(mapa, 12, 35, 1, 'H');
gerarEspinhos(mapa, 18, 29, 1, 'H');
gerarEspinhos(mapa, 16, 26, 1, 'H');
gerarEspinhos(mapa, 17, 20, 1, 'H');
gerarEspinhos(mapa, 19, 23, 1, 'H');
gerarEspinhos(mapa, 19, 11, 1, 'H');
gerarEspinhos(mapa, 22, 15, 1, 'H');
gerarEspinhos(mapa, 12, 16, 1, 'H');
gerarEspinhos(mapa, 25, 20, 1, 'H');
gerarEspinhos(mapa, 31, 16, 1, 'H');
gerarEspinhos(mapa, 35, 18, 1, 'H');
gerarEspinhos(mapa, 36, 21, 1, 'H');
gerarEspinhos(mapa, 37, 25, 1, 'H');
gerarEspinhos(mapa, 35, 26, 1, 'H');
gerarEspinhos(mapa, 30, 5, 1, 'H');
gerarEspinhos(mapa, 26, 3, 1, 'H');
gerarEspinhos(mapa, 34, 2, 1, 'H');
gerarEspinhos(mapa, 35, 6, 1, 'H');
gerarEspinhos(mapa, 30, 10, 1, 'H');
gerarEspinhos(mapa, 35, 15, 1, 'H');
gerarEspinhos(mapa, 32, 9, 1, 'H');
gerarEspinhos(mapa, 37, 12, 1, 'H');
gerarEspinhos(mapa, 21, 37, 1, 'H');
gerarEspinhos(mapa, 24, 33, 1, 'H');
gerarEspinhos(mapa, 26, 35, 1, 'H');
gerarEspinhos(mapa, 23, 34, 1, 'H');
gerarEspinhos(mapa, 4, 35, 1, 'H');
gerarEspinhos(mapa, 7, 37, 1, 'H');
gerarEspinhos(mapa, 32, 36, 1, 'H');
gerarEspinhos(mapa, 37, 33, 1, 'H');
gerarEspinhos(mapa, 30, 32, 1, 'H');
gerarEspinhos(mapa, 30, 32, 1, 'H');
gerarEspinhos(mapa, 29, 17, 1, 'H');
gerarEspinhos(mapa, 36, 9, 1, 'H');

//espinhos verticais
gerarEspinhos(mapa, 22, 17, 6, 'V');
gerarEspinhos(mapa, 11, 9, 7, 'V');
gerarEspinhos(mapa, 26, 26, 7, 'V');
gerarEspinhos(mapa, 1, 18, 7, 'V');
gerarEspinhos(mapa, 5, 12, 7, 'V');
gerarEspinhos(mapa, 33, 31, 7, 'V');
gerarEspinhos(mapa, 1, 31, 7, 'V');

mapa[29][12] = 'P';
mapa[8][33] = 'C';
mapa[30][33] = 'B';
mapa[2][20] = 'T'; // Teleporte A
mapa[30][30] = 'T'; // Teleporte B

int playerX = startX, playerY = startY;
int chaveadquirida = 0;
int botaoAtivado = 0;
char comando;

 while(1){
     
        limpartela();
        criarmapa(mapa, vertical, horizontal, playerX, playerY, "caverna3", -1, -1, monstro2X, monstro2Y, -1, -1);
        
        printf("T = Teleporte\n");
        
        scanf(" %c", &comando);
        
        if(comando >= 'a') comando -= 32;
        if(comando == 'F') break;
        
        switch(comando){
            
            case 'W':
    if (playerX > 0 && mapa[playerX - 1][playerY] != '*') playerX--;
    break;
case 'S':
    if (playerX < vertical - 1 && mapa[playerX + 1][playerY] != '*') playerX++;
    break;
case 'A':
    if (playerY > 0 && mapa[playerX][playerY - 1] != '*') playerY--;
    break;
case 'D':
    if (playerY < horizontal - 1 && mapa[playerX][playerY + 1] != '*') playerY++;
    break;
        }
        
    // MOVIMENTO DO MONSTRO 2 (mais inteligente e com visão aumentada)
int distanciaX = abs(playerX - monstro2X);
int distanciaY = abs(playerY - monstro2Y);
int alcanceVisao = 12; // <-- Aumente aqui o alcance de visão do monstro2

int novoX2 = monstro2X;
int novoY2 = monstro2Y;

if (distanciaX + distanciaY <= alcanceVisao) {
    // Está dentro da visão, então persegue o jogador
    if (abs(playerX - monstro2X) > abs(playerY - monstro2Y)) {
        novoX2 += (playerX > monstro2X) ? 1 : -1;
    } else {
        novoY2 += (playerY > monstro2Y) ? 1 : -1;
    }
    
    // Pequena chance de erro para não ser impossível fugir
    if (rand() % 7 == 0) {
        switch (rand() % 4) {
            case 0: novoX2--; break;
            case 1: novoX2++; break;
            case 2: novoY2--; break;
            case 3: novoY2++; break;
        }
    }
    
} else {
    // Fora da visão, anda aleatoriamente
    switch (rand() % 4) {
        case 0: novoX2--; break;
        case 1: novoX2++; break;
        case 2: novoY2--; break;
        case 3: novoY2++; break;
    }
}

// Verifica se pode andar
if (novoX2 >= 0 && novoX2 < vertical && novoY2 >= 0 && novoY2 < horizontal &&
    mapa[novoX2][novoY2] != '*' && mapa[novoX2][novoY2] != '^') {
    monstro2X = novoX2;
    monstro2Y = novoY2;
}

 //monstro matou o player
if (monstro2X == playerX && monstro2Y == playerY) {
    vida--;
    if (vida > 0) {
        printf("O monstro te pegou! Vidas restantes: %d\n", vida);
        playerX = startX;
        playerY = startY;
        while(getchar() != '\n'); getchar();
    } else {
        printf("Game Over!\n");
        exit(0);
    }
}
        
    //teleporte
    
        if ((playerX == 2 && playerY == 20)) {
    playerX = 30;
    playerY = 30;
    printf("Você usou o teleporte!\n");
    getchar();
} else if ((playerX == 30 && playerY == 30)) {
    playerX = 2;
    playerY = 20;
    printf("Você usou o teleporte!\n");
    getchar();
}
        
       // Dentro do loop de jogo, após o movimento do jogador, verificar colisão:
if (mapa[playerX][playerY] == '^') { // se pisar em espinho
    vida--;
    if (vida > 0) {
        printf("Você pisou em um espinho! Vidas restantes: %d\n", vida);
        playerX = startX;
        playerY = startY;
        // opcional: pausa para o jogador ver a mensagem
        while(getchar() != '\n');
        getchar();
    } else {
        printf("Game Over!\n");
        exit(0);
    }
}
        
        //interação com a chave e porta
        if(mapa[playerX][playerY] == 'C'){
            chaveadquirida = 1;
            mapa[playerX][playerY] = ' ';
            printf("voce adquiriu a chave\n");
            while(getchar() != '\n');
            getchar();
        }
        
        if (mapa[playerX][playerY] == 'B' && !botaoAtivado) {
    botaoAtivado = 1;
    printf("Você apertou o botão. Algo se move ao longe...\n");
    mapa[playerX][playerY] = ' '; // para remover o B do mapa

    mapa[33][5] = ' '; // para liberar parede
    while(getchar() != '\n');
    getchar();
         }
        
         if(mapa[playerX][playerY] == 'P'){
            if(chaveadquirida){
                 limpartela();
            printf("Parabéns! Você terminou o jogo!\n");
            printf("Obrigado por jogar.\n");
            printf("CONTINUA...\n");
            while(getchar() != '\n');
            getchar();

        liberarmapa(mapa, vertical);
        exit(0); // encerra o programa
        }else{
        printf("voce precisará de uma chave para destrancar essa porta\n");
        while(getchar() != '\n');
        getchar();
    }
        }

}
      liberarmapa(mapa, vertical);
    printf("saindo do jogo\n");
    return;  
 }

int main() {
    
    char escolha = 0;

    while (escolha != 'f') {
        printf("\n\n");
        printf("\t\t###        ###    ###   ###          ###      ########   ##############    ###       ############\n");
        printf("\t\t###        ###    ###   ####         ###     ###    ###       ###          ###     ####\n");
        printf("\t\t###        ###    ###   #####        ###    ###      ###      ###          ###    ###\n");
        printf("\t\t###        ###    ###   ######       ###    ###      ###      ###          ###    ###\n");
        printf("\t\t###        ###    ###   ### ###      ###    ###      ###      ###          ###    ###\n");
        printf("\t\t###        ###    ###   ###  ###     ###    ############      ###          ###    ###\n");
        printf("\t\t###        ###    ###   ###   ###    ###    ###      ###      ###          ###    ###\n");
        printf("\t\t###        ###    ###   ###    ###   ###    ###      ###      ###          ###    ###\n");
        printf("\t\t###        ###    ###   ###      ### ###    ###      ###      ###          ###    ###\n");
        printf("\t\t########   ##########   ###       ######    ###      ###      ###          ###     ####\n");
        printf("\t\t########    ########    ###        #####    ###      ###      ###          ###        ##########\n\n");
        printf("\t\t\t\t\t\t\tJogar\n\n");
        printf("\t\t\t\t\t\t\tCreditos\n\n");
        printf("\t\t\t\t\t\t\tTutorial\n\n");
        printf("\t\t\t\t\t\t\tSair/Fechar\n\n");

        printf("\t\tteclas de interacao: j (para jogar), c (para creditos), t (para tutorial) e f (para sair/fechar.)\n\n");
        scanf(" %c", &escolha);

        switch (escolha) {
            case 'j':
                system("cls");
                printf("\ncarregando...\n");
                // Chama a função do mapa, começa na posição (1,1)
                mapavila(8, 5);
                break;

            case 'c':
               system("cls");
                printf("criadores:\nRonald Bruno\nTayron Reis\nThiago Luciano\nJose Milton\n");
                break;

            case 't':
                system("cls");
                printf("SIMBOLOS\n");
                printf("@: Simbolo que representa o jogador.\n");
                printf("A: Simbolo que representa um NPC.\n");
                printf("*: Simbolo que representa uma parede, o jogador nao pode passar pela parede.\n");
                printf("C: Simbolo que representa a chave para abrir a porta.\n");
                printf("P: Simbolo que representa a porta fechada.\n");
                printf("B: Simbolo que representa um botao que o jogador pode interagir.\n");
                printf("^: Simbolo que representa um espinho, reinicia fase.\n");
                printf("T: Simbolo que representa um teletransporte.\n");
                printf("M: Monstro nivel 1 (movimento aleatório).\n");
                printf("N: Monstro nivel 2 (segue o jogador).\n");
                printf("CONTROLES: W, A, S, D para mover e E para interagir.\n");
                break;

            case 'f':
               system("cls");
                printf("\nencerrando...\n");
                break;

            default:
                printf("opcao invalida\n");
                break;
        }

        if (escolha != 'f') {
            printf("\nDigite qualquer tecla e pressione ENTER para continuar: ");
            scanf(" %c", &escolha);
            system("cls");
        }
    }
    
    return 0;
    
}