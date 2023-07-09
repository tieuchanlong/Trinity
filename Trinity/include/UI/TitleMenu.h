#pragma once
#include "UI/EngineUIContainer.h"

class TitleMenu : public EngineUIContainer
{
public:
	TitleMenu();

	// --------------- Required for every object --------//
	static Object* Create() { return new TitleMenu(); }
	static void RegisterGameClass();
	static const char* GetObjectClassName() { return "TitleMenu"; }
	static int GetObjectClassNameHash() { return ToStringHash("TitleMenu"); }
	// -------------------------------------------------//

	virtual int Initialize() override;
	virtual int Destroy() override;

	virtual int OnConfirmOption() override;

private:
	void SetupMainLevels();
	void SetupMapEditorLevel();
	void SetupObjectEditorLevel();
	void QuitGame();
};