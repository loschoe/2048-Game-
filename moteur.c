#include "moteur.h"
#include "affichage.h" // Nécessaire car move() appelle print_grille()

void alloc_grille(Game *game) {
    game->grille = malloc(game->size * sizeof(int*));
    for (int i = 0; i < game->size; i++)
        game->grille[i] = calloc(game->size, sizeof(int));
}

void free_grille(Game *game) {
    if (game->grille != NULL) {
        for (int i = 0; i < game->size; i++) free(game->grille[i]);
        free(game->grille);
        game->grille = NULL;
    }
}

int getInput(void) {
    int k = _getch();
    if (k == 224) {
        k = _getch();
        switch (k) {
            case 72: return 0; // Haut
            case 80: return 1; // Bas
            case 75: return 2; // Gauche
            case 77: return 3; // Droite
        }
    }
    if (k == 27) return 5; // ESC
    return -1;
}

void init_grille(Game *game) {
    for (int i = 0; i < game->size; i++)
        for (int j = 0; j < game->size; j++)
            game->grille[i][j] = 0;

    for (int k = 0; k < 2; k++) {
        int i, j;
        do {
            i = rand() % game->size;
            j = rand() % game->size;
        } while (game->grille[i][j] != 0);
        game->grille[i][j] = (rand() % 2 + 1) * 2;
    }
    game->score = 0;
}

int is_full(Game *game) {
    for (int i = 0; i < game->size; i++)
        for (int j = 0; j < game->size; j++)
            if (game->grille[i][j] == 0) return 0;
    return 1;
}

int is_won(Game *game) {
    for (int i = 0; i < game->size; i++)
        for (int j = 0; j < game->size; j++)
            if (game->grille[i][j] == win_score) return 1;
    return 0;
}

int can_move(Game *game) {
    int s = game->size;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (game->grille[i][j] == 0) return 1;
            if (j+1 < s && game->grille[i][j] == game->grille[i][j+1]) return 1;
            if (i+1 < s && game->grille[i][j] == game->grille[i+1][j]) return 1;
        }
    }
    return 0;
}

int move(Game *game, int dir) {
    int s = game->size;
    int moved = 0;
    int prev[size_hard][size_hard]; 

    for (int i = 0; i < s; i++)
        for(int j = 0; j < s; j++) 
            prev[i][j] = game->grille[i][j];

    /* --- UP --- */
    if (dir == 0) {
        for (int j = 0; j < s; j++) {
            for (int i = 1; i < s; i++) {
                if (game->grille[i][j] != 0) {
                    int k = i;
                    while (k > 0 && game->grille[k-1][j] == 0) {
                        game->grille[k-1][j] = game->grille[k][j];
                        game->grille[k][j] = 0;
                        k--;
                        moved = 1;
                    }
                    if (k > 0 && game->grille[k-1][j] == game->grille[k][j]) {
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
    else if (dir == 1) {
        for (int j = 0; j < s; j++) {
            for (int i = s-2; i >= 0; i--) {
                if (game->grille[i][j] != 0) {
                    int k = i;
                    while (k < s-1 && game->grille[k+1][j] == 0) {
                        game->grille[k+1][j] = game->grille[k][j];
                        game->grille[k][j] = 0;
                        k++;
                        moved = 1;
                    }
                    if (k < s-1 && game->grille[k+1][j] == game->grille[k][j]) {
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
    else if (dir == 2) {
        for (int i = 0; i < s; i++) {
            for (int j = 1; j < s; j++) {
                if (game->grille[i][j] != 0) {
                    int k = j;
                    while (k > 0 && game->grille[i][k-1] == 0) {
                        game->grille[i][k-1] = game->grille[i][k];
                        game->grille[i][k] = 0;
                        k--;
                        moved = 1;
                    }
                    if (k > 0 && game->grille[i][k-1] == game->grille[i][k]) {
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
    else if (dir == 3) {
        for (int i = 0; i < s; i++) {
            for (int j = s-2; j >= 0; j--) {
                if (game->grille[i][j] != 0) {
                    int k = j;
                    while (k < s-1 && game->grille[i][k+1] == 0) {
                        game->grille[i][k+1] = game->grille[i][k];
                        game->grille[i][k] = 0;
                        k++;
                        moved = 1;
                    }
                    if (k < s-1 && game->grille[i][k+1] == game->grille[i][k]) {
                        game->grille[i][k+1] *= 2;
                        game->score += game->grille[i][k+1];
                        game->grille[i][k] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }

    if (!moved) return 0;

    int i, j;
    do {
        i = rand() % s;
        j = rand() % s;
    } while (game->grille[i][j] != 0);

    game->grille[i][j] = (rand() % 2 + 1) * 2;
    print_grille(game);
    return 1;
}