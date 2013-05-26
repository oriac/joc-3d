#include "../inc/cBicho.h"
#include "../inc/cScene.h"
#include "../inc/Globals.h"

cBicho::cBicho(void)
{
	seq=0;
	delay=0;
	x = y = z = 0;
	jumping = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(float posx,float posy,float posz,float width,float height,float depth)
{
	x = posx;
	y = posy;
	z = posz;
	w = width;
	h = height;
	d = depth;
}
void cBicho::SetPosition(float posx,float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}
void cBicho::GetPosition(float *posx,float *posy,float *posz)
{
	*posx = x;
	*posy = y;
	*posz = z;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = floor(x / TILE_SIZE);
	*ty = floor(abs(z / TILE_SIZE));
}
void cBicho::SetVol(float width,float height,float depth)
{
	w = width;
	h = height;
	d = depth;
}
void cBicho::GetVol(float *width,float *height,float *depth)
{
	*width = w;
	*height = h;
	*depth = d;
}
bool cBicho::Collides(cRect *rc)
{
	//return ((x>rc->left) && (x+w<rc->right) && (y>rc->bottom) && (y+h<rc->top));
	//return ((x<rc->xmax) && (x+w>rc->xmin) && (y<rc->ymax) && (y+h>rc->ymin) && (z<rc->zmax) && (z+d>rc->zmin));
	return ((x<rc->xmax) && (rc->xmin<x+w) && (y<rc->ymax) && (rc->ymin<y+h) && (z<rc->zmax) && (rc->zmin<z+d));
		//&& (y>rc->ymin) && (y+h<rc->ymax) && (z>rc->zmin) && (z+d<rc->zmax));
	//return false;
}

bool cBicho::Collides2(cRect *rc)
{
	//return ((x<rc->right) && (rc->left<x+w) && (y<rc->top) && (rc->bottom<y+h));
	return false;
}
bool cBicho::CollidesWall(int* map, bool right) 
{
	/*int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		if(right) {

			xaux = x;
			x += STEP_LENGTH*speed;

			if(CollidesMapWall(map,true))
			{
				x = xaux;
				//state = STATE_LOOKRIGHT;
				return true;
			}
			x = xaux;
		}
		else {
			xaux = x;
			x -= STEP_LENGTH*speed;

			if(CollidesMapWall(map,false))
			{
				x = xaux;
				//state = STATE_LOOKLEFT;
				return true;
			}
			x = xaux;
		}
	}
	//Advance, no problem*/
	return false;
}
bool cBicho::CollidesTopBot(int *map, bool top) {
	/*int yaux;
	
	//Whats next tile?
	if( (y % TILE_SIZE) == 0)
	{
		if(top) {

			yaux = y;
			y += STEP_LENGTH*speed;

			if(CollidesMapTop(map))
			{
				y = yaux;
				//state = STATE_LOOKUP;
				return true;
			}
			y = yaux;
		}
		else {
			yaux = y;
			y -= STEP_LENGTH*speed;

			if(CollidesMapFloor(map))
			{
				y = yaux;
				//state = STATE_LOOKDOWN;
				return true;
			}
			y = yaux;
		}
	}
	//Advance, no problem*/
	return false;
}

bool cBicho::CollidesMapWall(int *map,bool right)
{
	/*int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if(right)	tile_x += width_tiles;
	if( (y % TILE_SIZE) != 0)height_tiles++;
	
	for(j=0;j<height_tiles;j++)
	{
		if(map[ tile_x + ((tile_y+j)*SCENE_WIDTH) ] != 0)	return true;
	}
	*/
	return false;
}



bool cBicho::CollidesMapTop(int *map) {
	/*int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	tile_y += height_tiles;
	if( (x % TILE_SIZE) != 0) width_tiles++;
	for(j=0;j<width_tiles;j++)
	{
		if(map[ tile_x+j + ((tile_y)*SCENE_WIDTH) ] != 0)	return true;
	}
	*/
	return false;
}


bool cBicho::CollidesMapFloor(int *map) {
	/*int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if( (x % TILE_SIZE) != 0) width_tiles++;
	for(j=0;j<width_tiles;j++)
	{
		if(map[ tile_x+j + ((tile_y)*SCENE_WIDTH) ] != 0)	return true;
	}
	*/
	return false;
}

void cBicho::GetArea(cRect *rc)
{
	/*rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;*/
	rc->xmin = x;
	rc->ymin = y;
	rc->zmin = z;
	rc->xmax = x+w;
	rc->ymax = y+h;
	rc->zmax = z+d;
}
void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	/*int screen_x,screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);*/
}
void cBicho::MoveUp(vector<cBicho> *caixes, vector<vector<int>> map)
{
	
		float xaux, zaux;
		xaux=x;
		zaux=z;
		int tx,ty;
		int suelo;
		suelo = ((int)floor(y+0.05))/4;
		GetTile(&tx,&ty);
		x-=0.1*sin(rot*PI/180);
		z-=0.1*cos(rot*PI/180);
		cRect rect;

		for(int i=-1;i<=1;++i) {
			for(int j=-1;j<=1;++j) {
				//if(!(i==0 && j==0)) {
				if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
					caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
					if(Collides(&rect)) {
						z = zaux;
						for(int i=-1;i<=1;++i) {
							for(int j=-1;j<=1;++j) {
								caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
								if(Collides(&rect)) {
									x = xaux;
									z-=0.1*cos(rot*PI/180);
									for(int i=-1;i<=1;++i) {
										for(int j=-1;j<=1;++j) {
											caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
											if(Collides(&rect)) {
												z = zaux;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		/*for(unsigned int i=1;i<=4;++i) {
			caixes[tx*SCENE_WIDTH+ty+i].GetArea(&rect);
			if(Collides(&rect)) {
				x = xaux;
				z = zaux;
			}
		}*/


}

void cBicho::MoveDown(vector<cBicho> *caixes, vector<vector<int>> map)
{
	/*int yaux;
	
	//Whats next tile?
	if( (y % TILE_SIZE) == 0)
	{
		yaux = y;
		y -= STEP_LENGTH*speed;

		if(CollidesMapFloor(map))
		{
			y = yaux;
			state = STATE_LOOKDOWN;
		}
	}
	//Advance, no problem
	else
	{
		y -= STEP_LENGTH*speed;
		if(state != STATE_WALKDOWN && state != STATE_DDOWNLEFT && state != STATE_DDOWNRIGHT)
		{
			state = STATE_WALKDOWN;
			seq = 0;
			delay = 0;
		}
	}*/
		//x+=0.1*sin(rot*PI/180);
		//z+=0.1*cos(rot*PI/180);

		float xaux, zaux;
		xaux=x;
		zaux=z;
		int tx,ty;
		int suelo;
		suelo = ((int)floor(y))/4;
		GetTile(&tx,&ty);
		x+=0.1*sin(rot*PI/180);
		z+=0.1*cos(rot*PI/180);
		cRect rect;

		for(int i=-1;i<=1;++i) {
			for(int j=-1;j<=1;++j) {
				//if(!(i==0 && j==0)) {
				if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
					caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
					if(Collides(&rect)) {
						z = zaux;
						for(int i=-1;i<=1;++i) {
							for(int j=-1;j<=1;++j) {
								caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
								if(Collides(&rect)) {
									x = xaux;
									z-=0.1*cos(rot*PI/180);
									for(int i=-1;i<=1;++i) {
										for(int j=-1;j<=1;++j) {
											caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
											if(Collides(&rect)) {
												z = zaux;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

}


void cBicho::StrafeLeft(vector<cBicho> *caixes, vector<vector<int>> map)
{
	/*int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH*speed;

		if(CollidesMapWall(map,false))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH*speed;
		if(state != STATE_WALKLEFT && state !=STATE_DUPLEFT && state != STATE_DDOWNLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}*/
	//x-=0.1*sin((rot+90)*0.017);
	//z-=0.1*cos((rot+90)*0.017);

			float xaux, zaux;
		xaux=x;
		zaux=z;
		int tx,ty;
		int suelo;
		suelo = ((int)floor(y))/4;
		GetTile(&tx,&ty);
		x-=0.1*sin((rot+90)*PI/180);
		z-=0.1*cos((rot+90)*PI/180);
		cRect rect;

		for(int i=-1;i<=1;++i) {
			for(int j=-1;j<=1;++j) {
				//if(!(i==0 && j==0)) {
				if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
					caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
					if(Collides(&rect)) {
						z = zaux;
						for(int i=-1;i<=1;++i) {
							for(int j=-1;j<=1;++j) {
								caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
								if(Collides(&rect)) {
									x = xaux;
									z-=0.1*cos(rot*PI/180);
									for(int i=-1;i<=1;++i) {
										for(int j=-1;j<=1;++j) {
											caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
											if(Collides(&rect)) {
												z = zaux;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

}

void cBicho::StrafeRight(vector<cBicho> *caixes, vector<vector<int>> map)
{
	/*int xaux;

	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH*speed;

		if(CollidesMapWall(map,true))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH*speed;

		if(state != STATE_WALKRIGHT && state !=STATE_DUPRIGHT && state != STATE_DDOWNRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}*/
	//x+=0.1*sin((rot+90)*0.017);
	//z+=0.1*cos((rot+90)*0.017);
			float xaux, zaux;
		xaux=x;
		zaux=z;
		int tx,ty;
		int suelo;
		suelo = ((int)floor(y))/4;
		GetTile(&tx,&ty);
		x+=0.1*sin((rot+90)*PI/180);
		z+=0.1*cos((rot+90)*PI/180);
		cRect rect;

		for(int i=-1;i<=1;++i) {
			for(int j=-1;j<=1;++j) {
				//if(!(i==0 && j==0)) {
				if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
					caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
					if(Collides(&rect)) {
						z = zaux;
						for(int i=-1;i<=1;++i) {
							for(int j=-1;j<=1;++j) {
								caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
								if(Collides(&rect)) {
									x = xaux;
									z-=0.1*cos(rot*PI/180);
									for(int i=-1;i<=1;++i) {
										for(int j=-1;j<=1;++j) {
											caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
											if(Collides(&rect)) {
												z = zaux;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

}
void cBicho::Shoot(int *map)
{
	if(state == STATE_SHOOT_LEFT || state == STATE_WALKLEFT || state == STATE_LOOKLEFT)
		{
			state = STATE_SHOOT_LEFT;
			seq = 0;
			delay = 0;
		}
	else if(state == STATE_SHOOT_RIGHT || state == STATE_WALKRIGHT || state == STATE_LOOKRIGHT)	{
			state = STATE_SHOOT_RIGHT;
			seq = 0;
			delay = 0;
		}
}
void cBicho::Stop()
{
	switch(state)
	{
		case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
		case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
		case STATE_WALKUP:		state = STATE_LOOKUP;		break;
		case STATE_WALKDOWN:	state = STATE_LOOKDOWN;		break;
		case STATE_DUPLEFT:		state = STATE_LOOKUP;		break;
		case STATE_DUPRIGHT:	state =	STATE_LOOKUP;		break;
		case STATE_DDOWNLEFT:	state = STATE_LOOKDOWN;		break;
		case STATE_DDOWNRIGHT:	state =	STATE_LOOKDOWN;		break;
	}
}
void cBicho::Jump(int *map)
{
	if(!jumping)
	{
		if(CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
		}
	}
}

void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}
void cBicho::SetSpeed(int i) {
	speed = i;
}

void cBicho::AddRot(float x) {
	rot+=x;
	if(rot>360)rot=0;
}

void cBicho::SetRot(float x) {
	rot = x;
}

float cBicho::GetRot() {
	return rot;
}

void cBicho::DrawBB() {
	float x,y,z,w,h,d;
	GetPosition(&x,&y,&z);
	GetVol(&w,&h,&d);
	glBegin(GL_LINES);
	glColor3f(1,1,0); glVertex3f(x,y,z); glVertex3f(x+w,y,z); // X
	glColor3f(1,1,0); glVertex3f(x,y,z); glVertex3f(x,y+h,z); // Y
	glColor3f(1,1,0); glVertex3f(x,y,z); glVertex3f(x,y,z+d); // Z
	glColor3f(1,1,0); glVertex3f(x+w,y+h,z+d); glVertex3f(x,y+h,z+d); // X
	glColor3f(1,1,0); glVertex3f(x+w,y+h,z+d); glVertex3f(x+w,y,z+d); // Y
	glColor3f(1,1,0); glVertex3f(x+w,y+h,z+d); glVertex3f(x+w,y+h,z); // Z

	glColor3f(1,1,0); glVertex3f(x+w,y,z+d); glVertex3f(x,y,z+d); // X
	glColor3f(1,1,0); glVertex3f(x+w,y,z+d); glVertex3f(x+w,y,z); // Y
	//glColor3f(1,1,0); glVertex3f(x+w,y,z+d); glVertex3f(x+w,y+h,z); // Z

	glColor3f(1,1,0); glVertex3f(x,y+h,z); glVertex3f(x,y+h,z+d); // X
	glColor3f(1,1,0); glVertex3f(x,y+h,z); glVertex3f(x+w,y+h,z); // Y
	//glColor3f(1,1,0); glVertex3f(x+w,y+h,z+d); glVertex3f(x+w,y+h,z); // Z

	glColor3f(1,1,0); glVertex3f(x,y,z+d); glVertex3f(x,y+h,z+d); // X
	glColor3f(1,1,0); glVertex3f(x+w,y,z); glVertex3f(x+w,y+h,z); // Y
	glEnd();

}