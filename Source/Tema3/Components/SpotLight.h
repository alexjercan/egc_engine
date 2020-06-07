#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "../Input/Input.h"

#include <corecrt_math_defines.h>
#include <include/glm.h>

//Componenta care contine pozitia, rotatia si scalarea unui obiect
class SpotLight : public Component {
public:
	SpotLight();
	~SpotLight();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new SpotLight(*this); }

	Transform* target;

	glm::vec3 light_direction;
	float cutoff;

private:
	Transform* transform;
};