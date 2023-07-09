#include <DirectX11BasePch.h>
#include "UI/CreatureEditorMenu.h"
#include "UI/EngineButton.h"
#include "UI/EngineSlider.h"
#include "GameAccessor.h"

CreatureEditorMenu::CreatureEditorMenu() : EngineUIContainer()
{
	m_pCurCreature = 0;
	m_iCreatureIndex = 0;
}

void CreatureEditorMenu::RegisterGameClass()
{
	GET_OBJECT_MANAGER()->Register(ToStringHash("CreatureEditorMenu"), CreatureEditorMenu::Create);
}

int CreatureEditorMenu::Initialize()
{
	int iRet = EngineUIContainer::Initialize();

	m_pInteractibleUIs->Add(GetUIByName("CreatureXSlider"));
	m_pInteractibleUIs->Add(GetUIByName("CreatureYSlider"));
	m_pInteractibleUIs->Add(GetUIByName("CreatureZSlider"));
	m_pInteractibleUIs->Add(GetUIByName("CreatureSizeXSlider"));
	m_pInteractibleUIs->Add(GetUIByName("CreatureSizeYSlider"));
	m_pInteractibleUIs->Add(GetUIByName("CreatureSizeZSlider"));
	m_pInteractibleUIs->Add(GetUIByName("CreatureColorRSlider"));
	m_pInteractibleUIs->Add(GetUIByName("CreatureColorGSlider"));
	m_pInteractibleUIs->Add(GetUIByName("CreatureColorBSlider"));
	m_pInteractibleUIs->Add(GetUIByName("PrevBodyPartButton"));
	m_pInteractibleUIs->Add(GetUIByName("NextBodyPartButton"));
	SetNextUIContainer(OBJECT_EDITOR_MENU);

	// Set up value change callback with slider
	for (int i = 0; i < 9; i++)
	{
		XMFLOAT3 vColor = dynamic_cast<EngineSlider*>(m_pInteractibleUIs->GetElementAtIndex(i)->GetValue())->GetColor();
		dynamic_cast<EngineSlider*>(m_pInteractibleUIs->GetElementAtIndex(i)->GetValue())->SetHighlightColor(XMFLOAT3(vColor.x + 0.25f, vColor.y + 0.3f, vColor.z));
		dynamic_cast<EngineSlider*>(m_pInteractibleUIs->GetElementAtIndex(i)->GetValue())->Subscribe(std::bind(&CreatureEditorMenu::OnCreatureSliderValueChange, this));
	}

	// Set up body part change with button
	dynamic_cast<EngineButton*>(GetUIByName("PrevBodyPartButton"))->Subscribe(std::bind(&CreatureEditorMenu::OnCreatureBodyPartChangePrev, this));
	dynamic_cast<EngineButton*>(GetUIByName("NextBodyPartButton"))->Subscribe(std::bind(&CreatureEditorMenu::OnCreatureBodyPartChangeNext, this));

	XMFLOAT3 vColor = dynamic_cast<EngineButton*>(GetUIByName("PrevBodyPartButton"))->GetColor();
	dynamic_cast<EngineButton*>(GetUIByName("PrevBodyPartButton"))->SetHighlightColor(XMFLOAT3(vColor.x + 0.2f, vColor.y + 0.1f, vColor.z));

	vColor = dynamic_cast<EngineButton*>(GetUIByName("NextBodyPartButton"))->GetColor();
	dynamic_cast<EngineButton*>(GetUIByName("NextBodyPartButton"))->SetHighlightColor(XMFLOAT3(vColor.x + 0.2f, vColor.y + 0.1f, vColor.z));

	// Reset the body part index
	for (int i = 0; i < MAX_NUM_CREATURES; i++)
	{
		m_iBodyPartIndexes[i] = 0;
		m_iBodySections[i] = 0;
	}

	return iRet;
}

void CreatureEditorMenu::Show(Creature* pCreature, int iCreatureIndex)
{
	m_pCurCreature = pCreature;
	m_iCreatureIndex = iCreatureIndex;

	// Set the creature value on the slider
	BodyPartComponent* pBodyPart = m_pCurCreature->GetBodyPartByIndex((BodySection)m_iBodySections[m_iCreatureIndex], m_iBodyPartIndexes[m_iCreatureIndex]);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureXSlider"))->SetValue(pBodyPart->GetLocalPosition().x);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureXSlider"))->SetMinValue(pBodyPart->GetLocalPosition().x - 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureXSlider"))->SetMaxValue(pBodyPart->GetLocalPosition().x + 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureYSlider"))->SetValue(pBodyPart->GetLocalPosition().y);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureYSlider"))->SetMinValue(pBodyPart->GetLocalPosition().y - 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureYSlider"))->SetMaxValue(pBodyPart->GetLocalPosition().y + 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureZSlider"))->SetValue(pBodyPart->GetLocalPosition().z);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureZSlider"))->SetMinValue(pBodyPart->GetLocalPosition().z - 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureZSlider"))->SetMaxValue(pBodyPart->GetLocalPosition().z + 5.0f);

	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeXSlider"))->SetValue(pBodyPart->GetSize().x);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeXSlider"))->SetMinValue(pBodyPart->GetSize().x - 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeXSlider"))->SetMaxValue(pBodyPart->GetSize().x + 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeYSlider"))->SetValue(pBodyPart->GetSize().y);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeYSlider"))->SetMinValue(pBodyPart->GetSize().y - 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeYSlider"))->SetMaxValue(pBodyPart->GetSize().y + 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeZSlider"))->SetValue(pBodyPart->GetSize().z);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeZSlider"))->SetMinValue(pBodyPart->GetSize().z - 5.0f);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeZSlider"))->SetMaxValue(pBodyPart->GetSize().z + 5.0f);

	dynamic_cast<EngineSlider*>(GetUIByName("CreatureColorRSlider"))->SetValue(pBodyPart->GetColor().x);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureColorGSlider"))->SetValue(pBodyPart->GetColor().y);
	dynamic_cast<EngineSlider*>(GetUIByName("CreatureColorBSlider"))->SetValue(pBodyPart->GetColor().z);
	m_pCurCreature->GetBodyPartByIndex((BodySection)m_iBodySections[m_iCreatureIndex], m_iBodyPartIndexes[m_iCreatureIndex])->SetAlpha(0.2f);
}

