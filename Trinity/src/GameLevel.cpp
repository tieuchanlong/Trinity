#include <DirectX11BasePch.h>
#include <GameLevel.h>
#include "GameAccessor.h"
#include "EngineLevelManager.h"
#include "BaseFactory.h"
#include "ObjectSpawner.h"

GameLevel::GameLevel() : Level()
{
	m_bAddedBases = false;
	m_bPaused = false;
}

void GameLevel::RegisterGameClass()
{
	EngineObjectManager::GetInstance()->Register(ToStringHash("GameLevel"), GameLevel::Create);
}

bool GameLevel::ReadSaveData(rapidjson::Value::ConstValueIterator& itr)
{
	bool bRet = Level::ReadSaveData(itr);

	m_iLevelGenerationChance = (*itr)["LevelGenerationChance"].GetInt();
	itr++;

	return bRet;
}

bool GameLevel::WriteSaveData(rapidjson::Writer<rapidjson::StringBuffer>* writer)
{
	bool bRet = Level::WriteSaveData(writer);

	writer->StartObject();
	writer->Key("LevelGenerationChance");
	writer->Int(m_iLevelGenerationChance);
	writer->EndObject();

	return bRet;
}

int GameLevel::PreUpdate()
{
	int iRet = Level::PreUpdate();

	if (!m_bAddedBases)
	{
		m_bAddedBases = true;

		for (int i = 0; i < MAX_GRID_WIDTH; i++)
		{
			for (int j = 0; j < MAX_GRID_HEIGHT; j++)
			{
				if (m_pBases[i][j])
				{
					BaseFactory::GetInstance()->AddBaseToQueue(m_pBases[i][j]);
				}
			}
		}
	}

	return iRet;
}

void GameLevel::AddBase(int iXIndex, int iYIndex, Base* pNewBase)
{
	pNewBase->SetWorldPosition(m_vPos + XMFLOAT3(iXIndex, 0, iYIndex));
	m_pBases[iXIndex][iYIndex] = pNewBase;
}

void GameLevel::LoadObjects()
{
	for (int i = 0; i < MAX_LOADING_OBJECTS_PER_FRAME; i++)
	{
		ObjectTemporaryData* pObjectData = m_pObjectTempData->GetElementAtIndex(m_iCurLoadingObjIndex)->GetValue();

		char fullPath[256] = { 0 };
		snprintf(fullPath, 256, "%s%s", Application::GetInstance()->GetCurDirectory(), pObjectData->sObjectSource);

		Object* pObject = GET_OBJECT_MANAGER()->CreateObjectBySource(fullPath);
		pObject->SetWorldPosition(pObjectData->vPos);
		pObject->SetObjectSource(_strdup(fullPath));
		AddObject(pObject);
		m_iCurLoadingObjIndex++;

		if (IsDoneLoadingObjects())
		{
			m_bLoadingObjects = false;
			return;
		}
	}
}

void GameLevel::AddObject(Object* pObject)
{
	if (dynamic_cast<Base*>(pObject))
	{
		AddBase(pObject->GetWorldPosition().x, pObject->GetWorldPosition().z, dynamic_cast<Base*>(pObject));
	}

	Level::AddObject(pObject);
}

void GameLevel::OnCancelPressed()
{
	Level::OnCancelPressed();

	m_bPaused = !m_bPaused;
	SetHidden(m_bPaused);
}

void GameLevel::OnResumeGame()
{
	Level::OnResumeGame();
	m_bPaused = false;
	SetHidden(false);
}
