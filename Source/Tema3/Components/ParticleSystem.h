#pragma once

#include "Component.h"
#include "GameObject.h"
#include "ParticleController.h"
#include <corecrt_math_defines.h>
#include <include/glm.h>

#define PARTICLE_LIFETIME 0.1f

class ParticleSystem : public Component
{
public:
	ParticleSystem();
	~ParticleSystem();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new ParticleSystem(*this); }

	void StartSystem();

	int nrParticles;
	float lifetime;

private:
	float elapsedTime = 0;
};
