#include "Files/PPMFile.h"
#include <fstream>
#include <iostream>
#include <string>
/*-----------------------------------------------------------
 void skipComment(FILE *fin)
 PPM allows comment lines, this routine skips over comments
 fin points an already open (binary read) file
 ------------------------------------------------------------*/
void PPMFile::skipComment(FILE *fin)
{
	char buf[120]; // assumes at most 120 character comments
	
	while (1) {
	   fscanf_s(fin, "%1s", &buf);
	   if (buf[0] != '#') { ungetc(buf[0], fin); return; }
	   else fgets(buf, 120, fin); /* skip comment line */
	}
}


/*---------------------------------------------------------------------
GLubyte *readPPM(FILE *fin, GLsizei *wid, GLsizei *ht)
	PPM raw format uses no compression.  Each color is represented by a
	byte for each channel r,g,b.  Bytes are assumed to be unsigned.

	Space is allocated for the bytes based upon the width and height
	read in the file header.  For the most portable result with OpenGL
	and graphics cards, use power of 2 sizes for width and height.
	The width and height read in the header of the ppm image are passed
	back into wid and ht. A Null pointer is returned if there was an error
	otherwise a pointer to the image bytes is returned.
	When finished with the image you should free the allocated space.
	only ppm RAW FORMAT  is supported by this routine
	make sure the file is opened for binary read
 ----------------------------------------------------------------------*/
unsigned char* PPMFile::readPPM(FILE *fin, GLsizei *wid, GLsizei *ht)
{
	unsigned char* bytes;
	char cookie[3];
	int width, height, maxComp;
	int n, r,c;
  
	fscanf_s(fin, "%2s", &cookie);
	
	if (strcmp("P6", cookie)) return NULL; /* not right file type */
	PPMFile::skipComment(fin);
	fscanf_s(fin, "%d", &width); *wid = width;
	PPMFile::skipComment(fin);	
	fscanf_s(fin, "%d", &height); *ht = height;
	PPMFile::skipComment(fin);		
	fscanf_s(fin, "%d", &maxComp);
	
	if (maxComp > 255) return NULL; /* data error */
	fgetc(fin);	/* skip 1 character */
	
	n = width * height * 3;
	bytes = new unsigned char [n];
	if (bytes == NULL) return NULL; /* couldn't allocate space */
	
	// OpenGL stores images from bottom to top while PPM stores from
	// top to bottom, thus we start at the max row and work backwards
	for (r=height-1; r>=0; r--)
		for (c=0; c<width; c++) {
			bytes[3*(r*width + c)]   = fgetc(fin); // red byte
			bytes[3*(r*width + c)+1] = fgetc(fin); // green byte
			bytes[3*(r*width + c)+2] = fgetc(fin); // blue byte
		}
	
	return bytes;	
}


void PPMFile::savePPM(char ppmFileName[], unsigned char* pixels, int width, int height){
	unsigned char* save_pixels = new unsigned char[width*height*3];

	// don't quite understand why.... but it works ^^
	for(unsigned int y = 0; y < height; y++){
        for(unsigned int x = 0; x < width; x++){
			for (unsigned int rgb = 0; rgb < 3; rgb++){
				save_pixels[(x*3 + y*width*3) + rgb - 1] = pixels[(x + (height-y-1)*width) * 3 + rgb];
			}
		}    
    }
	FILE** ppmFile = new FILE*;
	fopen_s(ppmFile, ppmFileName, "w");

	if (*ppmFile != NULL) {
		fprintf(*ppmFile, "P6\n");
		fprintf(*ppmFile, "%d %d\n", width, height);
		fprintf(*ppmFile, "255\n");
		fwrite(save_pixels, sizeof(char), width * height*3, *ppmFile);
	
		fclose(*ppmFile);
	}
	/*
	FILE** ppmFile = new FILE*;
	fopen_s(ppmFile, ppmFileName, "w");

	if (*ppmFile != NULL) {
		fprintf(*ppmFile, "P6\n");
		fprintf(*ppmFile, "%d %d\n", width, height);
		fprintf(*ppmFile, "255\n");
		for (unsigned int y = 0; y < height; y++)
			for (unsigned int x = 0; x < width; x++)
				for (unsigned int rgb = 0; rgb < 3; rgb++)
					fwrite(&pixels[x + y*width + rgb], 1, 1, *ppmFile);
	
		fclose(*ppmFile);
	}*/
}