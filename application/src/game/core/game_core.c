/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game_core.h"


void GameCore_Create()
{
    //todo séléction
    Plateau plateau = Plateau_2();
    Print_plateau(plateau);
    GameCore_Loop(plateau);

}

void GameCore_Loop(Plateau plateau)
{
    while (!GameCore_CanFinish(plateau))
    {
        GameCore_update(&plateau);
    }
    //GameCore_Finish();
}

void GameCore_update(Plateau* plateau)
{
    // Faudra gérer ler inputs
    char input;
    scanf("%c", &input);
    switch (input)
    {
    case 'q':
        if (ASSERT_LEFT(*plateau))
        {
            Cube_left(&plateau->cube);
            Print_plateau(*plateau);

        }
        break;
    case 'd':
        if (ASSERT_RIGHT(*plateau))
        {
            Cube_right(&plateau->cube);
            Print_plateau(*plateau);

        }
        break;
    case 'z':
        if (ASSERT_BEHIND(*plateau))
        {
            Cube_behind(&plateau->cube);
            Print_plateau(*plateau);

        }
        break;
    case 's':
        if (ASSERT_FRONT(*plateau))
        {
            Cube_front(&plateau->cube);
            Print_plateau(*plateau);

        }
        break;
    case 'a':
        if (ASSERT_ROTA(*plateau))
        {
            Cube_rota_left(&plateau->cube);
            Print_plateau(*plateau);

        }
        break;
    case 'e':
        if (ASSERT_ROTA(*plateau))
        {
            Cube_rota_right(&plateau->cube);
            Print_plateau(*plateau);

        }
        break;

    default:
        break;

    }

    Plateau_update(plateau);
}

bool GameCore_CanFinish(Plateau plateau)
{
    if (plateau.cube.i == 0 && plateau.cube.j == 2)
        if (plateau.cube.behind == FACE) // il a la tete devant la porte
        {
            if (Cube_key(plateau.cube) == true)
            {
                printf("yipi");
                return true;

            }
        }
    return false;
}

//  KEY_HOLE, AXE, SHIELD, BACKPACK, FACE, HEAD
//  NOTHING, BOX, PILLAR, DIAMOND, DOWN_AXE, DOWN_KEY,GHOST, END

bool ASSERT_LEFT(Plateau plateau)
{
    int value_left = plateau.board[plateau.cube.i][(plateau.cube.j) - 1].value;
    //printf("value left = %d\n", value_left);

    if (plateau.cube.j == 0)
    {
        return false;
    }
    if (value_left == NOTHING || value_left == END){
        return true;
    }
    if (value_left == DIAMOND && plateau.cube.key == false && plateau.cube.left == KEY_HOLE)
    {
        return true;
    }
    if (value_left == DOWN_KEY && plateau.cube.key == false)
    {
        return true;
    }
    if (value_left == DOWN_AXE && plateau.cube.axe == false)
    {
        return true;
    }

    return false;
}
bool ASSERT_RIGHT(Plateau plateau)
{
    int value_right = plateau.board[plateau.cube.i][(plateau.cube.j) + 1].value;
    //printf("value right = %d\n", value_right);

    if (plateau.cube.j == 4)
    {
        return false;
    }
    if (value_right == NOTHING || value_right == END)
    {
        return true;
    }
    if (value_right == DIAMOND && plateau.cube.key == false && plateau.cube.right == KEY_HOLE)
    {
        return true;
    }
    if (value_right == DOWN_KEY && plateau.cube.key == false)
    {
        return true;
    }
    if (value_right == DOWN_AXE && plateau.cube.axe == false)
    {
        return true;
    }

    return false;
}
bool ASSERT_BEHIND(Plateau plateau)
{
    int value_behind = plateau.board[plateau.cube.i - 1][(plateau.cube.j)].value;
    //printf("value top = %d\n", value_behind);
    if (plateau.cube.i == 0)
    {
        return false;
    }
    if (value_behind == NOTHING || value_behind == END)
    {
        return true;
    }
    if (value_behind == DIAMOND && plateau.cube.key == false && plateau.cube.behind == KEY_HOLE)
    {
        return true;
    }
    if (value_behind == DOWN_KEY && plateau.cube.key == false)
    {
        return true;
    }
    if (value_behind == DOWN_AXE && plateau.cube.axe == false)
    {
        return true;
    }

    return false;
}
bool ASSERT_FRONT(Plateau plateau)
{
    int value_front = plateau.board[plateau.cube.i + 1][(plateau.cube.j)].value;
    //printf("value bot = %d\n", value_front);
    if (plateau.cube.i == 3)
    {
        return false;
    }
    if (value_front == NOTHING || value_front == END)
    {
        return true;
    }
    if (value_front == DIAMOND && plateau.cube.key == false && plateau.cube.front == KEY_HOLE)
    {
        return true;
    }
    if (value_front == DOWN_KEY && plateau.cube.key == false)
    {
        return true;
    }
    if (value_front == DOWN_AXE && plateau.cube.axe == false)
    {
        return true;
    }

    return false;    
}

