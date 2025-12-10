#include "plateau.h"

Plateau *Plateau_create() {


    Plateau *plat = (Plateau *)calloc(1, sizeof(Plateau));
    AssertNew(plat);

    plat->plate = (char ** ) calloc(4,sizeof(char*));
    for(int i=0; i<4 ; i++){
        plat->plate[i] = (char * )calloc(5,sizeof(char));
    }
    plat->plate[0][2] = '.';

    plat->cube = Cube_create();

    return plat;
}


void Print_plateau(Plateau *plate){

    assert(plate != NULL);

    //system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("-------Rok passe partout-----------\n");
    printf("------| |------\n");
    for( int i=0 ; i<4; i ++){
        for( int j=0 ; j<5 ; j ++){
            char value = plate->plate[i][j];
            if (i == 0 && j == 2)
            {
                if (value == 'n')
                {
                    printf("[n]");
                }
                else
                {
                printf("[.]");
                }
            }
            else
            {
                if (value == 0)
                {
                    printf("[ ]");
                }
                else
                {
                    printf("[%c]", value);

                }
            }
            
        }
        printf("\n");
    }
    printf("-----------------------------\n");
    Cube_print(plate->cube);
    printf("-----------------------------\n");
}

void Add_pawn(Plateau* plate,char value, int i, int j)
{

    assert(plate != NULL || value != 'n' || value != 'p' || value != 'b' || value != 'k' || value != 'd' || value != 'h' || value != 'f' || i < 0 || i>4 || j < 0 || j>5);

    plate->plate[i][j] = value;
}

void Delete_pawn(Plateau* plate, char value)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (plate->plate[i][j] == value)
            {
                plate->plate[i][j] = 0;
            }
        }
    }
}

void Ask_add_pawn(Plateau* plate)
{
    char n;
    int i, j;
    do
    {
        printf("Quel pion voulez vous ajouter (n = nain, p = pilier, b = boite, k = key, d = diamant, h = hache , f = fantome )\n");
        scanf(" %c", &n);
    } while (n != 'n' && n != 'p' && n != 'b' && n != 'k' && n != 'd' && n != 'h' && n != 'f');

    do
    {
        printf("A quelle ligne ? (0-3)\n");
        scanf(" %d", &i);
    } while (i < 0 || i > 3);

    do
    {
        printf("A quelle colonne ? (0-4)\n");
        scanf(" %d", &j);
    } while (j < 0 || j > 4);

    if (plate->plate[i][j] != 0)
    {
        printf("Case déjà occupée !\n");
        return;
    }
    Add_pawn(plate, n, i, j);

}

void Bulid_Easy_Plateau(Plateau* plateau)
{
    Add_pawn(plateau, 'b', 1, 1);
    Add_pawn(plateau, 'k', 2, 0);
    Add_pawn(plateau, 'b', 2, 2);
    Add_pawn(plateau, 'p', 2, 3);
    Add_pawn(plateau, 'd', 2, 4);
    Add_pawn(plateau, 'p', 3, 0);
    Add_pawn(plateau, 'n', 3, 4);
    plateau->cube->i = 3;
    plateau->cube->j = 4;
    Set_Cube_East(plateau->cube);
}

void Bulid_Medium_Plateau(Plateau* plateau)
{
    Add_pawn(plateau, 'd', 0, 1);
    Add_pawn(plateau, 'n', 0, 3);
    Add_pawn(plateau, 'd', 1, 0);
    Add_pawn(plateau, 'h', 1, 1);
    Add_pawn(plateau, 'f', 1, 2);
    Add_pawn(plateau, 'p', 1, 3);
    Add_pawn(plateau, 'b', 2, 0);
    Add_pawn(plateau, 'k', 2, 3);
    Add_pawn(plateau, 'p', 3, 1);
    Add_pawn(plateau, 'b', 3, 3);

    plateau->cube->i = 0;
    plateau->cube->j = 3;
    Set_Cube_West(plateau->cube);

}

void Bulid_Hard_Plateau(Plateau* plateau)
{
    Add_pawn(plateau, 'b', 1, 1);
    Add_pawn(plateau, 'k', 2, 0);
    Add_pawn(plateau, 'b', 2, 2);
    Add_pawn(plateau, 'p', 2, 3);
    Add_pawn(plateau, 'd', 2, 4);
    Add_pawn(plateau, 'p', 3, 0);
    Add_pawn(plateau, 'n', 3, 4);

    plateau->cube->i = 3;
    plateau->cube->j = 4;
    Set_Cube_East(plateau->cube);
}
