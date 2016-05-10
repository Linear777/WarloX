#include <iostream>



class ParticleSystem
{
protected:
	float FRAME_RATE_DROP = 0;
	float constants[256];
	const char * path;

	char * IMAGE_BYTES_ALLOC;

public:
	virtual void OnCreate() = 0;
	virtual void OnChange() = 0;
	virtual void OnTick() = 0;
	virtual void OnDraw() = 0;


	ParticleSystem();

	~ParticleSystem();

	void loadSprite(unsigned __int16 size,char * BYTES);


};
