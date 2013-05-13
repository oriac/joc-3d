#pragma once

#include "../inc/cScene.h"
#include "../inc/cData.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

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
	int camera;
	float transX,transZ;
	float rot;
	bool mouseState;
	int x1,x2,y1,y2;
};
