#pragma once

#include "EngineLevel.h"
#include "Base.h"

#define MAX_GRID_WIDTH 20
#define MAX_GRID_HEIGHT 20

class GameLevel : public Level
{
public:
	GameLevel();

	// --------------- Required for every object --------//
	static GameLevel* Create() { return new GameLevel(); }
	static void RegisterGameClass();
	virtual const char* GetObjectClassName() { return "GameLevel"; }
	virtual int GetObjectClassNameHash() { return ToStringHash("GameLevel"); }

	virtual bool ReadSaveData(rapidjson::Value::ConstValueIterator& itr);
	virtual bool WriteSaveData(rapidjson::Writer<rapidjson::StringBuffer>* writer);
	// -------------------------------------------------//

	virtual int PreUpdate() override;

	void AddBase(int iXIndex, int iYIndex, Base* pNewBase);
	Base* GetBaseByIndex(int iXIndex, int iYIndex) { return m_pBases[iXIndex][iYIndex]; }
	void LoadObjects() override;
	void AddObject(Object* pObject) override;

	int GetLevelGenerationChance() { return m_iLevelGenerationChance; }

	void OnCancelPressed() override;
	void OnResumeGame() override;

protected:
	Base* m_pBases[MAX_GRID_WIDTH][MAX_GRID_HEIGHT];

	int m_iLevelGenerationChance;
	bool m_bAddedBases;
	bool m_bPaused;
};