#include "Terrain.h"

Terrain::Terrain()
{

}

Terrain::~Terrain()
{

}

void Terrain::Start()
{

}

void Terrain::Update(float deltaTimeSeconds)
{
	/*if(Input::spaceKeyDown == true) 
		Brush(glm::ivec2(MeshRenderer::light0->GetComponent<Transform> ()->position.z / 10 * height, 
		MeshRenderer::light0->GetComponent<Transform>()->position.x / 10 * width), 10, 5);*/

	for each (GameObject * p in terrainObject)
	{
		Transform* t = p->GetComponent<Transform>();
		t->position.y = GetHeightAt(t->position.x, t->position.z);
	}
}

void Terrain::Brush(glm::vec2 worldPosition, int radius, char value)
{
	int xi = worldPosition.x * width / 10.0f;
	int zi = worldPosition.y * height / 10.0f;

	glm::ivec2 center = glm::ivec2(zi, xi);
	for (int i = max(0, center.x - radius); i < min(height, center.x + radius); i++)
	{
		for (int j = max(0, center.y - radius); j < min(width, center.y + radius); j++)
		{
			float d2toC = (i - center.x) * (i - center.x) + (j - center.y) * (j - center.y);
			if (d2toC <= radius * radius)
			{
				int index = i * width + j;
				if (value / glm::clamp(d2toC / radius / radius, 0.1f, 1.0f) > data[index]) data[index] = 0;
				else data[index] = data[index] - value / glm::clamp(d2toC / radius / radius, 0.1f, 1.0f);;
			}
		}
	}
	
	for(auto it = terrainObject.begin(); it != terrainObject.end();)
	{
		Transform* t = (*it)->GetComponent<Transform>();
		float xO2 = (worldPosition.x - t->position.x) * (worldPosition.x - t->position.x) * width / 10.0f * width / 10.0f;
		float zO2 = (worldPosition.y - t->position.z) * (worldPosition.y - t->position.z) * height / 10.0f * height / 10.0f;

		if (xO2 + zO2 <= radius * radius)
		{
			PlayerController* pc = (*it)->GetComponent<PlayerController>();
			if (pc == NULL)
			{
				(*it)->Destroy();
				it = terrainObject.erase(it);
			}
			else
			{
				pc->health -= sqrt(xO2 + zO2) / radius;
				if (pc->health < 0)
				{
					gameObject->GetComponent<TurnBasedController>()->RemovePlayer((*it));
					(*it)->Destroy();
					it = terrainObject.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		else
		{
			it++;
		}
	}

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, (void*)data);
}