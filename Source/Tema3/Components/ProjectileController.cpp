#include "ProjectileController.h"

ProjectileController::ProjectileController()
{

}

ProjectileController::~ProjectileController()
{

}

void ProjectileController::Start()
{
	transform = gameObject->GetComponent<Transform>();
	forward = MeshRenderer::mainCamera->GetComponent<CameraComponent>()->camera->transform->GetLocalOZVector();
}

void ProjectileController::Update(float deltaTimeSeconds)
{
	if (isActive)
	{
		forward.y += deltaTimeSeconds * projectileDrop;
		transform->position -= forward * speed * deltaTimeSeconds;

		if (terrainParent->GetComponent<Terrain>()->GetIndexAt(transform->position.x, transform->position.z) < 0)
		{
			isActive = false;
		}
		float h = terrainParent->GetComponent<Terrain>()->GetHeightAt(transform->position.x, transform->position.z);
		if (transform->position.y < h)
		{
			isActive = false;
			terrainParent->GetComponent<Terrain>()->Brush(glm::vec2(transform->position.x, transform->position.z), 10, (char)100);
			gameObject->GetComponent<ParticleSystem>()->StartSystem();
		}
	}
	else
	{
		timeElapsed += deltaTimeSeconds;
		if (timeElapsed > PARTICLE_LIFETIME)
		{
			if(MeshRenderer::mainCamera->GetComponent<CameraComponent>()->target == gameObject->GetComponent<Transform> ())
				MeshRenderer::mainCamera->GetComponent<CameraComponent>()->target = playerParent->GetComponent<Transform>();
			gameObject->Destroy();
		}
	}
}