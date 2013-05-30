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
			glTranslatef(x+0.2,y+0.2,z+0.2);
			GLUquadricObj *q = gluNewQuadric();
			//glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_FLOOR));
			gluSphere(q, 0.2,64,64);
			gluDeleteQuadric(q);
		glPopMatrix();
}

bool cShoot::IsActive() {
	return active;
}

void cShoot::SetActive(bool b) {
	active = b;
}

void cShoot::SetIner(double x) {
	iner = x;
}

void cShoot::SetnumColisions(int c) {
	numColisions = c;
}

void cShoot::Setpunts(int p) {
	punts = p;
}

int cShoot::GetNumColisions() {
	return numColisions;
}

int cShoot::GetPunts(){
	return punts;
}

double cShoot::GetIner(){
	return iner;
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
		 //z+=(-sin(PI/180*rot)*cos(PI/180*rotV)*0.1);
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

/*void cShoot::Logic(cBicho &suelo) {
	cRect rect;
	iner -= 0.0005;
	if (iner < 0) iner = 0.0;
	//GetArea(cRect *rc)
	//GetArea(&rect);
	suelo.GetArea(&rect);
	//if(!caixes[caixes.size()-1].Collides(&rect)) {
	if(!Collides(&rect)) {
		float x,y,z;
		GetPosition(&x,&y,&z);
		//y -= 0.01;
		SetPosition(x,y,z);
	}
}*/

void cShoot::Logic(cBicho &terra, vector<cBicho> *caixes, vector<vector<int>> &map) {
        float yaux;
        float x,y,z;
                GetPosition(&x,&y,&z);
                iner -= 0.0015;
                if (iner < 0) iner = 0.0;
                yaux=y;
                int tx,ty;
				//if(!(rotV >= -5 && rotV <= 5 && y>=3.95 && y<=4.01)) y-=0.03;
				y-=0.03;
                int suelo;
                suelo = ((int)floor(y))/4;
                GetTile(&tx,&ty);
                SetPosition(x,y,z);
                cRect rect;
                terra.GetArea(&rect);
                if(!Collides(&rect)) {
					bool b=false;
                    for(int i=-1;i<=1 && !b;++i) {
                        for(int j=-1;j<=1 && !b;++j) {
                            //if(!(i==0 && j==0)) {
                            if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
                                caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                if(Collides(&rect)) {
                                    //y = yaux;
                                    //caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetPosition();
									b=true;
                                    y=rect.ymax;
									if(rotV<0)rotV -= 2*rotV; 
									//rotV -= 2*rotV;
                                    //rotV -= 2*rotV;
                                }
                            }
                        }
                    }
                }
                else {
                        y = yaux;
                        rotV -= 2*rotV;
                }
                SetPosition(x,y,z);
}


