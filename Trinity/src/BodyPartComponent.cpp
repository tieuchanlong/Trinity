#include <DirectX11BasePch.h>
#include "BodyPartComponent.h"
#include "EngineComponentManager.h"

BodyPartComponent::BodyPartComponent() : EngineCubeComponent()
{

}

void BodyPartComponent::RegisterGameClass()
{
	EngineComponentManager::GetInstance()->Register(ToStringHash("BodyPartComponent"), BodyPartComponent::Create);
}

bool BodyPartComponent::ReadSaveData(rapidjson::Value::ConstValueIterator& itr)
{
	bool bRet = Component::ReadSaveData(itr);

	const rapidjson::Value& obj = (*itr);

	m_vLocalPos = XMFLOAT3(obj["X"].GetDouble(), obj["Y"].GetDouble(), obj["Z"].GetDouble());
	m_vSize = XMFLOAT3(obj["SizeX"].GetDouble(), obj["SizeY"].GetDouble(), obj["SizeZ"].GetDouble());
	m_vColor = XMFLOAT3(obj["ColorR"].GetDouble(), obj["ColorG"].GetDouble(), obj["ColorB"].GetDouble());
	m_iBodyPartType = obj["BodyPartType"].GetInt();
	itr++;

	return bRet;
}

bool BodyPartComponent::WriteSaveData(rapidjson::Writer<rapidjson::StringBuffer>* writer)
{
	bool bRet = Component::WriteSaveData(writer);

	writer->StartObject();
	writer->Key("X");
	writer->Double(m_vLocalPos.x);
	writer->Key("Y");
	writer->Double(m_vLocalPos.y);
	writer->Key("Z");
	writer->Double(m_vLocalPos.z);
	writer->Key("SizeX");
	writer->Double(m_vSize.x);
	writer->Key("SizeY");
	writer->Double(m_vSize.y);
	writer->Key("SizeZ");
	writer->Double(m_vSize.z);
	writer->Key("ColorR");
	writer->Double(m_vColor.x);
	writer->Key("ColorG");
	writer->Double(m_vColor.y);
	writer->Key("ColorB");
	writer->Double(m_vColor.z);
	writer->Key("BodyPartType");
	writer->Int(m_iBodyPartType);
	writer->EndObject();

	return bRet;
}
