#pragma once

#include "settings.h"
#include "../plateau/plateau.h"
#include "../game_core.h"

typedef struct GameHashmapEntry
{
    size_t id_prev;
    Plateau currState;
    size_t id_next;
} GameHashmapEntry;


typedef struct GameHashmap
{
    GameHashmapEntry* m_entries;
    size_t* m_idMap;
    size_t m_capacity;
    size_t m_size;
    int cube_index;
} GameHashmap;

uint64_t hash_maker(Plateau plate);


GameHashmap* GameHashmap_create(size_t capacity);

//fonction qui doit résoudre le plateau:

GameHashmap* Solver(Plateau plateau, size_t capacity);


void Solver_print(GameHashmap* hash_map);

int Solver_nb(GameHashmap* hash_map);
