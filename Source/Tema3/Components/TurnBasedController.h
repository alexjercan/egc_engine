#pragma once

#include "Component.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "PlayerController.h"

#include "../Input/Input.h"

#include <corecrt_math_defines.h>
#include <include/glm.h>

//Componenta care contine pozitia, rotatia si scalarea unui obiect
class TurnBasedController : public Component
{
public:
	TurnBasedController();
	~TurnBasedController();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new TurnBasedController(*this); }

	void AddPlayer(GameObject* player) { players.push_back(player); }
	void RemovePlayer(GameObject* player) {
		int index = 0;
		for (auto it = players.begin(); it != players.end();)
		{
			if ((*it) == player)
			{
				players.erase(it);
				break;
			}
			else
			{
				index++;
				it++;
			}
		}
		if (index < currentPlayer) currentPlayer--;
	}

private:
	std::vector<GameObject*> players;
	int currentPlayer = 0;
};

