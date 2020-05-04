// Usually in a header file we have 2 parts:
// 1. function declarations
// 2. constant definition


//constant definition
#define ESC 0x1B // 01xB or 27, all are ok
//make enumeration for fg colors
enum FG {BLACK=30,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE};
#define bg(c) (c+10)   //this is called macro definition

#define UNICODE
#define BAR "\u2590"
#define BOX "\u25AC"
#define HEART "\u2665"
#define DEBUG //for conditional compilation

//making a constant in a name will make your program more meaningful/readable
//now we can use color names in our function setfgcolor()

typedef struct
{
	int row;
	int col;
}Position;



//function declarations

void setfgcolor(int);
void setbgcolor(int);
void setcolors(int, int);
void resetcolors(void);
void clearscreen(void);
void gotoXY(int, int);
void drawbar(int, int);
void drawrect(int, int, int, int, int);
Position getscreensize(void);
