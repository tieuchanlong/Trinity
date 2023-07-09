#include <DirectX11BasePch.h>
#include "MapEditorLevel.h"
#include "GameAccessor.h"
#include "GameLevel.h"
#include "BaseFactory.h"
#include "EngineMouse.h"
#include "UI/MapEditorMenu.h"
#include <iostream>
#include <filesystem>

MapEditorLevel::MapEditorLevel() : Level()
{
	m_bPaused = false;
}

void MapEditorLevel::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("MapEditorLevel"), MapEditorLevel::Create);
}

int MapEditorLevel::PreUpdate()
{
	int iRet = Level::PreUpdate();

	m_pLevels[m_iCurLevel]->PreUpdate();

	return iRet;
}

int MapEditorLevel::Initialize()
{
	int iRet = Level::Initialize();

	for (int i = 0; i < MAX_LEVEL_SOURCES; i++)
	{
		m_pObjectSpawners[i] = new List<ObjectSpawner>();
		m_iCurObjectSpawnerIndex[i] = 0;
	}

	SetupLevelResources();
	EngineMouse::GetInstance()->SetActive(false);
	Application::GetInstance()->GetMainCamera()->SetLockedRotation(true);
	GET_GUI_MANAGER()->AddMenu(MAP_EDITOR_MENU);
	GET_GUI_MANAGER()->AddMenu(LEVEL_EDITOR_MENU);

	return iRet;
}

int MapEditorLevel::Render()
{
	int iRet = Level::Render();

	m_pLevels[m_iCurLevel]->Render();

	return iRet;
}

int MapEditorLevel::Update(float fDeltaTime)
{
	int iRet = Level::Update(fDeltaTime);

	m_pLevels[m_iCurLevel]->Update(fDeltaTime);

	if (m_pObjectSpawners[m_iCurLevel]->GetNumElements() > 0 && m_pObjectSpawners[m_iCurLevel]->GetElementAtIndex(m_iCurObjectSpawnerIndex[m_iCurLevel])->GetValue()->IsDoneSpawning())
	{
		m_pObjectSpawners[m_iCurLevel]->GetElementAtIndex(m_iCurObjectSpawnerIndex[m_iCurLevel])->GetValue()->ShowSpawnRegionHighlights(true);
	}

	return iRet;
}

int MapEditorLevel::Destroy()
{
	int iRet = Level::Destroy();

	EngineMouse::GetInstance()->SetActive(true);

	for (int i = 0; i < m_iNumLevelSources; i++)
	{
		if (m_pLevels[i])
		{
			m_pLevels[i]->Destroy();
			SafeReleaseTemplate(m_pLevels[i]);
		}
	}

	return iRet;
}

void MapEditorLevel::SetupLevelResources()
{
	char sLevelDir[256] = { 0 };
	snprintf(sLevelDir, 256, "%s\\common\\levels\\RandomLevels\\", Application::GetInstance()->GetCurDirectory());

	for (const auto& entry : std::filesystem::directory_iterator(sLevelDir))
	{
		if (entry.path().generic_string().find(".bak") == std::string::npos)
		{
			m_sLevelSources[m_iNumLevelSources] = entry.path().generic_string();
			m_sLevelNames[m_iNumLevelSources] = m_sLevelSources[m_iNumLevelSources].substr(m_sLevelSources[m_iNumLevelSources].find_last_of("/\\") + 1);
			m_sLevelNames[m_iNumLevelSources] = m_sLevelNames[m_iNumLevelSources].substr(0, m_sLevelNames[m_iNumLevelSources].find_first_of("."));
			m_iNumLevelSources++;
		}
	}

	m_iCurLevel = 0;
	m_pLevels[0] = dynamic_cast<GameLevel*>(GET_LEVEL_MANAGER()->CreateLevel(m_sLevelSources[0].c_str()));
	BaseFactory::GetInstance()->SetCurrentLevel(dynamic_cast<GameLevel*>(m_pLevels[0]));
	m_pLevels[0]->SetWorldPosition(XMFLOAT3(0, 0, 0));
	m_pLevels[0]->SetObjectSource(m_sLevelSources[0].c_str());
	m_pLevels[0]->Initialize();
}

