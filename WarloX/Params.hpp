#include <vector>
#include <glm\glm.hpp>

using namespace std;
struct Params
{
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec4> colors;
	vector<glm::vec2> textcoords;
	vector<GLuint> indices;
};