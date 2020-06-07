#include "GameObject.h"

std::vector<GameObject*> GameObject::gameObjects;
std::unordered_map<std::string, GameObject*> GameObject::prefabs;

GameObject::GameObject()
{
	parent = NULL;
	this->name = (char*)calloc(100, sizeof(char));
	this->name = _itoa((int)(prefabs.size()), this->name, 10);
}

GameObject::GameObject(const GameObject& go)
{
	parent = NULL;
	name = _strdup(go.name);

	components.clear();

	for each (Component * c in go.components)
	{
		AddComponent(c->Clone());
	}
}

GameObject::GameObject(char* name)
{
	parent = NULL;
	this->name = name;
}

GameObject::~GameObject()
{

}

void GameObject::Start()
{
	for each (Component * c in components)
	{
		c->Start();
	}
}

void GameObject::Update(float deltaTimeSeconds)
{
	for each (Component* c in components)
	{
		c->Update(deltaTimeSeconds);
	}
}

glm::mat4 GameObject::GetModelMatrix(GameObject* gameObject)
{
	if (gameObject == NULL)
	{
		return glm::mat4(1);
	}
	else
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		Transform* transform = gameObject->GetComponent<Transform>();
		modelMatrix = glm::translate(modelMatrix, transform->position);

		modelMatrix = glm::rotate(modelMatrix, transform->rotation.x, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, transform->rotation.y, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, transform->rotation.z, glm::vec3(0, 0, 1));

		modelMatrix = glm::scale(modelMatrix, transform->scale);

		return GameObject::GetModelMatrix(gameObject->parent) * modelMatrix;
	}
}

GameObject* GameObject::Instantiate(GameObject* prefab, GameObject* rootObject)
{
	if (prefab == NULL) return NULL;

	GameObject* root = prefab->Clone();
	root->parent = rootObject;
	root->Start();
	gameObjects.push_back(root);
	
	for (auto iter = GameObject::prefabs.begin(); iter != GameObject::prefabs.end(); iter++)
	{
		if (iter->second->parent == prefab)
		{
			Instantiate(iter->second, root);
		}
	}
	return root;
}

void GameObject::Destroy()
{
	for (int i = 0; i < gameObjects.size();)
	{
		if (gameObjects[i] == this)
		{
			for (int j = 0; j < gameObjects.size();)
			{
				if (gameObjects[j]->parent == this)
				{
					gameObjects[j]->Destroy();
				}
				else j++;
			}

			gameObjects.erase(gameObjects.begin() + i);
		}
		else i++;
	}
}