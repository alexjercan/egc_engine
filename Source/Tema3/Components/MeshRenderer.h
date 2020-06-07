#pragma once
#include "Component.h"
#include "GameObject.h"
#include "SpotLight.h"
#include "CameraComponent.h"

#include <Core\Engine.h>
#include <Core\GPU\Mesh.h>
#include <Core\GPU\Shader.h>
#include <Engine\Component\Camera\Camera.h>

#define INT 0
#define TEXTURE 1
#define FLOAT 2
#define TIME 3
#define HEIGHTMAP 4
#define LIGHT_POSITION0 5
#define LIGHT_DIRECTION0 6
#define LIGHT_POSITION1 7
#define LIGHT_DIRECTION1 8
#define CUTOFF_ANGLE 9
#define EYE_POSITION 10

//Componenta care contine o mesha, un shader si un set de caracteristici pentru shader
class MeshRenderer : public Component {
public:
	MeshRenderer();
	MeshRenderer(Mesh* mesh, Shader* shader, std::vector<char*> shaderAttName, 
		std::vector<int> shaderAttType, std::vector<float> shaderAttValue);
	~MeshRenderer();

	void Start() override;
	void Update(float deltaTimeSeconds) override;
	Component* Clone() const { return new MeshRenderer(*this); }

	static GameObject* mainCamera;
	static GameObject* light0;
	static GameObject* light1;

	Mesh* mesh;
	Shader* shader;
	std::vector<char*> shaderAttName;
	std::vector<int> shaderAttType;
	std::vector<float> shaderAttValue;

private:
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, std::vector<char*> shaderAttName, 
		std::vector<int> shaderAttType, std::vector<float> shaderAttValue, const glm::mat4& modelMatrix);

};
