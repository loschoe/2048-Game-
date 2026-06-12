#include "affichage.h"

void clean_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void title(void) {
    printf("\033[1;34m"
"\n"
"██████╗  ██████╗ ██╗  ██╗ █████╗      ██████╗  █████╗ ███╗   ███╗███████╗\n"
"╚════██╗██╔═████╗██║  ██║██╔══██╗    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n"
" █████╔╝██║██╔██║███████║╚█████╔╝    ██║  ███╗███████║██╔████╔██║█████╗  \n"
"██╔═══╝ ████╔╝██║╚════██║██╔══██╗    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n"
"███████╗╚██████╔╝     ██║╚█████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n"
"╚══════╝ ╚═════╝      ╚═╝ ╚════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n"
"\n"
"\033[0m");
}

int choisir_difficulte(void) {
    int choix;
    system("cls");
    title();
    
    printf("\033[1;34m+---------------------------------+\n");
    printf("|     CHOIX DE LA DIFFICULTÉ      |\n");
    printf("+---------------------------------+\n");
    printf("|  1 - Standard (4x4)             |\n");
    printf("|  2 - Medium   (5x5)             |\n");
    printf("|  3 - Hard     (8x8)             |\n");
    printf("+---------------------------------+\n");
    printf("> \033[0m");

    fflush(stdout);
    
    if (scanf("%d", &choix) != 1) choix = 1;
    clean_stdin();

    switch (choix) {
        case 1: return size_standard;
        case 2: return size_medium;
        case 3: return size_hard;
        default:
            printf("\033[1;31mChoix invalide, difficulté Standard sélectionnée.\033[0m\n");
            Sleep(1000);
            return size_standard;
    }
}

int menu_principal(void) {
    int choix;
    system("cls");
    title();

    printf("\033[1;34m+----- MENU PRINCIPAL -----+\n");
    printf("| 1 - JOUER                |\n");
    printf("+--------------------------+\n");
    printf("| 2 - Choisir la difficulté|\n");
    printf("+--------------------------+\n");
    printf("| 3 - Quitter              |\n");
    printf("+--------------------------+\n");
    printf("> \033[0m");

    fflush(stdout);

    if (scanf("%d", &choix) != 1) choix = -1;
    clean_stdin();
    return choix;
}

const char* tileColor(int v) {
    switch (v) {
        case 0: return "\033[0m";
        case 2: return "\033[30;47m";
        case 4: return "\033[30;43m";
        case 8: return "\033[37;41m";
        case 16: return "\033[37;45m";
        case 32: return "\033[37;44m";
        case 64: return "\033[37;42m";
        case 128: return "\033[30;103m";
        case 256: return "\033[30;102m";
        case 512: return "\033[30;106m";
        case 1024: return "\033[30;105m";
        case 2048: return "\033[30;101m";
        default: return "\033[30;107m";
    }
}

void centerText(char *dest, int value) {
    if (value == 0) {
        sprintf(dest, "      ");
        return;
    }
    char tmp[10];
    sprintf(tmp, "%d", value);
    int len = (int)strlen(tmp);
    int left = (6 - len) / 2;
    int right = 6 - len - left;
    sprintf(dest, "%*s%s%*s", left, "", tmp, right, "");
}

void print_grille(Game *game) {
    system("cls");
    title();
    printf("\033[1;37;44m SCORE: %d \033[0m\n\n", game->score);
    int s = game->size;

    printf("\033[1;34m+");
    for (int k = 0; k < s; k++) printf("------+");
    printf("\033[0m\n");

    for (int i = 0; i < s; i++) {
        printf("\033[1;34m|\033[0m");
        for (int j = 0; j < s; j++) {
            char centered[10];
            centerText(centered, game->grille[i][j]);
            printf("%s%s\033[0m\033[1;34m|\033[0m", tileColor(game->grille[i][j]), centered);
        }
        printf("\n\033[1;34m+");
        for (int k = 0; k < s; k++) printf("------+");
        printf("\033[0m\n");
    }
}