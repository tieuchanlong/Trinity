#pragma once

#include "EngineCubeComponent.h"

class BodyPartComponent : public EngineCubeComponent
{
public:
	BodyPartComponent();

	// --------------- Required for every component --------//
	static Component* Create() { return new BodyPartComponent(); }
	static void RegisterGameClass();
	virtual const char* GetComponentClassName() override { return "BodyPartComponent"; }
	virtual int GetComponentClassNameHash() override { return ToStringHash("BodyPartComponent"); }

	virtual bool ReadSaveData(rapidjson::Value::ConstValueIterator& itr);
	virtual bool WriteSaveData(rapidjson::Writer<rapidjson::StringBuffer>* writer);
	// -------------------------------------------------//

	void SetBodyPartType(int iBodyPartType) { m_iBodyPartType = iBodyPartType; }
	int GetBodyPartType() { return m_iBodyPartType; }

protected:
	int m_iBodyPartType;
};