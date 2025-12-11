/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "game/ui/game_ui_manager.h"

typedef struct Scene Scene;
typedef struct GameUiPage
{
    Scene* m_scene;
    GameUIManager* m_manager;
    UIFocusManager* m_focusManager;

    UIList* m_fullscreenList;
    UIList* m_elapsedList;

    GameUIAction m_nextAction;
    UIObject* m_mainPanel;
} GameUiPage;

GameUiPage* GameUiPage_create(Scene* scene, GameUIManager* manager);
void GameUiPage_destroy(GameUiPage* self);
void GameUiPage_update(GameUiPage* self, UIInput* input);
