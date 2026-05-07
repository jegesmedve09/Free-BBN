
#include "font.h"

//UPPERCASE
static const Rect upper_A[] = {
    {1, 1, 2, 30}, //left leg
    {13, 1, 2, 30}, //right leg
    {1, 1 ,14, 2}, //top bar
    {1, 13, 14, 2}, //middle bar
    {-1, 0, 0, 0}//terminator
};
static const Rect upper_B[] = {
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
static const Rect upper_C[] = {
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static const Rect upper_D[]={
    {1, 1, 2, 30}, //left line
	{1, 1, 12, 2}, //top line
	{13, 3, 2, 26}, //right
	{1, 29, 12, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_E[] = {
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 12, 14, 2}, //middle line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static const Rect upper_F[] = {
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 12, 14, 2}, //middle line
    {-1, 0, 0, 0} //terminator
};
static const Rect upper_G[]={
	{1, 1, 2, 30}, //left line
	{1, 1, 14, 2}, //top line	
	{1, 29, 14, 2}, //bottom line
    {13, 12, 2, 19},  //right line
    {9, 12, 6, 2}, //middle line
	{-1, 0, 0 ,0} //terminator
};
static const Rect upper_H[]={
	{1, 1, 2, 30}, //left line
    {1, 12, 14, 2}, //middle line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator
};
static const Rect upper_I[]={
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
	{7, 1, 2, 30}, //middle line
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_J[]={
    {13, 1, 2, 30}, //right line
    {1, 29, 14, 2}, //bottom line
    {1, 18, 2, 12}, //left line
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_K[]={
	{1, 1, 2, 30}, //left line
    {1, 12, 14, 2}, //middle line
    {13, 12, 2, 19},  //right line
    {9, 1, 2, 13}, //idk what the fuck to call this
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_L[]={
    {1, 1, 2, 30}, //left line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_M[]={
	{1, 1, 2, 30}, //left line
	{1, 1, 14, 2}, //top line
	{7, 1, 2, 30}, //middle line
	{13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator	
};
static const Rect upper_N[]={
	{1, 1, 2, 30}, //left line
	{1, 1, 8, 2}, //top line
	{7, 1, 2, 30}, //middle line
	{7, 29, 8, 2}, //bottom line
	{13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator	
};
static const Rect upper_O[]={
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0 ,0} //terminator
};
static const Rect upper_P[] = {
    {1, 1, 2, 30}, //left side
    {1, 1, 14, 2}, //top line
    {13, 1, 2, 13}, //right line
    {1, 12, 14, 2}, //middle line
    {-1, 0, 0, 0} //terminator
};
static const Rect upper_Q[]={
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
    {9, 22, 2, 10},  //right line
	{-1, 0, 0 ,0} //terminator
};
static const Rect upper_R[] = {
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
static const Rect upper_S[]={
    {1, 1, 14, 2}, //top line
    {1, 1, 2, 13}, //left line
    {1, 12, 14, 2}, //middle line
    {13, 12, 2, 19},  //right line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_T[]={
    {1, 1, 14, 2}, //top line
	{7, 1, 2, 29}, //middle line
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_U[]={
    {1, 1, 2, 30}, //left line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0 ,0} //terminator
};
static const Rect upper_V[]={
	{10, 16, 2, 15}, //right bottom line
	{4, 16, 2, 15}, //left bottom line
	{12, 1, 2, 15}, //right line
	{2, 1, 2, 15}, //left  line
	{4, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_W[]={
	{1, 1, 2, 30}, //left line
	{1, 29, 14, 2}, //top line
	{7, 1, 2, 30}, //middle line
	{13, 1, 2, 30}, //right line
	{-1, 0, 0, 0}//terminator	
};
static const Rect upper_X[]={
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
static const Rect upper_Y[]={
    {1, 1, 2, 13}, //left line
    {13, 1, 2, 13}, //right line
    {1, 12, 14, 2}, //middle line
	{7, 12, 2, 19}, //middle line
	{-1, 0, 0, 0} //terminator
};
static const Rect upper_Z[]={
    {1, 1, 14, 2}, //top line
    {13, 1, 2, 13}, //right line
    {1, 12, 14, 2}, //middle line
    {1, 12, 2, 19},  //left line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
//LOWERCASE
static const Rect lower_A[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {13, 1+13, 2, 17}, //right line
    {1, 9+13, 2, 9 },//left line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static const Rect lower_B[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1, 2, 29}, //left line
    {13, 1+13, 2, 17},//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static const Rect lower_C[]={
	{1, 1+13 ,14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect lower_D[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {13, 1, 2, 29},//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static const Rect lower_E[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 9 },//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static const Rect lower_F[]={
    {1, 1+13, 2, 17}, //left line
    {1, 9+13, 14, 2}, //middle
	{1, 1+13, 14, 2}, //top line
	{-1,0,0,0} //terminator
};
static const Rect lower_G[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {13, 1+13, 2, 17}, //right line
    {1, 1+13, 2, 9 },//left line
    {1, 16+13, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static const Rect lower_H[]={
	{1, 1, 2, 30}, //left line
	{1, 1+13, 14, 2}, //middle line
    {13, 1+13, 2, 17}, //right line
	{-1,0,0,0} //terminator
};
static const Rect lower_I[]={
	{7, 3+13, 2, 15}, //line
	{7, 9, 2, 2}, //dot
	{-1, 0, 0, 0} //terminator
};
static const Rect lower_J[]={
	{10, 3+13, 2, 15}, //line
	{10, 9, 2, 2}, //dot
	{4, 29, 8, 2}, //bottom line
	{4, 12+13, 2, 6}, //left line
	{-1, 0, 0, 0} //terminator
};
static const Rect lower_K[]={
	{1,  1,  2, 30},//left line 
    {3, 13,  12,  2},//middle upper
    {13,  6,  2,  8},//upper line
    {3, 17,  12,  2},//middle lower
    {13, 17,  2, 14},//lower line
    {-1, 0,  0,  0}// terminator
};
static const Rect lower_L[]={
    {1, 1, 8, 2}, //top line
    {1, 29, 14, 2}, //bottom line
	{7, 1, 2, 30}, //middle line
	{-1, 0, 0, 0} //terminator
};
static const Rect lower_M[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {7, 1+13, 2, 17}, //middle line
    {13, 1+13, 2, 17},//right line
	{-1,0,0,0} //terminator
};
static const Rect lower_N[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 17},//right line
	{-1,0,0,0} //terminator
};
static const Rect lower_O[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 17},//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static const Rect lower_P[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 9 },//right line
	{-1,0,0,0} //terminator
};
static const Rect lower_Q[]={
	{1, 1+13, 14, 2}, //top line
    {1, 9+13, 14, 2}, //middle
    {13, 1+13, 2, 17}, //right line
    {1, 1+13, 2, 9 },//left line
	{-1,0,0,0} //terminator
};
static const Rect lower_R[]={
    {1, 1+13, 2, 17}, //left line
	{1, 1+13, 14, 2}, //top line
	{-1,0,0,0} //terminator
};
static const Rect lower_S[]={
	{1, 1+13, 14, 2}, //top line
    {1, 1+13, 2, 9 },//left line
    {1, 9+13, 14, 2}, //middle
    {13, 9+13, 2, 9 },//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0}//terminator
};
static const Rect lower_T[]={
	{4, 1, 2, 29}, //line
	{2, 1+13, 8, 2}, //middle line
	{4, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect lower_U[]={
    {1, 1+13, 2, 17}, //left line
    {13, 1+13, 2, 17},//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0} //terminator
};
static const Rect lower_V[]={
	{10, 1+13, 2, 16}, //right bottom line
	{4, 1+13, 2, 16}, //left bottom line
	{4, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect lower_W[]={
	{1, 16+13, 14, 2}, //bottom
    {1, 1+13, 2, 17}, //left line
    {7, 1+13, 2, 17}, //middle line
    {13, 1+13, 2, 17},//right line
	{-1,0,0,0} //terminator
};
static const Rect lower_X[]={
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
static const Rect lower_Y[]={
    {1, 1+13, 2, 9 },//left line
    {13, 1+13, 2, 9 },//right line
    {1, 9+13, 14, 2}, //middle
	{7, 9+13, 2, 9}, //line
    {-1, 0, 0, 0} //terminator
};
static const Rect lower_Z[]={
	{1, 1+13, 14, 2}, //top line
    {13, 1+13, 2, 9 },//left line
    {1, 9+13, 14, 2}, //middle
    {1, 9+13, 2, 9 },//right line
    {1, 29, 14, 2}, //bottom line
	{-1,0,0,0}//terminator
};
//SPECIAL
static const Rect dash[]={
	{1, 16, 14, 2}, //obvious
	{-1, 0, 0, 0} //terminator
};
static const Rect plus[]={
	{1, 16, 14, 2}, //horizontal
	{7, 10, 2, 14}, //vertikaal
	{-1, 0, 0, 0} //terminator
};
static const Rect questionmark[]={
	{1, 1, 14, 2}, //top line
    {13, 1, 2, 9 },//left line
    {1, 9, 14, 2}, //middle
    {1, 9, 2, 9 },//right line
    {1, 18, 14, 2}, //bottom line
    {6, 26, 4, 4}, //dot
	{-1,0,0,0}//terminator
};
static const Rect double_dot[]={
    {5, 12, 4, 4}, //dot
    {5, 24, 4, 4}, //dot
	{-1,0,0,0}//terminator
};
static const Rect line[]={
	{7, 1, 2, 29}, //line
	{-1, 0, 0, 0} //terminator
};
static const Rect curly_shit_left[]={
	{7, 1, 2, 30}, //vertical line
	{7, 1, 8, 2}, //top line
	{1, 1+13, 8, 2}, //middle line,
	{7, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect curly_shit_right[]={
	{7, 1, 2, 30}, //vertical line
	{1, 1, 8, 2}, //top line
	{7, 1+13, 8, 2}, //middle line,
	{1, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect underscore[]={
	{1, 29, 14, 2}, //ISNT THIS FUCKING OBVIOUS
	{-1, 0, 0, 0}
};
static const Rect bracket_left[]={
	{7, 1, 2, 30}, //vertical line
	{7, 1, 8, 2}, //top line
	{7, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect bracket_right[]={
	{7, 1, 2, 30}, //vertical line
	{1, 1, 8, 2}, //top line
	{1, 29, 8, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect star[]={
	{4, 5, 10, 2}, //horizontal
	{8, 1, 2, 10}, //vertikaal
	{6, 3, 6, 6}, //block
	{-1, 0, 0, 0} //terminator
};
static const Rect exclamation[]={
	{6, 1, 4, 20}, //middle v line
    {6, 27, 4, 4}, //dot
	{-1, 0, 0, 0}//terminator
};
static const Rect dollar[]={
    {1, 1, 14, 2}, //top line
    {1, 1, 2, 13}, //left line
    {1, 12, 14, 2}, //middle h line
	{7, 1, 2, 29}, //middle v line
    {13, 12, 2, 19},  //right line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect dot[]={
    {6, 27, 4, 4}, //dot
	{-1, 0, 0, 0}//terminator
};
static const Rect comma[]={
    {6, 23, 4, 10}, //dot -2
	{-1, 0, 0, 0}//terminator
};
static const Rect upcomma[]={
    {6, 0, 4, 10}, //dot
	{-1, 0, 0, 0}//terminator
};
static const Rect per[]={
    {11, 1, 2, 6}, //line 1
    {9, 7, 2, 6}, //line 2
    {7, 13, 2, 6}, //line 3
    {5, 19, 2, 6}, //line 4
    {3, 25, 2, 6}, //line 5
	{-1, 0, 0, 0} //terminator
};
//numerical
static const Rect one[]={
    {1, 1, 8, 2}, //top line
    {1, 29, 14, 2}, //bottom line
	{7, 1, 2, 30}, //middle line
	{-1, 0, 0, 0} //terminator
};
static const Rect twa[]={
    {1, 1, 14, 2}, //top line
    {13, 1, 2, 16}, //right line
    {1, 15, 14, 2}, //middle line
    {1, 15, 2, 15},  //left line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect three[] = {
    {13, 1, 2, 30}, //right line
    {1, 1, 14, 2}, //top line
    {1, 15, 14, 2}, //middle line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static const Rect four[]={
    {1, 1, 2, 16}, //right line
    {1, 15, 14, 2}, //middle line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0, 0} //terminator
};
static const Rect five[]={
    {1, 1, 14, 2}, //top line
    {1, 1, 2, 16}, //left line
    {1, 15, 14, 2}, //middle line
    {13, 17, 2, 14},  //right line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect six[]={
    {1, 1, 14, 2}, //top line
    {1, 1, 2, 29}, //left line
    {1, 15, 14, 2}, //middle line
    {13, 17, 2, 14},  //right line
    {1, 29, 14, 2}, //bottom line
	{-1, 0, 0, 0} //terminator
};
static const Rect seven[] = {
    {13, 1, 2, 30}, //right line
    {1, 1, 14, 2}, //top line
    {-1, 0, 0, 0} //terminator
};
static const Rect eight[] = {
    {13, 1, 2, 30}, //right line
    {1, 1, 2, 29}, //left line
    {1, 1, 14, 2}, //top line
    {1, 15, 14, 2}, //middle line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static const Rect hitler[] = {
    {13, 1, 2, 30}, //right line
    {1, 1, 2, 16}, //left line
    {1, 1, 14, 2}, //top line
    {1, 15, 14, 2}, //middle line
    {1, 29, 14, 2}, //bottom line
    {-1, 0, 0, 0} //terminator
};
static const Rect nulla[]={
    {1, 1, 2, 30}, //left line
    {1, 1, 14, 2}, //top line
    {1, 29, 14, 2}, //bottom line
    {13, 1, 2, 30}, //right line
	{-1, 0, 0 ,0} //terminator
};

const Rect* ascii_map[128] = {
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
    ['e']=lower_E,//31
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
    [',']=comma,
    ['\'']=upcomma,
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
static const Rect up[]={
	{4, 1, 24, 22}, //block
	{8, 23, 16, 4}, //line 1
	{12 , 27, 8, 4}, //line 2
	{-1, 0, 0, 0} //terminator
};
static const Rect down[]={
	{12, 1, 8, 4}, //line 1
	{8, 5, 16, 4}, //line 2
	{4, 9, 24, 22}, //block
	{-1, 0, 0, 0} //terminator
};
static const Rect left[]={
	{1, 4, 22, 24},//block//
	{23, 8, 4, 16},//line 1
	{27, 12, 4, 8},//line 2
	{-1, 0, 0, 0}//terminator
};
static const Rect right[]={
	{1, 12, 4, 8},//line 1
	{5, 8, 4, 16},//line 2
	{9, 4, 22, 24},//block
	{-1, 0, 0, 0}//terminator
};
static const Rect select[]={
	{1, 7, 28, 16}, //block
	{-1, 0, 0, 0}//terminator
};
static const Rect start[]={
	{1, 4, 14, 24},//block//
	{15, 8, 8, 16},//line 1
	{23, 12, 8, 8},//line 2
	{-1, 0, 0, 0}//terminator
};
static const Rect cross[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//icon
	{9, 9, 2, 2}, //left u1
	{11, 11, 2, 2}, //left u2
	{13, 13, 2, 2}, //left u3
	{9, 21, 2, 2},//left d1
	{11, 19, 2, 2},//left d2
	{13, 17, 2, 2}, //left d3
	{15, 15, 2, 2}, //middle
	{21, 9, 2, 2},//right u1
	{19, 11, 2, 2},//right u2
	{17, 13, 2, 2},//right u3
	{21, 21, 2, 2},//right d1
	{19, 19, 2, 2},//right d2
	{17, 17, 2, 2},//right d3
	{-1, 0, 0, 0} //terminator
};
static const Rect square[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//icon
	{9, 9, 14, 2}, //top
	{9, 9, 2, 14}, //left
	{21, 9, 2, 14},//right
	{9, 21, 14, 2},//bottom
	{-1, 0, 0, 0} //terminator
};
static const Rect circle[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//icon
	{11, 9, 10, 2}, //top
	{9, 11, 2, 10}, //left
	{21, 11, 2, 10},//right
	{11, 21, 10, 2},//bottom
	{-1, 0, 0, 0} //terminator
};
static const Rect triangle[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//icon
	{15, 9, 2, 3}, //top
	{13, 12, 2, 3}, //left 1
	{17, 12, 2, 3},//right1
	{11, 15, 2, 3},//left 2
	{19, 15, 2, 3},//right 2
	{9, 18, 2, 3},//left 3
	{21, 18, 2, 3},//right 3
	{9, 21, 14, 2},//bottom
	{-1, 0, 0, 0}//terminator
};
static const Rect L1[]={
	//box&tail
	{1, 1, 28, 2}, //top line
	{1, 1, 2, 26}, //left line
	{28, 1, 2, 26}, //right line
	{1, 25, 28, 2}, //bottom line
	{5, 27, 22, 4}, //tail
	//letter
	{6, 5, 2, 18}, //left line
	{6, 21, 8, 2}, //bottom line
	//number
	{18, 5, 5, 2}, //top
	{21, 5, 2, 18}, //middle
	{18, 21, 8, 2}, //bottom
	{-1, 0, 0, 0}//terminator
};
static const Rect L2[]={
	//box&tail
	{1, 1, 28, 2}, //top line
	{1, 1, 2, 26}, //left line
	{28, 1, 2, 26}, //right line
	{1, 25, 28, 2}, //bottom line
	{5, 27, 22, 4}, //tail
	//letter
	{6, 5, 2, 18}, //left line
	{6, 21, 8, 2}, //bottom line
	//number
	{18, 5, 8, 2}, //top
	{24, 5, 2, 10}, //right
	{18, 13, 8, 2}, //middle
	{18, 13, 2, 10}, //left
	{18, 21, 8, 2}, //bottom
	{-1, 0, 0, 0}//terminator
};
static const Rect L3[]={
	//box&tail
	{1, 1, 28, 2}, //top line
	{1, 1, 2, 26}, //left line
	{28, 1, 2, 26}, //right line
	{1, 25, 28, 2}, //bottom line
	{5, 27, 22, 4}, //tail
	//letter
	{6, 5, 2, 18}, //left line
	{6, 21, 8, 2}, //bottom line
	//number
	{18, 5, 8, 2}, //top
	{24, 5, 2, 18}, //right
	{18, 13, 8, 2}, //middle
	{18, 21, 8, 2}, //bottom
	{-1, 0, 0, 0}//terminator
};
static const Rect R1[]={
	//box&tail
	{1, 1, 28, 2}, //top line
	{1, 1, 2, 26}, //left line
	{28, 1, 2, 26}, //right line
	{1, 25, 28, 2}, //bottom line
	{5, 27, 22, 4}, //tail
	//letter
	{6, 5, 2, 18}, //left line
	{6, 5, 8, 2}, //top line
	{12, 5, 2, 10}, //right line
	{6, 13, 8, 2}, //middle line
	{10, 13, 2, 10}, //right leg
	//number
	{18, 5, 5, 2}, //top
	{21, 5, 2, 18}, //middle
	{18, 21, 8, 2}, //bottom
	{-1, 0, 0, 0}//terminator
};
static const Rect R2[]={
	//box&tail
	{1, 1, 28, 2}, //top line
	{1, 1, 2, 26}, //left line
	{28, 1, 2, 26}, //right line
	{1, 25, 28, 2}, //bottom line
	{5, 27, 22, 4}, //tail
	//letter
	{6, 5, 2, 18}, //left line
	{6, 5, 8, 2}, //top line
	{12, 5, 2, 10}, //right line
	{6, 13, 8, 2}, //middle line
	{10, 13, 2, 10}, //right leg
	//number
	{18, 5, 8, 2}, //top
	{24, 5, 2, 10}, //right
	{18, 13, 8, 2}, //middle
	{18, 13, 2, 10}, //left
	{18, 21, 8, 2}, //bottom
	{-1, 0, 0, 0}//terminator
};
static const Rect R3[]={
	//box&tail
	{1, 1, 28, 2}, //top line
	{1, 1, 2, 26}, //left line
	{28, 1, 2, 26}, //right line
	{1, 25, 28, 2}, //bottom line
	{5, 27, 22, 4}, //tail
	//letter
	{6, 5, 2, 18}, //left line
	{6, 5, 8, 2}, //top line
	{12, 5, 2, 10}, //right line
	{6, 13, 8, 2}, //middle line
	{10, 13, 2, 10}, //right leg
	//number
	{18, 5, 8, 2}, //top
	{24, 5, 2, 18}, //right
	{18, 13, 8, 2}, //middle
	{18, 21, 8, 2}, //bottom
	{-1, 0, 0, 0}//terminator
};
static const Rect L[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
	
	
};
static const Rect L_up[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{15, 4, 2, 2},
	{14, 5, 4, 2},
	{13, 6, 6, 1},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
};
static const Rect L_up_right[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{21, 7, 4, 1},
	{22, 7, 3, 2},
	{23, 7, 2, 3},
	{24, 7, 1, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
};
static const Rect L_right[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{25, 13, 1, 6},
	{26, 14, 1, 4},
	{27, 15, 1, 2},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
};
static const Rect L_right_down[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{21, 24, 4, 1},
	{22, 23, 3, 2},
	{23, 22, 2, 3},
	{24, 21, 1, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
};
static const Rect L_down[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{15, 26, 2, 2},
	{14, 25, 4, 2},
	{13, 25, 6, 1},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
};
static const Rect L_left_down[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{7, 24, 4, 1},
	{7, 23, 3, 2},
	{7, 22, 2, 3},
	{7, 21, 1, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
};
static const Rect L_left[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{6, 13, 1, 6},
	{5, 14, 1, 4},
	{4, 15, 1, 2},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
};
static const Rect L_up_left[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{7, 7, 4, 1},
	{7, 7, 3, 2},
	{7, 7, 2, 3},
	{7, 7, 1, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 21, 6, 2},
	{-1, 0, 0, 0}//terminator
};


static const Rect R[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};
static const Rect R_up[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{15, 4, 2, 2},
	{14, 5, 4, 2},
	{13, 6, 6, 1},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};
static const Rect R_up_right[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{21, 7, 4, 1},
	{22, 7, 3, 2},
	{23, 7, 2, 3},
	{24, 7, 1, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};
static const Rect R_right[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{25, 13, 1, 6},
	{26, 14, 1, 4},
	{27, 15, 1, 2},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};
static const Rect R_right_down[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{21, 24, 4, 1},
	{22, 23, 3, 2},
	{23, 22, 2, 3},
	{24, 21, 1, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};
static const Rect R_down[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{15, 26, 2, 2},
	{14, 25, 4, 2},
	{13, 25, 6, 1},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};
static const Rect R_left_down[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{7, 24, 4, 1},
	{7, 23, 3, 2},
	{7, 22, 2, 3},
	{7, 21, 1, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};
static const Rect R_left[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{6, 13, 1, 6},
	{5, 14, 1, 4},
	{4, 15, 1, 2},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};
static const Rect R_up_left[]={
	//CIRCLE
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	//Arrow
	{7, 7, 4, 1},
	{7, 7, 3, 2},
	{7, 7, 2, 3},
	{7, 7, 1, 4},
	//Letter
	{13, 11, 2, 10},
	{13, 11, 6, 2},
	{17, 11, 2, 6},
	{13, 15, 6, 2},
	{16, 15, 2, 6},
	{-1, 0, 0, 0}//terminator
};


//MISC
static const Rect folder[]={
	{2, 8, 27, 20}, //block
	{1, 10, 2, 16}, //side left
	{28, 10, 2, 16}, //side right
	{4, 5, 10, 5}, //top block
	{5, 4, 8, 2}, //top block flap
	{-1, 0, 0, 0} //terminator
};
static const Rect file[]={
	{5, 7, 22, 24}, //block
	{7, 5, 20, 4},//flap 1
	{9, 3, 18, 4},//flap 2
	{11, 1, 16, 4},//flap 3
	{-1, 0, 0, 0} //terminator
};


static const Rect this_bitch[]={
	//i wont commentate,
	//take my word, this is a circle
	//i hate my life, why did i start Free-BBN
	{1, 12, 2, 8},//middle point
	{2, 9, 2, 4},
	{3, 8, 2, 2},
	{4, 6, 2, 3},
	{5, 5, 2, 2},// middle point
	{6, 4, 3, 2},
	{8, 3, 2, 2},
	{9, 2, 4, 2},
	{12, 1, 8, 2},// middle point
	{19, 2, 4, 2},
	{22, 3, 2, 2},
	{23, 4, 3, 2},
	{25, 5, 2, 2},//middle point
	{26, 6, 2, 3},
	{27, 8, 2, 2},
	{28, 9, 2, 4},
	{29, 12, 2, 8}, //middle point
	{28, 19, 2, 4},
	{27, 22, 2, 2},
	{26, 23, 2, 3},
	{25, 25, 2, 2}, //middle point
	{23, 26, 3, 2},
	{22, 27, 2, 2},
	{19, 28, 4, 2},
	{12, 29, 8, 2},//middle point
	{9, 28, 4, 2},
	{8, 27, 2, 2},
	{6, 26, 3, 2},
	{5, 25, 2, 2}, //middle point
	{4, 23, 2, 3},
	{3, 22, 2, 2},
	{2, 19, 2, 4},
	{-1, 0, 0, 0}//terminator
};


const Rect* icon_map[128]={
	['\x00']=up,
	['\x01']=down,
	['\x02']=left,
	['\x03']=right,
	['\x04']=select,
	['\x05']=start,
	['\x06']=cross,
	['\x07']=square,
	['\x08']=circle,
	['\x09']=triangle,
	['\x0A']=L1,
	['\x0B']=L2,
	['\x0C']=L3,
	['\x0D']=R1,
	['\x0E']=R2,
	['\x0F']=R3,
	['\x10']=L,
	['\x11']=L_up,
	['\x12']=L_up_right,
	['\x13']=L_right,
	['\x14']=L_right_down,
	['\x15']=L_down,
	['\x16']=L_left_down,
	['\x17']=L_left,
	['\x18']=L_up_left,
	['\x19']=R,
	['\x1A']=R_up,
	['\x1B']=R_up_right,
	['\x1C']=R_right,
	['\x1D']=R_right_down,
	['\x1E']=R_down,
	['\x1F']=R_left_down,
	['\x20']=R_left,
	['\x21']=R_up_left,
	
	//MISC
	['\x22']=folder,
	['\x23']=file,
	['\x24']=this_bitch,
};

