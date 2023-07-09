#include <DirectX11BasePch.h>
#include "UI/MapEditorMenu.h"
#include "GameAccessor.h"
#include "UI/EngineSelector.h"
#include "UI/EngineButton.h"
#include "MapEditorLevel.h"

MapEditorMenu::MapEditorMenu() : EngineUIContainer()
{

}

void MapEditorMenu::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("MapEditorMenu"), MapEditorMenu::Create);
}

int MapEditorMenu::Initialize()
{
	int iRet = EngineUIContainer::Initialize();

	SetNextUIContainer(LEVEL_EDITOR_MENU);

	dynamic_cast<EngineSelector*>(GetUIByName("LevelSelector"))->SetHighlightColor(XMFLOAT3(0, 0.7, 0));
	dynamic_cast<EngineButton*>(GetUIByName("SaveDataButton"))->SetHighlightColor(XMFLOAT3(0.9, 0.9, 0.2));
	//dynamic_cast<EngineButton*>(GetUIByName("CreateLevelButton"))->SetHighlightColor(XMFLOAT3(1.0, 0.5, 0.4));
	dynamic_cast<EngineButton*>(GetUIByName("SaveDataButton"))->Subscribe(std::bind(&MapEditorMenu::OnSaveLevelData, this));
	//dynamic_cast<EngineButton*>(GetUIByName("CreateLevelButton"))->Subscribe(std::bind(&MapEditorMenu::OnCreateNewLevel, this));
	m_pInteractibleUIs->Add(dynamic_cast<EngineSelector*>(GetUIByName("LevelSelector")));
	m_pInteractibleUIs->Add(dynamic_cast<EngineButton*>(GetUIByName("SaveDataButton")));
	//m_pInteractibleUIs->Add(dynamic_cast<EngineButton*>(GetUIByName("CreateLevelButton")));

	dynamic_cast<EngineSelector*>(GetUIByName("LevelSelector"))->Subscribe(std::bind(&MapEditorLevel::OnLevelSelectorOptionChanged, dynamic_cast<MapEditorLevel*>(GET_CURRENT_LEVEL())));

	int iNumLevels = dynamic_cast<MapEditorLevel*>(GET_CURRENT_LEVEL())->GetNumLevels();

	for (int i = 0; i < iNumLevels; i++)
	{
		dynamic_cast<EngineSelector*>(GetUIByName("LevelSelector"))->AddOption(dynamic_cast<MapEditorLevel*>(GET_CURRENT_LEVEL())->GetLevelName(i));
	}

	return iRet;
}

void MapEditorMenu::OnSaveLevelData()
{
	dynamic_cast<MapEditorLevel*>(GET_CURRENT_LEVEL())->OnSaveLevel();
}

void MapEditorMenu::OnCreateNewLevel()
{

}
