#include <DirectX11BasePch.h>
#include "GameApplication.h"
#include "Creature.h"
#include "Base.h"
#include "GameObjectSpawner.h"
#include "GameLevel.h"
#include "ObjectEditorLevel.h"
#include "MapEditorLevel.h"
#include "GameLevelManager.h"
#include "UI/TitleMenu.h"
#include "UI/TransitionMenu.h"
#include "UI/ObjectEditorMenu.h"
#include "UI/CreatureEditorMenu.h"
#include "UI/MapEditorMenu.h"
#include "UI/LevelEditorMenu.h"
#include "UI/PauseMenu.h"

GameApplication* GameApplication::GetInstance()
{
	if (!instance)
	{
		instance = new GameApplication();
	}

	return dynamic_cast<GameApplication*>(instance);
}

void GameApplication::RegisterGameClass()
{
	Application::RegisterGameClass();

	Creature::RegisterGameClass();
	BodyPartComponent::RegisterGameClass();
	Base::RegisterGameClass();
	GameObjectSpawner::RegisterGameClass();
	GameLevel::RegisterGameClass();
	ObjectEditorLevel::RegisterGameClass();
	MapEditorLevel::RegisterGameClass();

	TitleMenu::RegisterGameClass();
	TransitionMenu::RegisterGameClass();
	ObjectEditorMenu::RegisterGameClass();
	CreatureEditorMenu::RegisterGameClass();
	MapEditorMenu::RegisterGameClass();
	LevelEditorMenu::RegisterGameClass();
	PauseMenu::RegisterGameClass();
}

int GameApplication::InitUtilityClasses()
{
	// Initialize camera
	m_pCameras = new List<Camera>();

	// Initialize level manager
	m_pLevelManager = new GameLeveManager();

	return 0;
}

GameApplication::GameApplication() : Application()
{

}
