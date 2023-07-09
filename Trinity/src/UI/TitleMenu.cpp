#include <DirectX11BasePch.h>
#include "UI/TitleMenu.h"
#include "UI/EngineButton.h"
#include "GameAccessor.h"

TitleMenu::TitleMenu() : EngineUIContainer()
{

}

void TitleMenu::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("TitleMenu"), TitleMenu::Create);
}

int TitleMenu::Initialize()
{
	int iRet = EngineUIContainer::Initialize();

	// Add in the buttons for interaction
	m_pInteractibleUIs->Add(GetUIByName("MainGameButton"));
	m_pInteractibleUIs->Add(GetUIByName("MapEditorButton"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectEditorButton"));
	m_pInteractibleUIs->Add(GetUIByName("QuitButton"));

	dynamic_cast<EngineButton*>(GetUIByName("MainGameButton"))->Subscribe(std::bind(&TitleMenu::SetupMainLevels, this));
	dynamic_cast<EngineButton*>(GetUIByName("MapEditorButton"))->Subscribe(std::bind(&TitleMenu::SetupMapEditorLevel, this));
	dynamic_cast<EngineButton*>(GetUIByName("ObjectEditorButton"))->Subscribe(std::bind(&TitleMenu::SetupObjectEditorLevel, this));
	dynamic_cast<EngineButton*>(GetUIByName("QuitButton"))->Subscribe(std::bind(&TitleMenu::QuitGame, this));
	Application::GetInstance()->GetMainCamera()->SetLockedAll(true);

	return iRet;
}

int TitleMenu::Destroy()
{
	int iRet = EngineUIContainer::Destroy();

	Application::GetInstance()->GetMainCamera()->SetLockedAll(false);

	return iRet;
}

int TitleMenu::OnConfirmOption()
{
	int iRet = EngineUIContainer::OnConfirmOption();

	switch (m_iHighlightedUIIndex)
	{
	case 0:
	{
		// Main Game
		SetupMainLevels();
	}
	break;
	case 1:
	{
		// Level Editor
		SetupMapEditorLevel();
	}
	break;
	case 2:
	{
		// Object Editor
		SetupObjectEditorLevel();
	}
	break;
	case 3:
	{
		// Quit
		QuitGame();
	}
	break;
	default:
		break;
	}

	return iRet;
}

void TitleMenu::SetupMainLevels()
{
	GET_GAME_LEVEL_MANAGER()->SetupLevels();
}

void TitleMenu::SetupMapEditorLevel()
{
	GET_GAME_LEVEL_MANAGER()->SetupMapEditorLevel();
}

void TitleMenu::SetupObjectEditorLevel()
{
	GET_GAME_LEVEL_MANAGER()->SetupObjectEditorLevel();
}

void TitleMenu::QuitGame()
{
	Application::GetInstance()->Quit();
}
