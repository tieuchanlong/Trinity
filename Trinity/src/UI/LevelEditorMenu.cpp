#include <DirectX11BasePch.h>
#include "UI/LevelEditorMenu.h"
#include "GameAccessor.h"
#include "MapEditorLevel.h"
#include "UI/EngineButton.h"
#include "UI/EngineSlider.h"

LevelEditorMenu::LevelEditorMenu() : EngineUIContainer()
{

}

void LevelEditorMenu::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("LevelEditorMenu"), LevelEditorMenu::Create);
}

int LevelEditorMenu::Initialize()
{
	int iRet = EngineUIContainer::Initialize();

	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerXSlider"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerYSlider"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerZSlider"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerMinXSlider"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerMinYSlider"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerMinZSlider"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerMaxXSlider"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerMaxYSlider"));
	m_pInteractibleUIs->Add(GetUIByName("ObjectSpawnerMaxZSlider"));
	m_pInteractibleUIs->Add(GetUIByName("PrevObjectSpawnerButton"));
	m_pInteractibleUIs->Add(GetUIByName("NextObjectSpawnerButton"));
	SetNextUIContainer(MAP_EDITOR_MENU);

	// Set up value change callback with slider
	for (int i = 0; i < 9; i++)
	{
		XMFLOAT3 vColor = dynamic_cast<EngineSlider*>(m_pInteractibleUIs->GetElementAtIndex(i)->GetValue())->GetColor();
		dynamic_cast<EngineSlider*>(m_pInteractibleUIs->GetElementAtIndex(i)->GetValue())->SetHighlightColor(XMFLOAT3(vColor.x + 0.25f, vColor.y + 0.3f, vColor.z));
		dynamic_cast<EngineSlider*>(m_pInteractibleUIs->GetElementAtIndex(i)->GetValue())->Subscribe(std::bind(&LevelEditorMenu::OnObjectSpawnerSliderValueChange, this));
	}

	// Set up body part change with button
	dynamic_cast<EngineButton*>(GetUIByName("PrevObjectSpawnerButton"))->Subscribe(std::bind(&LevelEditorMenu::OnLevelObjectSpawnerChangePrev, this));
	dynamic_cast<EngineButton*>(GetUIByName("NextObjectSpawnerButton"))->Subscribe(std::bind(&LevelEditorMenu::OnLevelObjectSpawnerChangeNext, this));

	XMFLOAT3 vColor = dynamic_cast<EngineButton*>(GetUIByName("PrevObjectSpawnerButton"))->GetColor();
	dynamic_cast<EngineButton*>(GetUIByName("PrevObjectSpawnerButton"))->SetHighlightColor(XMFLOAT3(vColor.x + 0.2f, vColor.y + 0.1f, vColor.z));

	vColor = dynamic_cast<EngineButton*>(GetUIByName("NextObjectSpawnerButton"))->GetColor();
	dynamic_cast<EngineButton*>(GetUIByName("NextObjectSpawnerButton"))->SetHighlightColor(XMFLOAT3(vColor.x + 0.2f, vColor.y + 0.1f, vColor.z));

	return iRet;
}

void LevelEditorMenu::OnLevelObjectSpawnerChangePrev()
{
	dynamic_cast<MapEditorLevel*>(GET_CURRENT_LEVEL())->OnLevelObjectSpawnerChangePrev();
}

void LevelEditorMenu::OnLevelObjectSpawnerChangeNext()
{
	dynamic_cast<MapEditorLevel*>(GET_CURRENT_LEVEL())->OnLevelObjectSpawnerChangeNext();
}

void LevelEditorMenu::OnObjectSpawnerSliderValueChange()
{
	if (0 <= m_iHighlightedUIIndex && m_iHighlightedUIIndex <= 2)
	{
		// Change object spawner location
		
	}
	else if (3 <= m_iHighlightedUIIndex && m_iHighlightedUIIndex <= 5)
	{
		// Change object spawner min size
		
	}
	else if (6 <= m_iHighlightedUIIndex && m_iHighlightedUIIndex <= 8)
	{
		// Change object spawner max color
		
	}
}
