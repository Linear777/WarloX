#pragma once
#include "Dependencies\glew\glew.h"
#include "texture.hpp"

class RectangleGround
{
private:
		unsigned int W;
		unsigned int H;

	  
public:
	GLuint VAO;

	RectangleGround(unsigned int W, unsigned int H) : W(W), H(H)
	{

	}

	void SetUP(uint mode)
	{
		float vertical_coords[12] =
		{
			-1.f, 1.f, 0.f,
			-1.f, 0.f, 0.f,
			1.f,  0.f,  0.f,
			1.f,  1.f,  0.f

		};

		float horizontal_coords[12] =
		{
			-1.f, 0.f, -1.f,
			-1.f, 0.f, 1.f,
			1.f, 0.f, 1.f,
			1.f,0.f,-1.f
			
		};

		float textureCoords[12] =
		{
			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
			0.f,1.f

		};


		

		float *vertices;

		mode ? vertices = horizontal_coords : vertices = vertical_coords;

		unsigned int indices[] = { 0, 1, 3, 3, 1, 2 };
		for (int i = 0; i < 12; i++){ vertices[i] *= 300.f; if (i<12) textureCoords[i] *= 5.f; }

		GLuint VBO;
		GLuint TBO;
		GLuint EBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &TBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, TBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, &textureCoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid*)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*6,&indices[0],GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
	

	GLuint getTexture(const string& path)
	{
		Texture texture(GL_TEXTURE_2D,path.c_str());
		texture.Load();

		
		return texture.getTexture();
	}

};