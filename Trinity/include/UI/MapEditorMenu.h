#pragma once
#include "UI/EngineUIContainer.h"
#include "UI/EngineSelector.h"

class MapEditorMenu : public EngineUIContainer
{
public:
	MapEditorMenu();

	// --------------- Required for every object --------//
	static Object* Create() { return new MapEditorMenu(); }
	static void RegisterGameClass();
	static const char* GetObjectClassName() { return "MapEditorMenu"; }
	static int GetObjectClassNameHash() { return ToStringHash("MapEditorMenu"); }
	// -------------------------------------------------//

	virtual int Initialize() override;

	void OnSaveLevelData();
	void OnCreateNewLevel();

	int GetLevelSelectorOption() {
		return dynamic_cast<EngineSelector*>(GetUIByName("LevelSelector"))->GetSelectedOption();
	}

	int GetPrevLevelSelectorOption() {
		return dynamic_cast<EngineSelector*>(GetUIByName("LevelSelector"))->GetPrevOption();
	}

private:
	int m_iLevelIndex;

};