#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "game.h"

void title(void);
int choisir_difficulte(void);
int menu_principal(void);
const char* tileColor(int v);
void centerText(char *dest, int value);
void print_grille(Game *game);

#endif