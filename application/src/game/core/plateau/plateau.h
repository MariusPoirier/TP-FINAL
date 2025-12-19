#pragma once

#include "settings.h"
#include "../character/cube.h"

typedef enum Cell_Value
{ NOTHING, BOX, PILLAR, DIAMOND, DOWN_AXE, DOWN_KEY,GHOST, END}Cell_Value;

typedef struct Cell
{
    int i, j;
    Cell_Value value;
}Cell;


typedef struct Plateau
{
    Cell board[4][5];

    Cube cube;

} Plateau;

/// @brief Crée un plateau.
/// 
/// @param taille la taille du plateau (ex: 3 = tab 3x2).
/// @return Le plateau créée.
Plateau Plateau_create();

Plateau Plateau_1();
Plateau Plateau_2();
Plateau Plateau_3();
Plateau Plateau_4();
Plateau Plateau_5();
Plateau Plateau_6();
Plateau Plateau_7();

/// @brief Affiche le plateau.
/// 
/// @param plate le plateau à afficher.
/// @return L'affichage du tableau.
void Print_plateau(Plateau plateau);

void Plateau_update(Plateau *plateau);


int Plateau_count_elem(Plateau plateau);
void Plateau_search_ghost(Plateau* plateau);

bool Plateau_even(Plateau plateau1, Plateau plateau2);

Plateau Plateau_copy(Plateau plateau);
