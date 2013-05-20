#pragma once

#include "../inc/cTexture.h"
//#include "../inc/cBox.h"
#include "../inc/Globals.h"
#include <vector>
#include <cmath>

using namespace std;

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_LOOKUP		4
#define STATE_LOOKDOWN		5
#define STATE_SHOOT_LEFT	6
#define STATE_SHOOT_RIGHT	7
#define STATE_DUPLEFT		8
#define STATE_DUPRIGHT		9
#define STATE_DDOWNLEFT		10
#define STATE_DDOWNRIGHT	11
#define STATE_WALKUP		12
#define STATE_WALKDOWN		13
#define STATE_EXPLOTE		14

class cRect
{
public:
	int xmin,ymin,zmin,
		xmax,ymax,zmax;
};

class cBicho
{
public:
	cBicho(void);
	cBicho(float x,float y,float z,float w,float h,float d);
	~cBicho(void);

	void SetPosition(float x, float y, float z);
	void GetPosition(float *x,float *y,float *z);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetVol(float width,float height,float depth);
	void GetVol(float *width,float *height,float *depth);

	bool Collides(cRect *rc);
	bool Collides2(cRect *rc);
	bool CollidesWall(int *map, bool right);
	bool CollidesMapWall(int *map,bool right);
	bool CollidesTopBot(int *map,bool top);
	bool CollidesMapTop(int *map);
	bool CollidesMapFloor(int *map);
	void GetArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);

	void MoveUp(vector<cBicho> caixes, int *map);
	void MoveDown();
	void StrafeRight();
	void StrafeLeft();
	void Shoot(int *map);
	void Jump(int *map);
	void Stop();

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

	void SetSpeed(int i);
	void AddRot(float x);
	void SetRot(float x);

	void DrawBB();
	
private:
	float x,y,z;
	int w,h,d;
	int state;
	float rot;

	bool jumping;
	int jump_alfa;
	int jump_y;
	int speed;
	int seq,delay;
};
