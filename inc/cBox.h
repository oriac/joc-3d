#pragma once
#include "../inc/cBicho.h"


class cBox:public cBicho
{
public:
	cBox(void);
	cBox(float x,float y,float z, float w,float h,float d);
	~cBox(void);
};

