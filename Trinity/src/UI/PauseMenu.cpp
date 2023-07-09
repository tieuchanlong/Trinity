#include <DirectX11BasePch.h>
#include "UI/PauseMenu.h"
#include "UI/EngineButton.h"
#include "GameAccessor.h"

PauseMenu::PauseMenu() : EngineUIContainer()
{

}

void PauseMenu::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("PauseMenu"), PauseMenu::Create);
}

int PauseMenu::Initialize()
{
	int iRet = EngineUIContainer::Initialize();

	dynamic_cast<EngineButton*>(GetUIByName("ResumeGameButton"))->Subscribe(std::bind(&PauseMenu::OnResumeGame, this));
	dynamic_cast<EngineButton*>(GetUIByName("GoToTitleButton"))->Subscribe(std::bind(&PauseMenu::OnGoToTitle, this));
	dynamic_cast<EngineButton*>(GetUIByName("QuitButton"))->Subscribe(std::bind(&PauseMenu::OnQuitGame, this));

	m_pInteractibleUIs->Add(dynamic_cast<EngineButton*>(GetUIByName("ResumeGameButton")));
	m_pInteractibleUIs->Add(dynamic_cast<EngineButton*>(GetUIByName("GoToTitleButton")));
	m_pInteractibleUIs->Add(dynamic_cast<EngineButton*>(GetUIByName("QuitButton")));
	Application::GetInstance()->GetMainCamera()->SetLockedAll(true);

	return iRet;
}

int PauseMenu::Destroy()
{
	int iRet = EngineUIContainer::Destroy();

	Application::GetInstance()->GetMainCamera()->SetLockedAll(false);

	return iRet;
}

void PauseMenu::OnResumeGame()
{
	GET_GAME_LEVEL_MANAGER()->ResumeGame();
}

void PauseMenu::OnGoToTitle()
{
	GET_GAME_LEVEL_MANAGER()->ReturnToTitle();
}

void PauseMenu::OnQuitGame()
{
	Application::GetInstance()->Quit();
}

int PauseMenu::OnConfirmOption()
{
	int iRet = EngineUIContainer::OnConfirmOption();

	return iRet;
}
