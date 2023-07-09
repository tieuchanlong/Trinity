#pragma once
#include "EngineAccessor.h"
#include "GameLevelManager.h"

#define GET_GAME_LEVEL_MANAGER() dynamic_cast<GameLeveManager*>(Application::GetInstance()->GetLevelManager())