void CreatureEditorMenu::OnCreatureSliderValueChange()
{
	if (0 <= m_iHighlightedUIIndex && m_iHighlightedUIIndex <= 2)
	{
		// Change creature body part location
		m_pCurCreature->GetBodyPartByIndex((BodySection)m_iBodySections[m_iCreatureIndex], m_iBodyPartIndexes[m_iCreatureIndex])->SetLocalPosition(XMFLOAT3(dynamic_cast<EngineSlider*>(GetUIByName("CreatureXSlider"))->GetValue(), dynamic_cast<EngineSlider*>(GetUIByName("CreatureYSlider"))->GetValue(), dynamic_cast<EngineSlider*>(GetUIByName("CreatureZSlider"))->GetValue()));
	}
	else if (3 <= m_iHighlightedUIIndex && m_iHighlightedUIIndex <= 5)
	{
		// Change creature body part size
		m_pCurCreature->GetBodyPartByIndex((BodySection)m_iBodySections[m_iCreatureIndex], m_iBodyPartIndexes[m_iCreatureIndex])->SetSize(XMFLOAT3(dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeXSlider"))->GetValue(), dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeYSlider"))->GetValue(), dynamic_cast<EngineSlider*>(GetUIByName("CreatureSizeZSlider"))->GetValue()));
	}
	else if (6 <= m_iHighlightedUIIndex && m_iHighlightedUIIndex <= 8)
	{
		// Change creature body part color
		m_pCurCreature->GetBodyPartByIndex((BodySection)m_iBodySections[m_iCreatureIndex], m_iBodyPartIndexes[m_iCreatureIndex])->SetColor(XMFLOAT3(dynamic_cast<EngineSlider*>(GetUIByName("CreatureColorRSlider"))->GetValue(), dynamic_cast<EngineSlider*>(GetUIByName("CreatureColorGSlider"))->GetValue(), dynamic_cast<EngineSlider*>(GetUIByName("CreatureColorBSlider"))->GetValue()));
	}
}

void CreatureEditorMenu::OnCreatureBodyPartChangePrev()
{
	BodyPartComponent* pBodyPart = m_pCurCreature->GetBodyPartByIndex((BodySection)m_iBodySections[m_iCreatureIndex], m_iBodyPartIndexes[m_iCreatureIndex]);
	pBodyPart->SetAlpha(1.0f);
	m_iBodyPartIndexes[m_iCreatureIndex]--;

	if (m_iBodyPartIndexes[m_iCreatureIndex] < 0)
	{
		m_iBodySections[m_iCreatureIndex] = (m_iBodySections[m_iCreatureIndex] - 1 + NUM_BODY_SECTIONS) % NUM_BODY_SECTIONS;

		while (m_pCurCreature->GetNumBodyParts((BodySection)m_iBodySections[m_iCreatureIndex]) <= 0)
		{
			m_iBodySections[m_iCreatureIndex] = (m_iBodySections[m_iCreatureIndex] - 1 + NUM_BODY_SECTIONS) % NUM_BODY_SECTIONS;
		}

		m_iBodyPartIndexes[m_iCreatureIndex] = m_pCurCreature->GetNumBodyParts((BodySection)m_iBodySections[m_iCreatureIndex]) - 1;
	}

	Show(m_pCurCreature, m_iCreatureIndex);
}

void CreatureEditorMenu::OnCreatureBodyPartChangeNext()
{
	BodyPartComponent* pBodyPart = m_pCurCreature->GetBodyPartByIndex((BodySection)m_iBodySections[m_iCreatureIndex], m_iBodyPartIndexes[m_iCreatureIndex]);
	pBodyPart->SetAlpha(1.0f);
	m_iBodyPartIndexes[m_iCreatureIndex]++;

	if (m_iBodyPartIndexes[m_iCreatureIndex] >= m_pCurCreature->GetNumBodyParts((BodySection)m_iBodySections[m_iCreatureIndex]))
	{
		m_iBodySections[m_iCreatureIndex] = (m_iBodySections[m_iCreatureIndex] + 1) % NUM_BODY_SECTIONS;

		while (m_pCurCreature->GetNumBodyParts((BodySection)m_iBodySections[m_iCreatureIndex]) <= 0)
		{
			m_iBodySections[m_iCreatureIndex] = (m_iBodySections[m_iCreatureIndex] + 1) % NUM_BODY_SECTIONS;
		}

		m_iBodyPartIndexes[m_iCreatureIndex] = 0;
	}

	Show(m_pCurCreature, m_iCreatureIndex);
}

