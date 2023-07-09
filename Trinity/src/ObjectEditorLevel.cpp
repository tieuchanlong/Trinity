#include <DirectX11BasePch.h>
#include "ObjectEditorLevel.h"
#include <iostream>
#include <filesystem>
#include "GameAccessor.h"
#include "EngineMouse.h"
#include "UI/ObjectEditorMenu.h"
#include "UI/CreatureEditorMenu.h"

ObjectEditorLevel::ObjectEditorLevel() : Level()
{
	m_iNumObjectSources = 0;
	m_iCurCreature = 0;
	m_bInitializeCreatureEditor = false;
	m_bPaused = false;
}

void ObjectEditorLevel::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("ObjectEditorLevel"), ObjectEditorLevel::Create);
}

int ObjectEditorLevel::Initialize()
{
	PrepareCreatureSources();
	int iRet = Level::Initialize();

	EngineMouse::GetInstance()->SetActive(false);
	Application::GetInstance()->GetMainCamera()->SetLockedRotation(true);
	GET_GUI_MANAGER()->AddMenu(OBJECT_EDITOR_MENU);
	GET_GUI_MANAGER()->AddMenu(CREATURE_EDITOR_MENU);

	return iRet;
}

int ObjectEditorLevel::Destroy()
{
	int iRet = Level::Destroy();

	EngineMouse::GetInstance()->SetActive(true);
	Application::GetInstance()->GetMainCamera()->SetLockedRotation(false);

	return iRet;
}

int ObjectEditorLevel::PreUpdate()
{
	int iRet = Level::PreUpdate();

	if (!m_bInitializeCreatureEditor && GET_GUI_MANAGER()->GetUIByType(CREATURE_EDITOR_MENU))
	{
		m_bInitializeCreatureEditor = true;
		dynamic_cast<ObjectEditorMenu*>(GET_GUI_MANAGER()->GetUIByType(OBJECT_EDITOR_MENU))->Show(m_pCreatures[0]);
		dynamic_cast<CreatureEditorMenu*>(GET_GUI_MANAGER()->GetUIByType(CREATURE_EDITOR_MENU))->Show(m_pCreatures[0], 0);
	}

	return iRet;
}

void ObjectEditorLevel::PrepareCreatureSources()
{
	char sCreatureDir[256] = { 0 };
	snprintf(sCreatureDir, 256, "%s\\common\\GameObjects\\Creatures\\", Application::GetInstance()->GetCurDirectory());

	for (const auto& entry : std::filesystem::directory_iterator(sCreatureDir))
	{
		if (entry.path().generic_string().find(".bak") == std::string::npos)
		{
			m_sObjectSources[m_iNumObjectSources] = entry.path().generic_string();
			m_sObjectNames[m_iNumObjectSources] = m_sObjectSources[m_iNumObjectSources].substr(m_sObjectSources[m_iNumObjectSources].find_last_of("/\\") + 1);
			m_sObjectNames[m_iNumObjectSources] = m_sObjectNames[m_iNumObjectSources].substr(0, m_sObjectNames[m_iNumObjectSources].find_first_of("."));
			m_iNumObjectSources++;
		}
	}

	m_pCreatures[0] = dynamic_cast<Creature*>(GET_OBJECT_MANAGER()->CreateObjectBySource(m_sObjectSources[0].c_str()));
	m_pCreatures[0]->SetWorldPosition(XMFLOAT3(0, 0, -10));
	m_pCreatures[0]->SetObjectSource(m_sObjectSources[0].c_str());
	AddObject(m_pCreatures[0]);
}

void ObjectEditorLevel::OnCreatureSelectorOptionChanged()
{
	int iPrevCreatureInd = dynamic_cast<ObjectEditorMenu*>(GET_GUI_MANAGER()->GetUIByType(OBJECT_EDITOR_MENU))->GetPrevCreatureSelectorOption();
	int iSelectedCreatureInd = dynamic_cast<ObjectEditorMenu*>(GET_GUI_MANAGER()->GetUIByType(OBJECT_EDITOR_MENU))->GetCreatureSelectorOption();

	m_pCreatures[iPrevCreatureInd]->SetHidden(true);

	if (!m_pCreatures[iSelectedCreatureInd])
	{
		m_pCreatures[iSelectedCreatureInd] = dynamic_cast<Creature*>(GET_OBJECT_MANAGER()->CreateObjectBySource(m_sObjectSources[iSelectedCreatureInd].c_str()));
		m_pCreatures[iSelectedCreatureInd]->SetWorldPosition(XMFLOAT3(0, 0, -10));
		m_pCreatures[iSelectedCreatureInd]->SetObjectSource(m_sObjectSources[iSelectedCreatureInd].c_str());
		AddObject(m_pCreatures[iSelectedCreatureInd]);
	}

	m_pCreatures[iSelectedCreatureInd]->SetHidden(false);
	dynamic_cast<ObjectEditorMenu*>(GET_GUI_MANAGER()->GetUIByType(OBJECT_EDITOR_MENU))->Show(m_pCreatures[iSelectedCreatureInd]);
	dynamic_cast<CreatureEditorMenu*>(GET_GUI_MANAGER()->GetUIByType(CREATURE_EDITOR_MENU))->Show(m_pCreatures[iSelectedCreatureInd], iSelectedCreatureInd);
}

void ObjectEditorLevel::OnCancelPressed()
{
	Level::OnCancelPressed();
	m_bPaused = !m_bPaused;
	SetHidden(m_bPaused);
}

void ObjectEditorLevel::OnResumeGame()
{
	Level::OnResumeGame();
	m_bPaused = false;
	SetHidden(false);
}

void ObjectEditorLevel::SetHidden(bool bHidden)
{
	if (m_bHidden != bHidden)
	{
		m_pCreatures[m_iCurCreature]->SetHidden(bHidden);
	}

	Level::SetHidden(bHidden);
}
