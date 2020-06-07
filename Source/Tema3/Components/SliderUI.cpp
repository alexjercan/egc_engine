#include "SliderUI.h"

SliderUI::SliderUI()
{
	value = NULL;
	maxValue = 0;
}

SliderUI::~SliderUI()
{

}

void SliderUI::Start()
{
	maxValue = 1;
	initialLength = gameObject->GetComponent<Transform>()->scale.x;
}

void SliderUI::Update(float deltaTimeSeconds)
{
	if (value != NULL && maxValue > 0 && *value > 0)
	{		
		float p = *value / maxValue;
		gameObject->GetComponent<Transform>()->scale.x = p * initialLength;
	}
}