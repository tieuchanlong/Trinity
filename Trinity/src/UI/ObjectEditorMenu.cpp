#include <DirectX11BasePch.h>
#include "UI/ObjectEditorMenu.h"
#include "UI/EngineSelector.h"
#include "UI/EngineButton.h"
#include "GameAccessor.h"
#include "ObjectEditorLevel.h"

ObjectEditorMenu::ObjectEditorMenu() : EngineUIContainer()
{
	m_pCurCreature = 0;
}

void ObjectEditorMenu::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("ObjectEditorMenu"), ObjectEditorMenu::Create);
}

int ObjectEditorMenu::Initialize()
{
	int iRet = EngineUIContainer::Initialize();

	SetNextUIContainer(CREATURE_EDITOR_MENU);

	dynamic_cast<EngineSelector*>(GetUIByName("CreatureSelector"))->SetHighlightColor(XMFLOAT3(0, 0.7, 0));
	dynamic_cast<EngineButton*>(GetUIByName("SaveDataButton"))->SetHighlightColor(XMFLOAT3(0.9, 0.9, 0.2));
	dynamic_cast<EngineButton*>(GetUIByName("CreateCreatureButton"))->SetHighlightColor(XMFLOAT3(1.0, 0.5, 0.4));
	dynamic_cast<EngineButton*>(GetUIByName("SaveDataButton"))->Subscribe(std::bind(&ObjectEditorMenu::OnSaveCreatureData, this));
	dynamic_cast<EngineButton*>(GetUIByName("CreateCreatureButton"))->Subscribe(std::bind(&ObjectEditorMenu::OnCreateNewCreature, this));
	m_pInteractibleUIs->Add(dynamic_cast<EngineSelector*>(GetUIByName("CreatureSelector")));
	m_pInteractibleUIs->Add(dynamic_cast<EngineButton*>(GetUIByName("SaveDataButton")));
	m_pInteractibleUIs->Add(dynamic_cast<EngineButton*>(GetUIByName("CreateCreatureButton")));

	dynamic_cast<EngineSelector*>(GetUIByName("CreatureSelector"))->Subscribe(std::bind(&ObjectEditorLevel::OnCreatureSelectorOptionChanged, dynamic_cast<ObjectEditorLevel*>(GET_CURRENT_LEVEL())));

	int iNumCreatures = dynamic_cast<ObjectEditorLevel*>(GET_CURRENT_LEVEL())->GetNumCreatures();

	for (int i = 0; i < iNumCreatures; i++)
	{
		dynamic_cast<EngineSelector*>(GetUIByName("CreatureSelector"))->AddOption(dynamic_cast<ObjectEditorLevel*>(GET_CURRENT_LEVEL())->GetCreatureName(i));
	}

	return iRet;
}

void ObjectEditorMenu::OnSaveCreatureData()
{
	GET_OBJECT_MANAGER()->SaveObject(m_pCurCreature);
}

void ObjectEditorMenu::OnCreateNewCreature()
{

}
