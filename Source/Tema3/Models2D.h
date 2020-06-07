#pragma once
#include <vector>
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <GL\glew.h>
#include <include\gl.h>
#include <corecrt_math_defines.h>

namespace Models2D
{
	inline Mesh* CreateRectangle(std::string name, glm::vec3 center, float length, float heigth, glm::vec3 color)
	{
		std::vector<VertexFormat> v =
		{
			VertexFormat(center, color),
			VertexFormat(center + glm::vec3(0, heigth / 2, 0), color),
			VertexFormat(center + glm::vec3(-length, heigth / 2, 0), color),
			VertexFormat(center + glm::vec3(-length, -heigth / 2, 0), color),
			VertexFormat(center + glm::vec3(0, -heigth / 2, 0), color)
		};

		std::vector<unsigned short> i = { 0, 1, 2, 3, 4 };

		Mesh* rect = new Mesh(name);
		rect->InitFromData(v, i);
		rect->SetDrawMode(GL_TRIANGLE_FAN);
		return rect;
	}
}
