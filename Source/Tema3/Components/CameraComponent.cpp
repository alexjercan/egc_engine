#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
	camera = NULL;
	transform = NULL;
	target = NULL;
	distanceToTarget = 2;
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::Start()
{
	transform = gameObject->GetComponent<Transform>(); 
	rotationSpeed = M_PI / 2;
}

void CameraComponent::Update(float deltaTimeSeconds)
{
	PlayerController* pc = target->gameObject->GetComponent<PlayerController>();
	if (pc != NULL)
	{
		if (pc->IsActive())
		{
			transform->rotation.y = target->rotation.y;
			float yRotationI = glm::sign(Input::deltaMouseY) * rotationSpeed;
			transform->rotation.x -= yRotationI * deltaTimeSeconds;
			if (transform->rotation.x > M_PI / 4 && transform->rotation.x < M_PI) transform->rotation.x = M_PI / 4;
			if (transform->rotation.x > M_PI && transform->rotation.x < 2 * M_PI - M_PI / 4) transform->rotation.x = 2 * M_PI - M_PI / 4;
		}

		transform->position.x = target->position.x + sin(transform->rotation.y);
		transform->position.z = target->position.z + cos(transform->rotation.y);
		transform->position.y = target->position.y + 0.5 - sin(transform->rotation.x) / 5;
	}
	else if (pc == NULL)
	{
		transform->rotation.x = 0;
		transform->rotation.z = 0;

		transform->position.x = target->position.x + sin(transform->rotation.y);
		transform->position.z = target->position.z + cos(transform->rotation.y);
		transform->position.y = target->position.y - sin(transform->rotation.x);
	}


	if (camera == NULL) printf("CameraComponent: no camera attached!\n");
	camera->SetPosition(transform->position);
	camera->SetRotation(transform->rotation);
}