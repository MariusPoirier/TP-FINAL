/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "game/game_config.h"
#include "game/core/game_core.h"

typedef struct Scene Scene;

#define GAME_GRID_GRAPHIC_SIZE_X 7
#define GAME_GRID_GRAPHIC_SIZE_Y 6


/// @brief Structure représentant la scène du menu principal du jeu.
typedef struct GameGraphics
{
    Scene* m_scene;
    AABB m_gridAABB;
    Vec2 m_padding;
    Vec2 m_spacing;

    AABB m_cells[GAME_GRID_GRAPHIC_SIZE_Y][GAME_GRID_GRAPHIC_SIZE_X];

    
    AABB m_cells_top[1][1];
    AABB m_gridAABB_top;

    AABB m_cells_left[1][1];
    AABB m_gridAABB_left;

    AABB m_cells_right[1][1];
    AABB m_gridAABB_right;

    AABB m_cells_bottom[1][1];
    AABB m_gridAABB_bottom;

    AABB m_cells_center[1][1];
    AABB m_gridAABB_center;

    AABB m_cells_bottom_bottom[1][1];
    AABB m_gridAABB_bottom_bottom;
    

    int m_selectedRowIndex;
    int m_selectedColIndex;

    SpriteGroup* m_spriteBox;
    SpriteGroup* m_spriteKey;
    SpriteGroup* m_spriteGhost;
    SpriteGroup* m_spritePillar;
    SpriteGroup* m_spriteAxe;
    SpriteGroup* m_spriteDiamond;
    SpriteGroup* m_spriteCube;
    SpriteGroup* m_spriteCube_base;
    SpriteGroup* m_spriteStone;
    SpriteGroup* m_spriteDoor;

    SpriteGroup* m_spriteCube_key;
    SpriteGroup* m_spriteCube_axe;
    SpriteGroup* m_spriteCube_axe_key;

    SpriteGroup* m_spriteMedal;

    Plateau plateau;

    bool m_enabled;
} GameGraphics;

GameGraphics* GameGraphics_create(Scene* scene);
void GameGraphics_destroy(GameGraphics* self);
void GameGraphics_update(GameGraphics* self);
void GameGraphics_render(GameGraphics* self);

INLINE void GameGraphics_setEnabled(GameGraphics* self, bool enabled)
{
    assert(self && "self must not be NULL");
    self->m_enabled = enabled;
}
