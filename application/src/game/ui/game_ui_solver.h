/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "game/ui/game_ui_manager.h"

typedef struct Scene Scene;
typedef struct GameUiSolverPage
{
    Scene* m_scene;
    GameUIManager* m_manager;
    UIFocusManager* m_focusManager;

    UIList* m_LevelList;
    //UIList* m_elapsedList;

    GameUIAction m_nextAction;
    UIObject* m_mainPanel;
} GameUiSolverPage;

GameUiSolverPage* GameUiSolverPage_create(Scene* scene, GameUIManager* manager);
void GameUiSolverPage_destroy(GameUiSolverPage* self);
void GameUiSolverPage_update(GameUiSolverPage* self, UIInput* input);
