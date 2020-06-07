#include "SpotLight.h"

SpotLight::SpotLight()
{
	light_direction = glm::vec3(0, -1, 0);
	cutoff = (float)M_PI;
}

SpotLight::~SpotLight()
{

}

void SpotLight::Start()
{
	transform = gameObject->GetComponent<Transform>();
}

void SpotLight::Update(float deltaTimeSeconds)
{
	transform->position.x = target->position.x;
	transform->position.z = target->position.z;
}