#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <assert.h>
#include <errno.h>

#define size_standard 4
#define size_medium 5
#define size_hard 8

#define win_score 2048

/* ------------------ STRUCTURE ------------------ */

typedef struct
{
    int size;
    int **grille;
    int score;
} Game;

/* ------------------ TITRE ------------------ */

void title()
{
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

/* ------------------ DIFFICULTÉ ------------------ */

int choisir_difficulte(void)
{
    int choix;
    system("cls");
    title();
    printf("\033[44;97m");
    printf("\033[1;34m+---------------------------------+\033[0m\n");
    printf("\033[1;34m|\033[0m \033[44;97m     CHOIX DE LA DIFFICULTÉ     \033[0m \033[1;34m|\033[0m\n");
    printf("\033[1;34m+---------------------------------+\033[0m\n");
    printf("\033[1;34m|\033[0m \033[44;97m 1 - Standard (4x4)              \033[0m \033[1;34m|\033[0m\n");
    printf("\033[1;34m+---------------------------------+\033[0m\n");
    printf("\033[1;34m|\033[0m \033[44;97m 2 - Medium   (5x5)              \033[0m \033[1;34m|\033[0m\n");
    printf("\033[1;34m+---------------------------------+\033[0m\n");
    printf("\033[1;34m|\033[0m \033[44;97m 3 - Hard     (8x8)              \033[0m \033[1;34m|\033[0m\n");
    printf("\033[1;34m+---------------------------------+\033[0m\n");
    printf("\033[44;97m> \033[0m");


    scanf("%d", &choix);

    switch (choix)
    {
        case 1: return size_standard;
        case 2: return size_medium;
        case 3: return size_hard;
        default:
            printf("Choix invalide, difficulté Standard sélectionnée.\n");
            return size_standard;
    }
}

/* ------------------ LOG ------------------ */

void write_log(const char *message)
{
    FILE *log = fopen("log.txt", "a");
    if (!log) return;

    time_t now = time(NULL);
    char *t = ctime(&now);
    if (t) t[strlen(t)-1] = '\0';

    fprintf(log, "[%s] %s\n", t ? t : "???", message);
    fclose(log);
}

/* ------------------ ALLOCATION ------------------ */

void alloc_grille(Game *game)
{
    game->grille = malloc(game->size * sizeof(int*));
    for (int i = 0; i < game->size; i++)
        game->grille[i] = calloc(game->size, sizeof(int));
}

/* ------------------ INPUT ------------------ */

int getInput(void)
{
    int k = _getch();

    if (k == 224)
    {
        k = _getch();
        switch (k)
        {
            case 72: return 0; // Haut
            case 80: return 1; // Bas
            case 75: return 2; // Gauche
            case 77: return 3; // Droite
        }
    }

    if (k == 27) return 5; // ESC

    return -1;
}

/* ------------------ INIT ------------------ */

void init_grille(Game *game)
{
    for (int i = 0; i < game->size; i++)
        for (int j = 0; j < game->size; j++)
            game->grille[i][j] = 0;

    for (int k = 0; k < 2; k++)
    {
        int i, j;
        do {
            i = rand() % game->size;
            j = rand() % game->size;
        } while (game->grille[i][j] != 0);

        game->grille[i][j] = (rand() % 2 + 1) * 2;
    }

    game->score = 0;
}

/* ------------------ CHECKS ------------------ */

int is_full(Game *game)
{
    for (int i = 0; i < game->size; i++)
        for (int j = 0; j < game->size; j++)
            if (game->grille[i][j] == 0)
                return 0;
    return 1;
}

int is_won(Game *game)
{
    for (int i = 0; i < game->size; i++)
        for (int j = 0; j < game->size; j++)
            if (game->grille[i][j] == win_score)
                return 1;
    return 0;
}

int can_move(Game *game)
{
    int s = game->size;

    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < s; j++)
        {
            if (game->grille[i][j] == 0) return 1;

            if (j+1 < s && game->grille[i][j] == game->grille[i][j+1]) return 1;
            if (i+1 < s && game->grille[i][j] == game->grille[i+1][j]) return 1;
        }
    }
    return 0;
}

/* ------------------ COULEURS ------------------ */

