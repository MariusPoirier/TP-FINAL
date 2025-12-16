/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/ui/game_ui_solver.h"
#include "game/ui/game_settings_page.h"
#include "game/ui/game_ui_manager.h"
#include "game/core/solver/solver.h"
#include "game/core/plateau/plateau.h"
#include "game/scene.h"
#include "game/game_config.h"
#include "common/ui_style.h"

static void GameUiSolverPage_onClick(void* selectable)
{
    GameUiSolverPage* self = (GameUiSolverPage*)UISelectable_getUserData(selectable);
    assert(self && "self must not be NULL");

    int action = UISelectable_getUserId(selectable);
    assert(action >= 0 && action < GAME_UI_ACTION_COUNT && "Invalid action id");
    self->m_nextAction = action;

    printf("Button clicked: %s\n", UIObject_getObjectName(selectable));
}

static void GameUiSolverPage_onItemChanged(void* selectable, int currItemIdx, int prevItemIdx, bool increase)
{
    GameUiSolverPage* self = (GameUiSolverPage*)UISelectable_getUserData(selectable);
    assert(self && "self must not be NULL");

    printf("List item changed: %s\n", UIObject_getObjectName(selectable));
}

GameUiSolverPage* GameUiSolverPage_create(Scene* scene, GameUIManager* manager)
{
    UICanvas* canvas = manager->m_canvas;
    AssetManager* assets = Scene_getAssetManager(scene);
    UIRect rect = { 0 };
    TTF_Font* font = NULL;
    char buffer[128] = { 0 };

    GameUiSolverPage* self = (GameUiSolverPage*)calloc(1, sizeof(GameUiSolverPage));
    AssertNew(self);

    self->m_scene = scene;
    self->m_manager = manager;
    self->m_mainPanel = UIObject_create("main-panel");
    self->m_nextAction = GAME_UI_ACTION_NONE;
    self->m_focusManager = UIFocusManager_create();
    UIFocusManager_setCanvas(self->m_focusManager, canvas);

    UIObject_setParent(self->m_mainPanel, canvas);
    rect.anchorMin = Vec2_set(0.15f, 0.0f);
    rect.anchorMax = Vec2_set(0.3f, 1.0f);
    rect.offsetMin = Vec2_zero;
    rect.offsetMax = Vec2_zero;
    UIObject_setRect(self->m_mainPanel, rect);

    UIGridLayout* layout = UIGridLayout_create("main-layout", 5, 1);
    UIObject_setParent(layout, self->m_mainPanel);
    UIGridLayout_setRowSizes(layout, 25.0f);
    UIGridLayout_setRowSpacings(layout, 5.f);
    UIGridLayout_setRowSpacing(layout, 0, 100.f);
    UIGridLayout_setRowSpacing(layout, 2, 10.f);

    // Title
    font = AssetManager_getFont(assets, FONT_BIG_BOLD);
    UILabel* label = UILabel_create("title-label", font);
    UILabel_setTextString(label, "Le Solver tah Lewandowski");
    UILabel_setAnchor(label, Vec2_anchor_center);
    UILabel_setColor(label, g_colors.white);
    UIGridLayout_addObject(layout, label, 0, 0, 1, 1);

    // Niveau layout
    UIGridLayout* levellayout = UIGridLayout_create("level-layout", 1, 2);
    UIGridLayout_setColumnSizes(levellayout, 100.f);
    UIGridLayout_setColumnSpacings(levellayout, 5.f);
    UIGridLayout_addObject(layout, levellayout, 2, 0, 1, 1);

    font = AssetManager_getFont(assets, FONT_NORMAL);

    const char* toggleItems[] = { "Easy", "Medium" , "Hard" };
    const int toggleItemCount = sizeof(toggleItems) / sizeof(toggleItems[0]);


    UIList* fullLevelList = UIList_create(
        "fullscreen-list", font, toggleItemCount,
        0 | 1 | 2
    );

    self->m_LevelList = fullLevelList;

    UIList_setLabelString(fullLevelList, "0");
    for (int i = 0; i < toggleItemCount; ++i)
    {
        UIList_setItemString(fullLevelList, i, toggleItems[i]);
    }
    UIStyle_setDefaultList(fullLevelList, assets);
    UISelectable_setUserData(fullLevelList, self);
    UISelectable_setUserId(fullLevelList, GAME_UI_ACTION_CHANGE_FULLSCREEN);
    UIList_setOnItemChangedCallback(fullLevelList, GameUiSolverPage_onItemChanged);

    SDL_WindowFlags windowFlags = SDL_GetWindowFlags(g_window);
    if (windowFlags & SDL_WINDOW_FULLSCREEN)
    {
        UIList_setSelectedItem(fullLevelList, 1);
    }
    else
    {
        UIList_setSelectedItem(fullLevelList, 0);
    }


    UIGridLayout_addObject(levellayout, fullLevelList, 0, 0, 1, 1);
    UIFocusManager_addSelectable(self->m_focusManager, fullLevelList);


    // Button Generete level
    UIButton* levelButton = UIButton_create("level-button", font);
    UIButton_setLabelString(levelButton, "PRINTF");
    UIButton_setOnClickCallback(levelButton, GameUiSolverPage_onClick);
    UISelectable_setUserData(levelButton, self);
    UISelectable_setUserId(levelButton, GAME_UI_ACTION_SHOW_SOLUTION);
    UIStyle_setDefaultButton(levelButton);

    UIGridLayout_addObject(levellayout, levelButton, 0, 1, 1, 1);
    UIFocusManager_addSelectable(self->m_focusManager, levelButton);


    // Button layout
    UIGridLayout* buttonlayout = UIGridLayout_create("button-layout", 1, 2);
    UIGridLayout_setColumnSizes(buttonlayout, 100.f);
    UIGridLayout_setColumnSpacings(buttonlayout, 5.f);
    UIGridLayout_addObject(layout, buttonlayout, 3, 0, 1, 1);

    // Resoudre button
    UIButton* solveButton = UIButton_create("previous-button", font);
    UIButton_setLabelString(solveButton, "Coup précédent");
    UIButton_setOnClickCallback(solveButton, GameUiSolverPage_onClick);
    UISelectable_setUserData(solveButton, self);
    UISelectable_setUserId(solveButton, GAME_UI_ACTION_PREV_STEP);
    UIStyle_setDefaultButton(solveButton);

    UIGridLayout_addObject(buttonlayout, solveButton, 0, 0, 1, 1);
    UIFocusManager_addSelectable(self->m_focusManager, solveButton);

    // Generate button
    UIButton* generateButton = UIButton_create("next-button", font);
    UIButton_setLabelString(generateButton, "Coup suivant");
    UIButton_setOnClickCallback(generateButton, GameUiSolverPage_onClick);
    UISelectable_setUserData(generateButton, self);
    UISelectable_setUserId(generateButton, GAME_UI_ACTION_NEXT_STEP);
    UIStyle_setDefaultButton(generateButton);

    UIGridLayout_addObject(buttonlayout, generateButton, 0, 1, 1, 1);
    UIFocusManager_addSelectable(self->m_focusManager, generateButton);

    //UIFocusManager_setFocused(self->m_focusManager, fullscreenList);

    UIButton* backButton = UIButton_create("back-button", font);
    UIButton_setLabelString(backButton, "Back");
    UIButton_setOnClickCallback(backButton, GameUiSolverPage_onClick);
    UISelectable_setUserData(backButton, self);
    UISelectable_setUserId(backButton, GAME_UI_ACTION_QUIT);
    UIStyle_setDefaultButton(backButton);

    UIGridLayout_addObject(layout, backButton, 4, 0, 1, 1);

    UIFocusManager_addSelectable(self->m_focusManager, backButton);

    return self;
}

