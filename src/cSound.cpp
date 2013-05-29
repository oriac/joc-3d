#include "../inc/cSound.h"



cSound::cSound(void)
{
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
}


cSound::~cSound(void)
{
}

void cSound::PlaySound(char *path,bool loop){
	FMOD::Sound *s;
	if(loop) {
		channel1->stop();
		system->createStream(path, 
					  FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &s);
		system->playSound(FMOD_CHANNEL_FREE, s, false, &channel1);
	}
	else {
		system->createSound(path, FMOD_SOFTWARE, 0, 
						&s);
		system->playSound(FMOD_CHANNEL_FREE, s, false,&channel2 );
	}
}

void cSound::PlaySound(char *path,bool loop,float vol) {
	FMOD::Sound *s;
	if(loop) {
		channel1->stop();
		system->createStream(path, 
					  FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &s);
		system->playSound(FMOD_CHANNEL_FREE, s, false, &channel1);
	}
	else {
		system->createSound(path, FMOD_SOFTWARE, 0, 
						&s);
		system->playSound(FMOD_CHANNEL_FREE, s, false,&channel2 );
		channel2->setVolume(vol);
	}
}

void cSound::Load3DSound(char *path) {
	system->createSound(path, FMOD_3D, 0, &DBonk);
	DBonk->set3DMinMaxDistance(0.5f * 1.0f, 5000.0f * 1.0f);
	DBonk->setMode(FMOD_LOOP_OFF);
}

void cSound::Play3DSound(float vol) {
	    FMOD_VECTOR pos = { -10.0f * 1.0f, 0.0f, 0.0f };
        FMOD_VECTOR vel = {  0.0f, 0.0f, 0.0f };
			FMOD_VECTOR forward        = { 0.0f, 0.0f, 1.0f };
    FMOD_VECTOR up             = { 0.0f, 1.0f, 0.0f };
		channel2->setVolume(vol);
		//set3DListenerAttributes(0,0,0,0,0);
		system->set3DListenerAttributes(0,&pos,NULL,&forward, &up);
        system->playSound(FMOD_CHANNEL_FREE, DBonk, false, &channel2);
}

void cSound::Set3Dat(float x, float y, float z) {
	FMOD_VECTOR pos = {x, y, z};
	FMOD_VECTOR lastpos        = { 0.0f, 0.0f, 0.0f };

	channel2->set3DAttributes(&lastpos,NULL);
	
}



void cSound::Update() {
	system->update();
}