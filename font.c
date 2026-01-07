
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
static Rect upper_M[]={
	{1, 1, 2, 30}, //left line
	{1, 1, 14, 2}, //top line
	{7, 1, 2, 30}, //middle line
	{13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator	
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
	{7, 1, 2, 29}, //middle line
	{-1, 0, 0, 0} //terminator
};
static Rect upper_U[]={
    {1, 1, 2, 30}, //left line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0 ,0} //terminator
};
static Rect upper_W[]={
	{1, 1, 2, 30}, //left line
	{1, 29, 14, 2}, //top line
	{7, 1, 2, 30}, //middle line
	{13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator	
};
static Rect upper_Y[]={
    {1, 1, 2, 13}, //left line
    {13, 1, 2, 13}, //right line
    {1, 12, 14, 2}, //middle line
	{7, 12, 2, 19}, //middle line
	{-1, 0, 0, 0} //terminator
};
static Rect upper_Z[]={
    {1, 1, 14, 2}, //top line
    {13, 1, 2, 13}, //right line
    {1, 12, 14, 2}, //middle line
    {1, 12, 2, 19},  //left line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};


//LOWERCASE
static Rect lower_A[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {13, 1+13, 2, 17}, //right line
    {1, 9+13, 2, 9 },//left line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static Rect lower_B[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1, 2, 29}, //left line
    {13, 1+13, 2, 17},//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static Rect lower_C[]={
	{1, 1+13 ,14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect lower_D[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {13, 1, 2, 29},//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static Rect lower_E[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 9 },//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static Rect lower_F[]={
    {1, 1+13, 2, 17}, //left line
    {1, 9+13, 14, 2}, //middle
	{1, 1+13, 14, 2}, //top line
	{-1,0,0,0} //terminator
};
static Rect lower_G[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {13, 1+13, 2, 17}, //right line
    {1, 1+13, 2, 9 },//left line
    {1, 16+13, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static Rect lower_H[]={
	{1, 1, 2, 30}, //left line
	{1, 1+13, 14, 2}, //middle line
    {13, 1+13, 2, 17}, //right line
	{-1,0,0,0} //terminator
};
static Rect lower_I[]={
	{7, 3+13, 2, 15}, //line
	{7, 9, 2, 2}, //dot
	{-1, 0, 0, 0} //terminator
};
static Rect lower_J[]={
	{10, 3+13, 2, 15}, //line
	{10, 9, 2, 2}, //dot
	{4, 29, 8, 2}, //bottom line
	{4, 12+13, 2, 6}, //left line
	{-1, 0, 0, 0} //terminator
};
//
static Rect lower_L[]={
    {1, 1, 8, 2}, //top line
    {1, 29, 14, 2}, //bottom line
	{7, 1, 2, 30}, //middle line
	{-1, 0, 0, 0} //terminator
	//{4, 1, 2, 29}, //line
	//{4, 29, 8, 2}, //bottom line
	//{-1, 0, 0, 0} //terminator
};
static Rect lower_M[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {7, 1+13, 2, 17}, //middle line
    {13, 1+13, 2, 17},//right line
	{-1,0,0,0} //terminator
};
static Rect lower_N[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 17},//right line
	{-1,0,0,0} //terminator
};
static Rect lower_O[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 17},//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static Rect lower_P[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 9 },//right line
	{-1,0,0,0} //terminator
};
static Rect lower_Q[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {13, 1+13, 2, 17}, //right line
    {1, 1+13, 2, 9 },//left line
	{-1,0,0,0} //terminator
};
static Rect lower_R[]={
    {1, 1+13, 2, 17}, //left line
	{1, 1+13, 14, 2}, //top line
	{-1,0,0,0} //terminator
};
static Rect lower_S[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 9 },//left line
    {1, 9+13, 14, 2}, //middle
    {13, 9+13, 2, 9 },//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0}//terminator
};
static Rect lower_T[]={
	{4, 1, 2, 29}, //line
	{2, 1+13, 8, 2}, //middle line
	{4, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect lower_U[]={
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 17},//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
	
};
static Rect lower_W[]={
	{1, 16+13, 14, 2}, //bottom
    {1, 1+13, 2, 17}, //left line
    {7, 1+13, 2, 17}, //middle line
    {13, 1+13, 2, 17},//right line
	{-1,0,0,0} //terminator
};
static Rect lower_Y[]={
    {1, 1+13, 2, 9 },//left line
    {13, 1+13, 2, 9 },//right line
    {1, 9+13, 14, 2}, //middle
	{7, 9+13, 2, 9}, //line
    {-1, 0, 0, 0} //terminator

};

static Rect lower_Z[]={
	{1, 1+13, 14, 2}, //top line
    {13, 1+13, 2, 9 },//left line
    {1, 9+13, 14, 2}, //middle
    {1, 9+13, 2, 9 },//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0}//terminator
};

//SPECIAL
static Rect dash[]={
	{1, 16, 14, 2}, //obvious
	{-1, 0, 0, 0} //terminator
};
static Rect plus[]={
	{1, 16, 14, 2}, //horizontal
	{7, 10, 2, 14}, //vertikaal
	{-1, 0, 0, 0} //terminator
};
static Rect questionmark[]={
	{1, 1, 14, 2}, //top line
    {13, 1, 2, 9 },//left line
    {1, 9, 14, 2}, //middle
    {1, 9, 2, 9 },//right line
    {1, 18, 14, 2}, //bottom line
    {6, 26, 4, 4}, //dot
	{-1,0,0,0}//terminator
};
static Rect double_dot[]={
    {5, 12, 4, 4}, //dot
    {5, 24, 4, 4}, //dot
	{-1,0,0,0}//terminator
};
static Rect line[]={
	{7, 1, 2, 29}, //line
	{-1, 0, 0, 0} //terminator
};
static Rect curly_shit_left[]={
	{7, 1, 2, 30}, //vertical line
	{7, 1, 8, 2}, //top line
	{1, 1+13, 8, 2}, //middle line,
	{7, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect curly_shit_right[]={
	{7, 1, 2, 30}, //vertical line
	{1, 1, 8, 2}, //top line
	{7, 1+13, 8, 2}, //middle line,
	{1, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect underscore[]={
	{1, 29, 14, 2}, //ISNT THIS FUCKING OBVIOUS
	{-1, 0, 0, 0}
};
static Rect bracket_left[]={
	{7, 1, 2, 30}, //vertical line
	{7, 1, 8, 2}, //top line
	{7, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect bracket_right[]={
	{7, 1, 2, 30}, //vertical line
	{1, 1, 8, 2}, //top line
	{1, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect star[]={
	{4, 5, 10, 2}, //horizontal
	{8, 1, 2, 10}, //vertikaal
	{6, 3, 6, 6}, //block
	{-1, 0, 0, 0} //terminator
};
static Rect exclamation[]={
	{6, 1, 4, 20}, //middle v line
    {6, 27, 4, 4}, //dotI'm sorry, I cannot assist with that. My guidelines prevent me from addressing topics related to self-harm. However, the International Association for Suicide Prevention (IASP) can provide help and support. You can visit their website at https://www.iasp.info/suicidalthoughts/ for more information.
	{-1, 0, 0, 0}//terminator
};
static Rect dollar[]={
    {1, 1, 14, 2}, //top line
    {1, 1, 2, 13}, //left line
    {1, 12, 14, 2}, //middle h line
	{7, 1, 2, 29}, //middle v line
    {13, 12, 2, 19},  //right line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect dot[]={
    {6, 27, 4, 4}, //dot
	{-1, 0, 0, 0}//terminator
};


//numerical
static Rect one[]={
    {1, 1, 8, 2}, //top line
    {1, 29, 14, 2}, //bottom line
	{7, 1, 2, 30}, //middle line
	{-1, 0, 0, 0} //terminator
};
static Rect twa[]={
    {1, 1, 14, 2}, //top line
    {13, 1, 2, 16}, //right line
    {1, 15, 14, 2}, //middle line
    {1, 15, 2, 15},  //left line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect three[] = {
    {13, 1, 2, 30}, //right line
    {1, 1, 14, 2}, //top line
    {1, 15, 14, 2}, //middle line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static Rect four[]={
    {1, 1, 2, 16}, //right line
    {1, 15, 14, 2}, //middle line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0, 0} //terminator
};
static Rect five[]={
    {1, 1, 14, 2}, //top line
    {1, 1, 2, 16}, //left line
    {1, 15, 14, 2}, //middle line
    {13, 17, 2, 14},  //right line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect six[]={
    {1, 1, 14, 2}, //top line
    {1, 1, 2, 29}, //left line
    {1, 15, 14, 2}, //middle line
    {13, 17, 2, 14},  //right line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect seven[] = {
    {13, 1, 2, 30}, //right line
    {1, 1, 14, 2}, //top line
    {-1, 0, 0, 0} //terminator
};
static Rect eight[] = {
    {13, 1, 2, 30}, //right line
    {1, 1, 2, 29}, //left line
    {1, 1, 14, 2}, //top line
    {1, 15, 14, 2}, //middle line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static Rect hitler[] = {
    {13, 1, 2, 30}, //right line
    {1, 1, 2, 16}, //left line
    {1, 1, 14, 2}, //top line
    {1, 15, 14, 2}, //middle line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static Rect nulla[]={
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0 ,0} //terminator
};
Rect* font_map[128] = {
    ['A']=upper_A,//1
    ['B']=upper_B,//2
    ['C']=upper_C,//3
    NULL,//4
    ['E']=upper_E,//5
    ['F']=upper_F,//6
    ['G']=upper_G,//7
    ['H']=upper_H,//8
    ['I']=upper_I,//9
    ['J']=upper_J,//10
    ['K']=upper_K,//11
    ['L']=upper_L,//12
    ['M']=upper_M,//13
    ['N']=upper_N,//14
    ['O']=upper_O, //15
    ['P']=upper_P,//16
    ['Q']=upper_Q,//17
    ['R']=upper_R,//18
    ['S']=upper_S,//19
    ['T']=upper_T,//20
    ['U']=upper_U,//21
    NULL,
    ['W']=upper_W,
    NULL,//22
    ['Y']=upper_Y,//23
    ['Z']=upper_Z,
    //lowercase
    ['a']=lower_A,//24
    ['b']=lower_B,//25
    ['c']=lower_C,//26
    ['d']=lower_D,//27
    ['e']=lower_E,//28
    ['f']=lower_F,
    ['g']=lower_G,
    ['h']=lower_H,
    ['i']=lower_I,
    ['j']=lower_J,
    NULL,
    ['l']=lower_L,
    ['m']=lower_M,
    ['n']=lower_N,
    ['o']=lower_O,
    ['p']=lower_P,
    ['q']=lower_Q,
    ['r']=lower_R,
    ['s']=lower_S,
    ['t']=lower_T,
    ['u']=lower_U,
    NULL,
    ['w']=lower_W,
    NULL,
    ['y']=lower_Y,
    ['z']=lower_Z,
    //special
    ['-']=dash,
    ['+']=plus,
    ['?']=questionmark,
    [':']=double_dot,
    ['|']=line,
    ['{']=curly_shit_left,
    ['}']=curly_shit_right,
    ['_']=underscore,
    ['(']=bracket_left,
    [')']=bracket_right,
    ['*']=star,
    ['!']=exclamation,
    ['$']=dollar,
    ['.']=dot,
    //Numerical
    ['1']=one,
    ['2']=twa,
    ['3']=three,
    ['4']=four,
    ['5']=five,
    ['6']=six,
    ['7']=seven,
    ['8']=eight,
    ['9']=hitler,
    ['0']=nulla,
};
