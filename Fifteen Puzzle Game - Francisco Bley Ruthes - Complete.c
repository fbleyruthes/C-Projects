//By Francisco Bley Ruthes

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <conio.h> // Função getch()
#include <windows.h> // Função sleep para desacelerar os loops e melhorar a visualização

// Constantes
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

// Funções
void printSlowly (char *string, int delayMiliSec);
void copyMatrices (int matrice1[][4], int matrice2[][4]);
void printMatrice (int matrice[][4]);
void printVoidCaracter (int piece);
void shuffle (int matrice[][4], char *dif, int *pi0, int *pj0);
int userMovement (int matrice[][4], char movement, int *pi0, int *pj0, int attempts);
int equalMatrices (int matrice1[][4], int matrice2[][4]);
void victoryMsg (char *dif);

int main() { // Programa principal

    int M1[4][4], M[4][4] = {{1, 2, 3, 4}, // Matrizes
                             {5, 6, 7, 8},
                             {9,10,11,12},
                             {13,14,15,0}};

    char answer[3], difficult[8], u; // O último elemento da string é '\0'

    // Conversas
    char welcome[] = "Welcome to the Fifteen Puzzle Game! Are you ready?";
    char yesAnswer [] = "THAT'S THE SPIRIT!";
    char noAnswer [] = "Really? You have already pressed the play button....... Now we will play anyway!!! XD HAHAHA";
    char noNoAnswer []= "YES or NO, buddy?!";
    char selectDifficult [] = "Do you want to play the LADYBUG, the CHICKEN, the MONKEY or the GOAT level?";
    char noDifficult [] = "I'm not 'hearing' you! Could you 'SHOUT' the words 'LADYBUG', 'CHICKEN', 'MONKEY' or 'GOAT'?! 'O'";
    char controlsMsg [] = "You need to change the positions of the pieces next to each other to find the following configuration, soldier! :D";
    char controlsMsg2 [] = "Use the 'W', 'A', 'S' and 'D' buttons to solve the puzzle.";
    char shuffleTime [] = "Shuffling time...";
    char go [] = "1...2...3  GO!GO!GO!";
    char quitQuestion [] = "I'm starting to think this game is too hard for you. Do you want to quit?";
    char yesQuitAnswer [] = "Okey-Dokey! Bye :P";
    char noQuitAnswer [] = "'YEAH BUDDY, LIGHT WEIGHT BABY!' ~ Ronnie Coleman";

    // Contadores e ponteiros.
    int c1 = 0, a1 = 1, a2 = 1, i0 = 3, j0 = 3, *pi0, *pj0, attempts = 0;

    pi0 = &i0; // i0 e j0 são os índices da posição do 0.
    pj0 = &j0; // já o pi0 e pj0 são os ponteiros para i0 e j0.

    copyMatrices(M1, M); // Agora as matrizes possuem os mesmos valores
    // Pergunta para o usuário se ele está preparado.
    printSlowly(welcome, 50);
    printf("\n");
    while (a1 > 0) {
        printf("   ");
        scanf("%s", answer);
        // Aceita qualquer forma de escrita de 'yes' or 'no', com capslock e sem.
        if (strcmp(answer, "YES") == 0 || strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0 || strcmp(answer, "yEs") == 0 || strcmp(answer, "yeS") == 0 || strcmp(answer, "YEs") == 0 || strcmp(answer, "yES") == 0 || strcmp(answer, "YeS") == 0) {
            system("cls");
            printSlowly(yesAnswer, 40);
            a1 = 0;
        } else {
            if (strcmp(answer, "NO") == 0 || strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0 || strcmp(answer, "nO") == 0) {
                system("cls");
                printSlowly(noAnswer, 40);
                a1 = 0;
                
            } else {
                printSlowly(noNoAnswer, 40);
                printf("\n");
            }          
        }   
    }

    // Mostra os controles para o usuário (W, A, S, D).
    printSlowly(controlsMsg, 60);
    printMatrice(M1);
    printf("\n");
    printSlowly(controlsMsg2, 60);
    // Escolha da dificuldade do jogo.
    while (c1 == 0) {
        printSlowly(selectDifficult, 50); 
        printf("\n");
        printf("   ");
        scanf("%s", difficult);
        system("cls");
        if ((strcmp(difficult, "LADYBUG") != 0) && (strcmp(difficult, "CHICKEN") != 0) && (strcmp(difficult, "MONKEY") != 0) && (strcmp(difficult, "GOAT") != 0)) {
            printSlowly(noDifficult, 40);
            printf("\n");
        } else {
            c1 = 1;
        }
    }

    system("cls"); // Limpa o console.
    printSlowly(shuffleTime, 200); 
    shuffle(M1, difficult, pi0, pj0); // Ativa a função de embaralhamento
    printf("\n");
    printf("\n");
    printSlowly(go, 250); // Alerta o início da gameplay.
    M[0][0] = 1;

    while (equalMatrices(M1, M)) {  // Usuário toma as 'rédeas' até a função embaralhada se igualar à original.
        
        printf("\n");
        u = getch(); // Não precisa apertar ENTER, recebe 1 caracter e nao apresenta o que o usuário digitou.
        attempts = userMovement(M1, u, pi0, pj0, attempts); // A função retorna o número de tentativas e garante o movimento do usuário.
        system("cls");
        printf("\n"); 
        printf("\n"); 
        printf("   Attempts: %d\n", attempts); // Número de tentivas impresso na tela.
        printMatrice(M1); // A nova matriz com a escolha do usuário é fornecida.

        if (attempts == 50){ // Quando o número de tentativas chega 50, o jogo entrega a opção de saída.
            printf("\n");
            printSlowly(quitQuestion, 60);
            while (a2 > 0) {
                printf("\n");
                printf("   ");
                scanf("%s", answer);
                if (strcmp(answer, "YES") == 0 || strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0 || strcmp(answer, "yEs") == 0 || strcmp(answer, "yeS") == 0 || strcmp(answer, "YEs") == 0 || strcmp(answer, "yES") == 0 || strcmp(answer, "YeS") == 0) {
                    printSlowly(yesQuitAnswer, 40);
                    a2 = 0;
                    printf("\n");
                    printf("\n");
                    printf("   ");
                    system("pause");
                } else {
                    if (strcmp(answer, "NO") == 0 || strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0 || strcmp(answer, "nO") == 0) {
                        printSlowly(noQuitAnswer, 40);
                        a2 = 0;
                    } else {
                        printSlowly(noNoAnswer, 40);
                    }
                }
            }
        }   
    }
    
    printf("\n");
    printf("\n");
    printf("   ");
    victoryMsg(difficult); // Mensagem de vitória para cada dificuldade.
    printf("\n");
    printf("\n");
    printf("   ");
    system("pause");
    return 0;
}