void MapEditorLevel::OnLevelSelectorOptionChanged()
{
	int iPrevLevelInd = dynamic_cast<MapEditorMenu*>(GET_GUI_MANAGER()->GetUIByType(MAP_EDITOR_MENU))->GetPrevLevelSelectorOption();
	int iSelectedLevelInd = dynamic_cast<MapEditorMenu*>(GET_GUI_MANAGER()->GetUIByType(MAP_EDITOR_MENU))->GetLevelSelectorOption();

	m_pLevels[iPrevLevelInd]->SetHidden(true);

	if (!m_pLevels[iSelectedLevelInd])
	{
		m_pLevels[iSelectedLevelInd] = dynamic_cast<GameLevel*>(GET_LEVEL_MANAGER()->CreateLevel(m_sLevelSources[iSelectedLevelInd].c_str()));
		BaseFactory::GetInstance()->SetCurrentLevel(dynamic_cast<GameLevel*>(m_pLevels[iSelectedLevelInd]));
		m_pLevels[iSelectedLevelInd]->SetWorldPosition(XMFLOAT3(0, 0, 0));
		m_pLevels[iSelectedLevelInd]->SetObjectSource(m_sLevelSources[iSelectedLevelInd].c_str());
		AddObject(m_pLevels[iSelectedLevelInd]);
	}

	m_iCurLevel = iSelectedLevelInd;
	m_pLevels[iSelectedLevelInd]->SetHidden(false);
}

void MapEditorLevel::AddObjectSpawner(ObjectSpawner* pObjectSpawner)
{
	pObjectSpawner->SetCanSpawnObjects(false);
	m_pObjectSpawners[m_iCurLevel]->Add(pObjectSpawner);
}

void MapEditorLevel::OnLevelObjectSpawnerChangePrev()
{
	if (m_pObjectSpawners[m_iCurLevel]->GetNumElements() <= 0)
	{
		return;
	}

	m_pObjectSpawners[m_iCurLevel]->GetElementAtIndex(m_iCurObjectSpawnerIndex[m_iCurLevel])->GetValue()->ShowSpawnRegionHighlights(false);
	m_iCurObjectSpawnerIndex[m_iCurLevel] = (m_iCurObjectSpawnerIndex[m_iCurLevel] - 1 + m_pObjectSpawners[m_iCurLevel]->GetNumElements()) % m_pObjectSpawners[m_iCurLevel]->GetNumElements();
	m_pObjectSpawners[m_iCurLevel]->GetElementAtIndex(m_iCurObjectSpawnerIndex[m_iCurLevel])->GetValue()->ShowSpawnRegionHighlights(true);
}

void MapEditorLevel::OnLevelObjectSpawnerChangeNext()
{
	if (m_pObjectSpawners[m_iCurLevel]->GetNumElements() <= 0)
	{
		return;
	}

	m_pObjectSpawners[m_iCurLevel]->GetElementAtIndex(m_iCurObjectSpawnerIndex[m_iCurLevel])->GetValue()->ShowSpawnRegionHighlights(false);
	m_iCurObjectSpawnerIndex[m_iCurLevel] = (m_iCurObjectSpawnerIndex[m_iCurLevel] + 1) % m_pObjectSpawners[m_iCurLevel]->GetNumElements();
	m_pObjectSpawners[m_iCurLevel]->GetElementAtIndex(m_iCurObjectSpawnerIndex[m_iCurLevel])->GetValue()->ShowSpawnRegionHighlights(true);
}

void MapEditorLevel::OnSaveLevel()
{
	GET_LEVEL_MANAGER()->SaveLevel(m_pLevels[m_iCurLevel]);
}

void MapEditorLevel::OnCancelPressed()
{
	Level::OnCancelPressed();
	m_bPaused = !m_bPaused;
	SetHidden(m_bPaused);
}

void MapEditorLevel::OnResumeGame()
{
	Level::OnResumeGame();
	m_bPaused = false;
	SetHidden(false);
}

void MapEditorLevel::SetHidden(bool bHidden)
{
	if (m_bHidden != bHidden)
	{
		m_pLevels[m_iCurLevel]->SetHidden(bHidden);

		if (m_pObjectSpawners[m_iCurLevel]->GetNumElements() > 0)
		{
			m_pObjectSpawners[m_iCurLevel]->GetElementAtIndex(m_iCurObjectSpawnerIndex[m_iCurLevel])->GetValue()->SetHidden(bHidden);
		}
	}

	Level::SetHidden(bHidden);
	m_bPaused = bHidden;  // Temporary, needs to have an OnResumeGame function for GameLevelManager
}
