#pragma once

#include <vector>
#include "Dependencies\glew\glew.h"
#include <glm\glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Dependencies\assimp\scene.h"

using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextCoords;

};

struct Textures
{
	GLuint ID;
	string type;
	aiString path;

};

class Shader;

class Mesh
{
	private:
		/* Render data */
		GLuint VAO, VBO, EBO,IVBO;

		/* Functions */
		void setupMesh();
		void setUpInstancedTransformations();
	public:
		/* Mesh data */
		vector<Vertex> vertices;
		vector<GLuint> indices;
		vector<Textures> textures;

		/* Function */
		Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Textures> textures);

		void InstancedDraw(Shader shader);
		void Draw(Shader shader);
};