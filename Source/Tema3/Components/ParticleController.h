#pragma once

#include "Component.h"
#include "GameObject.h"
#include <corecrt_math_defines.h>
#include <include/glm.h>

class ParticleController : public Component
{
public:
	ParticleController();
	~ParticleController();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new ParticleController(*this); }

	float lifetime;
	float zAngle;
	float tAngle;

private:
	float elapsedTime = 0;
	float distance = 0;
};

