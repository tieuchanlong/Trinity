#include <DirectX11BasePch.h>
#include "GameLevelManager.h"
#include "GameAccessor.h"
#include "BaseFactory.h"

const char* g_sRandomLevelPaths[MAX_RANDOM_LEVELS] = {
	"\\common\\levels\\RandomLevels\\Level1.json",
	"\\common\\levels\\RandomLevels\\Level2.json",
	"\\common\\levels\\RandomLevels\\Level3.json",
	"\\common\\levels\\RandomLevels\\Level4.json"
};

int GameLeveManager::Initialize()
{
	return EngineLevelManager::Initialize();
}

int GameLeveManager::Update(float fDeltaTime)
{
	int iRet = EngineLevelManager::Update(fDeltaTime);

	BaseFactory::GetInstance()->Update(fDeltaTime);

	if (m_bMainLevel)
	{
		if (!BaseFactory::GetInstance()->IsOccupied())
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = 0; j <= 1; j++)
				{
					int iLevelX = m_iCurLevelX + i;
					int iLevelY = m_iCurLevelY + j;

					if (iLevelX < 0 || iLevelY < 0 || iLevelX >= 2 * MAX_MAP_WIDTH || iLevelY >= 2 * MAX_MAP_HEIGHT)
					{
						continue;
					}

					if (m_pRandomLevel[iLevelX][iLevelY])
					{
						continue;
					}

					char fullLevelPath[256] = { 0 };
					int iRandomLevelIndex = rand() % MAX_RANDOM_LEVELS;
					snprintf(fullLevelPath, 256, "%s%s", Application::GetInstance()->GetCurDirectory(), g_sRandomLevelPaths[iRandomLevelIndex]);
					m_iGeneratingLevelX = iLevelX;
					m_iGeneratingLevelY = iLevelY;

					Level* pLevel = CreateLevel(fullLevelPath);
					BaseFactory::GetInstance()->SetCurrentLevel(dynamic_cast<GameLevel*>(pLevel));
					AddLevel(pLevel);
					pLevel->SetWorldPosition(XMFLOAT3(i * MAX_GRID_WIDTH, 0, j * MAX_GRID_HEIGHT));
					m_pRandomLevel[iLevelX][iLevelY] = pLevel;
					return iRet;
				}
			}
		}
	}

	return iRet;
}

GameLeveManager::GameLeveManager() : EngineLevelManager()
{
	m_bMainLevel = false;
}

void GameLeveManager::SetupLevels()
{
	// Remove title menu
	GET_GUI_MANAGER()->RemoveMenu(TITLE_MENU);
	GET_GUI_MANAGER()->AddMenu(TRANSITION_MENU);

	m_bMainLevel = true;
	m_iGeneratingLevelX = MAX_MAP_WIDTH;
	m_iGeneratingLevelY = MAX_MAP_HEIGHT;
	m_iCurLevelX = MAX_MAP_WIDTH;
	m_iCurLevelY = MAX_MAP_HEIGHT;

	// Set up initial surrounding 8 directions for adjacent levels as well
	char fullLevelPath[256] = { 0 };
	snprintf(fullLevelPath, 256, "%s\\common\\levels\\MainLevel.json", Application::GetInstance()->GetCurDirectory());

	Level* pLevel = CreateLevel(fullLevelPath);
	BaseFactory::GetInstance()->SetCurrentLevel(dynamic_cast<GameLevel*>(pLevel));
	AddLevel(pLevel);
	pLevel->SetWorldPosition(XMFLOAT3(0, 0, 0));
	m_pRandomLevel[m_iCurLevelX][m_iCurLevelY] = pLevel;
}

void GameLeveManager::SetupMapEditorLevel()
{
	// Remove title menu
	GET_GUI_MANAGER()->RemoveMenu(TITLE_MENU);
	GET_GUI_MANAGER()->AddMenu(TRANSITION_MENU);

	char fullLevelPath[256] = { 0 };
	snprintf(fullLevelPath, 256, "%s\\common\\levels\\MapEditorLevel.json", Application::GetInstance()->GetCurDirectory());

	Level* pLevel = CreateLevel(fullLevelPath);
	AddLevel(pLevel);
	pLevel->SetWorldPosition(XMFLOAT3(0, 0, 0));
}

void GameLeveManager::SetupObjectEditorLevel()
{
	// Remove title menu
	GET_GUI_MANAGER()->RemoveMenu(TITLE_MENU);
	GET_GUI_MANAGER()->AddMenu(TRANSITION_MENU);

	char fullLevelPath[256] = { 0 };
	snprintf(fullLevelPath, 256, "%s\\common\\levels\\ObjectEditorLevel.json", Application::GetInstance()->GetCurDirectory());

	Level* pLevel = CreateLevel(fullLevelPath);
	AddLevel(pLevel);
	pLevel->SetWorldPosition(XMFLOAT3(0, 0, 0));
}

void GameLeveManager::ReturnToTitle()
{
	// Destroy levels
	for (Iterator<Level>* it = m_pLevels->GetHead(); it != NULL; it = it->GetNext())
	{
		it->GetValue()->Destroy();
	}

	// Clean up levels
	m_pLevels->Clear();

	// Temporary, but have to check on why levels are not deleted properly
	for (int i = 0; i < 2 * MAX_MAP_WIDTH; i++)
	{
		for (int j = 0; j < 2 * MAX_MAP_HEIGHT; j++)
		{
			SafeReleaseTemplate(m_pRandomLevel[i][j]);
		}
	}

	m_bMainLevel = false;
	GET_GUI_MANAGER()->ClearAllMenus();
	GET_GUI_MANAGER()->AddMenu(TITLE_MENU);
}

void GameLeveManager::ResumeGame()
{
	GET_GUI_MANAGER()->RemoveMenu(PAUSE_MENU);

	for (Iterator<Level>* it = m_pLevels->GetHead(); it != NULL; it = it->GetNext())
	{
		it->GetValue()->OnResumeGame();
	}
}

void GameLeveManager::OnCancelPressed(const Event& e)
{
	EngineLevelManager::OnCancelPressed(e);

	if (!GET_GUI_MANAGER()->GetUIByType(TITLE_MENU) && !GET_GUI_MANAGER()->GetUIByType(TRANSITION_MENU))
	{
		if (GET_GUI_MANAGER()->GetUIByType(PAUSE_MENU))
		{
			GET_GUI_MANAGER()->RemoveMenu(PAUSE_MENU);
		}
		else
		{
			GET_GUI_MANAGER()->AddMenu(PAUSE_MENU);
		}
	}
}

