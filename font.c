
#include "font.h"

static Rect upper_A[] = {
    {1, 2, 2, 28}, //left leg
    {1, 30, 1, 1}, //left leg dot
    {13, 2, 2, 28}, //right leg
    {14, 30, 1, 1}, //right leg dot
    {2, 1 ,12, 2}, //top bar
    {3, 13, 8, 2}, //middle bar
    {-1, 0, 0, 0}//terminator
};

static Rect upper_B[] = {
    {1, 2, 2, 28}, //left line
    {2, 1, 12, 2}, //top line
    {13, 2, 2, 9}, //top right line
    {12, 10, 2, 2}, //top right block
    {11, 11, 2, 4}, //middle block
    {5, 12, 6, 2}, //middle line
    {12, 14, 2, 2}, //bottom right block
    {13, 15, 2, 15},  //bottom right line
    {2, 29, 12, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};

static Rect upper_E[] = {
    {1, 2, 2, 28}, //left line
    {2, 1, 12, 2}, //top line
    {14, 2, 1, 1}, //top dot
    {3, 12, 11, 2}, //middle line
    {14, 13, 1, 1}, //middle dot
    {2, 29, 12, 2}, //bottom line
    {14, 30, 1, 1}, //bottom dot
    {-1, 0, 0, 0} //terminator
};

static Rect upper_F[] = {
    {1, 2, 2, 28}, //left line
    {2, 30, 1, 1}, //left dot
    {2, 1, 12, 2}, //top line
    {14, 2, 1, 1}, //top dot
    {3, 12, 11, 2}, //middle line
    {14, 13, 1, 1}, //top dot
    {-1, 0, 0, 0} //terminator
};


static Rect upper_H[]={
	{1, 2, 2, 28}, //left line
	{1, 1, 1, 1}, //left dot top
	{1, 30, 1, 1}, //left dot bottom
    {3, 12, 10, 2}, //middle line
    {13, 2, 2, 28}, //right line
	{14, 1, 1, 1}, //right dot top
	{14, 30, 1, 1}, //right dot bottom
	{-1, 0, 0, 0}//terminator
};


static Rect upper_N_backup[]={
	{1, 2, 2, 28}, //left line
	{2, 30, 1, 1}, //left dot
	{2, 1, 4, 2}, //top line
	{5, 2, 2, 6}, //1st band
	{6, 7, 2, 7}, //2nd band
	{7, 13, 2, 7}, //3rd band
	{8, 19, 2, 6}, //4th band
	{9, 24, 2, 6}, //5th band
	{10, 29, 4, 2}, //bottom line
	{13, 2, 2, 28}, //right line
	{13, 1, 1, 1}, //right dot
	{-1, 0, 0, 0}//terminator
	
	
	
};

static Rect upper_N[]={
	{1, 2, 2, 28}, //left line
	{2, 30, 1, 1}, //left dot
	{2, 1, 6, 2}, //top line
	{7, 2, 2, 28}, //1st band
	//{9, 10, 2, 8}, //5th band
	{8, 29, 6, 2}, //bottom line
	{13, 2, 2, 28}, //right line
	{13, 1, 1, 1}, //right dot
	{-1, 0, 0, 0}//terminator
	
	
	
};


static Rect upper_R[] = {
    {1, 2, 2, 28}, //left side
    {2, 1, 12, 2}, //top line
    {13, 2, 2, 9}, //top right line
    {12, 10, 2, 2}, //top right block
    {11, 11, 2, 4}, //middle block
    {5, 12, 6, 2}, //middle line
    {12, 14, 2, 2}, //bottom right block
    {13, 15, 2, 15},  //bottom right line
    {-1, 0, 0, 0} //terminator
};




Rect* font_map[128] = {
    ['A']=upper_A,
    ['B']=upper_B,
    NULL,
    NULL,
    ['E']=upper_E,
    ['F']=upper_F,
    NULL,
    ['H']=upper_H,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ['N']=upper_N,
    NULL, 
    NULL,
    NULL,
    ['R']=upper_R,
    NULL,
    NULL,
};
