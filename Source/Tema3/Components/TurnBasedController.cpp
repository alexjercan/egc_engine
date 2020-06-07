#include "TurnBasedController.h"

TurnBasedController::TurnBasedController()
{

}

TurnBasedController::~TurnBasedController()
{

}

void TurnBasedController::Start()
{

}

void TurnBasedController::Update(float deltaTimeSeconds)
{
	if (Input::spaceKeyDown && players.size() > 0)
	{
		PlayerController* pc = players.at(currentPlayer)->GetComponent<PlayerController>();
		pc->SetActive(false);
		pc->movementLeft = pc->maxMovementPerTurn;
		currentPlayer = (currentPlayer + 1) % (int)players.size();
		players.at(currentPlayer)->GetComponent<PlayerController>()->SetActive(true);
		MeshRenderer::mainCamera->GetComponent<CameraComponent>()->target = players.at(currentPlayer)->GetComponent<Transform>();
	}
}