void printSlowly (char *string, int delayMiliSec) { // Imprime os textos de forma mais lenta.

    unsigned int l;
    char go [21] = "1...2...3  GO!GO!GO!";

    printf("\n");
    if (strcmp(string, go) == 0) { // Ajusta a posição da mensagem do char 'go'
        printf("             ");
    } else {
        printf("   ");
    }
    for (l = 0; l < strlen(string); l++) {
                printf("%c", string[l]);
                Sleep(delayMiliSec); // Atrasa a velocidade do loop (milissegundos)
    }
}

void copyMatrices (int matrice1[][4], int matrice2[][4]) { // Copia os valores de uma matriz para outra de mesmo tamanho

    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            matrice1[i][j] = matrice2[i][j];
        }
    }
}

void printMatrice(int matrice[][4]) { // Imprime matriz

    int i, j, b;

    printf("\n");
    printf("\n");
    printf("              ");
    printf("%c%C", 201); // Caracteres da tabela ASCII extendida
    for (b = 1; b < 17; b++) { // Borda superior da matriz
        printf("%c%C", 205); 
    }
    printf("%c%C", 187);
    printf("\n");
    for (i = 0; i < 4; i++) { // Bordas direita e esquerda da matriz
        for (j = 0; j < 4; j++) {
            if (j == 0) {
                printf("              %c%C", 186);
                printVoidCaracter(matrice[i][j]);
            } else {
                if (j == 3) {
                	printVoidCaracter(matrice[i][j]);
                    printf("%c%C", 186);
                } else {
                	if (matrice[i][j]!=0)
                    	printVoidCaracter(matrice[i][j]);
                    else printf(" %c%C ", 219, 219);
                }
            }
        }
        printf("\n");
    }
    printf("              ");
    printf("%c%C", 200);
    for (b = 1; b < 17; b++){ // Borda inferior da matriz
        printf("%c%C", 205);
    }
    printf("%c%C", 188);
}

void printVoidCaracter (int piece){
	if (piece !=0 )
        printf(" %2d ", piece);
    else 
        printf(" %c%C ", 219, 219);
}

