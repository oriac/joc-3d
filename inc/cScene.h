#pragma once

#include "../inc/cData.h"

#define SCENE_WIDTH		8	//#tiles
#define SCENE_DEPTH		8

#define TILE_SIZE		4	//space units

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	void Init();
	bool LoadLevel(int level);
	void Draw(cData *Data);
	int *GetMap();

private:
	void MakeCubeDL(float w,float h,float d,float tw,float th,float td);
	int dl_cube;

	int map[SCENE_WIDTH * SCENE_DEPTH];		//scene
};
