#include "solver.h"

uint64_t hash_maker(Plateau plateau)
{
    uint64_t hash = (uint64_t)plateau.cube.i;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube.j;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube.behind;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube.front;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube.left;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube.right;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube.axe;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    hash ^= (uint64_t)plateau.cube.key;
    hash = hash * 0xbf58476d1ce4e5b9ULL + 0x9e3779b97f4a7c15ULL;
    return hash;

}

GameHashmap* GameHashmap_create(size_t capacity)
{
    GameHashmap* hash_map = (GameHashmap*)calloc(1, sizeof(GameHashmap));
    AssertNew(hash_map);
    hash_map->m_size = 0;
    hash_map->m_capacity = capacity;
    hash_map->m_entries = (GameHashmapEntry*)calloc(capacity, sizeof(GameHashmapEntry));

    hash_map->m_idMap = (size_t*)calloc(capacity, sizeof(size_t));
    for (int i = 0; i < capacity; i++)
        hash_map->m_idMap[i] = -1;
    return hash_map;
}



GameHashmap* Solver(Plateau plateau, size_t capacity)
{
    size_t i_origin = 0;
    size_t i_working = 1;
    GameHashmap* hash_map = GameHashmap_create(capacity);
    GameHashmapEntry entry = { -1, plateau , -1};
    Plateau plateau_w;
    uint64_t hash;

    hash_map->m_entries[i_origin] = entry;
    hash_map->m_idMap[hash_maker(plateau) % capacity] = 0;
    hash_map->m_size++;

    plateau_w = hash_map->m_entries[i_origin].currState;

    while (i_origin != i_working)
    {
        plateau_w = hash_map->m_entries[i_origin].currState;
        if (ASSERT_LEFT(plateau_w))
        {
            Cube_left(&plateau_w.cube);
            Plateau_update(&plateau_w);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != -1)
            {
                if (Plateau_even(hash_map->m_entries[i_working].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == -1)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_origin;
                hash_map->m_idMap[hash % capacity] = i_working;
                hash_map->m_entries[i_working] = entry;
                i_working++;
                hash_map->m_size++;
            }
        }
        plateau_w = hash_map->m_entries[i_origin].currState;
        if (ASSERT_RIGHT(plateau_w))
        {
            Cube_right(&plateau_w.cube);
            Plateau_update(&plateau_w);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != -1)
            {
                if (Plateau_even(hash_map->m_entries[i_working].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == -1)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_origin;
                hash_map->m_idMap[hash % capacity] = i_working;
                hash_map->m_entries[i_working] = entry;
                i_working++;
                hash_map->m_size++;
            }
        }
        plateau_w = hash_map->m_entries[i_origin].currState;
        if (ASSERT_FRONT(plateau_w))
        {

            Cube_front(&plateau_w.cube);
            Plateau_update(&plateau_w);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != -1)
            {
                if (Plateau_even(hash_map->m_entries[i_working].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == -1)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_origin;
                hash_map->m_idMap[hash % capacity] = i_working;
                hash_map->m_entries[i_working] = entry;
                i_working++;
                hash_map->m_size++;
            }
        }
        plateau_w = hash_map->m_entries[i_origin].currState;
        if (ASSERT_BEHIND(plateau_w))
        {
            Cube_behind(&plateau_w.cube);
            Plateau_update(&plateau_w);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != -1)
            {
                if (Plateau_even(hash_map->m_entries[i_working].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == -1)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_origin;
                hash_map->m_idMap[hash % capacity] = i_working;
                hash_map->m_entries[i_working] = entry;
                i_working++;
                hash_map->m_size++;
            }
        }
        plateau_w = hash_map->m_entries[i_origin].currState;
        if (ASSERT_ROTA(plateau_w))
        {
            Cube_rota_right(&plateau_w.cube);
            Plateau_update(&plateau_w);

            hash = hash_maker(plateau_w);
            while (hash_map->m_idMap[hash % capacity] != -1)
            {
                if (Plateau_even(hash_map->m_entries[i_working].currState, plateau_w)) break;
                hash++;
            }
            if (hash_map->m_idMap[hash % capacity] == -1)
            {

                entry.currState = plateau_w;
                entry.id_prev = i_origin;
                hash_map->m_idMap[hash % capacity] = i_working;
                hash_map->m_entries[i_working] = entry;
                i_working++;
                hash_map->m_size++;
            }

        }
        i_origin++;
    }
   
    //printf("%d",Solver_nb(hash_map));
    return hash_map;

}


void Solver_print(GameHashmap* hash_map)
{

    int index = 0;
    int index_cube = 0;
    size_t res = 0;
    int index_desc;
    while (!GameCore_CanFinish(hash_map->m_entries[index].currState)) 
        index++;    
    Print_plateau(hash_map->m_entries[index].currState);
    while (index != 0)
    {
        //hash_map->m_size ++;
        res++;
        index_cube ++;
        printf("\n");

        size_t temp = index;

        index = hash_map->m_entries[index].id_prev;

        hash_map->m_entries[index].id_next = temp;
        printf("index test = %d\n", hash_map->m_entries[index].id_next);

        Print_plateau(hash_map->m_entries[index].currState);
        printf("la face en ce moment est %d\n", hash_map->m_entries[index].currState.cube.over);

        hash_map->m_idMap = index;
        printf("index = %d et index_next = %d \n", index, hash_map->m_entries[index].id_next);
        printf("index = %d et index_prev = %d \n", index, hash_map->m_entries[index].id_prev);
    }
    //printf("res = %d", res);
    
    //hash_map->m_size = res;

}

int Solver_nb(GameHashmap * hash_map)
{
    int count = 1;
    int index = 0;
    while (hash_map->m_size > index && !GameCore_CanFinish(hash_map->m_entries[index].currState))
        index++;
    if (hash_map->m_size == index) return -1;
    while (hash_map->m_entries[index].id_prev > 0)
    {
        index = hash_map->m_entries[index].id_prev;
        
        count++;
    }
    return count;
        //index++;

    //if(index == )
}

