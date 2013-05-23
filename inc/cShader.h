#pragma once

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
	void loadfromFile(char* vertexFile, char* fragmentFile);
private:
	int load(char* filename);
	GLubyte*   ShaderSource;
};