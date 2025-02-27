#include "../inc/cGame.h"
#include "../inc/Globals.h"


cGame::cGame(void) {
	teclaAct=false;
}
cGame::~cGame(void){}

void cGame::NextLevel() {
	camera = 2;
	rebots = 0;
	for (int i = 0; i < 3; i++) {
		caixes[i].clear();
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);


	glutSwapBuffers();
	Sleep(2000);

	if (actualLevel==1) {
		++actualLevel;
		player.SetPosition(4*1,0,4*-8);
		enemy.SetPosition(4*5,4*1,4*-2);
		enemy.Active();
	}
	else if (actualLevel == 2) {
		++actualLevel;
		enemy.Active();
		enemy.SetPosition(4*5,0,4*-3);
		player.SetPosition(4*1,0,4*-8);

	}
	else if(actualLevel == 3) {
		++actualLevel;
		player.SetPosition(4*1,6,4*-8);
		enemy.SetPosition(4*2,4*1,4*-3);
		enemy.Active();
	}
	else if(actualLevel == 4) {
		++actualLevel;
		player.SetPosition(4*1,0,4*-8);
		enemy.SetPosition(4*4,4*1,4*-2);
		enemy.Active();
	}
	else if(actualLevel == 5) {
		Init();
	}
	bool result = false;
	result = Scene.LoadLevel(actualLevel,caixes,terra,bullseyes);
	Scene.GetMap(map);
}

bool cGame::Init()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	tipoPintado = 0;
	camera = 2;
	startTime = glutGet(GLUT_ELAPSED_TIME);
	maxPosx = GetSystemMetrics(SM_CXSCREEN);
	maxPosy = GetSystemMetrics(SM_CYSCREEN);
	maxPosx = maxPosx/2;
	maxPosy = maxPosy/2;
	bool res=true;
	actualLevel = 1;
	Sound.PlaySound("resources/music/FTL - 14.mp3",true,0.6);
	dir = 1;
	time_init=glutGet(GLUT_ELAPSED_TIME);
	fps = fps_dibuix = 0;
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_WALL1,"resources/im/wall1.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_CHECK,"resources/im/checkerboard.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_WALL2,"resources/im/wall2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_WALL3,"resources/im/wall3.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_FLOOR,"resources/im/floor.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ROOF,"resources/im/roof.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_CROSSHAIR,"resources/im/crosshair.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_FONT,"resources/im/font.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BULL,"resources/im/bullseye.png",GL_RGBA);
	if(!res) return false;
	Scene.Init();
	res = Scene.LoadLevel(actualLevel,caixes,terra,bullseyes);
	Scene.GetMap(map);
	if(!res) return false;

	player.SetPosition(4*1,0,4*-8);
	player.SetVol(2,2,2);
	shoot.SetVol(0.4,0.4,0.4);
	enemy.SetPosition(4*1,0,4*-2);
	enemy.SetVol(4,4,4);
	enemy.Active();
	glewInit();
	shader.loadfromFile();

	return res;
}

bool cGame::Loop()
{
	bool res=true;
	int timePerFrame = 20;
	res = Process();
	endTime = glutGet(GLUT_ELAPSED_TIME);
	loopTime = endTime - startTime;
	startTime = glutGet(GLUT_ELAPSED_TIME);
	if (timePerFrame-loopTime >= 0) {
		Sleep(timePerFrame-loopTime);
	}
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = true;
	keysReleased[key] = false;
}

void cGame::ReadKeyboardSpecial(unsigned char key, int x, int y, bool press)
{
	keysSpecial[key] = true;
	keysSpecialReleased[key] = false;
}

void cGame::ReadKeyboardRelease(unsigned char key, int x, int y, bool press)
{
	keys[key] = false;
	keysReleased[key] = true;
}

