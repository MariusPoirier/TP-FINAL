/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/ui/game_ui_game.h"
#include "game/ui/game_settings_page.h"
#include "game/ui/game_ui_manager.h"
#include "game/scene.h"
#include "game/game_config.h"
#include "common/ui_style.h"

static void GameUiPage_onClick(void* selectable)
{
    GameUiPage* self = (GameUiPage*)UISelectable_getUserData(selectable);
    assert(self && "self must not be NULL");

    int action = UISelectable_getUserId(selectable);
    assert(action >= 0 && action < GAME_UI_ACTION_COUNT && "Invalid action id");
    self->m_nextAction = action;

    printf("Button clicked: %s\n", UIObject_getObjectName(selectable));
}

static void GameUiPage_onItemChanged(void* selectable, int currItemIdx, int prevItemIdx, bool increase)
{
    GameUiPage* self = (GameUiPage*)UISelectable_getUserData(selectable);
    assert(self && "self must not be NULL");

    printf("List item changed: %s\n", UIObject_getObjectName(selectable));
}

GameUiPage* GameUiPage_create(Scene* scene, GameUIManager* manager)
{
    UICanvas* canvas = manager->m_canvas;
    AssetManager* assets = Scene_getAssetManager(scene);
    UIRect rect = { 0 };
    TTF_Font* font = NULL;
    char buffer[128] = { 0 };

    GameUiPage* self = (GameUiPage*)calloc(1, sizeof(GameUiPage));
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
    UILabel_setTextString(label, "Rok Passe partour");
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


    UIList* fullscreenList = UIList_create(
        "fullscreen-list", font, toggleItemCount,
        UI_LIST_CONFIG_CYCLE | UI_LIST_CONFIG_AUTO_NAVIGATION
    );

    self->m_fullscreenList = fullscreenList;

    UIList_setLabelString(fullscreenList, "0");
    for (int i = 0; i < toggleItemCount; ++i)
    {
        UIList_setItemString(fullscreenList, i, toggleItems[i]);
    }
    UIStyle_setDefaultList(fullscreenList, assets);
    UISelectable_setUserData(fullscreenList, self);
    UISelectable_setUserId(fullscreenList, GAME_UI_ACTION_CHANGE_FULLSCREEN);
    UIList_setOnItemChangedCallback(fullscreenList, GameUiPage_onItemChanged);

    SDL_WindowFlags windowFlags = SDL_GetWindowFlags(g_window);
    if (windowFlags & SDL_WINDOW_FULLSCREEN)
    {
        UIList_setSelectedItem(fullscreenList, 1);
    }
    else
    {
        UIList_setSelectedItem(fullscreenList, 0);
    }


    UIGridLayout_addObject(levellayout, fullscreenList, 0, 0, 1, 1);
    UIFocusManager_addSelectable(self->m_focusManager, fullscreenList);

    // Button Generete level
    UIButton* levelButton = UIButton_create("level-button", font);
    UIButton_setLabelString(levelButton, "Générer le niveau");
    UIButton_setOnClickCallback(levelButton, GameUiPage_onClick);
    UISelectable_setUserData(levelButton, self);
    UISelectable_setUserId(levelButton, GAME_UI_ACTION_APPLY_SETTINGS);
    UIStyle_setDefaultButton(levelButton);

    UIGridLayout_addObject(levellayout, levelButton, 0, 1, 1, 1);
    UIFocusManager_addSelectable(self->m_focusManager, levelButton);


    // Button layout
    UIGridLayout* buttonlayout = UIGridLayout_create("button-layout", 1, 2);
    UIGridLayout_setColumnSizes(buttonlayout, 100.f);
    UIGridLayout_setColumnSpacings(buttonlayout, 5.f);
    UIGridLayout_addObject(layout, buttonlayout, 3, 0, 1, 1);

    // Resoudre button
    UIButton* solveButton = UIButton_create("solve-button", font);
    UIButton_setLabelString(solveButton, "Résoudre");
    UIButton_setOnClickCallback(solveButton, GameUiPage_onClick);
    UISelectable_setUserData(solveButton, self);
    UISelectable_setUserId(solveButton, GAME_UI_ACTION_APPLY_SETTINGS);
    UIStyle_setDefaultButton(solveButton);

    UIGridLayout_addObject(buttonlayout, solveButton, 0, 0, 1, 1);
    UIFocusManager_addSelectable(self->m_focusManager, solveButton);

    // Generate button
    UIButton* generateButton = UIButton_create("generate-button", font);
    UIButton_setLabelString(generateButton, "Générer");
    UIButton_setOnClickCallback(generateButton, GameUiPage_onClick);
    UISelectable_setUserData(generateButton, self);
    UISelectable_setUserId(generateButton, GAME_UI_ACTION_OPEN_MAIN);
    UIStyle_setDefaultButton(generateButton);

    UIGridLayout_addObject(buttonlayout, generateButton, 0, 1, 1, 1);
    UIFocusManager_addSelectable(self->m_focusManager, generateButton);

    UIFocusManager_setFocused(self->m_focusManager, fullscreenList);

    UIButton* backButton = UIButton_create("back-button", font);
    UIButton_setLabelString(backButton, "Résoudre");
    UIButton_setOnClickCallback(backButton, GameUiPage_onClick);
    UISelectable_setUserData(backButton, self);
    UISelectable_setUserId(backButton, GAME_UI_ACTION_APPLY_SETTINGS);
    UIStyle_setDefaultButton(backButton);

    UIGridLayout_addObject(layout, backButton, 4, 0, 1, 1);

    UIFocusManager_addSelectable(self->m_focusManager, backButton);

    return self;
}

void GameUiPage_destroy(GameUiPage* self)
{
    if (!self) return;

    UIObject_destroy(self->m_mainPanel);
    UIFocusManager_destroy(self->m_focusManager);

    free(self);
}

void GameUiPage_update(GameUiPage* self, UIInput* input)
{
    UIFocusManager_update(self->m_focusManager, input);

    switch (self->m_nextAction)
    {
    case GAME_UI_ACTION_OPEN_MAIN:
        self->m_manager->m_nextAction = GAME_UI_ACTION_OPEN_MAIN;
        break;

    case GAME_UI_ACTION_APPLY_SETTINGS:
    {
        int itemIndex = UIList_getSelectedItem(self->m_fullscreenList);
        SDL_SetWindowFullscreen(g_window, itemIndex == 1);
        g_gameConfig.showElapsedTime = (bool)UIList_getSelectedItem(self->m_elapsedList);
        self->m_manager->m_nextAction = GAME_UI_ACTION_OPEN_MAIN;
        break;
    }
    default:
        break;
    }
    self->m_nextAction = GAME_UI_ACTION_NONE;
}
