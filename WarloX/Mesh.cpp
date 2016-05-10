#include "Mesh.hpp"
#include "ShaderCompilator.hpp"
#include <time.h>

class Shader_Loader
{


};

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Textures> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->setupMesh();
}


void Mesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1,&this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(GLvoid *)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex,Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex,TextCoords));

	glBindVertexArray(0);

}

void Mesh::setUpInstancedTransformations()
{


}

void Mesh::InstancedDraw(Shader shader)
{





}

void Mesh::Draw(Shader shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = this->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		glUniform1f(glGetUniformLocation(shader.getProgram(), ("material." + name + number).c_str()), i);


		glBindTexture(GL_TEXTURE_2D, this->textures[i].ID);
	}
	glActiveTexture(GL_TEXTURE0);

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}