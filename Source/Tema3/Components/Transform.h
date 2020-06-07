#pragma once
#include "Component.h"
#include <corecrt_math_defines.h>
#include <include/glm.h>

//Componenta care contine pozitia, rotatia si scalarea unui obiect
class Transform : public Component {
public:
	Transform();
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Transform();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new Transform(*this); }

	glm::vec3 position;		//pozitia locala fata de parinte
	glm::vec3 rotation;		//rotatia locala fata de parinte
	glm::vec3 scale;		//scalarea locala fata de parinte
};