#pragma once
#include "ObjectSpawner.h"

class GameObjectSpawner : public ObjectSpawner
{
public:
	GameObjectSpawner();

	// --------------- Required for every object --------//
	static GameObjectSpawner* Create() { return new GameObjectSpawner(); }
	static void RegisterGameClass();
	virtual const char* GetObjectClassName() { return "GameObjectSpawner"; }
	virtual int GetObjectClassNameHash() { return ToStringHash("GameObjectSpawner"); }
	// -------------------------------------------------//

private:
};