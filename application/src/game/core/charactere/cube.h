#pragma once

#include "settings.h"
typedef struct Face
{
    // 1) trou clé
    // 2) hache
    // 3) bouclier
    // 4) backpack
    // 5) face
    // 6) head
    int code;

} Face;

typedef struct Cube
{

    Face* under;
    Face* right;
    Face* left;
    Face* behind;
    Face* front;
    Face* over;

    bool has_hache;
    bool has_key;

    int i, j;

} Cube;


/// @brief Crée une face.
/// 
/// @param face la face sur lequel le dé doit être.
/// @return Le cube créée.
Face* Face_create(int code);
/// @brief Crée un cube.
/// 
/// @param face la face sur lequel le dé doit être.
/// @return Le cube créée.
Cube Cube_create();

void Cube_print(Cube* cube);

void Cube_rota_right(Cube* cube);
void Cube_rota_left(Cube* cube);

void Cube_left(Cube* cube);
void Cube_behind(Cube* cube);
void Cube_right(Cube* cube);
void Cube_front(Cube* cube);

int Cube_GetI(Cube* cube);
int Cube_GetJ(Cube* cube);

void Cube_Set_North(Cube* cube);
void Cube_Set_South(Cube* cube);
void Cube_Set_East(Cube* cube);
void Cube_Set_South(Cube* cube);


/// @brief Dis si le cube à la hache.
/// 
/// @param self le cube que l'on veut.
/// @return booléen pour savoir si le cube à la hache.
bool Has_Hache(Cube* self);

/// @brief Dis si le cube à la clé.
/// 
/// @param self le cube que l'on veut.
/// @return booléen pour savoir si le cube à la clé.
bool Has_Key(Cube* self);