bool ASSERT_ROTA(Plateau plateau)
{
    int i = plateau.cube.i;
    int j = plateau.cube.j;
    if (plateau.cube.under != SHIELD) return false;
    //vérifier qu'il y a pas de boite ('b') autour
    if (i - 1 >= 0)
    {
        if (plateau.board[i-1][j].value == BOX)
            return false;
    }
    if (i - 1 < 4)
    {
        if (plateau.board[i+1][j].value == BOX)
            return false;
    }
    if (j - 1 >= 0)
    {
        if (plateau.board[i][j-1].value == BOX)
            return false;
    }
    if (j + 1 < 5)
    {
        if (plateau.board[i][j+1].value == BOX)
            return false;
    }
    return true;

}


/*

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

void GameCore_update(Plateau plateau)
{
    Print_plateau(plateau);
    printf("%u",hash_maker(plateau));
    char input=0;
    printf("Quel deplacement voulez vous faire ? (z = haut, s = bas, q = gauche, d = droite, a = rotation à gauche , e = roation à droite)\n");
    scanf(" %c", &input);

    int a;

    switch (input)
    {
    case 'z':
        printf("Vous avez choisi de déplacer vers le haut\n");
        a = GameCore_CanPlay(plateau, 'z' ,plateau.cube->i - 1, plateau.cube->j);
        if (a == 1)
        {
            plateau.plate[plateau.cube->i][plateau.cube->j] = 0;
            plateau.plate[plateau.cube->i - 1][plateau.cube->j] = 'n';
            Cube_behind(plateau.cube);
        }
        // Déplacement vers le haut

        break;
    case 's':
        printf("Vous avez choisi de déplacer vers le bas\n");
        a = GameCore_CanPlay(plateau, 's',plateau.cube->i + 1, plateau.cube->j);
        if (a == 1)
        {
            plateau.plate[plateau.cube->i][plateau.cube->j] = 0;
            plateau.plate[plateau.cube->i + 1][plateau.cube->j] = 'n';
            Cube_front(plateau.cube);
        }
        // Déplacement vers le bas
        break;
    case 'q':
        printf("Vous avez choisi de déplacer vers la gauche\n");
        a = GameCore_CanPlay(plateau,'q', plateau.cube->i, plateau.cube->j - 1);
        if (a == 1)
        {
            plateau.plate[plateau.cube->i][plateau.cube->j] = 0;
            plateau.plate[plateau.cube->i][plateau.cube->j - 1] = 'n';
            Cube_left(plateau.cube);
        }
        // Déplacement vers la gauche
        break;
    case 'd':
        printf("Vous avez choisi de déplacer vers la droite\n");
        a = GameCore_CanPlay(plateau,'d', plateau.cube->i, plateau.cube->j + 1);
        if (a == 1)
        {
            plateau.plate[plateau.cube->i][plateau.cube->j] = 0;
            plateau.plate[plateau.cube->i][plateau.cube->j + 1] = 'n';
            Cube_right(plateau.cube);
        }
        // Déplacement vers la droite
        break;

    case 'e':
        printf("Vous avez choisi de tourner vers la droite\n");
        a = GameCore_CanRotate(plateau);
        if (a == 1)
        {
            Cube_rota_right(plateau.cube);
        }
        // Rotaion vers la droite
        break;
    case 'a':
        printf("Vous avez choisi de tourner vers la gauche\n");
        a = GameCore_CanRotate(plateau);
        if (a == 1)
        {
            Cube_rota_left(plateau.cube);
        }
        // Rotation vers la gauche
        break;

    default:
        break;
    }

}

void GameCore_Init_turn(Plateau *plateau)
{
    do
    {
    GameCore_update(*plateau);
    } while (!GameCore_CanFinish(plateau));
    GameCore_Finish();
}

bool GameCore_CanPlay(Plateau plateau, char direction , int i, int j)
{
    int futur_code;
    switch (direction)
    {
    case 'z':
        futur_code = plateau.cube->over->code;
        break;
    case 's':
        futur_code = plateau.cube->front->code;
        break;
    case 'q':
        futur_code = plateau.cube->left->code;
        break;
    case 'd':
        futur_code = plateau.cube->right->code;
        break;
    }
    if (i > 3 || i < 0 || j > 4 || j < 0)
    {
        printf("torlolo");
        return false;
    }
    if (plateau.plate[i][j] == 'd') // on tombe sur un diamans
    {
        if (plateau.cube->under->code == 1 && plateau.cube->key == false)
        {
            return true;
        }
        return false;
    }
    if (plateau.plate[i][j] == 'k') // on tombe sur la clé
    {
        if (futur_code == 1 )
        {
            plateau.cube->key = true;
            plateau.plate[i][j] = 0;
            return true;
        }
        return false;
    }
    if (plateau.plate[i][j] == 0 || plateau.plate[i][j] == '.')
    {
        return true;
    }
    return false;
}

bool GameCore_CanRotate(Plateau plateau)
{
    int i = plateau.cube->i;
    int j = plateau.cube->j;
    if (plateau.cube->under->code == 3)
    {
        //vérifier qu'il y a pas de boite ('b') autour
        if (i - 1 >= 0)
        {
            if (plateau.plate[i][j] == 'b')
            {
                return false;
            }
        }
        if (i - 1 < 4)
        {
            if (plateau.plate[i][j] == 'b')
            {
                return false;
            }
        }
        if (j - 1 >= 0)
        {
            if (plateau.plate[i][j] == 'b')
            {
                return false;
            }
        }
        if (j + 1 < 5)
        {
            if (plateau.plate[i][j] == 'b')
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
    if (plateau.cube.behind == HEAD) // il a la tete devant la porte
    {
        if (Cube_key(plateau.cube) == true)
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
*/
