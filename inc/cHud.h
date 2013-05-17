#pragma once

#include "../inc/cTexture.h"
#include "../inc/Globals.h"
#include <string>

using namespace std;

class cHud
{
public:
	cHud(void);
	~cHud(void);
	void DrawHearts(int tex_id,int life,int d);
	void DrawPrepareToFight(int text_id,int d);
	void DrawCrossHair(int tex_id,int x,int y);

private:
	void Draw(int tex_id, float tx,float ty, int step_x,int step_y,float trans_x, float trans_y);
};



