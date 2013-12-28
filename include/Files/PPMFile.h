/*   ppmRead.h
	 Read PPM images into memory for use by OpenGL
	 M. Wainer, 1999
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <glut.h>

class PPMFile{
private:
	static void skipComment(FILE *fin);
public:
	static GLubyte *readPPM(FILE *fin, GLsizei *wid, GLsizei *ht);
	static void savePPM(char ppmFileName[], unsigned char* pixels, int width, int height);
};