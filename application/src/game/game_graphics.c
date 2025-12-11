/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/game_graphics.h"
#include "common/assets.h"
#include "common/common.h"
#include "game/input.h"
#include "game/scene.h"
#include "game/game_config.h"

//GameCore* core = &(g_gameConfig.core);

GameGraphics* GameGraphics_create(Scene* scene)
{
    GameGraphics* self = (GameGraphics*)calloc(1, sizeof(GameGraphics));

    AssertNew(self);

    TTF_Font* font = NULL;

    self->m_scene = scene;
    self->m_padding = Vec2_set(0.0f, 0.0f);
    self->m_spacing = Vec2_set(0.2f, 0.2f);
    self->m_gridAABB.lower = Vec2_add(Vec2_set(-4.f, -4.f), Vec2_set(11.0f, 5.0f));
    self->m_gridAABB.upper = Vec2_add(Vec2_set(+4.f, +4.f), Vec2_set(11.0f, 5.0f));
    self->m_enabled = false;

    /*
    self->m_gridAABB_2.lower = Vec2_add(Vec2_set(-1.f, -1.f), Vec2_set(3.0f, 5.0f));
    self->m_gridAABB_2.upper = Vec2_add(Vec2_set(+1.f, +1.f), Vec2_set(3.0f, 5.0f));
    */

    self->plateau = Plateau_create();
    Bulid_Easy_Plateau(self->plateau);
    self->m_selectedColIndex = self->plateau->cube->j + 1;
    self->m_selectedRowIndex = self->plateau->cube->i + 1;

    // Création des personnages

    AssetManager* assets = Scene_getAssetManager(scene);
    SpriteSheet* spriteSheet = AssetManager_getSpriteSheet(assets, SPRITE_GAME);
    AssertNew(spriteSheet);
    self->m_spriteNain = SpriteSheet_getGroupByName(spriteSheet, "rabbit");
    self->m_spriteBox = SpriteSheet_getGroupByName(spriteSheet, "mushroom");
    self->m_spriteKey = SpriteSheet_getGroupByName(spriteSheet, "fox");
    self->m_spriteDiamond = SpriteSheet_getGroupByName(spriteSheet, "fox");
    self->m_spriteHache = SpriteSheet_getGroupByName(spriteSheet, "fox");
    self->m_spriteFantome = SpriteSheet_getGroupByName(spriteSheet, "fox");
    self->m_spritePillier = SpriteSheet_getGroupByName(spriteSheet, "fox");
    self->m_spriteStone = SpriteSheet_getGroupByName(spriteSheet, "mushroom");
    self->m_spriteDoor = SpriteSheet_getGroupByName(spriteSheet, "fox");

AssertNew(self->m_spriteNain);

return self;
}

void GameGraphics_destroy(GameGraphics* self)
{
    if (!self) return;
    free(self);
}

static void GameGraphics_updateCells(GameGraphics* self)
{
    float totalPaddingX = self->m_padding.x * 2.f;
    float totalPaddingY = self->m_padding.y * 2.f;
    float totalSpacingX = self->m_spacing.x * (GAME_GRID_SIZE_X - 1);
    float totalSpacingY = self->m_spacing.y * (GAME_GRID_SIZE_Y - 1);

    Vec2 gridSize = AABB_getSize(&(self->m_gridAABB));

    float cellW = (gridSize.x - totalPaddingX - totalSpacingX) / GAME_GRID_SIZE_X;

    //float cellH = (gridSize.y - totalPaddingY - totalSpacingY) / GAME_GRID_SIZE_Y;
    float cellH = cellW;

    /*
    Vec2 gridSize_2 = AABB_getSize(&(self->m_gridAABB));

    float cellW_2 = (gridSize_2.x - totalPaddingX - totalSpacingX) / GAME_GRID_SIZE_X;
    float cellH_2 = cellW_2;
    */


    for (int i = 0; i < GAME_GRID_SIZE_Y; i++)
    {
        for (int j = 0; j < GAME_GRID_SIZE_X; j++)
        {
            float cellX = self->m_gridAABB.lower.x + self->m_padding.x + j * (cellW + self->m_spacing.x);
            float cellY = self->m_gridAABB.lower.y + self->m_padding.y + i * (cellH + self->m_spacing.y);
            self->m_cells[GAME_GRID_SIZE_Y - 1 - i][j].lower = Vec2_set(cellX, cellY);
            self->m_cells[GAME_GRID_SIZE_Y - 1 - i][j].upper = Vec2_set(cellX + cellW, cellY + cellH);
        }
    }

    /*
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            float cellX = self->m_gridAABB_2.lower.x + self->m_padding.x + j * (cellW_2 + self->m_spacing.x);
            float cellY = self->m_gridAABB_2.lower.y + self->m_padding.y + i * (cellH_2 + self->m_spacing.y);
            self->m_cells_2[3 - 1 - i][j].lower = Vec2_set(cellX, cellY);
            self->m_cells_2[3 - 1 - i][j].upper = Vec2_set(cellX + cellW_2, cellY + cellH_2);
        }
    }
    */


}

