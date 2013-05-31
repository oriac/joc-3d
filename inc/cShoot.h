#pragma once
#include "../inc/cBicho.h"
#include "../inc/cScene.h"
#include "../inc/cPlayer.h"
#include "../inc/cSound.h"



class cShoot : public cBicho
{
public:
	cShoot(void);
	~cShoot(void);
	void Draw();
	void SetInitPos(int playerState,int x, int y);
	//void MoveLeft(int *map);
	//void MoveRight(int *map);
	bool IsActive();
	void SetActive(bool b);
	void SetIner(double x);
	void Setpunts(int p);
	void SetnumColisions(int c);
	int GetNumColisions();
	int GetPunts();
    double GetIner(); 
	void ShootStep(int shootState,int *map);
	void ShootCollides(int shootState, int *map);
	void CanShoot(int *map,cBicho &Player);
	void MoveShoot();
	void setRot(float rotv, float rot);
	void MoveUp(vector<cBicho> *caixes, vector< vector<int> > &map, cBicho &terra, cSound &Sound,int &rebots);
	//void Logic(cBicho &caixes);
	void Logic(cBicho &terra, vector<cBicho> *caixes, vector<vector<int>> &map);
private:
	bool active;
	float rotV;
	float rot;
	double iner;
	int numColisions;
	int punts;
};

