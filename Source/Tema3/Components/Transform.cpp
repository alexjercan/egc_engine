#include "Transform.h"

Transform::Transform()
{

}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Transform::~Transform()
{

}

void Transform::Start()
{

}

void Transform::Update(float deltaTimeSeconds)
{
	if (rotation.x >= 2 * M_PI) rotation.x = rotation.x - 2 * M_PI;
	if (rotation.y >= 2 * M_PI) rotation.y = rotation.y - 2 * M_PI;
	if (rotation.z >= 2 * M_PI) rotation.z = rotation.z - 2 * M_PI;
	if (rotation.x < 0) rotation.x = 2 * M_PI + rotation.x;
	if (rotation.y < 0) rotation.y = 2 * M_PI + rotation.y;
	if (rotation.z < 0) rotation.z = 2 * M_PI + rotation.z;
}