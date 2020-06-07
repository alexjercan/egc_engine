#pragma once
#include <vector>
#include "Component.h"
#include <include/glm.h>
#include "Transform.h"
#include <unordered_map>

class GameObject {
public:
	GameObject();
	GameObject(const GameObject& go);
	GameObject(char* name);
	~GameObject();

	//Initializeaza toate componentele obiectului
	void Start();
	//Actualizeaza toate componentele obiectului
	void Update(float deltaTimeSeconds);

	GameObject* Clone() const { return new GameObject(*this); }

	//Intoarce o componenta in functie de tip (prima componenta gasita)
	template <class T> T* GetComponent()
	{		
		for each (Component* c in components)
		{
			if (dynamic_cast<T*>(c))
			{
				return (T*)c;
			}
		}
		return NULL;
	}

	//Adauga o componenta la acest obiect
	void AddComponent(Component* component)
	{
		component->gameObject = this;
		components.push_back(component);
	}

	//intoarce model matrixul global (cu tot cu transformarile parintelui)
	static glm::mat4 GetModelMatrix(GameObject* gameObject);
	static GameObject* Instantiate(GameObject* prefab, GameObject* rootObject = NULL);
	void Destroy();

	GameObject* parent;
	char* name;

	//obiectele din scena
	static std::vector<GameObject*> gameObjects;
	static std::unordered_map<std::string, GameObject*> prefabs;

private:
	std::vector<Component*> components;
};
