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

    Plateau plateau = Plateau_create();
    char diff[10];
    scanf("%s", &diff);

    switch (*diff)
    {
    case 'f':
        printf("Vous avez choisi la difficulte facile\n");
        Bulid_Easy_Plateau(plateau);
        break;
    case 'm':
        printf("Vous avez choisi la difficulte moyenne\n");
        Bulid_Medium_Plateau(plateau);
        break;
    case 'd':
        printf("Vous avez choisi la difficulte difficile\n");
        Bulid_Hard_Plateau(plateau);
        break;
    default:
        printf("Difficulté non reconnue, difficulte facile choisie par défaut\n");
        break;
    }

    GameCore_Init_turn(plateau);
}

void GameCore_update(Plateau plateau)
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
        a = GameCore_CanPlay(plateau, 'z' ,  - 1, plateau.cube.j);
        if (a == 1)
        {
            plateau.board[plateau.cube.i][plateau.cube.j].value = 0;
            plateau.board[plateau.cube.i - 1][plateau.cube.j].value = 'n';
            Cube_behind(&plateau.cube);
        }
        // Déplacement vers le haut

        break;
    case 's':
        printf("Vous avez choisi de déplacer vers le bas\n");
        a = GameCore_CanPlay(plateau, 's', plateau.cube.i + 1, plateau.cube.j);
        if (a == 1)
        {
            plateau.board[plateau.cube.i][plateau.cube.j].value = 0;
            plateau.board[plateau.cube.i + 1][plateau.cube.j].value = 'n';
            Cube_front(&plateau.cube);
        }
        // Déplacement vers le bas
        break;
    case 'q':
        printf("Vous avez choisi de déplacer vers la gauche\n");
        a = GameCore_CanPlay(plateau,'q', plateau.cube.i, plateau.cube.j - 1);
        if (a == 1)
        {
            plateau.board[plateau.cube.i][plateau.cube.j].value = 0;
            plateau.board[plateau.cube.i][plateau.cube.j - 1].value = 'n';
            Cube_left(&plateau.cube);
        }
        // Déplacement vers la gauche
        break;
    case 'd':
        printf("Vous avez choisi de déplacer vers la droite\n");
        a = GameCore_CanPlay(plateau,'d', plateau.cube.i, plateau.cube.j + 1);
        if (a == 1)
        {
            plateau.board[plateau.cube.i][plateau.cube.j].value = 0;
            plateau.board[plateau.cube.i][plateau.cube.j + 1].value = 'n';
            Cube_right(&plateau.cube);
        }
        // Déplacement vers la droite
        break;
    
    case 'e':
        printf("Vous avez choisi de tourner vers la droite\n");
        a = GameCore_CanRotate(plateau);
        if (a == 1)
        {
            Cube_rota_right(&plateau.cube);
        }
        // Rotaion vers la droite
        break;
    case 'a':
        printf("Vous avez choisi de tourner vers la gauche\n");
        a = GameCore_CanRotate(plateau);
        if (a == 1)
        {
            Cube_rota_left(&plateau.cube);
        }
        // Rotation vers la gauche
        break;
    
    default:
        break;
    }
}

void GameCore_Init_turn(Plateau plateau)
{
    do
    {
    GameCore_update(plateau);
    } while (!GameCore_CanFinish(plateau));
    GameCore_Finish();
}

bool GameCore_CanPlay(Plateau plateau, char direction , int i, int j)
{
    int futur_code;
    switch (direction)
    {
    case 'z':
        futur_code = plateau.cube.behind->code;
        break;
    case 's':
        futur_code = plateau.cube.front->code;
        break;
    case 'q':
        futur_code = plateau.cube.left->code;
        break;
    case 'd':
        futur_code = plateau.cube.right->code;
        break;
    }

    if (i > 3 || i < 0 || j > 4 || j < 0)
    {
        //printf("torlolo");
        return false;
    }
    if (plateau.board[i][j].value == 'd') // on tombe sur un diamans
    {
        if (futur_code == 1 && plateau.cube.has_key == false)
        {
            return true;
        }
        return false;
    }
    if (plateau.board[i][j].value == 'k') // on tombe sur la clé
    {
        if (futur_code == 1 )
        {
            plateau.cube.has_key = true;
            plateau.board[i][j].value = 0;
            return true;
        }
        return false;
    }
    if (plateau.board[i][j].value == 'h') // on tombe sur le fantôme
    {
        if (futur_code == 2)
        {
            plateau.cube.has_hache = true;
            plateau.board[i][j].value = 0;
            Delete_pawn(plateau, 'f');
            return true;
        }
        return false;
    }
    if (plateau.board[i][j].value == 0 || plateau.board[i][j].value == '.')
    {
        return true;
    }
    return false;
}

bool GameCore_CanRotate(Plateau plateau)
{
    int i = plateau.cube.i;
    int j = plateau.cube.j;
    if (plateau.cube.under->code == 3)
    {
        //vérifier qu'il y a pas de boite ('b') autour
        if (i - 1 >= 0)
        {
            if (plateau.board[i-1][j].value == 'b')
            {
                return false;
            }
        }
        if (i - 1 < 4)
        {
            if (plateau.board[i+1][j].value == 'b')
            {
                return false;
            }
        }
        if (j - 1 >= 0)
        {
            if (plateau.board[i][j-1].value == 'b')
            {
                return false;
            }
        }
        if (j + 1 < 5)
        {
            if (plateau.board[i][j+1].value == 'b')
            {
                return false;
            }
        }
        return true;

    }
}

bool GameCore_CanFinish(Plateau plateau)
{
    if(plateau.cube.i == 0 && plateau.cube.j == 2)
    if (plateau.cube.behind->code == 5) // il a la tete devant la porte
    {
        if (Has_Key(&plateau.cube) == true)
        {
            return true;
        }
    }
    return false;
}

void GameCore_Finish()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("merci d'avoir joué\n");
    return;
}
