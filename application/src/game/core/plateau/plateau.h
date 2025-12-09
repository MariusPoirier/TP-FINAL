#pragma once

#include "settings.h"
#include "../charactere/cube.h"


typedef struct Plateau
{
    int  **plate;

} Plateau;

/// @brief Crée un plateau.
/// 
/// @param taille la taille du plateau (ex: 3 = tab 3x2).
/// @return Le plateau créée.
Plateau *Plateau_create();

/// @brief Affiche le plateau.
/// 
/// @param plate le plateau à afficher.
/// @return L'affichage du tableau.
void Print_plateau(Plateau *plate);

