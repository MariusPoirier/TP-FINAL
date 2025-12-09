/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game_core.h"

void GameCore_Start()
{
    printf("Bonjour et bienvenue dans Rok passe partout !\n");
    printf("Preparer vous à jouer à un jeu dejanter\n");
    printf("Voulez vous commencez ? (Yes : y ou No : n)\n");
    char val;
    scanf("%c", &val);

    if (val == 'y')
    {
        printf("C'est parti !\n");
        GameCore_Create();
    }
    else
    {
        printf("A la prochaine !\n");
        return;
    }
}

void GameCore_Create()
{
    printf("Quelle difficulte voulez vous ? (facile = f, moyen = m, difficile = d)\n");

    Plateau* plate = Plateau_create();
    char diff[10];
    scanf("%s", &diff);

    switch (*diff)
    {
    case 'f':
        printf("Vous avez choisi la difficulte facile\n");
        Bulid_Easy_Plateau(plate);
        break;
    case 'm':
        printf("Vous avez choisi la difficulte moyenne\n");
        Bulid_Medium_Plateau(plate);
        break;
    case 'd':
        printf("Vous avez choisi la difficulte difficile\n");
        Bulid_Hard_Plateau(plate);
        break;
    default:
        printf("Difficulté non reconnue, difficulte facile choisie par défaut\n");
        break;
    }

    GameCore_Init_turn(plate);
}

void GameCore_update(Plateau* plateau)
{
    Print_plateau(plateau);
    char input=0;
    printf("Quel deplacement voulez vous faire ? (z = haut, s = bas, q = gauche, d = droite, a = rotation à gauche , e = roation à droite)\n");
    scanf(" %c", &input);

    int a;

    switch (input)
    {
    case 'z':
        printf("Vous avez choisi de déplacer vers le haut\n");
        a = GameCore_CanPlay(plateau, plateau->cube->i - 1, plateau->cube->j);
        if (a == 1)
        {
            plateau->plate[plateau->cube->i][plateau->cube->j] = 0;
            plateau->plate[plateau->cube->i - 1][plateau->cube->j] = 'n';
            Cube_behind(plateau->cube);
        }
        // Déplacement vers le haut

        break;
    case 's':
        printf("Vous avez choisi de déplacer vers le bas\n");
        a = GameCore_CanPlay(plateau, plateau->cube->i + 1, plateau->cube->j);
        if (a == 1)
        {
            plateau->plate[plateau->cube->i][plateau->cube->j] = 0;
            plateau->plate[plateau->cube->i + 1][plateau->cube->j] = 'n';
            Cube_front(plateau->cube);
        }
        // Déplacement vers le bas
        break;
    case 'q':
        printf("Vous avez choisi de déplacer vers la gauche\n");
        a = GameCore_CanPlay(plateau, plateau->cube->i, plateau->cube->j-1);
        if (a == 1)
        {
            plateau->plate[plateau->cube->i][plateau->cube->j] = 0;
            plateau->plate[plateau->cube->i][plateau->cube->j - 1] = 'n';
            Cube_left(plateau->cube);
        }
        // Déplacement vers la gauche
        break;
    case 'd':
        printf("Vous avez choisi de déplacer vers la droite\n");
        a = GameCore_CanPlay(plateau, plateau->cube->i, plateau->cube->j+1);
        if (a == 1)
        {
            plateau->plate[plateau->cube->i][plateau->cube->j] = 0;
            plateau->plate[plateau->cube->i][plateau->cube->j + 1] = 'n';
            Cube_right(plateau->cube);
        }
        // Déplacement vers la droite
        break;
    /*
    case 'e':
        printf("Vous avez choisi de tourner vers la droite\n");
        a = GameCore_CanRotate(plateau, plateau->cube->i, plateau->cube->j + 1);
        if (a == 1)
        {
            plateau->plate[plateau->cube->i][plateau->cube->j] = 0;
            plateau->plate[plateau->cube->i][plateau->cube->j + 1] = 'n';
            Cube_right(plateau->cube);
        }
        // Déplacement vers la droite
    case 'a':
        printf("Vous avez choisi de tourner vers la gauche\n");
        a = GameCore_CanRotate(plateau, plateau->cube->i, plateau->cube->j + 1);
        if (a == 1)
        {
            plateau->plate[plateau->cube->i][plateau->cube->j] = 0;
            plateau->plate[plateau->cube->i][plateau->cube->j + 1] = 'n';
            Cube_right(plateau->cube);
        }
        // Déplacement vers la droite
    */
    default:
        break;
    }
}

void GameCore_Init_turn(Plateau *plateau)
{
    do
    {
    GameCore_update(plateau);
    } while (plateau->plate[0][2] != 'n');
}

bool GameCore_CanPlay(Plateau* plateau, int i, int j)
{
    if (i > 3 || i < 0 || j > 4 || j < 0)
    {
        printf("torlolo");
        return false;
    }
    if (plateau->plate[i][j] == 0 || plateau->plate[i][j] == '.')
    {
        return true;
    }
    if (plateau->plate[i][j] == 'd') // on tombe sur un diamans
    {
        // if face du bas = le trou
        //     -> true
        // else false
        return false;
    }
    return false;
}

bool GameCore_CanRotate(Plateau* plateau)
{
    int i = plateau->cube->i;
    int j = plateau->cube->j;
    if (plateau->cube->under->code == 3)
    {
        //vérifier qu'il y a pas de boite ('b') autour
        if (i - 1 >= 0)
        {
            if (plateau->plate[i][j] == 'b')
            {
                return false;
            }
        }
        if (i - 1 < 4)
        {
            if (plateau->plate[i][j] == 'b')
            {
                return false;
            }
        }
        if (j - 1 >= 0)
        {
            if (plateau->plate[i][j] == 'b')
            {
                return false;
            }
        }
        if (j + 1 < 5)
        {
            if (plateau->plate[i][j] == 'b')
            {
                return false;
            }
        }
        return true;

    }
}