void cGame::ReadKeyboardSpecialRelease(unsigned char key, int x, int y, bool press)
{
	keysSpecial[key] = false;
	keysSpecialReleased[key] = true;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

void cGame::ReadPosMouse(int x, int y)
{
	if(mouseState) {
		x2=x;
		y2=y;
		mouseState = false;
		SetCursorPos(maxPosx,maxPosy);
	}
	else {
		x1=x;
		y1=y;
		mouseState = true;
	}
}

//Process
bool cGame::Process()
{
	bool res=true;
	Sound.Update();
	if (enemy.IsAlive() && actualLevel == 5) {
		float x,y,z;
		enemy.GetPosition(&x,&y,&z);
		if (x >= 2*4 && x <= 7*4 ) {
			x = x+dir*0.1;
			enemy.SetPosition(x,y,z);
		}
		else { 
			dir = dir*-1;
			x = x+dir*0.1;
			enemy.SetPosition(x,y,z);
		}

	}
		if(shoot.IsActive()) {
			//if (shoot.GetIner() > 0)
			shoot.Logic(terra,caixes,map);
			shoot.MoveUp(caixes,map,terra,Sound,rebots);
			//if (shoot.GetIner() > 0)
		
		
		
			cRect rect;
			enemy.GetArea(&rect);
			//shoot.GetArea(&rect);
			if(shoot.Collides(&rect) && enemy.IsAlive()) {
				shoot.SetActive(false);
				enemy.kill();
				goinNextLevel = true;
				//NextLevel();
			}
		}

	
	//Process Input
	rot-=(x2-x1);
	player.SetRot(rot);
	x1 = x2;
	if(rot>360) rot = 0;
	else if(rot<0)rot = 360;
	rotV-=(y2-y1);
	y1 = y2;
	if(rotV>90) rotV = 90;
	else if(rotV<-90) rotV = -90;

	if(keys[27])	res=false;	
	
	if(keys[50]){
		camera = 2;
	}
	else if(keys[49]){
		camera = 1;
	}
	else if(keys[57]) {
		camera = 0;
	}
	else if(keys[51]) {
		camera = 3;
	}
	else if(keys[52]) {
		camera = 4;
	}
	if(camera == 1 || camera == 3) player.SetRot(rot);
	/*if(keys['q']) {
		player.StrafeLeft(caixes, map);
	}
	if(keys['e']) {
		player.StrafeRight(caixes, map);
	}*/
	if(keys['w']) {
		player.MoveUpPlayer(caixes,map);
		//player.MoveUp(caixes,map);
	}
	if(keys['s']) {
		//player.MoveDown(caixes, map);
		player.MoveDownPlayer(caixes,map);
	}
	if(keys['a']){ 
		if (camera == 3) player.SetRot(rot);
		else if(camera != 1) player.AddRot(0.5);
	}
	if(keys['d']){
		if (camera == 3) player.SetRot(rot);
		else if(camera != 1) player.AddRot(-0.5);
	}
	if(keys['r']) {
		float x,y,z;
		rebots = 0;
		player.GetPosition(&x,&y,&z);
		shoot.SetPosition(x+0.8,y+0.8,z+0.8);
		shoot.SetIner(0.6);
		//shoot.SetPosition();
		shoot.setRot(rotV,rot);
		shoot.SetActive(true);
	}
	if(keys['l']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if(keys['k']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if(keys['p']) {
		NextLevel();
		Sleep(500);
	}
	if(keys['f'] && !teclaAct) {
		teclaAct = true;
		++tipoPintado;
		if (tipoPintado > 2) tipoPintado = 0;
	}
	if(keysReleased['f']) {
		teclaAct = false;
	}
	player.Logic(terra,caixes,map);
	
	//Game Logic
	//...
	time_end = glutGet(GLUT_ELAPSED_TIME);
	if(time_end -time_init > 1000) {
		fps_dibuix=fps;
		fps=0;
		time_init=glutGet(GLUT_ELAPSED_TIME);
	}
	fps++;





	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//shader.render();
	float x,y,z;

	glLoadIdentity();
	if (shoot.IsActive()) {
		shoot.GetPosition(&x,&y,&z);
		x+=0.2;
		y+=0.2;
		z+=0.2;
	}
	else {
		player.GetPosition(&x,&y,&z);
		x+=1;
		y+=1;
		z+=1;
	}
	float pos2[4] = {x,y, z, 1.0};
	switch(camera) {
	case 1:
		
		glRotatef((-rotV),1,0,0);
		glRotatef((-rot),0,1,0);
		

		player.GetPosition(&x,&y,&z);
		glTranslatef(-x-1,-y-1,-z-1);
		//glLightfv(GL_LIGHT0, GL_POSITION, pos2);
		
		break;
	case 2:
		float x2,y2, z2;
		player.GetPosition(&x2,&y2,&z2);
		gluLookAt(64,36,-20,0,-8,-20,0,1,0);
		glBegin(GL_LINES);
		glColor3f(1,1,1); 
		glVertex3f(x2+1,y2+1,z2+1);
		glVertex3f(x2-cos(PI/180*rotV)*sin(PI/180*rot)*4,y2+sin(PI/180*rotV)*4,z2-cos(PI/180*rotV)*cos(PI/180*rot)*4); // X
		//glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
		//glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
		glEnd();
		glColor3f(1,1,1);
		//glLightfv(GL_LIGHT0, GL_POSITION, pos2);
		break;
	case 3:
		glTranslatef(0,-(1),-5);
		glRotatef((-rotV),1,0,0);
		glRotatef((-rot),0,1,0);
		//glLightfv(GL_LIGHT0, GL_POSITION, pos2);
		
		//float x,y,z;
		player.GetPosition(&x,&y,&z);
		glTranslatef(-x-1,-y-1,-z-1);
		//glLightfv(GL_LIGHT0, GL_POSITION, pos2);
		break;
	case 4:
		glTranslatef(0,-(2),-5);
		glRotatef((-rotV),1,0,0);
		glRotatef((-rot),0,1,0);
		
		//float x,y,z;
		shoot.GetPosition(&x,&y,&z);
		glTranslatef(-x,-y,-z);
		//glLightfv(GL_LIGHT0, GL_POSITION, pos2);
		break;
	default:
		glTranslatef(0.0f,-2.0f,-40.0f);
		glRotatef(20,1.0f,0.0f,0.0f);
		break;
	}
	glLightfv(GL_LIGHT0, GL_POSITION, pos2);
	if(tipoPintado !=0) {
		glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
		glEnd();
		glColor3f(1,1,1);
	}
	//void gluSphere(GLUquadric *qobj,GLdouble radius,GLint slices,GLint stacks
				
	if(camera != 1 && tipoPintado !=2 ) {
		//shader.render();
		player.Draw(&Data);
		//glLightfv(GL_LIGHT0, GL_POSITION, pos2);
		//shader.norender();
		
	}
	if(enemy.IsAlive() && tipoPintado !=2) enemy.Draw(0,&Data);
	

	shader.render();

	if(tipoPintado !=2) Scene.Draw(&Data);
		//glLightfv(GL_LIGHT0, GL_POSITION, pos2);
	shader.norender();
			/*glColor3f( 0.0f, 0.0f, 0.0f );
			glLineWidth(4.0f);
			glPolygonOffset( -1.0f, -1.0f );
			//caixes[k][i].DrawBB();
			Scene.Draw(&Data);*/
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glEnable( GL_POLYGON_OFFSET_LINE );      
	if (tipoPintado !=2) {		
		for(unsigned int k=0;k<2;++k) {
			for(unsigned int i=0;i<caixes[k].size();++i) {
				glColor3f( 0.0f, 0.0f, 0.0f );
				glLineWidth(4.0f);
				glPolygonOffset( -1.0f, -1.0f );
				caixes[k][i].DrawLines();
			}
		}
		glDisable( GL_POLYGON_OFFSET_FILL );
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
	if (tipoPintado !=0) {
		glLineWidth(1.0f);
		for(unsigned int k=0;k<3;++k) {
			for(unsigned int i=0;i<caixes[k].size();++i) {
				caixes[k][i].DrawBB();
			}
		}
	}
	glColor3f( 1.0f, 1.0f, 1.0f );
	if (shoot.IsActive() && tipoPintado != 2) {
		//shoot.GetPosition(&x,&y,&z);
		//y+=0.1*sin(rotV*PI/180.0);
		//shoot.SetPosition(x,y,z);
		//shader.render();
		glColor3f(1,1,0);
		shoot.Draw();
		glColor3f(1,1,1);
		//shader.norender();
	}
	if (shoot.IsActive() && tipoPintado !=0) shoot.DrawBB();
	if (enemy.IsAlive() && tipoPintado !=0) enemy.DrawBB();
	if(tipoPintado !=0) {
		player.DrawBB();
		terra.DrawBB();
	}
	glColor3f(1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	if (camera == 3 || camera == 1) {
		Hud.DrawCrossHair(Data.GetID(IMG_CROSSHAIR),SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	}
	glLoadIdentity();
	Hud.Drawfps(Data.GetID(IMG_FONT), startTime-(2000*(actualLevel-1)), SCREEN_WIDTH, SCREEN_HEIGHT);
	//glLoadIdentity();
	if(goinNextLevel) {
		glLoadIdentity();
		Hud.DrawPrepareToFight(Data.GetID(IMG_FONT), SCREEN_WIDTH, SCREEN_HEIGHT);
		goinNextLevel = false;
		NextLevel();
	}
	glLoadIdentity();
	Hud.Drawrebots(Data.GetID(IMG_FONT), rebots, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);


	glutSwapBuffers();
}
