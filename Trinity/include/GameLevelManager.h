#pragma once
#include "EngineLevelManager.h"

#define MAX_ALL_LEVELS_WIDTH 400
#define MAX_ALL_LEVELS_HEIGHT 400
#define MAX_RANDOM_LEVELS 4
#define MAX_MAP_WIDTH 10
#define MAX_MAP_HEIGHT 10

class GameLeveManager : public EngineLevelManager
{
public:
	GameLeveManager();
	virtual int Initialize() override;
	virtual int Update(float fDeltaTime) override;
	void SetupLevels();
	void SetupMapEditorLevel();
	void SetupObjectEditorLevel();
	void ReturnToTitle();
	void ResumeGame();

	void OnCancelPressed(const Event& e) override;

	bool IsMainLevel() { return m_bMainLevel; }

private:
	bool m_bMainLevel;
	int m_iCurLevelX;
	int m_iCurLevelY;
	int m_iGeneratingLevelX;
	int m_iGeneratingLevelY;
	Level* m_pRandomLevel[2*MAX_MAP_WIDTH][2*MAX_MAP_HEIGHT];
};