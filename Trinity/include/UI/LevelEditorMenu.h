#pragma once
#include "UI/EngineUIContainer.h"

class LevelEditorMenu : public EngineUIContainer
{
public:
	LevelEditorMenu();

	// --------------- Required for every object --------//
	static Object* Create() { return new LevelEditorMenu(); }
	static void RegisterGameClass();
	static const char* GetObjectClassName() { return "LevelEditorMenu"; }
	static int GetObjectClassNameHash() { return ToStringHash("LevelEditorMenu"); }
	// -------------------------------------------------//

	virtual int Initialize() override;
	void OnLevelObjectSpawnerChangePrev();
	void OnLevelObjectSpawnerChangeNext();
	void OnObjectSpawnerSliderValueChange();

private:
	int m_iLevelIndex;
	int m_iHighlightedUIIndex;

};