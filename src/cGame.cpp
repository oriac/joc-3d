#include "../inc/cGame.h"
#include "../inc/Globals.h"


cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	bool res=true;
	time_init=glutGet(GLUT_ELAPSED_TIME);
	fps = fps_dibuix = 0;
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_CULL_FACE);
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
	Scene.Init();
	res = Scene.LoadLevel(1,caixes);
	map = Scene.GetMap();
	if(!res) return false;

	player.SetPosition(8,6,-8);
	player.SetVol(2,2,2);
	shoot.SetVol(0.4,0.4,0.4);
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
		shoot.Logic(caixes);
		shoot.MoveUp(caixes,map);
	}

	
	//Process Input
	rot-=(x2-x1);
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
	if(camera == 1 || camera == 3) player.SetRot(rot);
	if(keys['q']) {
		player.StrafeLeft();
	}
	if(keys['e']) {
		player.StrafeRight();
	}
	if(keys['w']) {
		player.MoveUp(caixes,map);
	}
	if(keys['s']) {
		player.MoveDown();
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
	player.Logic(caixes);
	
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
	float x,y,z;

	glLoadIdentity();
	
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
		glTranslatef(0,-(2),-10);
		glRotatef((-rotV),1,0,0);
		glRotatef((-rot),0,1,0);
		
		//float x,y,z;
		player.GetPosition(&x,&y,&z);
		glTranslatef(-x-1,-y-1,-z-1);
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
	//void gluSphere(GLUquadric *qobj,GLdouble radius,GLint slices,GLint stacks);
	if(camera != 1) {
		player.Draw();
	}
	
	Scene.Draw(&Data);
	for(unsigned int i=0;i<caixes.size();++i) {
		caixes[i].DrawBB();
	}
	
	if (shoot.IsActive()) {
		//shoot.GetPosition(&x,&y,&z);
		//y+=0.1*sin(rotV*PI/180.0);
		//shoot.SetPosition(x,y,z);
		shoot.Draw();
		shoot.DrawBB();
	}
	player.DrawBB();
	glColor3f(1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	Hud.DrawCrossHair(Data.GetID(IMG_CROSSHAIR),SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	glLoadIdentity();
	Hud.Drawfps(Data.GetID(IMG_FONT), fps_dibuix, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}
