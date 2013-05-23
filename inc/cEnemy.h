#pragma once

#include "../inc/cBicho.h"
#include <queue>
#include <vector>
#include "../inc/cData.h"
using namespace std;

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

    typedef struct {
            int x;
            int y;
			int dist;
			int nextx;
			int nexty;
    } Estado;
	typedef struct {
			int tilex;
			int tiley;
	} Point;
class cEnemy: public cBicho
{
public:
	cEnemy();
	~cEnemy();
	int GetStep();
	void Init(bool ismelee, vector <Point> pat); 
	void SetStep(int x, int y, int * map);
	void Draw(int tex_id, cData *Data);
	int NextStep(int x, int y, int*map);
	Estado Logic(int x, int y,int posx, int posy, int* map);
	void Active();
	void kill();
	bool IsAlive();
	bool IsExplote();
	int CaulculStep(int x, int y);
private:
	bool explote;
	bool alive;
	bool melee;
	int nextStep;
	int PointActual;
	vector <Point> patrulla;
};

