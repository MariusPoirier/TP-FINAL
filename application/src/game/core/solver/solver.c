#include "solver.h"
/*
uint16_t hash_maker(Plateau plateau)
{
    uint64_t hash = (uint64_t)plateau.cube->i;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube->j;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube->behind->code;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube->front->code;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube->left->code;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube->right->code;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube->axe;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube->key;
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


void Solver(Plateau plateau, size_t capacity)
{
    int i_working = 0;
    int i_placement = 1;
    GameHashmap *hash_map = GameHashmap_create(capacity);
    GameHashmapEntry entry = { -1, plateau };
    Plateau plateau_w;
    uint64_t hash;


    hash_map->m_entries[i_working] = entry;
    hash_map->m_idMap[hash_maker(plateau) % capacity];

    while (!GameCore_CanFinish(&plateau_w))
    {
        plateau_w = hash_map->m_entries[i_working].currState;
        if (GameCore_CanPlay(plateau_w, 'z', plateau_w.cube->i - 1, plateau_w.cube->j))
        {
            plateau_w.plate[plateau_w.cube->i][plateau_w.cube->j] = 0;
            plateau_w.plate[plateau_w.cube->i - 1][plateau_w.cube->j] = 'n';
            Cube_behind(plateau_w.cube);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != 0)
            {
                if (Plateau_even(hash_map->m_entries[i_working].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == 0)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_working;
                hash_map->m_idMap[hash] = i_placement;
                hash_map->m_entries[i_placement] = entry;


                i_placement++;
            }

        }
        // Bis
        plateau_w = hash_map->m_entries[i_working].currState;
        if (GameCore_CanPlay(plateau_w, 's', plateau_w.cube->i + 1, plateau_w.cube->j))
        {
            plateau_w.plate[plateau_w.cube->i][plateau_w.cube->j] = 0;
            plateau_w.plate[plateau_w.cube->i + 1][plateau_w.cube->j] = 'n';
            Cube_front(plateau_w.cube);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != 0)
            {
                if (Plateau_even(hash_map->m_entries[hash_map->m_idMap[hash]].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == 0)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_working;
                hash_map->m_idMap[hash] = i_placement;
                hash_map->m_entries[i_placement] = entry;


                i_placement++;
            }

        }
        plateau_w = hash_map->m_entries[i_working].currState;
        if (GameCore_CanPlay(plateau_w, 'q', plateau_w.cube->i , plateau_w.cube->j - 1))
        {
            plateau_w.plate[plateau_w.cube->i][plateau_w.cube->j] = 0;
            plateau_w.plate[plateau_w.cube->i][plateau_w.cube->j - 1] = 'n';
            Cube_front(plateau_w.cube);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != 0)
            {
                if (Plateau_even(hash_map->m_entries[hash_map->m_idMap[hash]].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == 0)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_working;
                hash_map->m_idMap[hash] = i_placement;
                hash_map->m_entries[i_placement] = entry;


                i_placement++;
            }

        }
        plateau_w = hash_map->m_entries[i_working].currState;
        if (GameCore_CanPlay(plateau_w, 'd', plateau_w.cube->i, plateau_w.cube->j + 1))
        {
            plateau_w.plate[plateau_w.cube->i][plateau_w.cube->j] = 0;
            plateau_w.plate[plateau_w.cube->i][plateau_w.cube->j + 1] = 'n';
            Cube_front(plateau_w.cube);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != 0)
            {
                if (Plateau_even(hash_map->m_entries[hash_map->m_idMap[hash]].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == 0)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_working;
                hash_map->m_idMap[hash] = i_placement;
                hash_map->m_entries[i_placement] = entry;


                i_placement++;
            }

        }
        
    }
    printf("SAUCIISSSSSSSSSE");

    
}

*/
