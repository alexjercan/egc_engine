#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "CameraComponent.h"
#include "Terrain.h"
#include "ProjectileController.h"

#include "../Input/Input.h"

#include <Component/Transform/Transform.h>
#include <corecrt_math_defines.h>
#include <include/glm.h>

//Componenta care contine pozitia, rotatia si scalarea unui obiect
class PlayerController : public Component
{
public:
	PlayerController();
	~PlayerController();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new PlayerController(*this); }

	void SetActive(bool value) { isActive = value; }
	bool IsActive() { return isActive; }

	float movementSpeed;
	float rotationSpeed;

	float maxMovementPerTurn = 5.0f;
	float movementLeft = maxMovementPerTurn;

	float maxHealth = 5.0f;
	float health = maxHealth;	

	GameObject* terrainParent;

private:
	Transform* transform;
	bool isActive = false;
};

