#include <DirectX11BasePch.h>
#include "BaseFactory.h"
#include "GameAccessor.h"

const char* g_sBasePaths[NUM_BASE_TYPES] = {
	"\\common\\GameObjects\\Bases\\Forest\\ForestBase.json",
	"\\common\\GameObjects\\Bases\\Water\\WaterBase.json",
	"\\common\\GameObjects\\Bases\\Sand\\SandBase.json"
};

BaseFactory* BaseFactory::instance = 0;
BaseFactory* BaseFactory::GetInstance()
{
	if (!instance)
	{
		instance = new BaseFactory();
	}

	return instance;
}

int BaseFactory::Initialize()
{
	return 0;
}

int BaseFactory::Destroy()
{
	return 0;
}

int BaseFactory::Update(float fDetaltaTime)
{
	if (m_pCurrentLevel && m_pCurrentLevel->IsDoneLoadingObjects())
	{
		GenerateBases(m_pCurrentLevel);
		m_pCurrentLevel = 0;
	}

	return 0;
}

Base* BaseFactory::GenerateBaseByType(int iEnvironmentType)
{
	char fullLevelPath[500] = { 0 };
	snprintf(fullLevelPath, 500, "%s%s", Application::GetInstance()->GetCurDirectory(), g_sBasePaths[iEnvironmentType]);

	return dynamic_cast<Base*>(GET_OBJECT_MANAGER()->CreateObjectBySource(fullLevelPath));
}

bool BaseFactory::GenerateBases(GameLevel* pLevel)
{
	if (pLevel->IsDoneLoadingObjects())
	{
		while (!m_pBaseQueue->IsEmpty())
		{
			Base* pBase = m_pBaseQueue->PopFront();

			int randCheck = rand() % 100 + 1;

			if (randCheck < pLevel->GetLevelGenerationChance())
			{
				continue;
			}

			int iXIndex = pBase->GetWorldPosition().x - pLevel->GetWorldPosition().x;
			int iYIndex = pBase->GetWorldPosition().z - pLevel->GetWorldPosition().z;

			int iNumNeighbors = 0;

			for (int i = 0; i < NUM_DIRECTIONS; i++)
			{
				int iNewXIndex = iXIndex + g_iDirections[i][0];
				int iNewYIndex = iYIndex + g_iDirections[i][1];

				if (!(iNewXIndex >= 0 && iNewXIndex < MAX_GRID_WIDTH && iNewYIndex >= 0 && iNewYIndex < MAX_GRID_HEIGHT) || pLevel->GetBaseByIndex(iNewXIndex, iNewYIndex))
				{
					iNumNeighbors++;
				}
			}

			// If a base is already occupied 4 side, we don't need to do anything with it
			if (iNumNeighbors == NUM_DIRECTIONS)
			{
				continue;
			}

			for (int i = 0; i < NUM_DIRECTIONS; i++)
			{
				int iNewXIndex = iXIndex + g_iDirections[i][0];
				int iNewYIndex = iYIndex + g_iDirections[i][1];

				if ((iNewXIndex >= 0 && iNewXIndex < MAX_GRID_WIDTH && iNewYIndex >= 0 && iNewYIndex < MAX_GRID_HEIGHT) && !pLevel->GetBaseByIndex(iNewXIndex, iNewYIndex))
				{
					Base* pNewBase = GenerateBaseByType(pBase->GetBaseType());
					pNewBase->SetWorldPosition(XMFLOAT3(iNewXIndex, 0, iNewYIndex));
					pLevel->AddObject(pNewBase);
					m_pBaseQueue->Add(pNewBase);
				}
			}
		}
	}

	// Now go through spaces not occupied and spawn water tiles
	for (int i = 0; i < MAX_GRID_WIDTH; i++)
	{
		for (int j = 0; j < MAX_GRID_HEIGHT; j++)
		{
			if (!pLevel->GetBaseByIndex(i, j))
			{
				Base* pNewBase = GenerateBaseByType(WATER);
				pNewBase->SetWorldPosition(XMFLOAT3(i, pLevel->GetWorldPosition().y, j));
				pLevel->AddObject(pNewBase);
			}
		}
	}

	Application::GetInstance()->ReRender(); // Have to put here due to map editor level forgot to render level without object spawner, need to redesign into a better system
	return true;
}

BaseFactory::BaseFactory()
{
	m_pBaseQueue = new Queue<Base>();
	m_pCurrentLevel = 0;
}
