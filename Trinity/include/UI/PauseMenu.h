#pragma once
#include "UI/EngineUIContainer.h"

class PauseMenu : public EngineUIContainer
{
public:
	PauseMenu();

	// --------------- Required for every object --------//
	static Object* Create() { return new PauseMenu(); }
	static void RegisterGameClass();
	static const char* GetObjectClassName() { return "PauseMenu "; }
	static int GetObjectClassNameHash() { return ToStringHash("PauseMenu "); }
	// -------------------------------------------------//

	virtual int Initialize() override;
	virtual int Destroy() override;

	void OnResumeGame();
	void OnGoToTitle();
	void OnQuitGame();

	virtual int OnConfirmOption() override;

private:
};