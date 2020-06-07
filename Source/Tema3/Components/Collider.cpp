#include "Collider.h"

Collider::Collider()
{
	transform = NULL;
}

Collider::Collider(glm::vec3 centerOffset, glm::vec3 size)
{
	transform = NULL;
	this->centerOffset = centerOffset;
	this->size = size;
}

Collider::~Collider()
{

}

void Collider::Start()
{
	transform = gameObject->GetComponent<Transform>();
}

//Calculeaza pozitia fiecarui punct al colliderului si apoi afla minimul si maximul pe axe
void Collider::Update(float deltaTimeSeconds)
{
	glm::vec3 newP = glm::vec3(gameObject->GetComponent<Transform>()->position) + size * glm::vec3(1, 1, 1) + centerOffset;//dsf
	minI = maxI = newP;

	newP = glm::vec3(gameObject->GetComponent<Transform>()->position) + size * glm::vec3(1, 1, -1) + centerOffset;//dss
	GetMinI(newP);
	GetMaxI(newP);

	newP = glm::vec3(gameObject->GetComponent<Transform>()->position) + size * glm::vec3(-1, 1, 1) + centerOffset;//ssf
	GetMinI(newP);
	GetMaxI(newP);

	newP = glm::vec3(gameObject->GetComponent<Transform>()->position) + size * glm::vec3(-1, 1, -1) + centerOffset;//sss
	GetMinI(newP);
	GetMaxI(newP);

	newP = glm::vec3(gameObject->GetComponent<Transform>()->position) + size * glm::vec3(1, -1, 1) + centerOffset;//djf
	GetMinI(newP);
	GetMaxI(newP);

	newP = glm::vec3(gameObject->GetComponent<Transform>()->position) + size * glm::vec3(1, -1, -1) + centerOffset;//djs
	GetMinI(newP);
	GetMaxI(newP);

	newP = glm::vec3(gameObject->GetComponent<Transform>()->position) + size * glm::vec3(-1, -1, 1) + centerOffset;//sjf
	GetMinI(newP);
	GetMaxI(newP);

	newP = glm::vec3(gameObject->GetComponent<Transform>()->position) + size * glm::vec3(-1, -1, -1) + centerOffset;//sjs
	GetMinI(newP);
	GetMaxI(newP);
}

//Functia verifica daca exista o coliziune intre acest obiect si altul
bool Collider::IsCollision(Collider other)
{
	return (minI.x <= other.maxI.x && maxI.x >= other.minI.x) &&
		(minI.y <= other.maxI.y && maxI.y >= other.minI.y) &&
		(minI.z <= other.maxI.z && maxI.z >= other.minI.z);
}

void Collider::GetMinI(glm::vec3 newP)
{
	if (minI.x > newP.x) minI.x = newP.x;
	if (minI.y > newP.y) minI.y = newP.y;
	if (minI.z > newP.z) minI.z = newP.z;
}

void Collider::GetMaxI(glm::vec3 newP)
{
	if (maxI.x < newP.x) maxI.x = newP.x;
	if (maxI.y < newP.y) maxI.y = newP.y;
	if (maxI.z < newP.z) maxI.z = newP.z;
}