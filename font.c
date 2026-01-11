
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
static Rect upper_D[]={
    {1, 1, 2, 30}, //left line
	{1, 1, 12, 2}, //top line
	{13, 3, 2, 26}, //right
	{1, 29, 12, 2}, //bottom line
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
static Rect upper_V[]={
	{10, 16, 2, 15}, //right bottom line
	{4, 16, 2, 15}, //left bottom line
	{12, 1, 2, 15}, //right line
	{2, 1, 2, 15}, //left  line
	{4, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect upper_W[]={
	{1, 1, 2, 30}, //left line
	{1, 29, 14, 2}, //top line
	{7, 1, 2, 30}, //middle line
	{13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator	
};
static Rect upper_X[]={
	{1, 1, 2, 4}, //top left 1
	{3, 5, 2, 4}, //top left 2
	{5, 9, 2, 4}, //top left 3
	{13, 1, 2, 4},//top right 1
	{11, 5, 2, 4}, //top right 2
	{9, 9, 2, 4}, //top right 3
	{7, 13, 2, 6},//middle
	{1, 27, 2, 4},//bottom left 1
	{3, 23, 2, 4}, //bottom left 2
	{5, 19, 2, 4}, //bottom left 3
	{13, 27, 2, 4}, //bottom right 1
	{11, 23, 2, 4},//bottom right 2
	{9, 19, 2, 4}, //bottom right 3
	{-1, 0, 0, 0} //terminator
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
static Rect lower_K[]={
	{1,  1,  2, 30},//left line 
    {3, 13,  12,  2},//middle upper
    {13,  6,  2,  8},//upper line
    {3, 17,  12,  2},//middle lower
    {13, 17,  2, 14},//lower line
    {-1, 0,  0,  0}// terminator
};
static Rect lower_L[]={
    {1, 1, 8, 2}, //top line
    {1, 29, 14, 2}, //bottom line
	{7, 1, 2, 30}, //middle line
	{-1, 0, 0, 0} //terminator
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
static Rect lower_V[]={
	{10, 1+13, 2, 16}, //right bottom line
	{4, 1+13, 2, 16}, //left bottom line
	{4, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static Rect lower_W[]={
	{1, 16+13, 14, 2}, //bottom
    {1, 1+13, 2, 17}, //left line
    {7, 1+13, 2, 17}, //middle line
    {13, 1+13, 2, 17},//right line
	{-1,0,0,0} //terminator
};
static Rect lower_X[]={
	{1, 1+13, 2, 2}, //top left 1
	{3, 3+13, 2, 2}, //top left 2
	{5, 5+13, 2, 2}, //top left 3
	{13, 1+13, 2, 2},//top right 1
	{11, 3+13, 2, 2},//top right 2
	{9, 5+13, 2, 2},//top right 3
	{7, 7+13, 2, 5},//middle
	{1, 16+13, 2, 2}, //bottom left 1
	{3, 14+13, 2, 2}, //bottom left 2
	{5, 12+13, 2, 2}, //bottom left 3
	{13, 16+13, 2, 2}, //bottom right 1
	{11, 14+13, 2, 2}, //bottom right 2
	{9, 12+13, 2, 2}, //bottom right 3
	{-1, 0, 0, 0}
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
    {6, 27, 4, 4}, //dot
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
static Rect per[]={
    {11, 1, 2, 6}, //line 1
    {9, 7, 2, 6}, //line 2
    {7, 13, 2, 6}, //line 3
    {5, 19, 2, 6}, //line 4
    {3, 25, 2, 6}, //line 5
	{-1, 0, 0, 0} //terminator
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

Rect* ascii_map[128] = {
    ['A']=upper_A,//1
    ['B']=upper_B,//2
    ['C']=upper_C,//3
    ['D']=upper_D,//4
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
    ['O']=upper_O,//15
    ['P']=upper_P,//16
    ['Q']=upper_Q,//17
    ['R']=upper_R,//18
    ['S']=upper_S,//19
    ['T']=upper_T,//20
    ['U']=upper_U,//21
    ['V']=upper_V,//22
    ['W']=upper_W,//23
    ['X']=upper_X,//24
    ['Y']=upper_Y,//25
    ['Z']=upper_Z,//26
    //lowercase
    ['a']=lower_A,//27
    ['b']=lower_B,//28
    ['c']=lower_C,//29
    ['d']=lower_D,//30
    ['e']=lower_E,//30
    ['f']=lower_F,//32
    ['g']=lower_G,//33
    ['h']=lower_H,//34
    ['i']=lower_I,//35
    ['j']=lower_J,//36
    ['k']=lower_K,//37
    ['l']=lower_L,//38
    ['m']=lower_M,//39
    ['n']=lower_N,//40
    ['o']=lower_O,//41
    ['p']=lower_P,//42
    ['q']=lower_Q,//43
    ['r']=lower_R,//44
    ['s']=lower_S,//45
    ['t']=lower_T,//46
    ['u']=lower_U,//47
    ['v']=lower_V,//48
    ['w']=lower_W,//49
    ['x']=lower_X,//50
    ['y']=lower_Y,//51
    ['z']=lower_Z,//52
    //special
    ['-']=dash,//53
    ['+']=plus,//54
    ['?']=questionmark,//55
    [':']=double_dot,//56
    ['|']=line,//57
    ['{']=curly_shit_left,//58
    ['}']=curly_shit_right,//59
    ['_']=underscore,//60
    ['(']=bracket_left,//61
    [')']=bracket_right,//62
    ['*']=star,//63
    ['!']=exclamation,//64
    ['$']=dollar,//65
    ['.']=dot,//66
    ['/']=per,//67
    //Numerical
    ['1']=one,//68
    ['2']=twa,//69
    ['3']=three,//70
    ['4']=four,//71
    ['5']=five,//71
    ['6']=six,//73
    ['7']=seven,//74
    ['8']=eight,//75
    ['9']=hitler,//76
    ['0']=nulla,//77
};

//controller
static Rect up[]={
	{4, 1, 24, 22}, //block
	{8, 23, 16, 4}, //line 1
	{12 , 27, 8, 4}, //line 2
	{-1, 0, 0, 0} //terminator
};
static Rect down[]={
	{12, 1, 8, 4}, //line 1
	{8, 5, 16, 4}, //line 2
	{4, 9, 24, 22}, //block
	{-1, 0, 0, 0} //terminator
};
static Rect left[]={
	{1, 10, 10, 12},//block
	{11, 12, 2, 8},//line 1
	{13, 14, 2, 4},//line 2
	{-1, 0, 0, 0}//terminator
};
static Rect right[]={
	{1, 14, 2, 4},//line 1
	{3, 12, 2, 8},//line 2
	{5, 10, 10, 12},//block
	{-1, 0, 0, 0}//terminator
};
static Rect select[]={
	{1, 12, 14, 8}, //block
	{-1, 0, 0, 0}//terminator
};

Rect* icon_map[128]={
	['\x00']=up,
	
};
