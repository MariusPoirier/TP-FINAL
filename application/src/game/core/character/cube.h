#pragma once

#include "settings.h"
typedef enum Face_Value
{ Key_Hole, AXE, SHIELD, BACKPACK, FACE, HEAD }
Face_Value;


typedef struct Cube
{

    Face_Value under;
    Face_Value right;
    Face_Value left;
    Face_Value behind;
    Face_Value front;
    Face_Value over;

    bool axe;
    bool key;

    int i,j;

} Cube;



/// @brief Crée un cube.
/// 
/// @param face la face sur lequel le dé doit être.
/// @return Le cube créée.
Cube Cube_create();

void Cube_print(Cube cube);

void Cube_rota_right(Cube *cube);
void Cube_rota_left(Cube *cube);

void Cube_left(Cube *cube);
void Cube_behind(Cube *cube);
void Cube_right(Cube *cube);
void Cube_front(Cube *cube);

int getCubeI(Cube cube);
int getCubeJ(Cube cube);

void Cube_SetNorth(Cube *cube);
void Cube_SetWest(Cube *cube);
void Cube_SetEast(Cube *cube);

void Cube_SetSouth(Cube *cube);


/// @brief Dis si le cube à la hache.
/// 
/// @param self le cube que l'on veut.
/// @return booléen pour savoir si le cube à la hache.
bool Cube_axe(Cube self);

/// @brief Dis si le cube à la clé.
/// 
/// @param self le cube que l'on veut.
/// @return booléen pour savoir si le cube à la clé.
bool Cube_key(Cube self);
