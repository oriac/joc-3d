
#include "../inc/cPlayer.h"

cPlayer::cPlayer() {hp = 0;alive=false;points=0; explote = false;}
cPlayer::~cPlayer(){}

void cPlayer::Draw()
{	
	/*float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	xo = 0.25f;	yo = 0.5f;
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.25f;	yo = 0.75f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 0.0f + (GetFrame()*0.25f);	yo = 0.5f ;
								NextFrame(3);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.0f+ (GetFrame()*0.25f); yo = 0.75f ;
								NextFrame(3);
								break;
		case STATE_LOOKUP:		xo = 0.25f;	yo = 1.0f;
								break;
		case STATE_WALKUP:		xo = 0.0f + (GetFrame()*0.25f); yo = 1.0;
								NextFrame(3);
								break;
		case STATE_WALKDOWN:	xo = 0.0f + (GetFrame()*0.25f); yo = 0.25f;
								NextFrame(3);
								break;
		
			//4						
		case STATE_LOOKDOWN:	xo = 0.25f;	yo = 0.25f;
								break;
		case STATE_SHOOT_LEFT:	xo = 0.25f; yo = 0.5f;
								break;
		case STATE_SHOOT_RIGHT: xo = 0.25f; yo = 0.75f;
								break;
		case STATE_DUPLEFT:		xo = 0.0f + (GetFrame()*0.25f); yo = 1.0;
								NextFrame(3);
								break;
		case STATE_DUPRIGHT:	xo = 0.0f + (GetFrame()*0.25f); yo = 1.0;
								NextFrame(3);
								break;
		case STATE_DDOWNLEFT:	xo = 0.0f + (GetFrame()*0.25f); yo = 0.25f;
								NextFrame(3);
								break;
		case STATE_DDOWNRIGHT:	xo = 0.0f + (GetFrame()*0.25f); yo = 0.25f;
								NextFrame(3);
								break;
		case STATE_EXPLOTE:		xo = 0.75f; yo = 0.25f + (GetFrame()*0.25f);
								if (yo == 1.0f) explote = false;
								NextFrame(4);
								break;
	}
	xf = xo + 0.25f;
	yf = yo - 0.25f;
	*/
	//DrawRect(tex_id,xo,yo,xf,yf);
	float x,y,z;
	GetPosition(&x,&y,&z);
	
		glPushMatrix();
		    double rot = GetRot();
			glTranslatef(x+1,y,z+1);
			float pos2[4] = {0,+2, 0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos2);
			glRotatef((rot),0,1,0);

			//float pos2[4] = {x, y, z, 1.0};
			GLUquadricObj *q = gluNewQuadric();
			//glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_FLOOR));
			gluSphere(q, 1,128,128);
	
			gluDeleteQuadric(q);
		glPopMatrix();
}

int cPlayer::GetHp() {
	return hp;
}

void cPlayer::WinHp() {
	if(hp<=9)hp++;
}

void cPlayer::LoseHp() {
	hp--;
}

bool cPlayer::isAlive() {
	return alive;
}
bool cPlayer::IsExplote() {
	return explote;
}
void cPlayer::AddPoints(int punts) {
	points += punts;
}

void cPlayer::Respawn() {
	hp = 3;
	alive = true;
	points = 0;
}

string cPlayer::GetPoints() {
	stringstream ss;
	ss << points;
	return ss.str();
}

void cPlayer::Dead() {
	cBicho::SetState(STATE_EXPLOTE);
	explote = true;
	alive = false;
}

/*void cPlayer::Logic(cBicho &terra, vector<cBicho> *caixes) {
	cRect rect;
	//GetArea(cRect *rc)
	//GetArea(&rect);
	terra.GetArea(&rect);
	//if(!caixes[caixes.size()-1].Collides(&rect)) {
	if(!Collides(&rect)) {
		float x,y,z;
		GetPosition(&x,&y,&z);
		y -= 0.05;
		//SetPosition(x,y,z);
		int suelo;
		suelo = ((int)floor(y))/4;
		int tx,ty;
		GetTile(&tx,&ty);
		caixes[suelo][(ty)*SCENE_DEPTH+ (tx)].GetArea(&rect);
		if(Collides(&rect)) y += 0.051;
		SetPosition(x,y,z);
	}
}*/

void cPlayer::Logic(cBicho &terra, vector<cBicho> *caixes, vector<vector<int>> &map) {
	float yaux;
	float x,y,z;
		GetPosition(&x,&y,&z);
		yaux=y;
		int tx,ty;
		y-=0.05;
		int suelo;
		suelo = ((int)floor(y))/4;
		GetTile(&tx,&ty);
		
		cRect rect;
		terra.GetArea(&rect);
		if(!Collides(&rect)) {
			for(int i=-1;i<=1;++i) {
				for(int j=-1;j<=1;++j) {
					//if(!(i==0 && j==0)) {
					if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
						caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
						if(Collides(&rect)) {
							y = yaux;
						}
					}
				}
			}
		}
		else {
			y = yaux;
		}
		SetPosition(x,y,z);
}

