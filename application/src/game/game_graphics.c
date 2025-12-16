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

    self->m_gridAABB_top.lower = Vec2_add(Vec2_set(-0.3f, -0.3f), Vec2_set(3.6f, 6.3f));
    self->m_gridAABB_top.upper = Vec2_add(Vec2_set(+0.3f, +0.3f), Vec2_set(3.6f, 6.3f));

    self->m_gridAABB_center.lower = Vec2_add(Vec2_set(-0.3f, -0.3f), Vec2_set(3.6f, 5.6f));
    self->m_gridAABB_center.upper = Vec2_add(Vec2_set(+0.3f, +0.3f), Vec2_set(3.6f, 5.6f));

    self->m_gridAABB_left.lower = Vec2_add(Vec2_set(-0.3f, -0.3f), Vec2_set(2.9f, 5.6f));
    self->m_gridAABB_left.upper = Vec2_add(Vec2_set(+0.3f, +0.3f), Vec2_set(2.9f, 5.6f));

    self->m_gridAABB_right.lower = Vec2_add(Vec2_set(-0.3f, -0.3f), Vec2_set(4.3f, 5.6f));
    self->m_gridAABB_right.upper = Vec2_add(Vec2_set(+0.3f, +0.3f), Vec2_set(4.3f, 5.6f));
     
    self->m_gridAABB_bottom.lower = Vec2_add(Vec2_set(-0.3f, -0.3f), Vec2_set(3.6f, 4.9f));
    self->m_gridAABB_bottom.upper = Vec2_add(Vec2_set(+0.3f, +0.3f), Vec2_set(3.6f, 4.9f));

    self->m_gridAABB_bottom_bottom.lower = Vec2_add(Vec2_set(-0.3f, -0.3f), Vec2_set(3.6f, 4.2f));
    self->m_gridAABB_bottom_bottom.upper = Vec2_add(Vec2_set(+0.3f, +0.3f), Vec2_set(3.6f, 4.2f));
    

    self->plateau = Plateau_2();
    Print_plateau(self->plateau);
    self->m_selectedColIndex = self->plateau.cube.j + 1;
    self->m_selectedRowIndex = self->plateau.cube.i + 1;


    // Création des personnages

    AssetManager* assets = Scene_getAssetManager(scene);
    SpriteSheet* spriteSheet = AssetManager_getSpriteSheet(assets, SPRITE_GAME);
    AssertNew(spriteSheet);
    self->m_spriteCube = SpriteSheet_getGroupByName(spriteSheet, "nain");
    self->m_spriteBox = SpriteSheet_getGroupByName(spriteSheet, "box");
    self->m_spriteKey = SpriteSheet_getGroupByName(spriteSheet, "key");
    self->m_spriteDiamond = SpriteSheet_getGroupByName(spriteSheet, "diamond");
    self->m_spriteAxe = SpriteSheet_getGroupByName(spriteSheet, "axe");
    self->m_spriteGhost = SpriteSheet_getGroupByName(spriteSheet, "fantom");
    self->m_spritePillar = SpriteSheet_getGroupByName(spriteSheet, "pillier");
    self->m_spriteStone = SpriteSheet_getGroupByName(spriteSheet, "rock");
    self->m_spriteDoor = SpriteSheet_getGroupByName(spriteSheet, "door");

    self->m_spriteCube_base = SpriteSheet_getGroupByName(spriteSheet, "nain");
    self->m_spriteCube_key = SpriteSheet_getGroupByName(spriteSheet, "nain_key");
    self->m_spriteCube_axe = SpriteSheet_getGroupByName(spriteSheet, "nain_hache");
    self->m_spriteCube_axe_key = SpriteSheet_getGroupByName(spriteSheet, "nain_hache_key");

    self->m_spriteMedal = SpriteSheet_getGroupByName(spriteSheet, "medal");

    AssertNew(self->m_spriteCube);
    AssertNew(self->m_spriteBox);
    AssertNew(self->m_spriteKey);
    

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
    float totalSpacingX = self->m_spacing.x * (GAME_GRID_GRAPHIC_SIZE_X - 1);
    float totalSpacingY = self->m_spacing.y * (GAME_GRID_GRAPHIC_SIZE_Y - 1);

    Vec2 gridSize = AABB_getSize(&(self->m_gridAABB));

    float cellW = (gridSize.x - totalPaddingX - totalSpacingX) / GAME_GRID_GRAPHIC_SIZE_X;

    //float cellH = (gridSize.y - totalPaddingY - totalSpacingY) / GAME_GRID_SIZE_Y;
    float cellH = cellW;

    /*
    Vec2 gridSize_2 = AABB_getSize(&(self->m_gridAABB));

    float cellW_2 = (gridSize_2.x - totalPaddingX - totalSpacingX) / GAME_GRID_SIZE_X;
    float cellH_2 = cellW_2;
    */


    for (int i = 0; i < GAME_GRID_GRAPHIC_SIZE_Y; i++)
    {
        for (int j = 0; j < GAME_GRID_GRAPHIC_SIZE_X; j++)
        {
            float cellX = self->m_gridAABB.lower.x + self->m_padding.x + j * (cellW + self->m_spacing.x);
            float cellY = self->m_gridAABB.lower.y + self->m_padding.y + i * (cellH + self->m_spacing.y);
            self->m_cells[GAME_GRID_GRAPHIC_SIZE_Y - 1 - i][j].lower = Vec2_set(cellX, cellY);
            self->m_cells[GAME_GRID_GRAPHIC_SIZE_Y - 1 - i][j].upper = Vec2_set(cellX + cellW, cellY + cellH);
        }
    }

    float cellX = self->m_gridAABB_top.lower.x + self->m_padding.x  * (cellW + self->m_spacing.x);
    float cellY = self->m_gridAABB_top.lower.y + self->m_padding.y  * (cellH + self->m_spacing.y);
    self->m_cells_top[0][0].lower = Vec2_set(cellX, cellY);
    self->m_cells_top[0][0].upper = Vec2_set(cellX + cellW, cellY + cellH);

    cellX = self->m_gridAABB_center.lower.x + self->m_padding.x * (cellW + self->m_spacing.x);
    cellY = self->m_gridAABB_center.lower.y + self->m_padding.y * (cellH + self->m_spacing.y);
    self->m_cells_center[0][0].lower = Vec2_set(cellX, cellY);
    self->m_cells_center[0][0].upper = Vec2_set(cellX + cellW, cellY + cellH);

    cellX = self->m_gridAABB_right.lower.x + self->m_padding.x * (cellW + self->m_spacing.x);
    cellY = self->m_gridAABB_right.lower.y + self->m_padding.y * (cellH + self->m_spacing.y);
    self->m_cells_right[0][0].lower = Vec2_set(cellX, cellY);
    self->m_cells_right[0][0].upper = Vec2_set(cellX + cellW, cellY + cellH);

    cellX = self->m_gridAABB_left.lower.x + self->m_padding.x * (cellW + self->m_spacing.x);
    cellY = self->m_gridAABB_left.lower.y + self->m_padding.y * (cellH + self->m_spacing.y);
    self->m_cells_left[0][0].lower = Vec2_set(cellX, cellY);
    self->m_cells_left[0][0].upper = Vec2_set(cellX + cellW, cellY + cellH);

    cellX = self->m_gridAABB_bottom.lower.x + self->m_padding.x * (cellW + self->m_spacing.x);
    cellY = self->m_gridAABB_bottom.lower.y + self->m_padding.y * (cellH + self->m_spacing.y);
    self->m_cells_bottom[0][0].lower = Vec2_set(cellX, cellY);
    self->m_cells_bottom[0][0].upper = Vec2_set(cellX + cellW, cellY + cellH);

    cellX = self->m_gridAABB_bottom_bottom.lower.x + self->m_padding.x * (cellW + self->m_spacing.x);
    cellY = self->m_gridAABB_bottom_bottom.lower.y + self->m_padding.y * (cellH + self->m_spacing.y);
    self->m_cells_bottom_bottom[0][0].lower = Vec2_set(cellX, cellY);
    self->m_cells_bottom_bottom[0][0].upper = Vec2_set(cellX + cellW, cellY + cellH);

    /*
    Vec2 gridSize_top = AABB_getSize(&(self->m_gridAABB_top));
    float cellW_top = (gridSize_top.x - totalPaddingX - totalSpacingX);
    float cellH_top = cellW_top;
    float cellX_top = self->m_gridAABB_top.lower.x + self->m_padding.x * (cellW_top + self->m_spacing.x);
    float cellY_top = self->m_gridAABB_top.lower.y + self->m_padding.y * (cellH_top + self->m_spacing.y);
    self->m_cells_top[0][0].lower = Vec2_set(cellX_top, cellY_top);
    self->m_cells_top[0][0].upper = Vec2_set(cellX_top + cellW_top, cellY_top + cellH_top);
    */

    /*
    Vec2 gridSize_center = AABB_getSize(&(self->m_gridAABB_center));
    cellW = (gridSize_center.x - totalPaddingX - totalSpacingX);
    cellH = cellW;
    self->m_cells_center[0][0].lower = Vec2_set(cellX, cellY);
    self->m_cells_center[0][0].upper = Vec2_set(cellX + cellW, cellY + cellH);
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
    //printf("%d\n", self->m_enabled);
    //printf("%d / %d \n", self->m_selectedRowIndex, self->m_selectedColIndex);

    if (input->players->I_pressed)
    {
        self->plateau = Plateau_1();
        Print_plateau(self->plateau);
        self->m_selectedColIndex = self->plateau.cube.j + 1;
        self->m_selectedRowIndex = self->plateau.cube.i + 1;
        self->m_enabled = true;
    }
    else if (input->players->O_pressed)
    {
        self->plateau = Plateau_2();
        Print_plateau(self->plateau);
        self->m_selectedColIndex = self->plateau.cube.j + 1;
        self->m_selectedRowIndex = self->plateau.cube.i + 1;
        self->m_enabled = true;
    }
    else if (input->players->P_pressed)
    {
        self->plateau = Plateau_3();
        Print_plateau(self->plateau);
        self->m_selectedColIndex = self->plateau.cube.j + 1;
        self->m_selectedRowIndex = self->plateau.cube.i + 1;
        self->m_enabled = true;
    }

    if (self->m_enabled == false)
    {
        return;
    }


    if (input->players->left_pressed)
    {
        bool assert = ASSERT_LEFT(self->plateau);
        //printf("Le test gauche : %d\n", assert);
        if (ASSERT_LEFT(self->plateau))
        {
            // le personnage va à gauche
            Cube_left(&self->plateau.cube);
            self->m_selectedColIndex--;
            Plateau_update(&self->plateau);
        }

    }
    else if (input->players->right_pressed)
    {
        bool assert = ASSERT_RIGHT(self->plateau);
        //printf("%d\n", GameCore_CanPlay(self->plateau, 'd', self->plateau->cube->i, self->plateau->cube->j + 1));
        //printf("Le test droite : %d\n", assert);
        if (assert)
        {
            // le personnage va à droite
            Cube_right(&self->plateau.cube);
            self->m_selectedColIndex++;
            Plateau_update(&self->plateau);
        }
    }
    else if (input->players->up_pressed)
    {
        bool assert = ASSERT_BEHIND(self->plateau);
        //printf("Le test haut : %d\n", assert);
        // le personnage va en haut
        if (assert)
        {
            Cube_behind(&self->plateau.cube);
            self->m_selectedRowIndex--;
            Plateau_update(&self->plateau);
        }
    }
    else if (input->players->down_pressed)
    {
        bool assert = ASSERT_FRONT(self->plateau);
        //printf("Le test bas : %d\n", assert);
        if (assert)
        {
            // le personnage va en bas
            Cube_front(&self->plateau.cube);
            self->m_selectedRowIndex++;
            Plateau_update(&self->plateau);
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
        if (ASSERT_ROTA(self->plateau))
        {
            Cube_rota_left(&self->plateau.cube);
        }
    }
    else if (input->players->rotate_right_pressed)
    {
        if (ASSERT_ROTA(self->plateau))
        {
            Cube_rota_right(&self->plateau.cube);
        }
    }

    //printf("La position du nain sur le plateau est : %d %d\n", self->plateau.cube.i, self->plateau.cube.j);
    //Print_plateau(self->plateau);

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

    if (self->plateau.cube.key)
    {
        self->m_spriteCube = self->m_spriteCube_key;

        if (self->plateau.cube.axe)
        {
            self->m_spriteCube = self->m_spriteCube_axe_key;
        }
    }
    else
    {
        self->m_spriteCube = self->m_spriteCube_base;

        if (self->plateau.cube.axe)
        {
            self->m_spriteCube = self->m_spriteCube_axe;
        }
    }

    bool Have_already_win = (self->m_selectedRowIndex == 0 && self->m_selectedColIndex == 3);
    
    for (int i = 0; i < GAME_GRID_GRAPHIC_SIZE_Y; i++)
    {
        for (int j = 0; j < GAME_GRID_GRAPHIC_SIZE_X; j++)
        {
            
            AABB* cellAABB = &(self->m_cells[i][j]);
            rect.x = Camera_worldToViewX(camera, cellAABB->lower.x);
            rect.y = Camera_worldToViewY(camera, cellAABB->upper.y);
            rect.w = (cellAABB->upper.x - cellAABB->lower.x) * scale;
            rect.h = (cellAABB->upper.y - cellAABB->lower.y) * scale;
            

            /*
            
            AABB* cellAABB_top = &(self->m_cells_top[i][j]);
            rect_top.x = Camera_worldToViewX(camera, cellAABB_top->lower.x);
            rect_top.y = Camera_worldToViewY(camera, cellAABB_top->upper.y);
            rect_top.w = (cellAABB_top->upper.x - cellAABB_top->lower.x) * scale;
            rect_top.h = (cellAABB_top->upper.y - cellAABB_top->lower.y) * scale;
            

            SDL_RenderFillRect(g_renderer, &rect_top);    
            */

            //printf("les coordonnées du nain sont : %d %d\n", self->m_selectedRowIndex, self->m_selectedColIndex);

            bool isSelected = (i == self->m_selectedRowIndex && j == self->m_selectedColIndex);

            SDL_Color color = isSelected ? g_colors.gray9 : g_colors.gray7;

            if (self->m_selectedRowIndex == 0 && self->m_selectedColIndex == 3)
            {
                self->m_enabled = false;
                color = g_colors.green2;
            }

            SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(g_renderer, &rect);

            

            if (i == 0 || i == 5 || j == 0 || j == 6)
            {
                if (j != 3 || i != 0)
                {
                    SpriteGroup_render(self->m_spriteStone, 0, &rect, Vec2_anchor_north_west, 1.0f);
                }
                else
                {
                    if (!Have_already_win)
                    {
                        SpriteGroup_render(self->m_spriteDoor, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    }
                }
            }
            else
            {
                // NOTHING, BOX, PILLAR, DIAMOND, DOWN_AXE, DOWN_KEY, GHOST, END
                //Print_plateau(self->plateau);
                switch (self->plateau.board[i - 1][j - 1].value) {
                case DOWN_KEY:
                    SpriteGroup_render(self->m_spriteKey, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case PILLAR:
                    SpriteGroup_render(self->m_spritePillar, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case BOX:
                    SpriteGroup_render(self->m_spriteBox, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case DOWN_AXE:
                    SpriteGroup_render(self->m_spriteAxe, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case GHOST:
                    SpriteGroup_render(self->m_spriteGhost, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                case DIAMOND:
                    SpriteGroup_render(self->m_spriteDiamond, 0, &rect, Vec2_anchor_north_west, 1.0f);
                    break;
                }
            }

            if (isSelected)
            {
                //printf("%d\n", self->plateau->cube->over->code);
                if (!Have_already_win)
                {
                    SpriteGroup_render(self->m_spriteCube, self->plateau.cube.over, &rect, Vec2_anchor_north_west, 1.0f);
                }
                else
                {
                    SpriteGroup_render(self->m_spriteMedal, 0, &rect, Vec2_anchor_north_west, 1.0f);
                }

            }

            
        }
    }



    SDL_FRect rect_top = { 0 };
    AABB* cellAABB_top = &(self->m_cells_top[0][0]);
    rect_top.x = Camera_worldToViewX(camera, cellAABB_top->lower.x);
    rect_top.y = Camera_worldToViewY(camera, cellAABB_top->upper.y);
    rect_top.w = (cellAABB_top->upper.x - cellAABB_top->lower.x) * scale;
    rect_top.h = (cellAABB_top->upper.y - cellAABB_top->lower.y) * scale;
    SpriteGroup_render(self->m_spriteCube, self->plateau.cube.behind, &rect_top, Vec2_anchor_north_west, 1.0f);
    
    
    SDL_FRect rect_center = { 0 };
    AABB* cellAABB_center = &(self->m_cells_center[0][0]);
    rect_center.x = Camera_worldToViewX(camera, cellAABB_center->lower.x);
    rect_center.y = Camera_worldToViewY(camera, cellAABB_center->upper.y);
    rect_center.w = (cellAABB_center->upper.x - cellAABB_center->lower.x) * scale;
    rect_center.h = (cellAABB_center->upper.y - cellAABB_center->lower.y) * scale;
    SpriteGroup_render(self->m_spriteCube, self->plateau.cube.over, &rect_center, Vec2_anchor_north_west, 1.0f);

    SDL_FRect rect_right = { 0 };
    AABB* cellAABB_right = &(self->m_cells_right[0][0]);
    rect_right.x = Camera_worldToViewX(camera, cellAABB_right->lower.x);
    rect_right.y = Camera_worldToViewY(camera, cellAABB_right->upper.y);
    rect_right.w = (cellAABB_right->upper.x - cellAABB_right->lower.x) * scale;
    rect_right.h = (cellAABB_right->upper.y - cellAABB_right->lower.y) * scale;
    SpriteGroup_render(self->m_spriteCube, self->plateau.cube.right, &rect_right, Vec2_anchor_north_west, 1.0f);

    SDL_FRect rect_left = { 0 };
    AABB* cellAABB_left = &(self->m_cells_left[0][0]);
    rect_left.x = Camera_worldToViewX(camera, cellAABB_left->lower.x);
    rect_left.y = Camera_worldToViewY(camera, cellAABB_left->upper.y);
    rect_left.w = (cellAABB_left->upper.x - cellAABB_left->lower.x) * scale;
    rect_left.h = (cellAABB_left->upper.y - cellAABB_left->lower.y) * scale;
    SpriteGroup_render(self->m_spriteCube, self->plateau.cube.left, &rect_left, Vec2_anchor_north_west, 1.0f);

    SDL_FRect rect_bottom = { 0 };
    AABB* cellAABB_bottom = &(self->m_cells_bottom[0][0]);
    rect_bottom.x = Camera_worldToViewX(camera, cellAABB_bottom->lower.x);
    rect_bottom.y = Camera_worldToViewY(camera, cellAABB_bottom->upper.y);
    rect_bottom.w = (cellAABB_bottom->upper.x - cellAABB_bottom->lower.x) * scale;
    rect_bottom.h = (cellAABB_bottom->upper.y - cellAABB_bottom->lower.y) * scale;
    SpriteGroup_render(self->m_spriteCube, self->plateau.cube.front, &rect_bottom, Vec2_anchor_north_west, 1.0f);

    SDL_FRect rect_bottom_bottom = { 0 };
    AABB* cellAABB_bottom_bottom = &(self->m_cells_bottom_bottom[0][0]);
    rect_bottom_bottom.x = Camera_worldToViewX(camera, cellAABB_bottom_bottom->lower.x);
    rect_bottom_bottom.y = Camera_worldToViewY(camera, cellAABB_bottom_bottom->upper.y);
    rect_bottom_bottom.w = (cellAABB_bottom_bottom->upper.x - cellAABB_bottom_bottom->lower.x) * scale;
    rect_bottom_bottom.h = (cellAABB_bottom_bottom->upper.y - cellAABB_bottom_bottom->lower.y) * scale;
    SpriteGroup_render(self->m_spriteCube, self->plateau.cube.under, &rect_bottom_bottom, Vec2_anchor_north_west, 1.0f);
       

}
