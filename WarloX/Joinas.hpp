#pragma once
#include <vector>
#include "wogsiw_math.hpp"
#include "Mesh.hpp"

/*
Author: Matus Cicman
Date: 9/22/2015
Corp: Ignia Corporation 

	Stack Data types which will store our transformation matrixes for instance rendering
	(we can use it for any object and and mesh)


	runnin
*/

using namespace std;

struct Joinas
{
private:
	vector<Matrix4f> transforms;
	vector<Vector3f> positions;
	Mesh &mesh;

public:

	Joinas(Mesh& mesh, uint reserve, vector<Vector3f> positions) : mesh(mesh)
	{
		this->positions = positions;
		transforms.reserve(reserve);

		MakeTransMatrixes();
	}

	void MakeTransMatrixes()
	{
		for (int i = 0; i < transforms.size(); i++)
		{
			Vector3f p = positions[i];
			transforms[i].InitTranslationTransform(p.x,p.y,p.z);
		}
	}
	
	//Call Instanced Draw
};