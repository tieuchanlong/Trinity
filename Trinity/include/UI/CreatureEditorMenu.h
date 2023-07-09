#pragma once
#include "UI/EngineUIContainer.h"
#include "Creature.h"

#define MAX_NUM_CREATURES 100

class CreatureEditorMenu : public EngineUIContainer
{
public:
	CreatureEditorMenu();

	// --------------- Required for every object --------//
	static Object* Create() { return new CreatureEditorMenu(); }
	static void RegisterGameClass();
	static const char* GetObjectClassName() { return "CreatureEditorMenu"; }
	static int GetObjectClassNameHash() { return ToStringHash("CreatureEditorMenu"); }
	// -------------------------------------------------//

	virtual int Initialize() override;
	void Show(Creature* pCreature, int iCreatureIndex);

private:
	int m_iCreatureIndex;
	int m_iBodySections[MAX_NUM_CREATURES];
	int m_iBodyPartIndexes[MAX_NUM_CREATURES];

	Creature* m_pCurCreature;

	void OnCreatureSliderValueChange();
	void OnCreatureBodyPartChangePrev();
	void OnCreatureBodyPartChangeNext();
};