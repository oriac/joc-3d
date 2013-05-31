#pragma once

#include "../gl/glew.h"
#include "../inc/cScene.h"
#include "../inc/cData.h"
#include "../inc/cPlayer.h"
#include "../inc/cHud.h"
//#include "../inc/cBox.h"
#include "../inc/cShoot.h"
#include "../inc/cEnemy.h"
#include "../inc/cShader.h"
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
	void NextLevel();
	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadKeyboardSpecial(unsigned char key, int x, int y, bool press);
	void ReadKeyboardRelease(unsigned char key, int x, int y, bool press);
	void ReadKeyboardSpecialRelease(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	void ReadPosMouse(int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	unsigned char keysSpecial[256];
	unsigned char keysReleased[256];
	unsigned char keysSpecialReleased[256];
	cScene Scene;
	cData Data;
	cPlayer player;
	cShoot shoot;
	cEnemy enemy;
	cHud Hud;
	cShader shader;
	cSound Sound;
	vector<cBicho> caixes[3];
	int bullseyes[3];
	cBicho terra;
	int camera;
	int actualLevel;
	float transX,transZ;
	float rot,rotV;
	bool mouseState;
	int x1,x2,y1,y2;
	vector< vector<int> > map;
	int time_init,time_end,fps;
	int fps_dibuix;
	int dir;
	int maxPosx;
	int maxPosy;
	unsigned char tipoPintado;
    double endTime;
	double startTime;
	double loopTime;
	bool goinNextLevel;
	int rebots;
	bool teclaAct;
};
