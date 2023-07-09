#pragma once
#include "EngineObject.h"

enum BaseType
{
	FOREST,
	WATER,
	SAND,
	NUM_BASE_TYPES,
};

class Base : public Object
{
public:
	Base();

	// --------------- Required for every object --------//
	static Base* Create() { return new Base(); }
	static void RegisterGameClass();
	virtual const char* GetObjectClassName() { return "Base"; }
	virtual int GetObjectClassNameHash() { return ToStringHash("Base"); }

	virtual bool ReadSaveData(rapidjson::Value::ConstValueIterator& itr);
	virtual bool WriteSaveData(rapidjson::Writer<rapidjson::StringBuffer>* writer);
	// -------------------------------------------------//

	int GetBaseType() { return m_iBaseType; }

protected:
	BaseType m_iBaseType;
};