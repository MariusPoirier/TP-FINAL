#pragma once

#include "settings.h"

typedef struct Cube
{
    char actual_face;
    bool has_hache;
    bool has_key;

} Cube;

/// @brief Crée un cube.
/// 
/// @param face la face sur lequel le dé doit être.
/// @return Le cube créée.
Cube *Cube_create(char face);

/// @brief Dis si le cube à la hache.
/// 
/// @param self le cube que l'on veut.
/// @return booléen pour savoir si le cube à la hache.
bool Has_Hache(Cube *self);

/// @brief Dis si le cube à la clé.
/// 
/// @param self le cube que l'on veut.
/// @return booléen pour savoir si le cube à la clé.
bool Has_Key(Cube *self);
