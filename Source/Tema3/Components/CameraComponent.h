#pragma once

#include <include/glm.h>
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "PlayerController.h"

#include "../Input/Input.h"

#include <Engine\Component\Camera\Camera.h>

class CameraComponent : public Component {
public:
	CameraComponent();
	~CameraComponent();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new CameraComponent(*this); }

	Transform* target;
	float distanceToTarget;

	EngineComponents::Camera* camera;

private:
	Transform* transform;
	float rotationSpeed;
};

