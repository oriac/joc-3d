#include "../inc/cGame.h"
#include "../inc/Globals.h"


cGame::cGame(void) {
	//vector< vector<int> > map(3,vector<int> (SCENE_WIDTH * SCENE_DEPTH));
}
cGame::~cGame(void){}

void cGame::NextLevel() {
	//Sleep(6000);
	for (int i = 0; i < 3; i++) {
		caixes[i].clear();
	}
	
	if (actualLevel==1) {
		++actualLevel;
		player.SetPosition(4*1,6,4*-8);
		enemy.SetPosition(4*1,4*1,4*-2);
		enemy.Active();
		/*Sound.PlaySound("resources/music/ff7.wav",true);
		for (int i = 0; i < 4; ++i) {
			if (i ==0) Item[i].SetTile(23,27);
			else if (i ==1) Item[i].SetTile(15,65);
			else if (i ==2) Item[i].SetTile(26,91);
			else Item[i].SetTile(13,115);
			Item[i].SetActive(true);
		}
		Player.SetTile(4,1);
		Player2.SetTile(7,1);*/
	}
	else if (actualLevel == 2 && player.isAlive()) {
		//Sound.PlaySoundA("resources/music/pvp.mp3",true);
		actualLevel = 3;
		/*for (int i = 0; i < 4; ++i) {
			if (i ==0) Item[i].SetTile(17,16);
			else if (i ==1) Item[i].SetTile(13,16);
			else if (i ==2) Item[i].SetTile(3,3);
			else Item[i].SetTile(27,3);
			Item[i].SetActive(true);
		}*/
		player.SetTile(1,1);
		//Player2.SetTile(22,20);
	}
	else if(actualLevel == 2) {
		actualLevel =1;
		this->Init();
	}
	bool result = false;
	result = Scene.LoadLevel(actualLevel,caixes,terra,bullseyes);
	Scene.GetMap(map);
	//Scene.ResetCam();
	//if (actualLevel == 3) Scene.Scroll(80);

	/*vector<Point> pat (4);
	for (int i = 0; i < 10; ++i) {
		Enemy[i].Init(true, pat);
		Enemy[i].SetWidthHeight(32,32);
		if (i < 5) Enemy[i].SetTile((i*4)%32,36);
		else Enemy[i].SetTile((i*2)%32,72);
		Enemy[i].SetSpeed(1);

	}
	
	Point p1,p2,p3,p4;
	p1.tilex = 29;
	p1.tiley = 6;
	p2.tilex = 29;
	p2.tiley= 3;
	p3.tilex = 4;
	p3.tiley = 3;
	p4.tilex = 4;
	p4.tiley = 6;
	for ( int i = 0; i < 10; i++) {
		int aux;
		if ( i < 5 ) aux = 46;
		else if ( i >= 5) aux = 120;
		p1.tiley = aux+2;
		p2.tiley = aux;
		p3.tiley = aux;
		p4.tiley = aux+2;
		pat[0] = p1;
		pat[1] = p2;
		pat[2] = p3;
		pat[3] = p4;
		Enemy2[i].Init(false,pat);
		Enemy2[i].SetWidthHeight(32,32);
		Enemy2[i].SetTile(4+(i*2),aux);
		Enemy2[i].SetSpeed(1);
	}
	firstPatrol = false;
	firstTrap = false;
	secondPatrol = false;
		//Shoots init
	for (int i = 0; i < 100; ++i) {
		Shoot[i].SetWidthHeight(16,16);
		Shoot[i].SetSpeed(2);
		Shoot[i].SetActive(false);
	}
	for (int i = 0; i < 100; ++i) {
		Shoot2[i].SetWidthHeight(16,16);
		Shoot2[i].SetSpeed(2);
		Shoot2[i].SetActive(false);
	}
	for (int i = 0; i < 500; ++i) {
		EnemyShoot[i].SetWidthHeight(16,16);
		EnemyShoot[i].SetSpeed(2);
		EnemyShoot[i].SetActive(false);
	}
	shootCount = 0;
	shootCount2 = 0;
	enemyShootCount = 0;*/
}

