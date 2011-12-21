////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	MODEL.h
////////////////////////////////////////////////

/*
NOTE:
This file contains the structures used by the md2 file format.
Info Ripped from  a  tutorial somewhere.
*/

#ifndef MD2STRUCTS_H
#define MD2STRUCTS_H

#include "Glee.h"
#include <gl\glu.h>										// Header File For The GLu32 Library

////////////////////////////////////////////////
//MD2 STRUCTURES

//MD2HEADER structure
struct md2_header
{

	int indent;
	int version;
	int skinwidth;
	int skinheight;

	int framesize;

	int num_skins;
	int num_vertices;
	int num_st;
	int num_tris;
	int num_glcmds;
	int num_frames;

	int offset_skins;
	int offset_st;
	int offset_tris;
	int offset_frames;
	int offset_glcmds;
	int offset_end;

};

//3d vector used to load stuff
struct md2_vec3
{
	float coords[3];
};

//texture info
struct md2_texinfo
{
	char name[68];
};

//texture coords
struct md2_texcoords
{
	short s;
	short t;
};

//triangles
struct md2_tri
{
	unsigned short vertex[3];
	unsigned short st[3];
};

//vertices
struct md2_ver
{
	unsigned char v[3];
	unsigned char normalIndex;
};

//frames
struct md2_frame
{
	md2_vec3 scale;
	md2_vec3 translate;
	char name[16];
	md2_ver *verts;
};

/*
NOTE:	Uncompressing vertices

see paper...

*/



#endif MD2STRUCTS_H