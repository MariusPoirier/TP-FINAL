#include "plateau.h"

Plateau Plateau_create()
{
    Plateau plateau;
    plateau.cube = Cube_create();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            plateau.board[i][j].value = NOTHING;
            plateau.board[i][j].i = i;
            plateau.board[i][j].j = j;


        }
    }
    plateau.board[0][2].value = END;
    return plateau;
}

Plateau Plateau_1()
{
    Plateau plateau = Plateau_create();
    plateau.cube = Cube_create();

    plateau.cube.i = 3;
    plateau.cube.j = 0;


    plateau.board[2][0].value = PILLAR;
    plateau.board[2][1].value = PILLAR;
    plateau.board[2][2].value = PILLAR;
    plateau.board[2][3].value = PILLAR;
    //plateau.board[2][4].value = DOWN_KEY;
    plateau.board[1][3].value = PILLAR;
    plateau.board[3][4].value = DOWN_KEY;
    plateau.board[3][1].value = DOWN_AXE;
    plateau.board[0][0].value = GHOST;

    return plateau;
}

Plateau Plateau_2()
{
    Plateau plateau = Plateau_create();
    plateau.cube = Cube_create();

    plateau.cube.i = 0;
    plateau.cube.j = 3;

    Cube_SetWest(&plateau.cube);

    plateau.board[0][1].value = DIAMOND;
    plateau.board[1][0].value = DIAMOND;
    plateau.board[1][1].value = DOWN_AXE;
    plateau.board[1][2].value = GHOST;
    plateau.board[1][3].value = PILLAR;
    plateau.board[2][0].value = BOX;
    plateau.board[2][3].value = DOWN_KEY;
    plateau.board[3][1].value = PILLAR;
    plateau.board[3][3].value = BOX;

    return plateau;
}

Plateau Plateau_3()
{
    Plateau plateau = Plateau_create();
    plateau.cube = Cube_create();

    plateau.cube.i = 3;
    plateau.cube.j = 2;
    Cube_SetSouth(&plateau.cube);

    plateau.board[1][1].value = DIAMOND;
    plateau.board[1][2].value = DOWN_KEY;
    plateau.board[1][3].value = BOX;
    plateau.board[2][2].value = BOX;

    return plateau;
}

Plateau Plateau_4()
{
    Plateau plateau = Plateau_create();
    plateau.cube = Cube_create();

    plateau.cube.i = 3;
    plateau.cube.j = 4;
    Cube_SetNorth(&plateau.cube);

    plateau.board[3][0].value = DOWN_KEY;

    return plateau;
}

Plateau Plateau_5()
{
    Plateau plateau = Plateau_create();
    plateau.cube = Cube_create();

    plateau.cube.i = 2;
    plateau.cube.j = 0;
    Cube_SetNorth(&plateau.cube);

    plateau.board[0][4].value = DOWN_AXE;
    plateau.board[1][0].value = DIAMOND;
    plateau.board[1][1].value = BOX;
    plateau.board[1][2].value = BOX;
    plateau.board[2][3].value = PILLAR;
    plateau.board[3][2].value = DOWN_KEY;
    plateau.board[3][3].value = GHOST;

    return plateau;
}

Plateau Plateau_6()
{
    Plateau plateau = Plateau_create();
    plateau.cube = Cube_create();

    plateau.cube.i = 3;
    plateau.cube.j = 0;
    Cube_SetNorth(&plateau.cube);

    plateau.board[0][0].value = DOWN_AXE;
    plateau.board[0][4].value = DIAMOND;
    plateau.board[1][2].value = DIAMOND;
    plateau.board[1][3].value = BOX;
    plateau.board[2][0].value = GHOST;
    plateau.board[2][1].value = PILLAR;
    plateau.board[2][2].value = DOWN_KEY;
    plateau.board[3][4].value = BOX;

    return plateau;
}

Plateau Plateau_7()
{
    Plateau plateau = Plateau_create();
    plateau.cube = Cube_create();

    plateau.cube.i = 1;
    plateau.cube.j = 0;
    Cube_SetSouth(&plateau.cube);

    plateau.board[0][0].value = GHOST;
    plateau.board[1][2].value = PILLAR;
    plateau.board[1][4].value = DIAMOND;
    plateau.board[2][1].value = BOX;
    plateau.board[2][2].value = DOWN_KEY;
    plateau.board[2][3].value = BOX;
    plateau.board[3][2].value = DOWN_AXE;

    return plateau;
}

void Print_plateau(Plateau plateau)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (plateau.cube.i == i && plateau.cube.j == j)
            {
                printf(" cube  ");
            }
            else
            {
                switch (plateau.board[i][j].value)
                {
                case NOTHING:
                    printf("nothing ");
                    break;
                case BOX:
                    printf("  box   ");
                    break;
                case PILLAR:
                    printf("pillar  ");
                    break;
                case DIAMOND:
                    printf("diamond ");
                    break;
                case END:
                    printf("  end   ");
                    break;
                case DOWN_KEY:
                    printf("  key   ");
                    break;
                case DOWN_AXE:
                    printf("  axe   ");
                    break;
                case GHOST:
                    printf(" ghost  ");
                    break;
                default:
                    printf("///////");
                    break;
                }
            }
        }
        printf("\n");
    }
}

void Plateau_update(Plateau* plateau)
{
    //printf("IS HAVE KEY ?%d", plateau->cube.key);

    // Il faut remove clé hache et fantôme;
    if (plateau->board[plateau->cube.i][plateau->cube.j].value == DOWN_KEY)
    {
        printf("test key picked\n");
        plateau->board[plateau->cube.i][plateau->cube.j].value = NOTHING;
        plateau->cube.key = true;
    }
    if (plateau->board[plateau->cube.i][plateau->cube.j].value == DOWN_AXE)
    {
        plateau->board[plateau->cube.i][plateau->cube.j].value = NOTHING;
        plateau->cube.axe = true;
        Plateau_search_ghost(plateau);
    }
    
}

void Plateau_search_ghost(Plateau* plateau)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (plateau->board[i][j].value == GHOST)
                plateau->board[i][j].value = NOTHING;
        }
    }

}

bool Plateau_even(Plateau plateau1, Plateau plateau2)
{
    if (plateau1.cube.under != plateau2.cube.under) return true;
    if (plateau1.cube.front != plateau2.cube.front) return true;
    if (plateau1.cube.left != plateau2.cube.left) return true;
    if (plateau1.cube.i != plateau2.cube.i) return true;
    if (plateau1.cube.j != plateau2.cube.j) return true;
    if (plateau1.cube.axe != plateau2.cube.axe) return true;
    if (plateau1.cube.key != plateau2.cube.key) return true;

}

Plateau Plateau_copy(Plateau plateau)
{
    Plateau new_plateau = Plateau_create();
    new_plateau.cube = plateau.cube;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            new_plateau.board[i][j] = plateau.board[i][j];
        }
    }
    return new_plateau;
}
