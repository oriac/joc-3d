#pragma once

#include "../inc/cData.h"
#include "../inc/cBicho.h"
//#include "../inc/cBox.h"
#include <vector>

using namespace std;

#define SCENE_WIDTH		10	//#tiles
#define SCENE_DEPTH		10

#define TILE_SIZE		4	//space units

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	void Init();
	bool LoadLevel(int level, vector<cBicho> *caixes, cBicho &terra,  int *bullseyes);
	void Draw(cData *Data);
	void GetMap(vector<vector<int>> &map);

private:
	void MakeCubeDL(float w,float h,float d,float tw,float th,float td);
	void MakeRampDL(float w,float h,float d,float tw,float th,float td);
	int dl_cube;
	int dl_ramp;

	vector< vector<int> > map;		//scene
	//int map2[SCENE_WIDTH * SCENE_DEPTH];		//scene
};
