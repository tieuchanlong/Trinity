#pragma once

#include "EngineObject.h"
#include "BodyPartComponent.h"

enum BodySection
{
	HEAD,
	MID_BODY,
	LEG,
	TAIL,
	NUM_BODY_SECTIONS,
};

enum EatingHabitType
{
	CARNIVORE,
	HERBIVORE,
	OMNIVORE,
	NUM_EATING_HABITS,
};


struct CreatureData
{
	float m_fAgression;
	float m_fSpeed;
	float m_fStrength;
	float m_fHP;
	EatingHabitType m_iEatingHabit;
};

class Creature : public Object
{
public:
	Creature();

	// --------------- Required for every object --------//
	static Creature* Create() { return new Creature(); }
	static void RegisterGameClass();
	virtual const char* GetObjectClassName() { return "Creature"; }
	virtual int GetObjectClassNameHash() { return ToStringHash("Creature"); }

	virtual bool ReadSaveData(rapidjson::Value::ConstValueIterator& itr);
	virtual bool WriteSaveData(rapidjson::Writer<rapidjson::StringBuffer>* writer);
	// -------------------------------------------------//

	virtual void AddComponent(Component* component) override;

	virtual int Update(float fDeltaTime) override;

	int GetNumBodyParts(BodySection iBodySection) { return m_pBodyParts[iBodySection]->GetNumElements(); }
	BodyPartComponent* GetBodyPartByIndex(BodySection iBodySection, int iIndex) { return m_pBodyParts[iBodySection]->GetElementAtIndex(iIndex)->GetValue(); }

protected:
	List<BodyPartComponent>* m_pBodyParts[NUM_BODY_SECTIONS];

	CreatureData m_pCreatureData;
};