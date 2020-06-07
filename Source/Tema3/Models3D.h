#pragma once

#include <vector>
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <GL\glew.h>
#include <include\gl.h>
#include <corecrt_math_defines.h>

namespace Models3D
{
	inline Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
	{
		unsigned int VAO = 0;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		unsigned int IBO;
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

		// ========================================================================
		// This section describes how the GPU Shader Vertex Shader program receives data

		// set vertex position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

		// set vertex normal attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

		// set texture coordinate attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

		// set vertex color attribute
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
		// ========================================================================

		// Unbind the VAO
		glBindVertexArray(0);

		// Check for OpenGL errors
		CheckOpenGLError();

		// Mesh information is saved into a Mesh object
		Mesh* mesh = new Mesh(name);
		mesh->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
		mesh->vertices = vertices;
		mesh->indices = indices;
		return mesh;
	}

	inline Mesh* CreateSimpleCube(const char* name)
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1), glm::vec3(0.1, 0.5, 0.8)),
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		return CreateMesh(name, vertices, indices);
	}

	inline Mesh* CreateTrunk(const char* name)
	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -0.5,  0.5), glm::vec3(1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(-1,  0.5,  0.5), glm::vec3(1), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-1, -0.5, -0.5), glm::vec3(1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(-1,  0.5, -0.5), glm::vec3(1), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(1), glm::vec3(0.1, 0.5, 0.8)),
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		return CreateMesh(name, vertices, indices);
	}

	inline Mesh* CreateCylinder(const char* name, int m_slices, int m_rings, float m_length, float m_radius)
	{
		std::vector<VertexFormat> vertices;
		std::vector<unsigned short> indices;

		int faces = m_slices * m_rings;        
		int nVerts = (m_slices + 1) * m_rings  
			+ 2 * (m_slices + 1);       

		float dTheta = 2 * M_PI / static_cast<float>(m_slices);
		float dy = m_length / static_cast<float>(m_rings - 1);

		int index = 0;

		for (int ring = 0; ring < m_rings; ++ring)
		{
			const float y = -m_length / 2.0f + static_cast<float>(ring) * dy;
			for (int slice = 0; slice < m_slices + 1; ++slice)
			{
				const float theta = static_cast<float>(slice) * dTheta;
				const float cosTheta = cosf(theta);
				const float sinTheta = sinf(theta);

				vertices.push_back(
					VertexFormat(glm::vec3(m_radius * cosTheta, y, m_radius * sinTheta), glm::vec3(1), glm::vec3(cosTheta, 0, sinTheta)));
				index++;
			}
		}

		for (int i = 0; i < m_rings - 1; ++i)
		{
			const int ringStartIndex = i * (m_slices + 1);
			const int nextRingStartIndex = (i + 1) * (m_slices + 1);

			for (int j = 0; j < m_slices; ++j)
			{
				indices.push_back(ringStartIndex + j);
				indices.push_back(ringStartIndex + j + 1);
				indices.push_back(nextRingStartIndex + j);
				indices.push_back(nextRingStartIndex + j);
				indices.push_back(ringStartIndex + j + 1);
				indices.push_back(nextRingStartIndex + j + 1);
			}
		}

		//=================================================

		vertices.push_back(
			VertexFormat(glm::vec3(0, m_length / 2.0f, 0), glm::vec3(1), glm::vec3(0, 1, 0)));

		dTheta = 2 * M_PI / static_cast<float>(m_slices);
		for (int slice = 0; slice < m_slices; ++slice)
		{
			const float theta = static_cast<float>(slice) * dTheta;
			const float cosTheta = cosf(theta);
			const float sinTheta = sinf(theta);

			vertices.push_back(
				VertexFormat(glm::vec3(m_radius * cosTheta, m_length / 2.0f, m_radius * sinTheta), glm::vec3(1), glm::vec3(0, 1, 0)));
		}

		for (int i = 0; i < m_slices; ++i)
		{
			if (i != m_slices - 1)
			{
				indices.push_back(index);
				indices.push_back(index + i + 1);
				indices.push_back(index + i + 2);
			}
			else
			{
				indices.push_back(index);
				indices.push_back(index + i + 1);
				indices.push_back(index + 1);
			}
		}

		//=================================================

		vertices.push_back(
			VertexFormat(glm::vec3(0, -m_length / 2.0f, 0), glm::vec3(1), glm::vec3(0, -1, 0)));

		dTheta = 2 * M_PI / static_cast<float>(m_slices);
		for (int slice = 0; slice < m_slices; ++slice)
		{
			const float theta = static_cast<float>(slice) * dTheta;
			const float cosTheta = cosf(theta);
			const float sinTheta = sinf(theta);

			vertices.push_back(
				VertexFormat(glm::vec3(m_radius * cosTheta, -m_length / 2.0f, m_radius * sinTheta), glm::vec3(1), glm::vec3(0, -1, 0)));
		}

		for (int i = 0; i < m_slices; ++i)
		{
			if (i != m_slices - 1)
			{
				indices.push_back(index);
				indices.push_back(index + i + 1);
				indices.push_back(index + i + 2);
			}
			else
			{
				indices.push_back(index);
				indices.push_back(index + i + 1);
				indices.push_back(index + 1);
			}
		}

		return CreateMesh(name, vertices, indices);
	}

	inline Mesh* CreateCylinder(const char* name, int m_slices, int m_rings, float m_length, float m_radius, float bumpiness)
	{
		std::vector<VertexFormat> vertices;
		std::vector<unsigned short> indices;

		int faces = m_slices * m_rings;
		int nVerts = (m_slices + 1) * m_rings
			+ 2 * (m_slices + 1);

		float dTheta = 2 * M_PI / static_cast<float>(m_slices);
		float dy = m_length / static_cast<float>(m_rings - 1);

		int index = 0;
		float aux = 0;

		for (int ring = 0; ring < m_rings; ++ring)
		{
			const float y = -m_length / 2.0f + static_cast<float>(ring) * dy;
			for (int slice = 0; slice < m_slices + 1; ++slice)
			{
				const float theta = static_cast<float>(slice) * dTheta;
				const float cosTheta = cosf(theta);
				const float sinTheta = sinf(theta);

				float factor = ((rand() % 10 - 5) * bumpiness / 5);
				if (slice == 0) factor = 0;
				if (slice == m_slices) factor = 0;
				if (ring == 0) factor = 0;
				if (ring == m_rings - 1) factor = 0;

				vertices.push_back(
					VertexFormat(glm::vec3((factor + m_radius) * cosTheta, y, (factor + m_radius) * sinTheta  ), glm::vec3(1), glm::vec3(cosTheta, 0, sinTheta)));
				index++;
			}
		}

		for (int i = 0; i < m_rings - 1; ++i)
		{
			const int ringStartIndex = i * (m_slices + 1);
			const int nextRingStartIndex = (i + 1) * (m_slices + 1);

			for (int j = 0; j < m_slices; ++j)
			{
				indices.push_back(ringStartIndex + j);
				indices.push_back(ringStartIndex + j + 1);
				indices.push_back(nextRingStartIndex + j);
				indices.push_back(nextRingStartIndex + j);
				indices.push_back(ringStartIndex + j + 1);
				indices.push_back(nextRingStartIndex + j + 1);
			}
		}

		//=================================================

		vertices.push_back(
			VertexFormat(glm::vec3(0, m_length / 2.0f, 0), glm::vec3(1), glm::vec3(0, 1, 0)));

		dTheta = 2 * M_PI / static_cast<float>(m_slices);
		for (int slice = 0; slice < m_slices; ++slice)
		{
			const float theta = static_cast<float>(slice) * dTheta;
			const float cosTheta = cosf(theta);
			const float sinTheta = sinf(theta);

			vertices.push_back(
				VertexFormat(glm::vec3(m_radius * cosTheta, m_length / 2.0f, m_radius * sinTheta), glm::vec3(1), glm::vec3(0, 1, 0)));
		}

		for (int i = 0; i < m_slices; ++i)
		{
			if (i != m_slices - 1)
			{
				indices.push_back(index);
				indices.push_back(index + i + 1);
				indices.push_back(index + i + 2);
			}
			else
			{
				indices.push_back(index);
				indices.push_back(index + i + 1);
				indices.push_back(index + 1);
			}
		}

		//=================================================

		vertices.push_back(
			VertexFormat(glm::vec3(0, -m_length / 2.0f, 0), glm::vec3(1), glm::vec3(0, -1, 0)));

		dTheta = 2 * M_PI / static_cast<float>(m_slices);
		for (int slice = 0; slice < m_slices; ++slice)
		{
			const float theta = static_cast<float>(slice) * dTheta;
			const float cosTheta = cosf(theta);
			const float sinTheta = sinf(theta);

			vertices.push_back(
				VertexFormat(glm::vec3(m_radius * cosTheta, -m_length / 2.0f, m_radius * sinTheta), glm::vec3(1), glm::vec3(0, -1, 0)));
		}

		for (int i = 0; i < m_slices; ++i)
		{
			if (i != m_slices - 1)
			{
				indices.push_back(index);
				indices.push_back(index + i + 1);
				indices.push_back(index + i + 2);
			}
			else
			{
				indices.push_back(index);
				indices.push_back(index + i + 1);
				indices.push_back(index + 1);
			}
		}

		return CreateMesh(name, vertices, indices);
	}

	inline Mesh* CreateSphere(const char* name, int m_stacks, int m_sectors, float m_radius)
	{
		//m_stacks numarul de fete longitudinal
		//m_sectors numarul de fete latitudinal
		std::vector<VertexFormat> vertices;
		std::vector<unsigned short> indices;

		float sectorStep = 2 * M_PI / m_sectors;
		float stackStep = M_PI / m_stacks;
		float sectorAngle, stackAngle;

		//stackAngle = u va fi de la pi/2 la -pi/2
		//sectorAngle = v va fi de la 0 la 2pi
		//x este r * cos(u) * cos(v) = xy * cos(v)
		//y este r * cos(u) * sin(v) = xy * sin(v)
		//z este r * sin(u)
		//xy este r * cos(u)

		float x, y, z;	//coordonatele parametrice
		float xy;		//componenta xy a punctului

		for (int i = 0; i < m_stacks; i++)
		{
			stackAngle = (float)M_PI / 2 - i * stackStep;	// de la pi/2 la -pi/2
			xy = m_radius * cosf(stackAngle);				// r * cos(u)
			z = m_radius * sinf(stackAngle);				// r * sin(u)

			for (int j = 0; j <= m_sectors; j++)
			{
				sectorAngle = j * sectorStep;				//de la 0 la 2pi

				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

				vertices.push_back(
					VertexFormat(glm::vec3(x, y, z), glm::vec3(1), glm::vec3(x, y, z) / m_radius));
			}

			//fiecare fata are nevoie de 2 triunghiuri
			//k1 este primul vertex din fata si k2 al doilea (longitudinal)
			//atunci ordinea triunghiurilor este k1->k2->k1+1, si k1+1->k2->k2+1
			int k1, k2;
			for (int i = 0; i < m_stacks; i++)
			{
				k1 = i * (m_sectors + 1);
				k2 = k1 + m_sectors + 1;

				for (int j = 0; j < m_sectors; j++, k1++, k2++)
				{
					if (i != 0)
					{
						indices.push_back(k1);
						indices.push_back(k2);
						indices.push_back(k1 + 1);
					}
					if (i != (m_stacks - 1))
					{
						indices.push_back(k1 + 1);
						indices.push_back(k2);
						indices.push_back(k2 + 1);
					}
				}
			}
		}

		return CreateMesh(name, vertices, indices);
	}

	inline Mesh* CreatePlane(const char* name, int m_lines, int m_columns)
	{
		std::vector<VertexFormat> vertices;
		std::vector<unsigned short> indices;

		for (int i = 0; i < m_lines; i++)
		{
			for (int j = 0; j < m_columns; j++)
			{
				float x = i / (float)m_lines;
				float y = j / (float)m_columns;
				vertices.push_back(VertexFormat(glm::vec3(x, 0, y), glm::vec3(1), glm::vec3(0, 1, 0), glm::vec2(x, y)));
			}
		}

		for (int i = 0; i < m_lines - 1; i++)
		{
			for (int j = 0; j < m_columns - 1; j++)
			{
				indices.push_back(i * m_lines + j + m_columns);
				indices.push_back(i * m_lines + j);
				indices.push_back(i * m_lines + j + m_columns + 1);
				indices.push_back(i * m_lines + j);
				indices.push_back(i * m_lines + j + 1);
				indices.push_back(i * m_lines + j + m_columns + 1);
			}
		}
		
		return CreateMesh(name, vertices, indices);
	}
}
