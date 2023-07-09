#pragma once

#include "Base.h"
#include "GameLevel.h"

#define NUM_DIRECTIONS 4

const int g_iDirections[NUM_DIRECTIONS][2] = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0},
};

class BaseFactory
{
public:
	static BaseFactory* GetInstance();

	virtual int Initialize();
	virtual int Destroy();
	virtual int Update(float fDetaltaTime);

	Base* GenerateBaseByType(int iEnvironmentType);
	virtual bool GenerateBases(GameLevel* pLevel);
	virtual void AddBaseToQueue(Base* pBase) { 
		m_pBaseQueue->Add(pBase); 
	}
	bool HasEmptyQueue() { return m_pBaseQueue->GetNumElements() == 0; }
	bool IsOccupied() { return m_pCurrentLevel != 0; }
	void SetCurrentLevel(GameLevel* pCurrentLevel) { m_pCurrentLevel = pCurrentLevel; }

protected:
	static BaseFactory* instance;
	BaseFactory();

	Queue<Base>* m_pBaseQueue;
	GameLevel* m_pCurrentLevel;
};