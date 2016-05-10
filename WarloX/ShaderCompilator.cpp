#include "Dependencies\glew\glew.h"
#include "ShaderCompilator.hpp"
#include <fstream>
#include <vector>




Shader::Shader()
{



}

Shader::~Shader()
{

	

}

GLuint Shader::getProgram()
{
	return this->program;
}

std::string Shader::readShader(char * filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good())
	{
		std::cout << "Couldn't find file or invalid format";
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned __int16)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	return shaderCode;
}

GLuint Shader::createShader(GLenum shaderType, std::string source,const char * name)
{
	GLuint shader = glCreateShader(shaderType);

	int compile_status = 0;
	const char * shader_code_pointer = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader,1,&shader_code_pointer,&shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (compile_status == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_info(info_log_length);
		glGetShaderInfoLog(shader,info_log_length,NULL,&shader_info[0]);
		std::cout << "Shader_Loader Error " << &shader_info[0] << std::endl;

		return 0;
	}

	return shader;
}


GLuint Shader::createProgram(char * Fdestination,char * Fdestination2)
{
	GLint link_status = 0;

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, readShader(Fdestination),"Vertex_Shader");
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, readShader(Fdestination2), "Fragment_Shader");
	this->program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);

	if (link_status == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_info(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &shader_info[0]);
		std::cout << "Program_link Error : " << &shader_info[0] << std::endl; 

		return 0;
	}
	return this->program;
}