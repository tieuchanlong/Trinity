#pragma once
#include <string>
#include "EngineLevel.h"
#include "GameObjectSpawner.h"

#define MAX_LEVEL_SOURCES 100

class MapEditorLevel : public Level
{
public:
	MapEditorLevel();

	// --------------- Required for every object --------//
	static MapEditorLevel* Create() { return new MapEditorLevel(); }
	static void RegisterGameClass();
	virtual const char* GetObjectClassName() { return "MapEditorLevel"; }
	virtual int GetObjectClassNameHash() { return ToStringHash("MapEditorLevel"); }
	// -------------------------------------------------//

	virtual int PreUpdate() override;
	virtual int Initialize() override;
	virtual int Render() override;
	virtual int Update(float fDeltaTime) override;
	virtual int Destroy() override;

	const char* GetLevelName(int iIndex) { return m_sLevelNames[iIndex].c_str(); }
	int GetNumLevels() { return m_iNumLevelSources; }

	void SetupLevelResources();
	void OnLevelSelectorOptionChanged();

	void AddObjectSpawner(ObjectSpawner* pObjectSpawner);
	void OnLevelObjectSpawnerChangePrev();
	void OnLevelObjectSpawnerChangeNext();
	void OnSaveLevel();

	void OnCancelPressed() override;
	void OnResumeGame() override;
	void SetHidden(bool bHidden) override;

private:
	Level* m_pLevels[MAX_LEVEL_SOURCES];

	List<ObjectSpawner>* m_pObjectSpawners[MAX_LEVEL_SOURCES];
	int m_iCurObjectSpawnerIndex[MAX_LEVEL_SOURCES];

	std::string m_sLevelSources[MAX_LEVEL_SOURCES];
	std::string m_sLevelNames[MAX_LEVEL_SOURCES];
	int m_iNumLevelSources;
	int m_iCurLevel;
	int m_iPrevLevel;
	bool m_bPaused;
};