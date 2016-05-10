#include "Dependencies\glew\glew.h"
#include "Dependencies\glut\freeglut.h"
#include <iostream>


	class Shader
	{
		private:
			std::string readShader(char * bytes);
			GLuint createShader(GLenum shaderType, std::string source, const char* name);
			GLuint program;

		public:
			Shader(void);
			~Shader(void);

			GLuint getProgram(void);
			GLuint createProgram(char * filenameVertex,char * filenameFragment);
	};

