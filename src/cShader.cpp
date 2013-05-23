#include "../inc/cShader.h"


using namespace std;


cShader::cShader(void)
{
}

cShader::~cShader(void)
{
}

void cShader::loadfromFile(char* vertexFile, char* fragmentFile) 
{
	load("vertexshader.txt");
}

unsigned long getFileLength(ifstream& file)
{
    if(!file.good()) return 0;
    
    unsigned long pos=file.tellg();
    file.seekg(0,ios::end);
    unsigned long len = file.tellg();
    file.seekg(ios::beg);
    
    return len;
}

int cShader::load(char* filename)
{
   ifstream file;
	file.open(filename, ios::in);
   if(!file) return -1;
    
   unsigned long len = getFileLength(file);
    
   if (len==0) return -2;   // "Empty File" 
    
   /*if (ShaderSource!=0)    // there is already a source loaded, free it!
   {
      if (_memalloc)
      delete[] ShaderSource;
   }*/
    
   ShaderSource = (GLubyte*) new char[len+1];
   //if (ShaderSource == 0) return -3;   // can't reserve memory
   //_memalloc = true;
     
   ShaderSource[len] = 0;  // len isn't always strlen cause some characters are stripped in ascii read...
                           // it is important to 0-terminate the real length later, len is just max possible value...
   unsigned int i=0;
   while (file.good())
   {
       ShaderSource[i] = file.get();       // get character from file.
       if (!file.eof())
        i++;
   }
    
   ShaderSource[i] = 0;  // 0 terminate it.
    
   file.close();
      
   return 0;
}