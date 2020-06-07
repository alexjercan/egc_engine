#include "MeshRenderer.h"
#include <stb\stb_image.h>

GameObject* MeshRenderer::mainCamera;
GameObject* MeshRenderer::light0;
GameObject* MeshRenderer::light1;

MeshRenderer::MeshRenderer()
{
	mesh = NULL;
	shader = NULL;
}

MeshRenderer::MeshRenderer(Mesh* mesh, Shader* shader, std::vector<char*> shaderAttName, 
	std::vector<int> shaderAttType, std::vector<float> shaderAttValue)
{
	this->mesh = mesh;
	this->shader = shader;
	this->shaderAttName = shaderAttName;
	this->shaderAttType = shaderAttType;
	this->shaderAttValue = shaderAttValue;
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Start()
{

}

void MeshRenderer::Update(float deltaTimeSeconds)
{
	RenderSimpleMesh(mesh, shader, shaderAttName, 
		shaderAttType, shaderAttValue, GameObject::GetModelMatrix(gameObject));
}

void  MeshRenderer::RenderSimpleMesh(Mesh* mesh, Shader* shader, std::vector<char*> shaderAttName,
	std::vector<int> shaderAttType, std::vector<float> shaderAttValue, const glm::mat4& modelMatrix)
{
	int location;
	if (!mesh) printf("MeshRenderer: no mesh!\n");
	if (!shader) printf("MeshRenderer: no shader!\n");
	if (!mainCamera)printf("MeshRenderer: no main camera!\n");

	CameraComponent* c = MeshRenderer::mainCamera->GetComponent<CameraComponent>();
	if (!c)printf("MeshRenderer: no CameraComponent!\n");

	if (!mesh || !shader || !mainCamera || !c) return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	location = glGetUniformLocation(shader->GetProgramID(), "Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	location = glGetUniformLocation(shader->GetProgramID(), "View");
	glm::mat4 viewMatrix = c->camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	location = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glm::mat4 projectionMatrix = c->camera->GetProjectionMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	for (int i = 0; i < shaderAttName.size(); i++)
	{
		location = glGetUniformLocation(shader->GetProgramID(), shaderAttName.at(i));
		if (location > -1)
		{
			if (shaderAttType.at(i) == FLOAT)
			{
				glUniform1f(location, shaderAttValue.at(i));
			}
			else if (shaderAttType.at(i) == TEXTURE)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, (int)shaderAttValue.at(i));
				glUniform1i(location, 0);
			}
			else if (shaderAttType.at(i) == INT)
			{
				glUniform1i(location, (int)shaderAttValue.at(i));
			}
			else if (shaderAttType.at(i) == TIME)
			{
				glUniform1f(location, Engine::GetElapsedTime());
			}
			else if (shaderAttType.at(i) == HEIGHTMAP)
			{			
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, (int)shaderAttValue.at(i));
				glUniform1i(location, 1);
			}
			else if (shaderAttType.at(i) == LIGHT_POSITION0)
			{
				Transform* t = MeshRenderer::light0->GetComponent<Transform>();
				glUniform3f(location, t->position.x, t->position.y, t->position.z);
			}
			else if (shaderAttType.at(i) == LIGHT_DIRECTION0)
			{
				SpotLight* s = MeshRenderer::light0->GetComponent<SpotLight>();
				glUniform3f(location, s->light_direction.x, s->light_direction.y, s->light_direction.z);
			}
			else if (shaderAttType.at(i) == CUTOFF_ANGLE)
			{
				SpotLight* s = MeshRenderer::light0->GetComponent<SpotLight>();
				glUniform1f(location, s->cutoff);
			}
			else if (shaderAttType.at(i) == LIGHT_POSITION1)
			{
				Transform* t = MeshRenderer::light1->GetComponent<Transform>();
				glUniform3f(location, t->position.x, t->position.y, t->position.z);
			}
			else if (shaderAttType.at(i) == LIGHT_DIRECTION1)
			{
				SpotLight* s = MeshRenderer::light1->GetComponent<SpotLight>();
				glUniform3f(location, s->light_direction.x, s->light_direction.y, s->light_direction.z);
			}
			else if (shaderAttType.at(i) == EYE_POSITION)
			{
				Transform* t = MeshRenderer::mainCamera->GetComponent<Transform>();
				glUniform3f(location, t->position.x, t->position.y, t->position.z);
			}
		}
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}