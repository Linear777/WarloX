#pragma once
#include <vector>
#include "Params.hpp"
#include "Dependencies\glew\glew.h"

/*Simple Cube Generator*/
class Box
{
	private:
		Params params;

	public:
		
		/*Declaration*/
		void generateSimpleCube();
		void prepare();

		Params& getParams();
};



/*Definitions*/

Params& Box::getParams()
{
	return this->params;
}

void Box::prepare()
{
	this->params.vertices.reserve(8);
	this->params.normals.reserve(8);
	this->params.colors.reserve(8);
	this->params.indices.reserve(36);
}

void Box::generateSimpleCube()
{
	this->params.vertices.push_back(glm::vec3(-1, -1, 1));
	this->params.vertices.push_back(glm::vec3(1, -1, 1));
	this->params.vertices.push_back(glm::vec3(-1, 1, 1));
	this->params.vertices.push_back(glm::vec3(1, 1, 1));
	this->params.vertices.push_back(glm::vec3(-1, -1, -1));
	this->params.vertices.push_back(glm::vec3(1, -1, -1));
	this->params.vertices.push_back(glm::vec3(-1, 1, -1));
	this->params.vertices.push_back(glm::vec3(1, 1, -1));

	vector<GLuint> indices = 
	{
									0,1,3,
									0,3,2,

									4,5,7,
									4,7,6,

									4,0,2,
									4,2,6,

									1,7,3,
									1,5,7,

									4,0,1,
									5,4,1,

									2,7,6,
									2,7,3
	};

	this->params.indices = indices;

}