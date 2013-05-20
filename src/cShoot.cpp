#include "../inc/cShoot.h"

cShoot::cShoot(void)
{
}


cShoot::~cShoot(void)
{
}

void cShoot::Draw()
{
	/*float xo,yo,xf,yf;
	xo = 0.0f;	yo = 0.25f;
	xf = xo + 0.25f;
	yf = yo - 0.25f;

	DrawRect(tex_id,xo,yo,xf,yf);*/
		float x,y,z;
	GetPosition(&x,&y,&z);
		glPushMatrix();
			glTranslatef(x,y,z);
			GLUquadricObj *q = gluNewQuadric();
			//glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_FLOOR));
			gluSphere(q, 0.2,16,16);
			gluDeleteQuadric(q);
		glPopMatrix();
}

bool cShoot::IsActive() {
	return active;
}

void cShoot::SetActive(bool b) {
	active = b;
}

void cShoot::SetInitPos(int playerState,int x, int y) {
	/*if(playerState == STATE_WALKLEFT||playerState == STATE_LOOKLEFT||playerState == STATE_SHOOT_LEFT)
				SetPosition(x-(TILE_SIZE*2)+(x%4),y);
			else if(playerState == STATE_LOOKUP||playerState == STATE_WALKUP)
				SetPosition(x-(x%4),y+(TILE_SIZE*2)-(y%4));
			else if(playerState == STATE_LOOKDOWN||playerState == STATE_WALKDOWN)
				SetPosition(x,y-(TILE_SIZE*2)+(y%4));
			else if(playerState == STATE_WALKRIGHT||playerState == STATE_LOOKRIGHT||playerState == STATE_SHOOT_RIGHT)
				SetPosition(x+(TILE_SIZE*2)-(x%4),y);
			else if(playerState == STATE_DUPLEFT)
				SetPosition(x-(TILE_SIZE*2)+(x%4),y+(TILE_SIZE*2)-(y%4));
			else if(playerState == STATE_DUPRIGHT)
				SetPosition(x+(TILE_SIZE*2)+(x%4),y+(TILE_SIZE*2)+(y%4));
			else if(playerState == STATE_DDOWNLEFT)
				SetPosition(x-(TILE_SIZE*2)-(x%4),y-(TILE_SIZE*2)-(y%4));
			else if(playerState == STATE_DDOWNRIGHT)
				SetPosition(x+(TILE_SIZE*2)-(x%4),y-(TILE_SIZE*2)+(y%4));*/
}

void cShoot::ShootStep(int shootState, int *map) {
	/*switch (shootState) {
				case STATE_SHOOT_LEFT:
					MoveLeft(map);
					break;
				case STATE_SHOOT_RIGHT:
					MoveRight(map);
					break;
				case STATE_WALKLEFT:
					MoveLeft(map);					
					break;
				case STATE_WALKRIGHT:
					MoveRight(map);
					break;
				case STATE_LOOKLEFT:
					MoveLeft(map);
					break;
				case STATE_LOOKRIGHT:
					MoveRight(map);
					break;
				case STATE_LOOKUP:
					MoveUp(map);
					break;
				case STATE_WALKUP:
					MoveUp(map);
					break;
				case STATE_LOOKDOWN:
					MoveDown(map);
					break;
				case STATE_WALKDOWN:
					MoveDown(map);
					break;
				case STATE_DUPLEFT:
					MoveUp(map);
					MoveLeft(map);
					SetState(STATE_DUPLEFT);
					break;
				case STATE_DUPRIGHT:
					MoveUp(map);
					MoveRight(map);
					SetState(STATE_DUPRIGHT);
					break;
				case STATE_DDOWNLEFT:
					MoveDown(map);
					MoveLeft(map);
					SetState(STATE_DDOWNLEFT);
					break;
				case STATE_DDOWNRIGHT:
					MoveDown(map);
					MoveRight(map);
					SetState(STATE_DDOWNRIGHT);
					break;
			}*/
}

void cShoot::ShootCollides(int shootState, int *map) {
	if(shootState == STATE_SHOOT_RIGHT||shootState == STATE_WALKRIGHT||shootState == STATE_LOOKRIGHT)
		active = !CollidesWall(map,true);
	else if(shootState == STATE_LOOKUP)
		active = !CollidesTopBot(map,true);
	else if(shootState == STATE_LOOKDOWN)
		active = !CollidesTopBot(map,false);
	else if(shootState == STATE_SHOOT_LEFT||shootState == STATE_WALKLEFT||shootState == STATE_LOOKLEFT)
		active = !CollidesWall(map,false);
	else if(shootState == STATE_DUPRIGHT)
		active = !(CollidesWall(map,true)||CollidesTopBot(map,true));
	else if(shootState == STATE_DUPLEFT)
		active = !(CollidesWall(map,false)||CollidesTopBot(map,true));
	else if(shootState == STATE_DDOWNLEFT)
		active = !(CollidesWall(map,false)||CollidesTopBot(map,false));
	else if(shootState == STATE_DDOWNRIGHT)
		active = !(CollidesWall(map,true)||CollidesTopBot(map,false));
}

void cShoot::CanShoot(int *map, cBicho &Player) {
	int x,y;
	GetTile(&x,&y);
	if(map[x+(y*SCENE_WIDTH)] != 0) active = false;
	else active = true;
	if(active) {
		if(GetState() == STATE_SHOOT_LEFT || GetState() == STATE_LOOKLEFT || GetState() == STATE_WALKLEFT ) {
			active = !(Player.CollidesMapWall(map,false));
			if(map[(x+1)+y*SCENE_WIDTH] != 0) active = false;
			if(map[(x+2)+y*SCENE_WIDTH] != 0) active = false;
		}
		else if(GetState() == STATE_LOOKDOWN||GetState() == STATE_WALKDOWN) {
			active = !(Player.CollidesTopBot(map,false));
			if(map[x+((y+1)*SCENE_WIDTH)] != 0) active = false;
		}
		else if(GetState() == STATE_LOOKUP||GetState() == STATE_LOOKUP) {
			active = !(Player.CollidesTopBot(map,true));
		}
		else if(GetState() == STATE_SHOOT_RIGHT || GetState() == STATE_LOOKRIGHT || GetState() == STATE_WALKRIGHT ) {
			active = !(Player.CollidesMapWall(map,true));
			if(map[(x+1)+y*SCENE_WIDTH] != 0) active = false;
		}
		else if(GetState() == STATE_DUPLEFT) {
			active = !(Player.CollidesWall(map,false));
		}
	}

}

void cShoot::MoveShoot()
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
		float x,y,z;
		this->GetPosition(&x,&y,&z);
		 x-=0.1*sin(rot*PI/180);
		 z-=0.1*cos(rot*PI/180);
		// z+=(-sin(PI/180*rot)*cos(PI/180*rotV)*0.1);
		 //x+=(-sin(PI/180*rot)*sin(PI/180*rotV)*0.1);
		y+=0.1*sin(rotV*PI/180.0);
		 this->SetPosition(x,y,z);
		/*x-=0.1*sin(rot*PI/180);
		z-=0.1*cos(rot*PI/180);*/
}

void cShoot::setRot(float rotv, float rot){
	this->rot = rot;
	rotV = rotv;
}