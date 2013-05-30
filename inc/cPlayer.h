#pragma once

#include "../inc/cBicho.h"
#include "../inc/cScene.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(cData *Data);
	int GetHp();
	void WinHp();
	void LoseHp();
	bool isAlive();
	void AddPoints(int punts);
	void Dead();
	void Respawn();
	bool IsExplote();
	string GetPoints();
	void Logic(cBicho &terra, vector<cBicho> *caixes, vector<vector<int>> &map);

private:
	bool explote;
	int hp;
	bool alive;
	int points;
	int rotV;
};
