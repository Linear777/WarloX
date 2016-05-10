#pragma once
#include "Dependencies\glew\glew.h"
#include <vector>
#include "Mesh.hpp"
#include "Dependencies\assimp\Importer.hpp"
#include "Dependencies\assimp\postprocess.h"
#include "Dependencies\assimp\scene.h"

class Shader;

class Model
{
public:
	Model(GLchar * path)
	{
		this->loadModel(path);
	}

	void Draw(Shader shader);
	void Draw(Shader shader,GLuint instancedVBO);
private:

	string directory;

	vector<Mesh> meshes;
	vector<Textures> textures_loaded;	//Save IDS of loaded textures

	void loadModel(string path);
	void processNode(aiNode * node, const aiScene * scene);

	Mesh processMesh(aiMesh * mesh, const aiScene * scene);
	vector<Textures> loadMaterialTextures(aiMaterial * mat,aiTextureType  type,string typeName);


	GLuint TextureFromFile(const char* path, string directory);
};