bool cGame::Init()
{
	bool res=true;
	actualLevel = 1;
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

	player.SetPosition(4*1,6,4*-8);
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

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
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
		SetCursorPos(400,300);
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
		if(shoot.IsActive()) {
		shoot.Logic(terra);
		shoot.MoveUp(caixes,map,terra);
		cRect rect;
		shoot.GetArea(&rect);
		if(enemy.Collides(&rect) && enemy.IsAlive()) {
			shoot.SetActive(false);
			enemy.kill();
			this->NextLevel();
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
	if(keys['q']) {
		player.StrafeLeft(caixes, map);
	}
	if(keys['e']) {
		player.StrafeRight(caixes, map);
	}
	if(keys['w']) {
		player.MoveUp(caixes,map);
	}
	if(keys['s']) {
		player.MoveDown(caixes, map);
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
		player.GetPosition(&x,&y,&z);
		shoot.SetPosition(x,y+0.5,z);
		shoot.SetIner(0.2);
		//shoot.SetPosition();
		shoot.setRot(rotV,rot);
		shoot.SetActive(true);
	}
	if(keys['l']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if(keys['k']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

	float pos2[4] = {0,0, -2, 0.0};
			glLightfv(GL_LIGHT0, GL_POSITION, pos2);
	switch(camera) {
	case 1:
		
		glRotatef((-rotV),1,0,0);
		glRotatef((-rot),0,1,0);
		

		player.GetPosition(&x,&y,&z);
		glTranslatef(-x,-y,-z);
		
		break;
	case 2:
		gluLookAt(64,32,-16,0,0,-16,0,1,0);
		break;
	case 3:
		glTranslatef(0,-(1),-5);
		glRotatef((-rotV),1,0,0);
		glRotatef((-rot),0,1,0);
		
		//float x,y,z;
		player.GetPosition(&x,&y,&z);
		glTranslatef(-x-1,-y-1,-z-1);
		break;
	case 4:
		glTranslatef(0,-(2),-5);
		glRotatef((-rotV),1,0,0);
		glRotatef((-rot),0,1,0);
		
		//float x,y,z;
		shoot.GetPosition(&x,&y,&z);
		glTranslatef(-x,-y,-z);
		break;
	default:
		glTranslatef(0.0f,-2.0f,-40.0f);
		glRotatef(20,1.0f,0.0f,0.0f);
		break;
	}
		
	glBegin(GL_LINES);
	glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
	glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
	glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
	glEnd();
	glColor3f(1,1,1);
	//void gluSphere(GLUquadric *qobj,GLdouble radius,GLint slices,GLint stacks
				
	if(camera != 1) {
		shader.render();
		player.Draw();
		shader.norender();
		
	}
	if(enemy.IsAlive()) enemy.Draw(0,&Data);
	

	shader.render();

	Scene.Draw(&Data);
		
	shader.norender();
			/*glColor3f( 0.0f, 0.0f, 0.0f );
			glLineWidth(4.0f);
			glPolygonOffset( -1.0f, -1.0f );
			//caixes[k][i].DrawBB();
			Scene.Draw(&Data);*/
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glEnable( GL_POLYGON_OFFSET_LINE );      
			
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
	for(unsigned int k=0;k<3;++k) {
		for(unsigned int i=0;i<caixes[k].size();++i) {
			caixes[k][i].DrawBB();
		}
	}
	glColor3f( 1.0f, 1.0f, 1.0f );
	if (shoot.IsActive()) {
		//shoot.GetPosition(&x,&y,&z);
		//y+=0.1*sin(rotV*PI/180.0);
		//shoot.SetPosition(x,y,z);
		shoot.Draw();
		shoot.DrawBB();
	}
	if (enemy.IsAlive()) enemy.DrawBB();
	player.DrawBB();
	glColor3f(1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	if (camera == 3 || camera == 1) {
		Hud.DrawCrossHair(Data.GetID(IMG_CROSSHAIR),SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	}
	glLoadIdentity();
	Hud.Drawfps(Data.GetID(IMG_FONT), fps_dibuix, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);

	//shader.norender();
	glutSwapBuffers();
}