void GameUiSolverPage_destroy(GameUiSolverPage* self)
{
    if (!self) return;

    UIObject_destroy(self->m_mainPanel);
    UIFocusManager_destroy(self->m_focusManager);

    free(self);
}

void GameUiSolverPage_update(GameUiSolverPage* self, UIInput* input)
{
    UIFocusManager_update(self->m_focusManager, input);

    switch (self->m_nextAction)
    {
    case GAME_UI_ACTION_OPEN_MAIN:
        self->m_manager->m_nextAction = GAME_UI_ACTION_OPEN_MAIN;
        break;
    case GAME_UI_ACTION_QUIT:
        self->m_manager->m_nextAction = GAME_UI_ACTION_START;
        break;
    case GAME_UI_ACTION_PREV_STEP:
        printf("Previous step\n");
        self->m_scene->m_gameGraphics->m_selectedColIndex += 1;
        break;
    case GAME_UI_ACTION_NEXT_STEP:
        printf("Next step\n");
        self->m_scene->m_gameGraphics->m_selectedColIndex -= 1;
        break;
    case GAME_UI_ACTION_SHOW_SOLUTION:
        GameHashmap *hash_map = GameHashmap_create(10000);
        Solver(self->m_scene->m_gameGraphics->plateau, hash_map->m_capacity);

        printf("Le nombre de coup est de : %d \n", hash_map->m_size);
        printf("Generate level button clicked\n");
        break;
    case GAME_UI_ACTION_APPLY_LEVEL:
    {

        int itemIndex = UIList_getSelectedItem(self->m_LevelList);
        printf("Selected level difficulty: %d\n", itemIndex);
        if (itemIndex == 0)
        {
            self->m_manager->m_nextAction = GAME_UI_ACTION_GENERATE_LEVEL_EASY;
            self->m_scene->m_gameGraphics->plateau = Plateau_1();
            Print_plateau(self->m_scene->m_gameGraphics->plateau);
            self->m_scene->m_gameGraphics->m_selectedColIndex = self->m_scene->m_gameGraphics->plateau.cube.j + 1;
            self->m_scene->m_gameGraphics->m_selectedRowIndex = self->m_scene->m_gameGraphics->plateau.cube.i + 1;
            self->m_scene->m_gameGraphics->m_enabled = true;
        }
        else if (itemIndex == 1)
        {
            self->m_manager->m_nextAction = GAME_UI_ACTION_GENERATE_LEVEL_MEDIUM;
            self->m_scene->m_gameGraphics->plateau = Plateau_2();
            Print_plateau(self->m_scene->m_gameGraphics->plateau);
            self->m_scene->m_gameGraphics->m_selectedColIndex = self->m_scene->m_gameGraphics->plateau.cube.j + 1;
            self->m_scene->m_gameGraphics->m_selectedRowIndex = self->m_scene->m_gameGraphics->plateau.cube.i + 1;
            self->m_scene->m_gameGraphics->m_enabled = true;
        }
        else if (itemIndex == 2)
        {
            self->m_manager->m_nextAction = GAME_UI_ACTION_GENERATE_LEVEL_HARD;
            self->m_scene->m_gameGraphics->plateau = Plateau_3();
            Print_plateau(self->m_scene->m_gameGraphics->plateau);
            self->m_scene->m_gameGraphics->m_selectedColIndex = self->m_scene->m_gameGraphics->plateau.cube.j + 1;
            self->m_scene->m_gameGraphics->m_selectedRowIndex = self->m_scene->m_gameGraphics->plateau.cube.i + 1;
            self->m_scene->m_gameGraphics->m_enabled = true;
        }
        //g_gameConfig.showElapsedTime = (bool)UIList_getSelectedItem(self->m_LevelList);        
        self->m_manager->m_nextAction = GAME_UI_ACTION_GENERATE_LEVEL_EASY;

        break;
    }
    default:
        break;
    }
    self->m_nextAction = GAME_UI_ACTION_NONE;
}
