#pragma once

#include "Application.h"

class GameApplication : public Application
{
public:
	static GameApplication* GetInstance();

	// Register object and component class
	virtual void RegisterGameClass() override;

	int InitUtilityClasses() override;
private:
	GameApplication();
};