#pragma once

#include "settings.h"
#include "../charactere/cube.h"


typedef struct Plateau
{
    char **plate;

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

/// @brief Ajoute un pion sur le plateau
/// 
/// @param plate le plateau de jeu.
/// @param value le pion à ajouter (n = nain, p = pilier, b = boite, k = key, d = diamant, h = hache , f = fantome ).
/// @param i la ligne
/// @param j la colonne
/// @return booléen si le pion à été ajouté True si ajouté , False sinon.
void Add_pawn(Plateau * plate, char value, int i, int j);

/// @brief Demande à l'utilisateur d'ajouter un pion sur le plateau
/// 
/// @param plate le plateau de jeu.
/// @return rien
void Ask_add_pawn(Plateau* plate);
