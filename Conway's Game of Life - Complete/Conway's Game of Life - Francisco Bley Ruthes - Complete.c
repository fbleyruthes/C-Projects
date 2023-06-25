// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> 
#include <windows.h> 

// Functions
void neighborhoodCheck(int **M, int ie, int je, int rows, int columns);
void printMatrice(int **M, int rows, int columns, char *fileName); 
void printSlowly (char *string, int delayMiliSec);
int numberOfParticles (int **M, int rows, int columns);

int main () {
    // Import text files variables
    FILE *pFILE;
    char fileRow[100];
    char fileName[100];
    int z = 0, rows, columns, k, w;
    
    int c, i, j, c2 = 1, c3 = 1, times = 0, elementsAlive, spawns = 0;
    char magicChoice[100];
    int **p;
    // Interactions texts 
    char arc1[] = "trick1.vid";
    char arc2[] = "trick2.vid";
    char arc3[] = "trick3.vid";
    char msg1 [] = "The wizard is here...";
    char msg2 [] = "He wants to show you something. Do you want to see?";
    char chooseMagic[] = "The wizard knows some magic tricks. Say the trick you want...";
    char noChooseMagic[] = "Shhhhh... don't bother him... he only knows three magic tricks. Write 'trick1.vid', 'trick2.vid' or 'trick3.vid'";
    char TIMES[] = "How many times do you think he can cast the spell?";
    char readyMsg[] = "Be ready. It might blow your mind...";
    char noAnswer [] = "Are you afraid? I got it. At least say 'bye' to the wizard.";
    char noNoAnswer []= "He's waiting... YES or NO?";
    char bye [] = "'When you're leaving, the wizard stares at you from afar...' o_o";
    char noBye [] = "Just say 'bye', please. This guy is crazy.";
    char answer[100];
    char msg3 [] = "'Suddenly, the wizard misdirects the spell and explodes his own head...'";
    char msg4 [] = "'You're still there without understanding anything'";

    printSlowly(msg1, 100);
    printSlowly(msg2, 100);
    printf("\n");

    while (c2 > 0) {
        scanf("%s", answer);
        // Accept any kind of 'Yes' or 'No' writing
        if (strcmp(answer, "YES") == 0 || strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0 || strcmp(answer, "yEs") == 0 || strcmp(answer, "yeS") == 0 || strcmp(answer, "YEs") == 0 || strcmp(answer, "yES") == 0 || strcmp(answer, "YeS") == 0) {
            system("cls");
            printSlowly(chooseMagic, 100);
            while (c3 > 0){
                printf("\n");
                scanf("%s", &magicChoice); // The player can choose the file he wants
                if (strcmp(magicChoice, arc1) == 0){
                    strcpy(fileName, "trick1.vid");
                    c3 = 0;
                } else {
                    if (strcmp(magicChoice, arc2) == 0){
                        strcpy(fileName, "trick2.vid");
                        c3 = 0;
                    } else {
                        if (strcmp(magicChoice, arc3) == 0){
                            strcpy(fileName, "trick3.vid");
                            c3 = 0;
                        } else {
                            system("cls");
                            printSlowly(noChooseMagic, 100);
                        }
                    }
                }
            }
            c2 = 0;
        } else {
            if (strcmp(answer, "NO") == 0 || strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0 || strcmp(answer, "nO") == 0) {
                system("cls");
                printSlowly(noAnswer, 100);
                while (c3 > 0){
                    printf("\n");
                    scanf("%s", answer);
                    if (strcmp(answer, "bye") == 0 || strcmp(answer, "Bye") == 0 || strcmp(answer, "bYe") == 0 || strcmp(answer, "byE") == 0 || strcmp(answer, "BYe") == 0 ||strcmp(answer, "ByE") == 0 ||strcmp(answer, "bYE") == 0 ||strcmp(answer, "BYE") == 0){
                        system("cls");
                        printSlowly(bye, 150);
                        c3 = 1;
                        return 0;
                    } else {
                        system("cls");
                        printSlowly(noBye, 100);
                    }
                }
                c2 = 0;
            } else {
                printSlowly(noNoAnswer, 1);
                printf("\n");
            }          
        }   
    }

    // 'fopen' opens the file and 'r' is for read the text file
    pFILE = fopen (fileName, "r"); // We dont need to put the address, because the text file is on the same directory

    if (pFILE == NULL) { // Check if pFILE received the text file. If it not, it returns 'NULL'
   		printf ("\nERROR! File issues.\n");
   		exit(1);

    } else { // Now it is time to know the correct number of rows and columns
        fgets(fileRow, 100, pFILE); // 'fgets' reads the pFILE lines and fileRow becomes an array os characters
        rows = atoi(fileRow); // 'atoi' converts 'fileRow' content into an integer 

        fgets(fileRow, 100, pFILE);
        columns = atoi(fileRow);
    }
            
        // We need to alocate a memorie space for our matrice using malloc and calloc
        p = (int **) malloc(rows * sizeof(int *));
        for (z = 0; z < rows; z++){
            p[z] = (int *) calloc(columns, sizeof(int)); // 'Calloc' put 0's in all positions
        }

        for (int w = 0; w < rows; w++) {
            fgets(fileRow, 100, pFILE);
            for (int k = 0; k < columns; k++) {
                p[w][k] = fileRow[k] - '0'; // Our pointer receives de 'fileRow' elements transform into integers
            }
            printf("\n");
        }

    system("cls");
    printSlowly(TIMES,100);
    printf("\n");

    while (times <= 0) { // The player can choose the number of generations
        if (scanf("%d", &times) != 1 || times <= 0) { // 'time' can be only an integer
            system("cls");
            printSlowly(TIMES, 100);
            printf("\n");
            while (getchar() != '\n');  // Clean the 'buffer' if the player types a text insted of a number
        }
    }

    system("cls");
    printSlowly(readyMsg, 150);
    system("cls");

    for (c = 0; c < times; c++){
        spawns += 1;
        for (i = 0; i < rows; i++){
            for (j = 0; j < columns; j++)
                neighborhoodCheck(p, i, j, rows, columns); //Checks the element neighborhood
        }
        elementsAlive = numberOfParticles(p, rows, columns);
        system("cls");
        printf("'IT'S WORKING! THIS IS THE %dth TIME I'M DOING IT!'\n", spawns); // Print the number of generations
        printf("'LOOK HOW MANY PARTICLES! BY MY COUNT WE HAVE %d!'\n\n\n", elementsAlive);// Print the number of elements alive
        printf(" (\\.   \\      ,/)\n");
        printf("  \\(   |\\     )/\n");
        printf("  //\\  | \\   /\\\\\n");
        printf(" (/ /\\_#oo#_/\\ \\)\n");
        printf("  \\/\\  ####  /\\/\n");
        printf("       `##'\n");
        printf("\n");
        printf("       'SHAZAM!'\n");
        printf("\n");
        printMatrice(p, rows, columns, fileName);
        //Sleep(50);
    }

    system("cls");
    printSlowly(msg3,100);
    printSlowly(msg4,100);

    // free the memorie
    for (z = 0; z < rows; z++){
        free(p[i]); // Columns first
    }
    free (p); // Rows after
    p = NULL; 

    return 0;
}

