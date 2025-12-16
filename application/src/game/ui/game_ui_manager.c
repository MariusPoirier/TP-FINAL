/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/ui/game_ui_manager.h"
#include "game/ui/game_ui_game.h"
#include "game/ui/game_ui_solver.h"
#include "game/ui/game_title_page.h"
#include "game/ui/game_settings_page.h"
#include "game/scene.h"
#include "game/game_config.h"

static void GameUIManager_closePages(GameUIManager* self);

GameUIManager* GameUIManager_create(Scene* scene)
{
    GameUIManager* self = (GameUIManager*)calloc(1, sizeof(GameUIManager));
    AssertNew(self);

    self->m_scene = scene;

    UICanvas* canvas = UICanvas_create("canvas");
    self->m_canvas = canvas;
    self->m_mainPage = GameTitlePage_create(scene, self);
    self->m_settingsPage = NULL;

    return self;
}

void GameUIManager_destroy(GameUIManager* self)
{
    if (!self) return;

    GameUIManager_closePages(self);
    UIObject_destroy(self->m_canvas);

    free(self);
}

static void GameUIManager_closePages(GameUIManager* self)
{
    GameTitlePage_destroy(self->m_mainPage);
    GameSettingsPage_destroy(self->m_settingsPage);
    GameUiPage_destroy(self->m_gameUiPage);
    GameUiSolverPage_destroy(self->m_gameUiSolverPage);

    g_gameConfig.inLevel = false;
    self->m_mainPage = NULL;
    self->m_settingsPage = NULL;
    self->m_gameUiPage = NULL;
    self->m_gameUiSolverPage = NULL;
}

void GameUIManager_update(GameUIManager* self, UIInput* input)
{
    Scene* scene = self->m_scene;
    UIObject_update(self->m_canvas);
    if (self->m_mainPage)
    {
        GameTitlePage_update(self->m_mainPage, input);
    }
    if (self->m_settingsPage)
    {
        GameSettingsPage_update(self->m_settingsPage, input);
    }
    if (self->m_gameUiPage)
    {
        GameUiPage_update(self->m_gameUiPage, input);
    }
    if (self->m_gameUiSolverPage)
    {
        GameUiSolverPage_update(self->m_gameUiSolverPage, input);
    }

    if (self->m_nextAction != GAME_UI_ACTION_NONE)
    {
        switch (self->m_nextAction)
        {
        case GAME_UI_ACTION_OPEN_SETTINGS:
            GameUIManager_closePages(self);
            self->m_settingsPage = GameSettingsPage_create(scene, self);
            break;

        case GAME_UI_ACTION_OPEN_MAIN:
            GameUIManager_closePages(self);
            self->m_mainPage = GameTitlePage_create(scene, self);
            break;

        case GAME_UI_ACTION_START:
            GameUIManager_closePages(self);
            g_gameConfig.inLevel = true;
            self->m_gameUiPage = GameUiPage_create(scene, self);
            GameGraphics_setEnabled(scene->m_gameGraphics, true);
            break;
        case GAME_UI_ACTION_SHOW_SOLUTION:
            GameUIManager_closePages(self);
            g_gameConfig.inLevel = true;
            self->m_gameUiSolverPage = GameUiSolverPage_create(scene, self);
            GameGraphics_setEnabled(scene->m_gameGraphics, false);
            break;

        case GAME_UI_ACTION_HIDE_SOLUTION:
            GameUIManager_closePages(self);
            g_gameConfig.inLevel = true;
            self->m_gameUiPage = GameUiPage_create(scene, self);
            GameGraphics_setEnabled(scene->m_gameGraphics, true);
            break;
        }
        self->m_nextAction = GAME_UI_ACTION_NONE;
    }

    UIObject_update(self->m_canvas);
}

void GameUIManager_render(GameUIManager* self)
{
    UIObject_render(self->m_canvas);
}
