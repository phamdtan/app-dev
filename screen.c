// in this file we are going to define a number of functions for screen
// manipulation. These functions include erase screen, set color attributes,
// set sursor location, etc.. using VT100 escape sequences.

// follow this reference: http://www.termsys.demon.co.uk/vtansi.htm
// to paste to putty: shift_insert key
 
#include <stdio.h>
#include "screen.h"

//function definition
void setfgcolor(int fg)
{
  printf("%c[1;%dm", ESC, fg);
}


void setbgcolor(int bg)
{
 printf("%c[1;%dm", ESC, bg);
}


void setcolors(int f, int b)
{
 setfgcolor(f);
 setbgcolor(bg(b));
}


void resetcolors(void)
{
 printf("%c[0m", ESC);
}


void clearscreen(void)
{
 printf("%c[2J", ESC);
}


void gotoXY(int row, int col)
{
 printf("%c[%d;%dH",ESC, row, col);
}


void drawbar(int col, int height)
{
 int i;
 for(i=1; i<=height; i++){
     gotoXY(35-i, col);
#ifdef UNICODE    // following codes are in conditional compilation
     printf("%s", BAR);
#else
     printf("%c", '#');
#endif
 }
}


void drawrect(int row, int col, int height, int width, int fg)
{
 int i,j;
 for(i=row;i<row+height;i++){
		for(j=col; j<col+width; j++){
			setfgcolor(fg);
			gotoXY(i,j);
#ifdef UNICODE
			printf("%s", HEART);
#else
			printf("%c","#");
#endif
		}
		printf("\n");
	}
}

Position getscreensize(void)
{
	//In this function, use terminal query function to query cursor pos
	//The terminal should return a string back to the program
	//If a query string "ESC[6n" is issued to the terminal
	Position p;
	int r,c;				//for decoding the report string
	char re[100] = "\0";	//empty string to get report
	gotoXY(999,999);		//force the cursor to the bottom right corner
	printf("%c[6n",ESC);	//send the query string for cursor position
	scanf("%s",re);			//get report from terminal
#ifdef DEBUG
	printf("%s\n",re);
#endif
	//we will decode the returned string
#include <string.h>
	if(strlen(re)>0)	//in this case we will get a cursor position report
	{
		char dum;		//dummy char to consume those symbols
		sscanf(re,"%c%c%d%c%d%c", &dum,&dum,&r,&dum,&c,&dum);
		p.row=r;
		p.col=c;
	}
	else
	{
		p.row=0;
		p.col=0;
	}
	return p;
}
