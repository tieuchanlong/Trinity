#pragma once
#include "UI/EngineUIContainer.h"

class TransitionMenu : public EngineUIContainer
{
public:
	TransitionMenu();

	// --------------- Required for every object --------//
	static Object* Create() { return new TransitionMenu(); }
	static void RegisterGameClass();
	static const char* GetObjectClassName() { return "TransitionMenu"; }
	static int GetObjectClassNameHash() { return ToStringHash("TransitionMenu"); }
	// -------------------------------------------------//

	virtual int Initialize() override;
	virtual int Update(float fDeltaTime) override;

	virtual int OnConfirmOption() override;

protected:
	bool m_bFinishedLoading;
};