void GameGraphics_update(GameGraphics* self)
{
    assert(self && "self must not be NULL");
    Scene* scene = self->m_scene;
    Input* input = Scene_getInput(scene);
    Camera* camera = Scene_getCamera(scene);

    GameGraphics_updateCells(self);

    Vec2 mouseWorldPos = { 0 };
    Camera_viewToWorld(camera, input->mouse.position.x, input->mouse.position.y, &mouseWorldPos);

    //Cube_print(self->plateau->cube);
    //Print_plateau(self->plateau);

    //printf("%d / %d \n", self->m_selectedRowIndex, self->m_selectedColIndex);
    
    if (self->m_enabled == false)
    {
        return;
    }
    if (input->players->left_pressed)
    {
        if (GameCore_CanPlay(self->plateau, 'q', self->plateau->cube->i, self->plateau->cube->j - 1))
        {
            // le personnage va à gauche
            self->m_selectedColIndex--;
            self->plateau->plate[self->plateau->cube->i][self->plateau->cube->j] = 0;
            self->plateau->plate[self->plateau->cube->i][self->plateau->cube->j -1] = 'n';
            Cube_left(self->plateau->cube);
        }

    }
    else if (input->players->right_pressed)
    {
        //printf("%d\n", GameCore_CanPlay(self->plateau, 'd', self->plateau->cube->i, self->plateau->cube->j + 1));
        if (GameCore_CanPlay(self->plateau, 'd', self->plateau->cube->i, self->plateau->cube->j + 1))
        {
            // le personnage va à droite
            self->m_selectedColIndex++;
            self->plateau->plate[self->plateau->cube->i][self->plateau->cube->j] = 0;
            self->plateau->plate[self->plateau->cube->i][self->plateau->cube->j + 1] = 'n';
            Cube_right(self->plateau->cube);
        }
    }
    else if (input->players->up_pressed)
    {
        // le personnage va en haut
        if (GameCore_CanPlay(self->plateau, 'z', self->plateau->cube->i - 1, self->plateau->cube->j))
        {
            self->m_selectedRowIndex--;
            self->plateau->plate[self->plateau->cube->i][self->plateau->cube->j] = 0;
            self->plateau->plate[self->plateau->cube->i - 1][self->plateau->cube->j] = 'n';
            Cube_behind(self->plateau->cube);
        }
    }
    else if (input->players->down_pressed)
    {
        if (GameCore_CanPlay(self->plateau, 's', self->plateau->cube->i + 1, self->plateau->cube->j))
        {
            // le personnage va en bas
            self->m_selectedRowIndex++;
            self->plateau->plate[self->plateau->cube->i][self->plateau->cube->j] = 0;
            self->plateau->plate[self->plateau->cube->i + 1][self->plateau->cube->j] = 'n';
            Cube_front(self->plateau->cube);
        }
    }
    else if (input->players->space_pressed)
    {
        if (self->m_selectedRowIndex != 0 || self->m_selectedColIndex != 3)
        {
            if (GameCore_CanFinish(self->plateau))
            {
                self->m_selectedRowIndex--;
            }
        }
    }
    else if (input->players->rotate_left_pressed)
    {
        if (GameCore_CanRotate(self->plateau))
        {
            Cube_rota_left(self->plateau->cube);
        }
    }
    else if (input->players->rotate_right_pressed)
    {
        if (GameCore_CanRotate(self->plateau))
        {
            Cube_rota_right(self->plateau->cube);
        }
    }

    /*
    if (input->mouse.leftPressed)
    {
        for (int i = 0; i < GAME_GRID_SIZE_Y; i++)
        {
            for (int j = 0; j < GAME_GRID_SIZE_X; j++)
            {
                AABB* cellAABB_2 = &(self->m_cells_2[i][j]);
                if (AABB_containsPoint(cellAABB_2, mouseWorldPos))
                {
                    self->m_selectedRowIndex = 2;
                    self->m_selectedColIndex = 2;
                }
            }
        }
    }
    */

}

