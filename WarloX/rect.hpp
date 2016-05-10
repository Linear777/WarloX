#pragma once
#include "Dependencies\glew\glew.h"
#include "Mesh.hpp"


const float normals_based[] =
{
	1.0f, 1.f, 1.f
};

const float textures[] =
{
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f
};

const float coordinates_based_standard[] =	/* Usable for terrain ground */
{
	-1.f,0.f,-1.f,
	-1.f,0.f,1.f,
	1.f,0.f,1.f,
	1.f,0.f,-1.f
};

const float coordinats_based_standard_perp[] =   /* Usable for grass or perpendicular boards*/
{

	-1.f,1.f,0.f,
	-1.f,-1.f,0.f,
	1.f,-1.f,0.f,
	1.f,1.f,0.f

};

const unsigned int indices [] = {0,1,3,3,1,2};


class Rect
{

private:
	
	enum DataStructures : int
	{
		VERTICES,
		NORMALS,
		INDICES,
		TEXTURES,
		INSTANCED

	};

	GLuint datas[5];
	GLuint VAO;


	/*Instanced Datas*/


	vector<GLfloat[3]> positions;

public:
	Rect()
	{


	}
	~Rect()
	{
	
	}


	GLuint setup()
	{
		glGenVertexArrays(1,&VAO);
		glGenBuffers(5,datas);
		
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, datas[VERTICES]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, coordinats_based_standard_perp, GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);


		glBindBuffer(GL_ARRAY_BUFFER, datas[NORMALS]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3, normals_based, GL_STATIC_DRAW);
		glEnableVertexAttribArray(NORMALS);
		glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, datas[TEXTURES]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, textures, GL_STATIC_DRAW);
		glEnableVertexAttribArray(TEXTURES);
		glVertexAttribPointer(TEXTURES, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, datas[INSTANCED]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * positions.size(), &positions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(INSTANCED);
		glVertexAttribPointer(INSTANCED, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
		glVertexAttribDivisor(INSTANCED,1);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, datas[INDICES]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices, GL_STATIC_DRAW);


		
	




	}

};