void printSlowly (char *string, int delayMiliSec) { // Imprime os textos de forma mais lenta.

    unsigned int l;

    printf("\n");

    for (l = 0; l < strlen(string); l++) {
                printf("%c", string[l]);
                Sleep(delayMiliSec); // Atrasa a velocidade do loop (milissegundos)
    }
}


void neighborhoodCheck(int **M, int ie, int je, int rows, int columns){

    int i, j, alive = 0;
    
    for (i = ie - 1; i <= ie + 1; i++){ // Count the number of cells alive among the elements
         for (j = je - 1; j <= je + 1; j++){
            if ((i >= 0 && i < rows) && (j >= 0 && j < columns) && (M[i][j] == 1) && ((i != ie) || (j != je))){ 
                alive += 1; // Consider cells outside the matrice dead
            } 
        }
    }
    if (M[ie][je] == 0){
        if (alive == 3){
            M[ie][je] = 1;
        }
    } else {
        if (M[ie][je] == 1) {
            if ((alive < 2) || (alive > 3)){
                M[ie][je] = 0;
            } else {
                if ((alive == 2) || (alive == 3)){
                    M[ie][je] = 1;
                }
            }    
        }        
    }
}

int numberOfParticles(int **M, int rows, int columns) {

    int i, j, particles = 0;

    for (i = 0; i < rows; i++){ 
        for (j = 0; j < columns; j++){
            if (M[i][j] == 1){
                particles += 1;
            }
        }
    }
    return particles;
}

void printMatrice(int **M, int rows, int columns, char *fileName) {

    int i, j, h;

    srand(time(NULL));

    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            if (M[i][j] == 1){ // Different matrices and colors for different spells
                if (strcmp(fileName, "trick1.vid") == 0){
                    printf("\033[1;37m%c\033[0m", 219); // Print two times a rectangle to fit better on screen
                    printf("\033[1;37m%c\033[0m", 219);
                } else {
                    if (strcmp(fileName, "trick2.vid") == 0){
                        printf("\033[1;32m%c\033[0m", 219);
                        printf("\033[1;32m%c\033[0m", 219);
                    } else {
                        if (strcmp(fileName, "trick3.vid") == 0){
                            printf("\033[1;31m%c\033[0m", 219);
                            printf("\033[1;31m%c\033[0m", 219);
                        }
                    }
                } 
            } else {
                printf("\033[30m%c\033[0m", 176);
                printf("\033[30m%c\033[0m", 176);
            }
        }
        printf("\n");
    }
}
