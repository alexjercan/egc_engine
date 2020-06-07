#pragma once

class GameObject;

class Component {
public:
	//Folosita pentru initializare
	virtual void Start() = 0;
	//Folosita pentru actualizare, se apeleaza in fiecre frame
	virtual void Update(float deltaTimeSeconds) = 0;

	virtual Component* Clone() const = 0;

	//Referinta catre obiectul care contine componenta
	GameObject* gameObject;
};
