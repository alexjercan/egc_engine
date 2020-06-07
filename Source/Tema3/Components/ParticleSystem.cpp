#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	nrParticles = 0;
	lifetime = 0;
	elapsedTime = 0;
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::Start()
{
	nrParticles = 10;
	lifetime = PARTICLE_LIFETIME;
	elapsedTime = 0;
}

void ParticleSystem::StartSystem()
{
	for (int i = 0; i < nrParticles; i++)
	{
		for (int j = 0; j < nrParticles; j++)
		{
			GameObject* go = GameObject::Instantiate(GameObject::prefabs["particlePrefab"]);
			float angleZ = 2 * M_PI * i / (float)nrParticles;
			float angleT = M_PI * j / (float)nrParticles;
			go->GetComponent<ParticleController>()->lifetime = lifetime;
			go->GetComponent<ParticleController>()->zAngle = angleZ;
			go->GetComponent<ParticleController>()->tAngle = angleT;
			go->GetComponent<Transform>()->position = gameObject->GetComponent<Transform>()->position;
		}
	}
}

void ParticleSystem::Update(float deltaTimeSeconds)
{

}