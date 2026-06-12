#ifndef MOTEUR_H
#define MOTEUR_H

#include "game.h"

void alloc_grille(Game *game);
void free_grille(Game *game);
void init_grille(Game *game);
int getInput(void);
int is_full(Game *game);
int is_won(Game *game);
int can_move(Game *game);
int move(Game *game, int dir);

#endif