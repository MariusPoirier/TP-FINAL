/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "plateau/plateau.h"
#include "solver/solver.h"
#include "game/input.h"

#define GAME_GRID_SIZE 5

typedef struct GameCore
{
    Plateau plateau;
    Input *input;
} GameCore;


/// @brief Crée le jeu.
void GameCore_Create();

/// @brief initialise un tour.
void GameCore_Loop(Plateau plateau);
/// @brief Un tour de jeu.
void GameCore_update(Plateau *plateau);

/// @brief initialise un tour.
void GameCore_Loop(Plateau plateau);

/// @brief Vérifie si un déplacement est possible
/// @param plateau Le plateau de jeu
/// @param i La ligne
/// @param j La colonne
/// @param direction La direction du déplacement
/// 
/// @return True si le déplacement est possible, False sinon
bool ASSERT_LEFT(Plateau plateau);

bool ASSERT_RIGHT(Plateau plateau);

bool ASSERT_BEHIND(Plateau plateau);

bool ASSERT_FRONT(Plateau plateau);

bool ASSERT_ROTA(Plateau plateau);

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
