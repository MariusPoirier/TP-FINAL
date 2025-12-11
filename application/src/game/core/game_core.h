/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "plateau/plateau.h"

#define GAME_GRID_SIZE_X 5
#define GAME_GRID_SIZE_Y 4

typedef struct GameCore
{
    int todo;
} GameCore;

/// @brief Commence le jeu.
void GameCore_Start();

/// @brief Crée le jeu.
void GameCore_Create();

/// @brief Un tour de jeu.
void GameCore_update(Plateau plateau);

/// @brief initialise un tour.
void GameCore_Init_turn(Plateau plateau);

/// @brief Vérifie si un déplacement est possible
/// @param plateau Le plateau de jeu
/// @param i La ligne
/// @param j La colonne
/// @param direction La direction du déplacement
/// 
/// @return True si le déplacement est possible, False sinon
bool GameCore_CanPlay(Plateau plateau,char directtion , int i ,int j);

/// @brief Vérifie si notre personnage peut tourner
/// @param plateau Le plateau de jeu
///
/// @return True si la rotation est possible, False sinon
bool GameCore_CanRotate(Plateau plateau);

/// @brief Vérifie si on peut finir la partie
/// @param plateau Le plateau de jeu
///
/// @return True si la fin est possible, False sinon
bool GameCore_CanFinish(Plateau plateau);

/// @brief Finis le jeu.
void GameCore_Finish();