void shuffle (int matrice[][4], char *dif, int *pi0, int *pj0) { // Mistura os elementos da matriz aleatoriamente.

    int direction, subst, c = 0, i = 3, j = 3; // Posição inicial do VAZIO M[3][3], chamado de '0'.

    srand(time(NULL)); // Muda a semente do 'random' baseado na hora do sistema.

    if (strcmp(dif, "LADYBUG") == 0) {
        c = 2; // Número de embaralhamentos, trocas de posições.
    } else {
        if (strcmp(dif, "CHICKEN") == 0) {
            c = 15;
        } else {  
            if (strcmp(dif, "MONKEY") == 0) {
                c = 30;
            } else {
                c = 40;
            }
        }
    }
    // Loop de embaralhamentos  
    while (c > 0) {
        direction = rand() % 4; // Sorteia um dos numeros: 0, 1, 2 ou 3 já definidos como valores de constantes anteriormente.
        switch (direction) {
            case LEFT:
                if (j > 0) {
                    subst = matrice[i][j-1]; // O substituto guarda o valor antigo da posição que queremos ir.
                    matrice[i][j-1] = matrice[i][j]; // A posição que queremos ir recebe o valor da posição em que estamos.
                    matrice[i][j] = subst; // A posição em que estávamos recebe o valor do substituto.
                    j--; // Novo índice da posição do VAZIO, ou '0'.
                    if (j == *pj0) {
                    	c++; // Vai emabaralhar até o vazio não voltar para sua posição anterior
					}
                } else 
                    c++; // Adiciona 1 embaralhamento caso não possa obedecer a ação.
            break;
            case RIGHT:
                if (j < 3) {
                    subst = matrice[i][j+1];
                    matrice[i][j+1] = matrice[i][j];
                    matrice[i][j] = subst;
                    j++;
                    if (j == *pj0) {
                    	c++;
					}
                } else
                    c++;
            break;
            case UP:
                if (i > 0) {
                    subst = matrice[i-1][j];
                    matrice[i-1][j] = matrice[i][j];
                    matrice[i][j] = subst;
                    i--;
                    if (i == *pi0) {
                    	c++;
					}
                } else 
                    c++;
            break;
            case DOWN:
                if (i < 3) {
                    subst = matrice[i+1][j];
                    matrice[i+1][j] = matrice[i][j];
                    matrice[i][j] = subst;
                    i++;
                    if (i == *pi0) {
                    	c++;
					}
                } else
                    c++;
            break;
            default:
                printf("\nDIRECTION MIX ERROR\n"); // Ajudou a encontrar erros no desenvolvimento
        }
        c--;
        system("cls"); // Limpa o console
        printf("\n");
        printf("\n");
        printf("                Just a moment!\n");
        printMatrice(matrice); // Imprime a matriz
    }
    *pi0 = i; // Os índices i0 e j0 do valor 0 são atualizados.
    *pj0 = j;
}

int userMovement (int matrice[][4], char movement, int *pi0, int *pj0, int attempts) { // Movimento do usuário

    int subst, direction, i, j;
    i = *pi0;
    j = *pj0;

    // Recebe os valores do W, A, S e D para movimentação do VAZIO.
    if ((movement == 'a') || (movement == 'A')){ // Com CAPSLOCK e sem
        direction = 0;
    } else {
        if ((movement == 'd') || (movement == 'D')){
            direction = 1;
        } else {
            if ((movement == 'w') || (movement == 'W')){
                direction = 2;
            } else {
                if ((movement == 's') || (movement == 'S')){
                    direction = 3;
                }
            }
        }
    }
    // Mesmo trecho de código da função 'shuffle', mas agora os valores tem origem da decisão do usuário, não de um 'random'.
    switch (direction) {
            case LEFT:
                if (j > 0) {
                    subst = matrice[i][j-1];
                    matrice[i][j-1] = matrice[i][j];
                    matrice[i][j] = subst;
                    j--;
                    attempts += 1;
                }
            break;
            case RIGHT:
                if (j < 3) {
                    subst = matrice[i][j+1];
                    matrice[i][j+1] = matrice[i][j];
                    matrice[i][j] = subst;
                    j++;
                    attempts += 1;
                }
            break;
            case UP:
                if (i > 0) {
                    subst = matrice[i-1][j];
                    matrice[i-1][j] = matrice[i][j];
                    matrice[i][j] = subst;
                    i--;
                    attempts += 1;
                }
            break;
            case DOWN:
                if (i < 3) { 
                    subst = matrice[i+1][j];
                    matrice[i+1][j] = matrice[i][j];
                    matrice[i][j] = subst;
                    i++;
                    attempts += 1;
                }
            break;
            default:
                printf("\nUSER MOVEMENT ERROR\n");
    }
    *pi0 = i; // Os índices i0 e j0 do valor 0 são atualizados.
    *pj0 = j;
    return attempts; // Retorna o número de tentativas.
}

int equalMatrices (int matrice1[][4], int matrice2[][4]) { // Checa se todos os elementos das matrizes são iguais

    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (matrice1[i][j] != matrice2[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}

void victoryMsg (char *dif) {

    // Mensagens de vitória.
    char ladybugMsg [] = "Too easy! That's not fair... '-'";
    char chikenMsg [] = "Winner winner chicken dinner!";
    char monkeyMsg [] = "You got that monkey off your back! Well done! ^-^";
    char goatMsg [] = "Incredible! YOU ARE THE GOAT!!! *-*";

    if (strcmp(dif, "LADYBUG") == 0) {
        printSlowly(ladybugMsg, 50);
    } else {
        if (strcmp(dif, "CHICKEN") == 0) {
            printSlowly(chikenMsg, 50);
        } else {
            if (strcmp(dif, "MONKEY") == 0) {
                printSlowly(monkeyMsg, 50);
            } else {
                printSlowly(goatMsg, 50);
            } 
        }    
    }
}
