#pragma once

#include "settings.h"
#include "../plateau/plateau.h"
#include "../game_core.h"

typedef struct GameHashmapEntry
{
    size_t id_prev;
    Plateau currState;
} GameHashmapEntry;


typedef struct GameHashmap
{
    GameHashmapEntry* m_entries;
    size_t* m_idMap;
    size_t m_capacity;
    size_t m_size;
} GameHashmap;

uint16_t hash_maker(Plateau plate);


GameHashmap *GameHashmap_create(size_t capacity);

//fonction qui doit résoudre le plateau:

GameHashmap *Solver(Plateau plateau, size_t capacity);


void Solver_print(GameHashmap *hash_map);
