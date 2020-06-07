#pragma once

#include <include/glm.h>
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

class Collider : public Component {
public:
	Collider();
	Collider(glm::vec3 centerOffset, glm::vec3 size);
	~Collider();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new Collider(*this); }

	bool IsCollision(Collider other);

	glm::vec3 centerOffset;
	glm::vec3 size;

private:
	void GetMinI(glm::vec3 newP);
	void GetMaxI(glm::vec3 newP);

	Transform* transform;
	glm::vec3 minI;
	glm::vec3 maxI;
};