#pragma once

#pragma comment(lib,"lib/fmodex_vc")

#include "../inc/Globals.h"
#include <string>
#include "../inc/fmod.hpp"
#include "../inc/fmod_errors.h"

class cSound
{
public:
	cSound(void);
	~cSound(void);
	void PlaySound(char* path,bool loop);
	void PlaySound(char* path,bool loop,float vol);
	void Load3DSound(char *path);
	void Play3DSound(float vol);
	void Set3Dat(float x, float y, float z);
	void Update();
private:
	FMOD::System     *system;
	FMOD::Channel    *channel1;
	FMOD::Channel    *channel2;
	FMOD::Sound *DBonk;
};

