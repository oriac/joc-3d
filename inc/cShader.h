#pragma once

#pragma comment(lib,"lib/glew32d")
#pragma comment(lib,"lib/glew32sd")

#include "../gl/glew.h"
#include "../inc/globals.h"
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class cShader
{
public:
	cShader(void);
	~cShader(void);
	void loadfromFile();
	void render();
	void norender();
private:
	int load(char* filename);
	GLubyte* ShaderSource;
	GLuint vshader;
	GLuint fshader;
	GLuint programa;
};