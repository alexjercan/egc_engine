#pragma once
#include "Component.h"
#include "../Input/Input.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "TurnBasedController.h"

#include "../Input/Input.h"

#include <corecrt_math_defines.h>
#include <include/glm.h>
#include <GL\glew.h>
#include <unordered_set>

//Componenta care contine pozitia, rotatia si scalarea unui obiect
class Terrain : public Component {
public:
	Terrain();
	~Terrain();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new Terrain(*this); }

	void Brush(glm::vec2 worldPosition, int radius, char value);
	
	void AddTerrainObject(GameObject* player) { terrainObject.push_back(player); }

	int GetIndexAt(float x, float z)
	{
		int xi = x * width / 10.0f;
		int zi = z * height / 10.0f;
		int index = xi + zi * width;
		if (index < 0 || index >= width * height) return -1;
		return index;
	}

	float GetHeightAt(float x, float z)
	{
		int index = GetIndexAt(x, z);
		if (index < 0) return 0;
		return data[index] / 255.0f;
	}

	unsigned char* data;
	int channels, width, height;
	GLuint textureID = 0;

private:
	std::vector<GameObject*> terrainObject;

};
