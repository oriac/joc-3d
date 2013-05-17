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
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}
bool cBicho::Collides(cRect *rc)
{
	//return ((x>rc->left) && (x+w<rc->right) && (y>rc->bottom) && (y+h<rc->top));
	return false;
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
void cBicho::MoveUp()
{
	/*int yaux;

	//Whats next tile?
	if( (y % TILE_SIZE) == 0)
	{
		yaux = y;
		y += STEP_LENGTH*speed;

		if(CollidesMapTop(map))
		{
			y = yaux;
			state = STATE_LOOKUP;
		}
	}
	//Advance, no problem
	else
	{
		y += STEP_LENGTH*speed;

		if(state != STATE_WALKUP && state != STATE_DUPLEFT && state != STATE_DUPRIGHT)
		{
			state = STATE_WALKUP;
			seq = 0;
			delay = 0;
		}
	}*/
		x-=0.1*sin(rot*0.017);
		z-=0.1*cos(rot*0.017);
}

void cBicho::MoveDown()
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
		x+=0.1*sin(rot*0.017);
		z+=0.1*cos(rot*0.017);
}


void cBicho::StrafeLeft()
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
	x-=0.1*sin((rot+90)*0.017);
	z-=0.1*cos((rot+90)*0.017);
}

void cBicho::StrafeRight()
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
	x+=0.1*sin((rot+90)*0.017);
	z+=0.1*cos((rot+90)*0.017);
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