#include <DirectX11BasePch.h>
#include "UI/TransitionMenu.h"
#include "GameAccessor.h"

TransitionMenu::TransitionMenu() : EngineUIContainer()
{
	m_bFinishedLoading = false;
}

void TransitionMenu::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("TransitionMenu"), TransitionMenu::Create);
}

int TransitionMenu::Initialize()
{
	int iRet = EngineUIContainer::Initialize();

	GetUIByName("LoadingText")->SetHidden(false);
	GetUIByName("ContinueText")->SetHidden(true);

	return iRet;
}

int TransitionMenu::Update(float fDeltaTime)
{
	int iRet = EngineUIContainer::Update(fDeltaTime);

	if (!m_bFinishedLoading && GET_GAME_LEVEL_MANAGER()->IsDoneLoadingLevels())
	{
		m_bFinishedLoading = true;
		GetUIByName("LoadingText")->SetHidden(true);
		GetUIByName("ContinueText")->SetHidden(false);
	}

	return iRet;
}

int TransitionMenu::OnConfirmOption()
{
	int iRet = EngineUIContainer::OnConfirmOption();

	if (GET_GAME_LEVEL_MANAGER()->IsDoneLoadingLevels())
	{
		GET_GUI_MANAGER()->RemoveMenu(TRANSITION_MENU);
	}

	return iRet;
}
