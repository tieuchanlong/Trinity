#pragma once
#include <string>
#include "EngineLevel.h"
#include "Creature.h"

#define MAX_OBJECT_SOURCES 100

class ObjectEditorLevel : public Level
{
public:
	ObjectEditorLevel();

	// --------------- Required for every object --------//
	static ObjectEditorLevel* Create() { return new ObjectEditorLevel(); }
	static void RegisterGameClass();
	virtual const char* GetObjectClassName() { return "ObjectEditorLevel"; }
	virtual int GetObjectClassNameHash() { return ToStringHash("ObjectEditorLevel"); }
	// -------------------------------------------------//

	int Initialize() override;
	int Destroy() override;
	int PreUpdate() override;

	void PrepareCreatureSources();
	void OnCreatureSelectorOptionChanged();

	const char* GetCreatureName(int iIndex) { return m_sObjectNames[iIndex].c_str(); }
	int GetNumCreatures() { return m_iNumObjectSources; }

	void OnCancelPressed() override;
	void OnResumeGame() override;
	void SetHidden(bool bHidden) override;

private:
	std::string m_sObjectSources[MAX_OBJECT_SOURCES];
	std::string m_sObjectNames[MAX_OBJECT_SOURCES];
	int m_iNumObjectSources;

	Creature* m_pCreatures[MAX_OBJECT_SOURCES];
	int m_iCurCreature;

	bool m_bInitializeCreatureEditor;
	bool m_bPaused;
};