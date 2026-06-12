#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define size_standard 4
#define size_medium 5
#define size_hard 8
#define win_score 2048

typedef struct
{
    int size;
    int **grille;
    int score;
} Game;

// Petite fonction utilitaire pour vider le tampon de saisie
void clean_stdin(void);

#endif