#include "solver.h"

uint16_t hash_maker(Plateau* plate)
{
    uint64_t hash = (uint64_t)plate->cube->i;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plate->cube->j;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plate->cube->behind->code;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plate->cube->front->code;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plate->cube->left->code;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plate->cube->right->code;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plate->cube->axe;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plate->cube->key;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    return hash;
    
}

GameHashmap *GameHashmap_create(size_t capacity)
{
    GameHashmap *hash_map = (GameHashmap*)calloc(1, sizeof(GameHashmap));
    AssertNew(hash_map);
    hash_map->m_size = 0;
    hash_map->m_capacity = capacity;
    hash_map->m_entries = (GameHashmapEntry*)calloc(capacity, sizeof(GameHashmapEntry));
    hash_map->m_idMap = (size_t*)calloc(capacity, sizeof(size_t));
    return hash_map;
}


void Solver(Plateau* plateau, size_t capacity)
{
    Print_plateau(plateau);
    GameHashmap *hash_map = GameHashmap_create(capacity);
    printf(capacity);
}
