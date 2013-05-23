#include "../inc/cScene.h"
#include "../inc/Globals.h"

cScene::cScene(void) {
	//map = new vector<vector<int>> (3,vector<int> (SCENE_WIDTH * SCENE_DEPTH));
	//vector< vector<int> > map(3,vector<int> (SCENE_WIDTH * SCENE_DEPTH));
	//map.reserve(3*SCENE_WIDTH * SCENE_DEPTH);
	map.resize(3);
	for(int i=0;i<3;i++) map[i].resize(SCENE_WIDTH * SCENE_DEPTH);
}
cScene::~cScene(void){}

void cScene::Init()
{
	//vector< vector<int> > map(3,vector<int> (SCENE_WIDTH * SCENE_DEPTH));
	MakeCubeDL((float)TILE_SIZE,(float)TILE_SIZE,(float)TILE_SIZE,1.0f,1.0f,1.0f);
	MakeRampDL((float)TILE_SIZE,(float)TILE_SIZE,(float)TILE_SIZE,1.0f,1.0f,1.0f);
}
bool cScene::LoadLevel(int level, vector<cBicho> *caixes, cBicho &terra, int *bullseyes)
{
	FILE *fd,*fd2,*fd3;
	char file[16],file2[16],file3[16],tile;
	int i,j;

	if(level<10) { 
		sprintf(file,"%s0%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);
		sprintf(file2,"%s%d%s",(char *)FILENAME,level+10,(char *)FILENAME_EXT);
		sprintf(file3,"%s%d%s",(char *)FILENAME,level+20,(char *)FILENAME_EXT);
	}

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	//level0
	for(i=0;i<=SCENE_DEPTH-1;i++)
	{
		for(j=0;j<SCENE_WIDTH;j++)
		{
			fscanf(fd,"%c",&tile);
			if(tile==' ')
			{
				//Tiles must be != 0 !!!
				cBicho caja;
				caixes[0].push_back(caja);
				//
				map[0][(i*SCENE_WIDTH)+j]=0;
			}
			else if(tile == 6) {
				cBicho caja((float)(j*TILE_SIZE),0.0,(float)((i+1)*-TILE_SIZE),4.0,4.0,4.0);
				caixes[1].push_back(caja);
				map[0][(i*SCENE_WIDTH)+j] = tile-48;
				bullseyes[0] = j;
				bullseyes[1] = 0;
				bullseyes[2] = i+1;
			}
			else
			{
				//Tiles = 1,2,3,...
				cBicho caja((float)(j*TILE_SIZE),0.0,(float)((i+1)*-TILE_SIZE),4.0,4.0,4.0);
				caixes[0].push_back(caja);
				map[0][(i*SCENE_WIDTH)+j] = tile-48;
			}
		}
		fscanf(fd,"%c",&tile); //pass enter
	}
	fclose(fd);
	//level1
	fd2=fopen(file2,"r");
	if(fd2==NULL) return false;
	for(i=0;i<=SCENE_DEPTH-1;i++)
	{
		for(j=0;j<SCENE_WIDTH;j++)
		{
			fscanf(fd2,"%c",&tile);
			if(tile==' ')
			{
				//Tiles must be != 0 !!!
				cBicho caja;
				caixes[1].push_back(caja);
				map[1][(i*SCENE_WIDTH)+j]=0;
			}
			else if(tile == 6) {
				cBicho caja((float)(j*TILE_SIZE),(float)TILE_SIZE,(float)((i+1)*-TILE_SIZE),4.0,4.0,4.0);
				caixes[1].push_back(caja);
				map[1][(i*SCENE_WIDTH)+j] = tile-48;
			}
			else
			{
				//Tiles = 1,2,3,...
				cBicho caja((float)(j*TILE_SIZE),(float)TILE_SIZE,(float)((i+1)*-TILE_SIZE),4.0,4.0,4.0);
				caixes[1].push_back(caja);
				map[1][(i*SCENE_WIDTH)+j] = tile-48;
			}
		}
		fscanf(fd2,"%c",&tile); //pass enter
	}
	fclose(fd2);
	//level2
	fd3=fopen(file3,"r");
	if(fd3==NULL) return false;
	for(i=0;i<=SCENE_DEPTH-1;i++)
	{
		for(j=0;j<SCENE_WIDTH;j++)
		{
			fscanf(fd3,"%c",&tile);
			if(tile==' ')
			{
				//Tiles must be != 0 !!!
				cBicho caja;
				caixes[2].push_back(caja);
				map[2][(i*SCENE_WIDTH)+j]=0;
			}
			else if(tile == 6) {
				cBicho caja((float)(j*TILE_SIZE),(float)TILE_SIZE*2,(float)((i+1)*-TILE_SIZE),4.0,4.0,4.0);
				caixes[2].push_back(caja);
				map[2][(i*SCENE_WIDTH)+j] = tile-48;
			}
			else
			{
				//Tiles = 1,2,3,...
				cBicho caja((float)(j*TILE_SIZE),(float)TILE_SIZE*2,(float)((i+1)*-TILE_SIZE),4.0,4.0,4.0);
				caixes[2].push_back(caja);
				map[2][(i*SCENE_WIDTH)+j] = tile-48;
			}
		}
		fscanf(fd3,"%c",&tile); //pass enter
	}
	fclose(fd3);

	float w  = (float)SCENE_WIDTH*TILE_SIZE;
	float d  = (float)SCENE_DEPTH*TILE_SIZE;
	cBicho caja(0.0,0,-40.0,w,1,d);
	terra = caja;
	//terra(0.0,0,-40.0,w,1,d);
	//terra.S

	return true;
}
void cScene::Draw(cData *Data)
{
	int i,j,x,z;
	float w,d,tw,td;

	glEnable(GL_TEXTURE_2D);
	
	//Walls
	for(i=0;i<SCENE_DEPTH;i++)
	{
		x = 0;
		z = i*TILE_SIZE;

		for(j=0;j<SCENE_WIDTH;j++)
		{
			glPushMatrix();
				glTranslatef(x,0,-z);
				switch(map[0][(i*SCENE_WIDTH)+j])
				{
					case 0:	break;
					case 1: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL1));
							glCallList(dl_cube);
							break;
					case 2: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL2));
							glCallList(dl_cube);
							break;
					case 3: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL3));
							glCallList(dl_cube);
							break;
					case 4: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL3));
							glCallList(dl_ramp);
							break;
					case 6: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_BULL));
							glCallList(dl_cube);
							break;
				}
			glPopMatrix();
			glPushMatrix();
				glTranslatef(x,(float)TILE_SIZE,-z);
				switch(map[1][(i*SCENE_WIDTH)+j])
				{
					case 0:	break;
					case 1: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL1));
							glCallList(dl_cube);
							break;
					case 2: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL2));
							glCallList(dl_cube);
							break;
					case 3: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL3));
							glCallList(dl_cube);
							break;
					case 4: glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL3));
							glCallList(dl_ramp);
							break;
				}
			glPopMatrix();
			x += TILE_SIZE;
		}
	}

	tw = (float)SCENE_WIDTH;
	td = (float)SCENE_DEPTH;
	w  = (float)SCENE_WIDTH*TILE_SIZE;
	d  = (float)SCENE_DEPTH*TILE_SIZE;
	//Floor
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_FLOOR));
	glBegin(GL_QUADS);
		// Bottom Face
		glTexCoord2f(  tw,   td); glVertex3f(0, 0, 0);
		glTexCoord2f(0.0f,   td); glVertex3f(w, 0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0,-d);
		glTexCoord2f(  tw, 0.0f); glVertex3f(0, 0,-d);
	glEnd();
	//Roof
	/*glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_ROOF));
	glBegin(GL_QUADS);
		// Top Face
		glTexCoord2f(0.0f,   td); glVertex3f(0, TILE_SIZE, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, TILE_SIZE,-d);
		glTexCoord2f(  tw, 0.0f); glVertex3f(w, TILE_SIZE,-d);
		glTexCoord2f(  tw,   td); glVertex3f(w, TILE_SIZE, 0);
	glEnd();*/

	glDisable(GL_TEXTURE_2D);
}

