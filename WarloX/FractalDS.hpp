#pragma once

#include "Dependencies\glew\glew.h"
#include "glm\glm.hpp"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class FractalDS
{

public:

	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<GLuint> indices;

	void generateTerrain(unsigned __int32 detail)
	{
		srand(time(NULL));

		this->detail = (1<<detail) + 1;

		//Allocate Array
		vals = new float *[this->detail];
		for (int i = 0; i < this->detail; i++)
		{
			vals[i] = new float[this->detail];
			for (int j = 0; j < this->detail; j++)
			{
				 vals[i][j] = 0;
			}
		}

		//Initialize corners
		
		int size = this->detail;

		while (size > 0)
		{

			DiamondStep(size);
			SquareStep(size);

			this->h /= this->smoothness;
			size /= 2;
		}

		float pol = this->detail / 2;

		for (int i = 0; i<this->detail; i++)
			for (int j = 0; j<this->detail; j++)
			{
				double x = i - pol;
				double y = j - pol;

				float r = (float)glm::sqrt(x*x + y*y);
			
				if (r <= pol)
				{
					r =  1.0f - r / pol;
					vals[i][j] *=  r;
				}
				else vals[i][j] = 0;
			}
		fillData();
	}


	float getSize(){ return (this->detail); }
	float** getValues() { return this->vals; }

	GLuint generateVAO()
	{
		GLuint VBO;
		GLuint EBO;
		GLuint VAO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);

		glBindVertexArray(0);

		return VAO;
	}


	GLuint getIndices() { return indices.size(); }
private:

	float **vals;
	float smoothness = 2.0f;
	float h = 1.0f;



	unsigned __int32 detail;
	enum Roughness { smooth = 1, easy, medium, hard, brutal };

	
	void DiamondStep(int w)
	{

		for (int i = w; i<this->detail; i += 2 * w)
			for (int j = w; j<this->detail; j += 2 * w)
			{

				vals[i][j] = ((vals[i - w][j - w] + vals
					[i - w][j + w] + vals[i + w][j + w] + vals[i + w][j - w]) / 4.0f);
				vals[i][j] += + t_rand(h);

			}
	}

	void SquareStep(int w)
	{
	
		for (int i = 0; i<this->detail; i += w)
			for (int j = w*(1 - (i / w) % 2); j<this->detail; j += 2 * w)
			{
				int c = 0;
				float sum = 0;

				if ((i - w) >= 0) { sum += vals[i - w][j]; c++; }
				if ((j - w) >= 0) { sum += vals[i][j - w]; c++; }
				if ((i + w) < this->detail) { sum += vals[i + w][j]; c++; }
				if ((j + w) < this->detail) { sum += vals[i][j + w]; c++; }

				if (c > 0) vals[i][j] = sum / c + t_rand(h);
				else vals[i][j] = 0;

			}
	}
	
	float t_rand(float val)
	{
		return -val + (((float)(rand())/(float)RAND_MAX))*2*val;
	}

	/*Pushes the data as vertices,indices and normals*/

	void fillData()
	{
		vertices.reserve(this->detail * this->detail);
		indices.reserve((this->detail-1)*(this->detail - 1) * 6);
		normals.reserve(this->detail * this->detail);

		unsigned __int32 count = 0;

		for (int x = 0; x < this->detail; x++)
		{
			for (int z = 0; z < this->detail; z++)
			{
				vertices.push_back(glm::vec3(x,vals[x][z]*500,z));
			}
		}	
		
			int i = 0;
		
		for (; i < (this->detail)*((this->detail)-1)-1; i++)
		{
			if (!((i + 1) % this->detail)) continue;
				
			indices.push_back(i);
			indices.push_back(i+this->detail);
			indices.push_back(i+1+this->detail);

			indices.push_back(i);
			indices.push_back(i+1+this->detail);
			indices.push_back(i+1);
		}

		generateVAO();
	}


	float procedure(float x)
	{
		if (x >= 0 && x <= 1.0f) return x;
		if (x > 1) return 1;
		else return 0;
	}

};


