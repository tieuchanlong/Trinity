#pragma once
#include "UI/EngineSelector.h"
#include "UI/EngineUIContainer.h"
#include "Creature.h"

class ObjectEditorMenu : public EngineUIContainer
{
public:
	ObjectEditorMenu();

	// --------------- Required for every object --------//
	static Object* Create() { return new ObjectEditorMenu(); }
	static void RegisterGameClass();
	static const char* GetObjectClassName() { return "ObjectEditorMenu"; }
	static int GetObjectClassNameHash() { return ToStringHash("ObjectEditorMenu"); }
	// -------------------------------------------------//

	virtual int Initialize() override;

	int GetCreatureSelectorOption() {
		return dynamic_cast<EngineSelector*>(GetUIByName("CreatureSelector"))->GetSelectedOption();
	}

	int GetPrevCreatureSelectorOption() {
		return dynamic_cast<EngineSelector*>(GetUIByName("CreatureSelector"))->GetPrevOption();
	}

	void Show(Creature* pCurCreature) { m_pCurCreature = pCurCreature; }

private:
	Creature* m_pCurCreature;

	void OnSaveCreatureData();
	void OnCreateNewCreature();
};