void cScene::MakeCubeDL(float w,float h,float d,float tw,float th,float td)
{
	dl_cube = glGenLists(1);
	glNewList(dl_cube,GL_COMPILE);
		glBegin(GL_QUADS);
			// Front Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(w, 0,  0);
			glTexCoord2f(  tw,   th); glVertex3f(w, h,  0);
			glTexCoord2f(0.0f,   th); glVertex3f(0, h,  0);
			// Back Face
			glTexCoord2f(  tw, 0.0f); glVertex3f(0, 0, -d);
			glTexCoord2f(  tw,   th); glVertex3f(0, h, -d);
			glTexCoord2f(0.0f,   th); glVertex3f(w, h, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0, -d);
			// Right face
			glTexCoord2f(  td, 0.0f); glVertex3f(w, 0, -d);
			glTexCoord2f(  td,   th); glVertex3f(w, h, -d);
			glTexCoord2f(0.0f,   th); glVertex3f(w, h,  0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0,  0);
			// Left Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -d);
			glTexCoord2f(  td, 0.0f); glVertex3f(0, 0,  0);
			glTexCoord2f(  td,   th); glVertex3f(0, h,  0);
			glTexCoord2f(0.0f,   th); glVertex3f(0, h, -d);
			// Bottom Face
			/*glTexCoord2f(  tw,   td); glVertex3f(0, 0, -d);
			glTexCoord2f(0.0f,   td); glVertex3f(w, 0, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(0, 0,  0);*/
			// Top Face
			glTexCoord2f(0.0f,   td); glVertex3f(0, h, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, h,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(w, h,  0);
			glTexCoord2f(  tw,   td); glVertex3f(w, h, -d);
		glEnd();
	glEndList();
}

void cScene::MakeRampDL(float w,float h,float d,float tw,float th,float td)
{
	dl_ramp = glGenLists(2);
	glNewList(dl_ramp,GL_COMPILE);
		glBegin(GL_QUADS);
			// Front Face
			/*glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(w, 0,  0);
			glTexCoord2f(  tw,   th); glVertex3f(w, h,  0);
			glTexCoord2f(0.0f,   th); glVertex3f(0, h,  0);*/
			// Back Face
			glTexCoord2f(  tw, 0.0f); glVertex3f(0, 0, -d);
			glTexCoord2f(  tw,   th); glVertex3f(0, h, -d);
			glTexCoord2f(0.0f,   th); glVertex3f(w, h, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0, -d);
			// Right face
			glTexCoord2f(  td, 0.0f); glVertex3f(w, 0, -d);
			glTexCoord2f(  td,   th); glVertex3f(w, h, -d);
			glTexCoord2f(0.0f,   th); glVertex3f(w, 0,  0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0,  0);
			// Left Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -d);
			glTexCoord2f(  td, 0.0f); glVertex3f(0, 0,  0);
			glTexCoord2f(  td,   th); glVertex3f(0, 0,  0);
			glTexCoord2f(0.0f,   th); glVertex3f(0, h, -d);
			// Bottom Face
			/*glTexCoord2f(  tw,   td); glVertex3f(0, 0, -d);
			glTexCoord2f(0.0f,   td); glVertex3f(w, 0, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(w, 0,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(0, 0,  0);*/
			// Top Face
			glTexCoord2f(0.0f,   td); glVertex3f(0, h, -d);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0,  0);
			glTexCoord2f(  tw, 0.0f); glVertex3f(w, 0,  0);
			glTexCoord2f(  tw,   td); glVertex3f(w, h, -d);

		glEnd();
	glEndList();
}

void cScene::GetMap(vector<vector<int>> &mapout) {
	mapout = map;
}