#include "../inc/cGame.h"
#include "../inc/Globals.h"


cGame::cGame(void) {}
cGame::~cGame(void){}

bool cGame::Init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
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
	Scene.Init();
	res = Scene.LoadLevel(1);
	if(!res) return false;

	player.SetPosition(8,6,-8);
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
	if(camera == 1) player.SetRot(rot);
	if(keys['q']) {
		player.StrafeLeft();
	}
	if(keys['e']) {
		player.StrafeRight();
	}
	if(keys['w']) {
		player.MoveUp();
	}
	if(keys['s']) {
		player.MoveDown();
	}
	if(keys['a']){ 
		if(camera != 1) player.AddRot(0.5);
	}
	if(keys['d']){
		if(camera != 1) player.AddRot(-0.5);
	}
	return res;
	//Game Logic
	//...
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Hud.DrawCrossHair(Data.GetID(IMG_CROSSHAIR),SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	switch(camera) {
	case 1:
		glRotatef((-rotV),1,0,0);
		glRotatef((-rot),0,1,0);
		
		float x,y,z;
		player.GetPosition(&x,&y,&z);
		glTranslatef(-x,-y,-z);
		break;
	case 2:
		gluLookAt(64,32,-16,0,0,-16,0,1,0);
		break;
	default:
		glTranslatef(0.0f,-2.0f,-40.0f);
		glRotatef(20,1.0f,0.0f,0.0f);
		break;
	}
	
	//void gluSphere(GLUquadric *qobj,GLdouble radius,GLint slices,GLint stacks);
	if(camera != 1) {
		player.Draw();
	}

	Scene.Draw(&Data);

	
	glutSwapBuffers();
}
