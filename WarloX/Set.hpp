#include "Dependencies\glew\glew.h"
#include "Model.hpp"
#include <map>

using namespace std;

class Set
{
	public:


		GLuint getInstancedBuffer(string key);

	private:
		GLuint IVBO;
		map<string, Model>  key_map;


};