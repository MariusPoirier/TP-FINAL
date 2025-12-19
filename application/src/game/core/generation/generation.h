#pragma once

#include "settings.h"
#include "../game_core.h"
#include<stdlib.h>
#include <time.h>

typedef enum Difficulty
{
    EASY, MEDIUM, HARD
} Difficulty;

bool generation_end(Cube cube);

void generation_map(Plateau* plateau);
void generation_fmap(Plateau* plateau);

void generation_map(Plateau* plateau);

Plateau generation(int difficulty);
