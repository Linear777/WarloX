#include "ParticleSystem.hpp"

using namespace std;

ParticleSystem::ParticleSystem()
{
	
}


ParticleSystem::~ParticleSystem()
{
	free(this->IMAGE_BYTES_ALLOC);
}


void ParticleSystem::loadSprite(unsigned __int16 size,char * BYTES)
{
	this->IMAGE_BYTES_ALLOC = (char*)malloc(size*sizeof(char));
	int i = 0;

	while ((IMAGE_BYTES_ALLOC[i] = BYTES[i++]) != '\0');
	
	cout << IMAGE_BYTES_ALLOC << endl;
}