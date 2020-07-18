#ifndef BMPLOADER_H
#define BMPLOADER_H

#include <string>
typedef unsigned char BYTE;

class BMPClass
{
public:
    BMPClass();
    ~BMPClass();
    BYTE& pixel(int x,int y,int c);
    void allocateMem();
    int width,height;
    BYTE* bytes;			//OpenGL formatted pixels
};

#define BMPError char
#define BMPNOTABITMAP 'b'	//Possible error flags
#define BMPNOOPEN 'o'
#define BMPFILEERROR 'f'
#define BMPBADINT 'i'
#define BMPNOERROR '\0'
#define BMPUNKNOWNFORMAT 'u'

//Loads the bmp in fname, and puts the data in bmp
BMPError BMPLoad(std::string fname,BMPClass& bmp);

//Translates my error codes into English
std::string TranslateBMPError(BMPError err);

#endif