const char* tileColor(int v)
{
    switch (v)
    {
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

/* ------------------ CENTRAGE ------------------ */

void centerText(char *dest, int value)
{
    if (value == 0)
    {
        sprintf(dest, "      ");
        return;
    }

    char tmp[10];
    sprintf(tmp, "%d", value);

    int len = strlen(tmp);
    int left = (6 - len) / 2;
    int right = 6 - len - left;

    sprintf(dest, "%*s%s%*s", left, "", tmp, right, "");
}

/* ------------------ AFFICHAGE ------------------ */

void print_grille(Game *game)
{
    system("cls");
    title();

    printf("\033[37;44mScore: %d\033[0m\n\n", game->score);

    int s = game->size;

    printf("\033[34m+");
    for (int k = 0; k < s; k++)
        printf("------+");
    printf("\033[0m\n");

    for (int i = 0; i < s; i++)
    {
        printf("\033[34m|\033[0m");

        for (int j = 0; j < s; j++)
        {
            char centered[10];
            centerText(centered, game->grille[i][j]);

            printf("%s%s\033[0m\033[34m|\033[0m",
                   tileColor(game->grille[i][j]),
                   centered);
        }

        printf("\n\033[34m+");
        for (int k = 0; k < s; k++)
            printf("------+");
        printf("\033[0m\n");
    }
}


int menu_principal() {
    int choix;

    system("cls");
    title();

    printf("+----- MENU PRINCIPAL ------+\n");
    printf("| 1 - JOUER                 |\n");
    printf("+---------------------------+\n");
    printf("| 2 - Choisir la difficulté |\n");
    printf("+---------------------------+\n");
    printf("| 3 - Quiiter               |\n");
    printf("+---------------------------+\n");
    printf("> ");


    scanf("%d", &choix);
    fflush(stdin);

    return choix;
}
/* ------------------ MOUVEMENTS ------------------ */

int move(Game *game, int dir)
{
    int s = game->size;
    int moved = 0;

    int **prev = malloc(s * sizeof(int*));
    for (int i = 0; i < s; i++)
    {
        prev[i] = malloc(s * sizeof(int));
        memcpy(prev[i], game->grille[i], s * sizeof(int));
    }

    /* --- UP --- */
    if (dir == 0)
    {
        for (int j = 0; j < s; j++)
        {
            for (int i = 1; i < s; i++)
            {
                if (game->grille[i][j] != 0)
                {
                    int k = i;
                    while (k > 0 && game->grille[k-1][j] == 0)
                    {
                        game->grille[k-1][j] = game->grille[k][j];
                        game->grille[k][j] = 0;
                        k--;
                        moved = 1;
                    }
                    if (k > 0 && game->grille[k-1][j] == game->grille[k][j])
                    {
                        game->grille[k-1][j] *= 2;
                        game->score += game->grille[k-1][j];
                        game->grille[k][j] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }

    /* --- DOWN --- */
    else if (dir == 1)
    {
        for (int j = 0; j < s; j++)
        {
            for (int i = s-2; i >= 0; i--)
            {
                if (game->grille[i][j] != 0)
                {
                    int k = i;
                    while (k < s-1 && game->grille[k+1][j] == 0)
                    {
                        game->grille[k+1][j] = game->grille[k][j];
                        game->grille[k][j] = 0;
                        k++;
                        moved = 1;
                    }
                    if (k < s-1 && game->grille[k+1][j] == game->grille[k][j])
                    {
                        game->grille[k+1][j] *= 2;
                        game->score += game->grille[k+1][j];
                        game->grille[k][j] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }

    /* --- LEFT --- */
    else if (dir == 2)
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = 1; j < s; j++)
            {
                if (game->grille[i][j] != 0)
                {
                    int k = j;
                    while (k > 0 && game->grille[i][k-1] == 0)
                    {
                        game->grille[i][k-1] = game->grille[i][k];
                        game->grille[i][k] = 0;
                        k--;
                        moved = 1;
                    }
                    if (k > 0 && game->grille[i][k-1] == game->grille[i][k])
                    {
                        game->grille[i][k-1] *= 2;
                        game->score += game->grille[i][k-1];
                        game->grille[i][k] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }

    /* --- RIGHT --- */
    else if (dir == 3)
    {
        for (int i = 0; i < s; i++)
        {
            for (int j = s-2; j >= 0; j--)
            {
                if (game->grille[i][j] != 0)
                {
                    int k = j;
                    while (k < s-1 && game->grille[i][k+1] == 0)
                    {
                        game->grille[i][k+1] = game->grille[i][k];
                        game->grille[i][k] = 0;
                        k++;
                        moved = 1;
                    }
                    if (k < s-1 && game->grille[i][k+1] == game->grille[i][k])
                    {
                        game->grille[i][k+1] *= 2;
                        game->score += game->grille[i][k+1];
                        game->grille[i][k] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }

    /* --- NO MOVE --- */
    if (!moved)
    {
        for (int i = 0; i < s; i++)
            memcpy(game->grille[i], prev[i], s * sizeof(int));

        for (int i = 0; i < s; i++) free(prev[i]);
        free(prev);

        return 0;
    }

    /* --- ADD NEW TILE --- */
    int i, j;
    do {
        i = rand() % s;
        j = rand() % s;
    } while (game->grille[i][j] != 0);

    game->grille[i][j] = (rand() % 2 + 1) * 2;

    for (int i2 = 0; i2 < s; i2++) free(prev[i2]);
    free(prev);

    print_grille(game);
    return 1;
}

/* ------------------ MAIN ------------------ */

int main(void)
{
    srand((unsigned int)time(NULL));
    SetConsoleOutputCP(CP_UTF8);

    Game *game = malloc(sizeof(Game));
    int difficulte = size_standard; 

    while (1)
    {
        int choix = menu_principal();

        if (choix == 1)
        {
            game->size = difficulte;
            alloc_grille(game);
            init_grille(game);
            print_grille(game);

            while (1)
            {
                if (is_won(game))
                {
                    printf("\033[1;32mVous avez gagné !\033[0m\n");
                    break;
                }

                if (is_full(game) && !can_move(game))
                {
                    printf("\033[1;31mVous avez perdu !\033[0m\n");
                    break;
                }

                if (_kbhit())
                {
                    int d = getInput();

                    if (d == 5)
                    {
                        printf("Retour au menu...\n");
                        break;
                    }

                    if (d != -1)
                        move(game, d);
                }
            }

            for (int i = 0; i < game->size; i++)
                free(game->grille[i]);
            free(game->grille);
        }

        else if (choix == 2)
        {
            difficulte = choisir_difficulte();
        }

        else if (choix == 3)
        {
            printf("Au revoir !\n");
            break;
        }

        else
        {
            printf("Choix invalide.\n");
        }
    }

    free(game);
    return 0;
}
