#pragma once

#include <include/glm.h>
#include <corecrt_math_defines.h>
#include "Component.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "Terrain.h"
#include "ParticleSystem.h"
#include "ParticleController.h"

class ProjectileController : public Component {
public:
	ProjectileController();
	~ProjectileController();

	void Start();
	void Update(float deltaTimeSeconds);
	Component* Clone() const { return new ProjectileController(*this); }

	float speed = 5;
	float projectileDrop = 1;
	GameObject* terrainParent;
	GameObject* playerParent;

private:
	bool isActive = true;
	Transform* transform;
	glm::vec3 forward;
	float timeElapsed = 0;
};