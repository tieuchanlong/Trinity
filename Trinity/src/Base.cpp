#include <DirectX11BasePch.h>
#include "Base.h"
#include "EngineObjectManager.h"
#include "EngineLevelManager.h"
#include "GameAccessor.h"

Base::Base() : Object()
{
	
}

void Base::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("Base"), Base::Create);
}

bool Base::ReadSaveData(rapidjson::Value::ConstValueIterator& itr)
{
	bool bRet = Object::ReadSaveData(itr);

	const rapidjson::Value& obj = (*itr);
	m_iBaseType = (BaseType)obj["BaseType"].GetInt();
	itr++;

	return bRet;
}

bool Base::WriteSaveData(rapidjson::Writer<rapidjson::StringBuffer>* writer)
{
	bool bRet = Object::WriteSaveData(writer);

	writer->StartObject();
	writer->Key("BaseType");
	writer->Int(m_iBaseType);
	writer->EndObject();

	return bRet;
}