void GameGraphics_render(GameGraphics* self)
{
    assert(self && "self must not be NULL");

    Scene* scene = self->m_scene;
    Camera* camera = Scene_getCamera(scene);
    float scale = Camera_getWorldToViewScale(camera);

    SDL_FRect rect = { 0 };
    //SDL_FRect rect_2 = { 0 };

    for (int i = 0; i < GAME_GRID_SIZE_Y; i++)
    {
        for (int j = 0; j < GAME_GRID_SIZE_X; j++)
        {
            AABB* cellAABB = &(self->m_cells[i][j]);
            rect.x = Camera_worldToViewX(camera, cellAABB->lower.x);
            rect.y = Camera_worldToViewY(camera, cellAABB->upper.y);
            rect.w = (cellAABB->upper.x - cellAABB->lower.x) * scale;
            rect.h = (cellAABB->upper.y - cellAABB->lower.y) * scale;

            /*
            AABB* cellAABB_2 = &(self->m_cells_2[i][j]);
            rect_2.x = Camera_worldToViewX(camera, cellAABB_2->lower.x);
            rect_2.y = Camera_worldToViewY(camera, cellAABB_2->upper.y);
            rect_2.w = (cellAABB_2->upper.x - cellAABB_2->lower.x) * scale;
            rect_2.h = (cellAABB_2->upper.y - cellAABB_2->lower.y) * scale;
            */


            //SDL_RenderFillRect(g_renderer, &rect_2);



            bool isSelected = (i == self->m_selectedRowIndex && j == self->m_selectedColIndex);

            SDL_Color color = isSelected ? g_colors.gray9 : g_colors.gray7;

            if (self->m_selectedRowIndex == 0 && self->m_selectedColIndex == 3)
            {
                color = g_colors.green2;
            }

            SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(g_renderer, &rect);

            if (isSelected)
            {
                SpriteGroup_render(self->m_spriteNain, 0, &rect, Vec2_anchor_north_west, 1.0f);
            }

            if (i == 0 || i == 5 || j == 0 || j == 6)
            {
                if (j != 3 || i != 0)
                {
                    SpriteGroup_render(self->m_spriteStone, 0, &rect, Vec2_anchor_north_west, 1.0f);
                }
                else
                {
                    SpriteGroup_render(self->m_spriteDoor, 0, &rect, Vec2_anchor_north_west, 1.0f);
                }
            }
            else
            {
                switch (self->plateau->plate[i - 1][j - 1]) {
                case 'k':
                    SpriteGroup_render(self->m_spriteKey, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case 'p':
                    SpriteGroup_render(self->m_spritePillier, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case 'b':
                    SpriteGroup_render(self->m_spriteBox, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case 'h':
                    SpriteGroup_render(self->m_spriteHache, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case 'f':
                    SpriteGroup_render(self->m_spriteFantome, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case 'd':
                    SpriteGroup_render(self->m_spriteDiamond, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;

                }
            }

            
        }
    }
}
