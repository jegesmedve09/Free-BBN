
#include "font.h"


//UPPERCASE
static Rect upper_A[] = {
    {1, 1, 2, 30}, //left leg
    {13, 1, 2, 30}, //right leg
    {1, 1 ,14, 2}, //top bar
    {1, 13, 14, 2}, //middle bar
    {-1, 0, 0, 0}//terminator
};
static Rect upper_B[] = {
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {13, 1, 2, 11}, //top right line
    {12, 10, 2, 2}, //top right block
    {11, 11, 2, 4}, //middle block
    {5, 12, 6, 2}, //middle line
    {12, 14, 2, 2}, //bottom right block
    {13, 15, 2, 15},  //bottom right line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static Rect upper_C[] = {
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static Rect upper_E[] = {
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 12, 14, 2}, //middle line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static Rect upper_F[] = {
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 12, 14, 2}, //middle line
    {-1, 0, 0, 0} //terminator
};
static Rect upper_G[]={
	{1, 1, 2, 30}, //left line
	{1, 1, 14, 2}, //top line	
	{1, 29, 14, 2}, //bottom line
    {13, 12, 2, 19},  //right line
    {9, 12, 6, 2}, //middle line
	{-1, 0, 0 ,0} //terminator
};
static Rect upper_H[]={
	{1, 1, 2, 30}, //left line
    {1, 12, 14, 2}, //middle line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator
};
static Rect upper_I[]={
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
	{7, 1, 2, 30}, //middle line
	{-1, 0, 0, 0} //terminator
};
static Rect upper_J[]={
    {13, 1, 2, 30}, //right line
    {1, 29, 14, 2}, //bottom line
    {1, 18, 2, 12}, //left line
	{-1, 0, 0, 0} //terminator
};
static Rect upper_K[]={
	{1, 1, 2, 30}, //left line
    {1, 12, 14, 2}, //middle line
    {13, 12, 2, 19},  //right line
    {9, 1, 2, 13}, //idk what the fuck to call this
	{-1, 0, 0, 0} //terminator
};
static Rect upper_L[]={
    {1, 1, 2, 30}, //left line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect upper_N[]={
	{1, 1, 2, 30}, //left line
	{1, 1, 8, 2}, //top line
	{7, 1, 2, 30}, //middle line
	{7, 29, 8, 2}, //bottom line
	{13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator	
};
static Rect upper_O[]={
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0 ,0} //terminator
};
static Rect upper_P[] = {
    {1, 1, 2, 30}, //left side
    {1, 1, 14, 2}, //top line
    {13, 1, 2, 13}, //right line
    {1, 12, 14, 2}, //middle line
    {-1, 0, 0, 0} //terminator
};
static Rect upper_Q[]={
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
    {9, 22, 2, 10},  //right line
	{-1, 0, 0 ,0} //terminator
};
static Rect upper_R[] = {
    {1, 1, 2, 30}, //left side
    {1, 1, 14, 2}, //top line
    {13, 1, 2, 10}, //top right line
    {12, 10, 2, 2}, //top right block
    {11, 11, 2, 4}, //middle block
    {1, 12, 10, 2}, //middle line
    {12, 14, 2, 2}, //bottom right block
    {13, 15, 2, 16},  //bottom right line
    {-1, 0, 0, 0} //terminator
};
static Rect upper_S[]={
    {1, 1, 14, 2}, //top line
    {1, 1, 2, 13}, //left line
    {1, 12, 14, 2}, //middle line
    {13, 12, 2, 19},  //right line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect upper_T[]={
    {1, 1, 14, 2}, //top line
	{7, 1, 2, 30}, //middle line
	{-1, 0, 0, 0} //terminator
};
static Rect upper_U[]={
    {1, 1, 2, 30}, //left line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0 ,0} //terminator
};
static Rect upper_Y[]={
    {1, 1, 2, 13}, //left line
    {13, 1, 2, 13}, //right line
    {1, 12, 14, 2}, //middle line
	{7, 12, 2, 19}, //middle line
	{-1, 0, 0, 0} //terminator
};


//LOWERCASE
static Rect lower_A[]={
	{},
	{-1,0,0,0} //terminator
};


//SPECIAL
static Rect dash[]={
	{1, 16, 14, 2}, //obvious
	{-1, 0, 0, 0} //terminator
};

Rect* font_map[128] = {
    ['A']=upper_A,
    ['B']=upper_B,
    ['C']=upper_C,
    NULL,
    ['E']=upper_E,
    ['F']=upper_F,
    ['G']=upper_G,
    ['H']=upper_H,
    ['I']=upper_I,
    ['J']=upper_J,
    ['K']=upper_K,
    ['L']=upper_L,
    NULL,
    ['N']=upper_N,
    ['O']=upper_O, 
    ['P']=upper_P,
    ['Q']=upper_Q,
    ['R']=upper_R,
    ['S']=upper_S,
    ['T']=upper_T,
    ['U']=upper_U,
    NULL,
    ['Y']=upper_Y,
    //special
    ['-']=dash,
};
