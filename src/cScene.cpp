#include "../inc/cScene.h"
#include "../inc/Globals.h"

cScene::cScene(void) {}
cScene::~cScene(void){}

void cScene::Init()
{
	MakeCubeDL((float)TILE_SIZE,(float)TILE_SIZE,(float)TILE_SIZE,1.0f,1.0f,1.0f);
	MakeRampDL((float)TILE_SIZE,(float)TILE_SIZE,(float)TILE_SIZE,1.0f,1.0f,1.0f);
}
bool cScene::LoadLevel(int level, vector<cBicho> &caixes)
{
	FILE *fd,*fd2;
	char file[16],file2[16],tile;
	int i,j;

	if(level<10) { 
		sprintf(file,"%s0%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);
		sprintf(file2,"%s%d%s",(char *)FILENAME,level+10,(char *)FILENAME_EXT);
	}

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	//for(i=SCENE_DEPTH-1;i>=0;i--)
	for(i=0;i<=SCENE_DEPTH-1;i++)
	{
		for(j=0;j<SCENE_WIDTH;j++)
		{
			fscanf(fd,"%c",&tile);
			if(tile==' ')
			{
				//Tiles must be != 0 !!!
				cBicho caja;
				caixes.push_back(caja);
				//
				map[(i*SCENE_WIDTH)+j]=0;
			}
			else
			{
				//Tiles = 1,2,3,...
				cBicho caja((float)(j*TILE_SIZE),0.0,(float)((i+1)*-TILE_SIZE),4.0,4.0,4.0);
				caixes.push_back(caja);
				map[(i*SCENE_WIDTH)+j] = tile-48;
			}
		}
		fscanf(fd,"%c",&tile); //pass enter
	}
	fclose(fd);
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
				map2[(i*SCENE_WIDTH)+j]=0;
			}
			else
			{
				//Tiles = 1,2,3,...
				cBicho caja((float)(j*TILE_SIZE),(float)TILE_SIZE,(float)((i+1)*-TILE_SIZE),4.0,4.0,4.0);
				caixes.push_back(caja);
				map2[(i*SCENE_WIDTH)+j] = tile-48;
			}
		}
		fscanf(fd2,"%c",&tile); //pass enter
	}
	fclose(fd2);

	float w  = (float)SCENE_WIDTH*TILE_SIZE;
	float d  = (float)SCENE_DEPTH*TILE_SIZE;
	cBicho caja(0.0,0,-40.0,w,1,d);
	caixes.push_back(caja);


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
				switch(map[(i*SCENE_WIDTH)+j])
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
			glPushMatrix();
				glTranslatef(x,(float)TILE_SIZE,-z);
				switch(map2[(i*SCENE_WIDTH)+j])
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

int* cScene::GetMap() {
	return map;
}