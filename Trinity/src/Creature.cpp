#include <DirectX11BasePch.h>
#include "Creature.h"
#include "GameAccessor.h"

Creature::Creature() : Object()
{
	for (int i = 0; i < NUM_BODY_SECTIONS; i++)
	{
		m_pBodyParts[i] = new List<BodyPartComponent>();
	}
}

void Creature::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("Creature"), Creature::Create);
}

bool Creature::ReadSaveData(rapidjson::Value::ConstValueIterator& itr)
{
	bool bRet = Object::ReadSaveData(itr);

	const rapidjson::Value& obj = (*itr);
	m_pCreatureData.m_fAgression = obj["CreatureAgression"].GetDouble();
	m_pCreatureData.m_fSpeed = obj["CreatureSpeed"].GetDouble();
	m_pCreatureData.m_fStrength = obj["CreatureStrength"].GetDouble();
	m_pCreatureData.m_fHP = obj["CreatureHP"].GetDouble();
	m_pCreatureData.m_iEatingHabit = (EatingHabitType)obj["CreatureEatingHabit"].GetInt();
	itr++;

	return bRet;
}

bool Creature::WriteSaveData(rapidjson::Writer<rapidjson::StringBuffer>* writer)
{
	bool bRet = Object::WriteSaveData(writer);

	writer->StartObject();
	writer->Key("CreatureAgression");
	writer->Double(m_pCreatureData.m_fAgression);
	writer->Key("CreatureSpeed");
	writer->Double(m_pCreatureData.m_fSpeed);
	writer->Key("CreatureStrength");
	writer->Double(m_pCreatureData.m_fStrength);
	writer->Key("CreatureHP");
	writer->Double(m_pCreatureData.m_fHP);
	writer->Key("CreatureEatingHabit");
	writer->Int(m_pCreatureData.m_iEatingHabit);
	writer->EndObject();

	return bRet;
}

void Creature::AddComponent(Component* component)
{
	Object::AddComponent(component);

	if (dynamic_cast<BodyPartComponent*>(component))
	{
		m_pBodyParts[dynamic_cast<BodyPartComponent*>(component)->GetBodyPartType()]->Add(dynamic_cast<BodyPartComponent*>(component));
	}
}

int Creature::Update(float fDeltaTime)
{
	return Object::Update(fDeltaTime);
}
