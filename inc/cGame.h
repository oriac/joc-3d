#pragma once

#include "../inc/cScene.h"
#include "../inc/cData.h"
#include "../inc/cPlayer.h"
#include "../inc/cHud.h"
//#include "../inc/cBox.h"
#include "../inc/cShoot.h"
#include <vector>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

using namespace std;

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	void ReadPosMouse(int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	cScene Scene;
	cData Data;
	cPlayer player;
	cShoot shoot;
	cHud Hud;
	vector<cBicho> caixes[3];
	int camera;
	float transX,transZ;
	float rot,rotV;
	bool mouseState;
	int x1,x2,y1,y2;
	int *map;
	int time_init,time_end,fps;
	int fps_dibuix;
};
