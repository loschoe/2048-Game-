#include "game.h"
#include "affichage.h"
#include "moteur.h"

int main(void)
{
    srand((unsigned int)time(NULL));
    SetConsoleOutputCP(CP_UTF8);

    Game *game = malloc(sizeof(Game));
    game->grille = NULL; 
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
                    printf("\n\033[1;32m+-------------------------------------+\n");
                    printf("|  VICTOIRE ! Vous avez atteint %d ! |\n", win_score);
                    printf("|  Score Final : %-20d |\n", game->score);
                    printf("+-------------------------------------+\033[0m\n");
                    printf("Appuyez sur ENTRÉE pour continuer...");
                    while (_getch() != 13);
                    break;
                }

                if (is_full(game) && !can_move(game))
                {
                    printf("\n\033[1;31m+-------------------------------------+\n");
                    printf("|  GAME OVER ! Plus de coups possibles|\n");
                    printf("|  Score Final : %-20d |\n", game->score);
                    printf("+-------------------------------------+\033[0m\n");
                    printf("Appuyez sur ENTRÉE pour continuer...");
                    while (_getch() != 13);
                    break;
                }

                if (_kbhit())
                {
                    int d = getInput();
                    if (d == 5) {
                        printf("\nRetour au menu principal...\n");
                        Sleep(1000);
                        break;
                    }
                    if (d != -1) move(game, d);
                }
            }
            free_grille(game);
        }
        else if (choix == 2)
        {
            difficulte = choisir_difficulte();
        }
        else if (choix == 3)
        {
            printf("\033[1;34mAu revoir !\033[0m\n");
            break;
        }
        else
        {
            printf("\033[1;31mChoix invalide.\033[0m\n");
            Sleep(1000);
        }
    }

    free(game);
    return 0;
}