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

    plateau.cube.i = 3;
    plateau.cube.j = 2;
    plateau.board[2][0].value = PILLAR;
    plateau.board[2][1].value = PILLAR;
    plateau.board[2][2].value = PILLAR;
    plateau.board[2][3].value = PILLAR;
    plateau.board[2][4].value = DOWN_KEY;
    plateau.board[1][3].value = PILLAR;
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
                default:
                    printf("///////");
                    break;
                }
            }
        }
        printf("\n");
    }
}