void cShoot::MoveUp(vector<cBicho> *caixes, vector< vector<int> > &map, cBicho &terra, cSound &Sound)
{
                double xaux, zaux, yaux;
                float x,y,z;
                //float rot;
                //rot = GetRot();
                GetPosition(&x,&y,&z);
                xaux=x;
                zaux=z;
                yaux=y;
                int tx,ty;
                GetTile(&tx,&ty);
                //x-=iner*sin(rot*PI/180);
                //z-=iner*cos(rot*PI/180);
                x+=-cos(PI/180*rotV)*sin(PI/180*rot)*iner;
                z+=-cos(PI/180*rotV)*cos(PI/180*rot)*iner;
                if(y<0)y=0;
                int suelo;
                
                //y+=sin(PI/180*rotV)*iner;
                suelo = ((int)floor(y))/4;
				//y-=0.01;
                SetPosition(x,y,z);
                cRect rect;
                bool b=false;
                bool desliza_z=true;
                bool desliza_x=true;
                bool desliza_y=true;
                //if(suelo>1)suelo=1;
                //caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                terra.GetArea(&rect);
                /*if(Collides(&rect)) {
                        y=0;
                        rotV -= 2*rotV;
                }*/
                /*int i=0;
                int j=0;
                                if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0 || map[suelo+1][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
                                        caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                        if(!Collides(&rect)) {
                                                //y+=sin(PI/180*rotV)*iner;
                                                
                                                suelo = ((int)floor(y))/4;
                                                caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                                if(Collides(&rect)) {
                                                        if(rotV >=0 && rotV <= 90) {
                                                                //double rotaux = 90.0 - (rot);
                                                                rotV -= 2*rotV;
                                                                //rot = 360-(rot);
                                                                //rot = fmod(rot,360);

                                                        }
                                                        else if(rotV >=-90 && rotV < 0) {
                                                                //double rotaux = (rot-90);
                                                                //double rotaux2 = 90-rotaux;
                                                                rotV -= 2*rotV;
                                                        }
                                                        b = true;
                                                        y=yaux;
                                                        SetPosition(x,y,z);
                                                }
                                        }
                                }*/
                
                b=false;
                suelo = ((int)floor(y))/4;
                for(int i=-1;i<=1 && !b;++i) {
                    for(int j=-1;j<=1 && !b;++j) {
                            //if(!(i==0 && j==0)) {
                        if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
                            caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                            if(Collides(&rect)) {
                                z = zaux;
                                //y = yaux;
                                SetPosition(x,y,z);
                                b = true;
                                for(int i=-1;i<=1;++i) {
                                    for(int j=-1;j<=1;++j) {
                                        caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                        if(Collides(&rect)) {
                                            x = xaux;
                                            //y = yaux;
                                            desliza_x = false;
                                            //z-=0.1*cos(rot*PI/180);
                                            z+=-sin(PI/180*rotV)*cos(PI/180*rot)*iner;
                                            SetPosition(x,y,z);
                                            for(int i=-1;i<=1;++i) {
                                                for(int j=-1;j<=1;++j) {
                                                    caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                                    if(Collides(&rect)) {
                                                        z = zaux;
                                                        //y = yaux;
                                                        desliza_z = false;
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
                if(b) {
                        if(desliza_x) {
                                if(rot >=0 && rot < 90) {
                                        double rotaux = 90.0 - (rot);
                                        rot += 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                        //rot = 360-(rot);
                                        //rot = fmod(rot,360);

                                }
                                else if(rot >=90 && rot < 180) {
                                        double rotaux = (rot-90);
                                        //double rotaux2 = 90-rotaux;
                                        rot -= 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                }
                                else if(rot >=180 && rot < 270) {
                                        double rotaux =  90 - (rot - 180);
                                        //double rotaux2 = 90-rotaux;
                                        rot += 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                }
                                else if(rot >=270 && rot < 360) {
                                        double rotaux = (rot-270);
                                        //double rotaux2 = 90-rotaux;
                                        rot -= 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                }
                        }
                        else if(desliza_z) {
                                if(rot >=0 && rot < 90) {
                                        double rotaux = 90.0 - (rot);
                                        rot += 180 + 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                        //rot = 360-(rot);
                                        //rot = fmod(rot,360);

                                }
                                else if(rot >=90 && rot < 180) {
                                        double rotaux = 90.0 - (rot-90);
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                        //double rotaux2 = 90-rotaux;
                                        rot += 2*rotaux;
                                }
                                else if(rot >=180 && rot < 270) {
                                        double rotaux =  (rot - 180);
                                        //double rotaux2 = 90-rotaux;
                                        rot -= 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                }
                                else if(rot >=270 && rot < 360) {
                                        double rotaux = 90.0 - (rot-90);
                                        //double rotaux2 = 90-rotaux;
                                        rot += 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                }
                        }
                }
                SetPosition(x,y,z);
                rot = fmod(rot,360);
                //SetRot(rot);
                /*for(unsigned int i=1;i<=4;++i) {
                        caixes[tx*SCENE_WIDTH+ty+i].GetArea(&rect);
                        if(Collides(&rect)) {
                                x = xaux;
                                z = zaux;
                        }
                }*/
                y+=sin(PI/180*rotV)*iner;
                SetPosition(x,y,z);
            if(map[suelo][(ty)*SCENE_DEPTH+ (tx)] == 0) {
                    //y+=sin(PI/180*rotV)*iner;
                for(int i=-1;i<=1 && !b;++i) {
					for(int j=-1;j<=1 && !b;++j) {
						caixes[suelo+1][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
						if(Collides(&rect)) {
							b = true;
							if(rotV >=0 && rotV <= 90) {
									//double rotaux = 90.0 - (rot);
									rotV -= 2*rotV;
									Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
									//rot = 360-(rot);
									//rot = fmod(rot,360);

							}
							else if(rotV >=-90 && rotV < 0) {
									//double rotaux = (rot-90);
									//double rotaux2 = 90-rotaux;
									rotV -= 2*rotV;
									Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
							}
							y = yaux;
							SetPosition(x,y,z);
						}
					}
				}
            }
                        //if(!b) {
                                //if(map[suelo][(ty)*SCENE_DEPTH+ (tx)] == 0) {
				//y = yaux;
				//y+=sin(PI/180*rotV)*iner;
                //SetPosition(x,y,z);
                b=false;
                suelo--;
                if(suelo<0)suelo=0;
                for(int i=-1;i<=1 && !b;++i) {
                    for(int j=-1;j<=1 && !b;++j) {
                        if(map[suelo][(ty)*SCENE_DEPTH+ (tx)] != 0) {
                            caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                            if(Collides(&rect)) {
                                b = true;
                                if(rotV >=0 && rotV <= 90) {
                                        //double rotaux = 90.0 - (rot);
                                        rotV -= 2*rotV;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                        //rot = 360-(rot);
                                        //rot = fmod(rot,360);

                                }
                                else if(rotV >=-90 && rotV < 0) {
                                        //double rotaux = (rot-90);
                                        //double rotaux2 = 90-rotaux;
										
                                        rotV -= 2*rotV;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                }
								//if(yaux<rect.ymax)
									y=rect.ymax;
								//else
									//y = yaux;
                                SetPosition(x,y,z);
                            }
                        }
                    }
                //}
        //}
                }


}
