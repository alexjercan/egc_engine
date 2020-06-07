#pragma once

#include "Component.h"
#include "GameObject.h"
#include <corecrt_math_defines.h>
#include <include/glm.h>

//Componenta care contine pozitia, rotatia si scalarea unui obiect
class SliderUI : public Component
{
public:
	SliderUI();
	~SliderUI();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new SliderUI(*this); }

	float* value;
	float maxValue;
	float initialLength;
};
