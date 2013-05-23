#include "../inc/cHud.h"


cHud::cHud(void)
{
}
cHud::~cHud(void)
{
}

void cHud::DrawHearts(int tex_id,int life, int d)
{	
	for(int i=0;i<life;i++) {
		glPushMatrix();
		glTranslatef(0, 420+d-32*i, 0.);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,tex_id);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1); glVertex2i(16,16);
			glTexCoord2f(1,1); glVertex2i(48,16);
			glTexCoord2f(1,0); glVertex2i(48,48);
			glTexCoord2f(0,0); glVertex2i(16,48);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}

void cHud::DrawCrossHair(int tex_id, int x, int y) {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef((x-16), (y-16), -0.5);
	//glTranslatef(0, 0, -0.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1); glVertex2i(0,0);
		glTexCoord2f(1,1); glVertex2i(32,0);
		glTexCoord2f(1,0); glVertex2i(32,32);
		glTexCoord2f(0,0); glVertex2i(0,32);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void cHud::DrawPrepareToFight(int tex_id, int d) {
	int step_x,step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	//writing punts:
	string aux = "prepare";
	int n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		//Draw50(tex_id,tx,ty,step_x,step_y,160.+50.*i,240+d);
	}
	aux = "to";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		//Draw50(tex_id,tx,ty,step_x,step_y,152.+50.*i,190+d);
	}
	aux = "fight";
	n = aux.size();
	for(int i=0;i<n;i++) {
		step_x = (aux[i]-'a')+33;
		step_y = step_x/10;
		step_x = step_x%10;
		//Draw50(tex_id,tx,ty,step_x,step_y,268.+50.*i,190+d);
	}
}

void cHud::Drawfps(int tex_id,int p, int x,int y) {
	stringstream ss;
	ss << p;
	string points = ss.str();
	int step_x, step_y;
	float tx,ty;
	tx = 1./16.;
	ty = 1./8.;
	int n = points.size();
	for(int i=0;i<n;i++) {
		step_x = (points[i]-'0')+16;
		step_y = step_x/10;
		step_x = step_x%10;
		//Draw(tex_id,tx,ty,step_x,step_y, x-20*3,y-20*3);
		//Draw(tex_id,tx,ty,step_x,step_y, x-100*i,x-100);
		Draw(tex_id,tx,ty,step_x,step_y, (x/1.5)+20*i,y/1.5);
	}
}

void cHud::Draw(int tex_id, float tx,float ty, int step_x,int step_y,float trans_x, float trans_y) {
			glPushMatrix();
			glTranslatef(trans_x,trans_y,-0.5);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,tex_id);
			glBegin(GL_QUADS);
				glTexCoord2f(tx*step_x,ty*(step_y+1));		glVertex2i(0,0);
				glTexCoord2f(tx*(step_x+1),ty*(step_y+1));	glVertex2i(20,0);
				glTexCoord2f(tx*(step_x+1),ty*step_y);		glVertex2i(20,20);
				glTexCoord2f(tx*step_x,ty*step_y);			glVertex2i(0,20);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		    glPopMatrix();
}


