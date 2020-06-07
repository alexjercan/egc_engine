#include "PlayerController.h"

PlayerController::PlayerController()
{

}

PlayerController::~PlayerController()
{

}

void PlayerController::Start()
{
	transform = gameObject->GetComponent<Transform>();
	rotationSpeed = M_PI / 2;
	movementSpeed = 1;
}

void PlayerController::Update(float deltaTimeSeconds)
{
	if (!isActive) return;

	float yRotationI = glm::sign(Input::deltaMouseX) * rotationSpeed;
	transform->rotation.y -= yRotationI * deltaTimeSeconds;

	if (Input::fire0)
	{
		GameObject* go = GameObject::Instantiate(GameObject::prefabs["projectilePrefab"]);
		Transform* t = go->GetComponent<Transform>();
		go->GetComponent<ProjectileController>()->terrainParent = terrainParent;
		go->GetComponent<ProjectileController>()->playerParent = gameObject;
		t->position = transform->position + glm::vec3(0, 0.25f, 0);
		MeshRenderer::mainCamera->GetComponent<CameraComponent>()->target = t;

		isActive = false;
	}

	if (movementLeft < 0) return;

	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = MeshRenderer::mainCamera->GetComponent<CameraComponent>()->camera->transform->GetLocalOXVector();
	glm::vec3 forward = MeshRenderer::mainCamera->GetComponent<CameraComponent>()->camera->transform->GetLocalOZVector();
	forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

	if (Input::w) transform->position -= forward * deltaTimeSeconds * movementSpeed;
	if (Input::s) transform->position += forward * deltaTimeSeconds * movementSpeed;
	if (Input::a) transform->position -= right * deltaTimeSeconds * movementSpeed;
	if (Input::d) transform->position += right * deltaTimeSeconds * movementSpeed;

	if (Input::w || Input::a || Input::s || Input::d) movementLeft -= deltaTimeSeconds;
}