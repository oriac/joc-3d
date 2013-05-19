#include "../inc/cBox.h"


cBox::cBox(void)
{
}

cBox::cBox(float x,float y,float z, float w,float h,float d) {
	SetPosition(x,y,z);
	SetVol(w,h,d);
}


cBox::~cBox(void)
{
}
