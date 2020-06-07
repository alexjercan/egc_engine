#include "ParticleController.h"

ParticleController::ParticleController()
{
	lifetime = 0;
	elapsedTime = 0;
	zAngle = 0;
	distance = 0;
}

ParticleController::~ParticleController()
{

}

void ParticleController::Start()
{

}

void ParticleController::Update(float deltaTimeSeconds)
{
	glm::vec3 dir = glm::vec3(distance * cos(zAngle) * sin(tAngle), 
		distance * sin(zAngle) * sin(tAngle), distance * cos(tAngle));
	gameObject->GetComponent<Transform>()->position += dir;
	distance += deltaTimeSeconds;
	elapsedTime += deltaTimeSeconds;
	if (elapsedTime >= lifetime)
	{
		gameObject->Destroy();
	}
}