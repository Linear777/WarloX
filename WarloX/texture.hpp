#pragma once

#include <iostream>
#include "Dependencies\SOIL\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Error.hpp"
using namespace std;

class Texture
{
public:
	Texture(GLenum TextureTarget, const std::string& FileName)
	{
		m_textureTarget = TextureTarget;
		m_fileName = FileName;
	}

	GLuint getTexture()
	{
		return m_textureObject;
	}
	bool Load()
	{
	
		unsigned char * image = SOIL_load_image(m_fileName.c_str(),&width,&height,&channels,SOIL_LOAD_RGBA);
		
		glGenTextures(1, &m_textureObject);
		glBindTexture(m_textureTarget, m_textureObject);
		glTexImage2D(m_textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(m_textureTarget, 0);


		Error::Message(1, "Texture Loaded");
		Error::Message(1, m_fileName.c_str());
		return true;
	}

	void Bind(GLenum TextureUnit)
	{
		glActiveTexture(TextureUnit);
		glBindTexture(m_textureTarget, m_textureObject);
	}
private:
	GLuint m_textureObject;
	GLuint m_textureTarget;
	string m_fileName;

	int width;
	int height;
	int channels;

};