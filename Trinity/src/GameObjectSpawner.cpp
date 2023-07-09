#include <DirectX11BasePch.h>
#include "GameObjectSpawner.h"
#include "GameAccessor.h"
#include "MapEditorLevel.h"

GameObjectSpawner::GameObjectSpawner() : ObjectSpawner()
{
	if (dynamic_cast<MapEditorLevel*>(GET_CURRENT_LEVEL()))
	{
		dynamic_cast<MapEditorLevel*>(GET_CURRENT_LEVEL())->AddObjectSpawner(this);
	}
}

void GameObjectSpawner::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("GameObjectSpawner"), GameObjectSpawner::Create);
}