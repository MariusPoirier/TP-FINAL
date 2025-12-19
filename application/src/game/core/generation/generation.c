#include "generation.h"

void generation_map(Plateau* plateau)
{
    int choice = rand() % 4;
    int i = rand() % 4;
    int j = rand() % 5;
    Cell_Value value = DIAMOND;
    switch (choice)
    {
    case 0:
        value = PILLAR;
        break;
    case 1:
        value = BOX;
        break;
    case 2:
    case 3:
        value = DIAMOND;
        break;
    }
    while ((i == plateau->cube.i && j == plateau->cube.j) || plateau->board[i][j].value != NOTHING)
    {
        i = rand() % 4;
        j = rand() % 5;
    }
    plateau->board[i][j].value = value;
}

void generation_fmap(Plateau* plateau)
{
    *plateau = Plateau_create();
    int i = rand() % 4;
    int j = rand() % 5;
    int rotas = rand() % 4;
    plateau->cube.i = i;
    plateau->cube.j = j;

    while(i == plateau->cube.i && j == plateau->cube.j)
    {
        i = rand() % 4;
        j = rand() % 5;
    }
    for (int i = 0; i < rotas; i++) Cube_rota_right(&plateau->cube);
    plateau->board[i][j].value = DOWN_KEY;
    while((i == plateau->cube.i && j == plateau->cube.j) || plateau->board[i][j].value != NOTHING)
    {
        i = rand() % 4;
        j = rand() % 5;
    }
    plateau->board[i][j].value = DOWN_AXE;
    while ((i == plateau->cube.i && j == plateau->cube.j) || plateau->board[i][j].value != NOTHING )
    {
        i = rand() % 4;
        j = rand() % 5;
    }
    plateau->board[i][j].value = GHOST;
}

Plateau generation(int difficulty)
{
    Plateau plateau = Plateau_create();
    Print_plateau(plateau);
    Plateau test;
    int nb_average = difficulty * 10;
    int nb_try = -1;

    while (nb_try + 5 < nb_average || nb_try - 10 > nb_average)
    {

        if (nb_try == -1 || nb_try - 10 > nb_average || Plateau_count_elem(plateau)>8)
        {
            generation_fmap(&plateau);
        }
        generation_map(&plateau);
        //test = plateau;
        nb_try = Solver_nb(Solver(plateau,20000));
    }

    printf("%d\n", Solver_nb(Solver(plateau, 20000)));
    Print_plateau(plateau);
    return plateau;
    
}

