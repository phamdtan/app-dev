
// we test functions of screen.c 
#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include "comm.h"
#include "sound.h"


int main(void)
{
	getchar();
    FILE *fp = fopen("test.wav", "r"); // open the wav file in read-only
    WAVheader h = readwavhdr(fp);
    displaywavhdr(h);
	wavdata(h, fp);	//to calculate dB values and display them as a barchart
    fclose(fp);


   Position cur = getscreensize();   //get screen size
   char postdata[100];
   sprintf(postdata, "row=%d&col=%d&id=e1900313", cur.row , cur.col);
   printf("%s\n", postdata);
   sendpost(URL, postdata);
   gotoXY(1,1);
   printf("Screen size: row = %d, col = %d\n", cur.row,cur.col);
   printf("Today we will make some animations. Press any key to continue\n");
   getchar(); // waiting for the user to press a key
/*    for(int i=0; i<100; i++) {
   		 setcolors(RED, GREEN);
  		 clearscreen();
		 gotoXY(1, i+1);
		 printf("HELLO\n");
		 usleep(250000);
    }
	for(int i=1;i<50;i++){
		 setcolors(RED, GREEN);
         clearscreen();
         gotoXY(i, 99);
         printf("HELLO\n");
         usleep(250000);
	}
    for(int i=1;i<100;i++){
	         setcolors(RED, GREEN);
         clearscreen();
         gotoXY(49,100-i );
         printf("HELLO\n");
         usleep(250000);
    }
    for(int i=1;i<50;i++){
         setcolors(RED, GREEN);
         clearscreen();
         gotoXY(50-i,1 );
         printf("HELLO\n");
         usleep(250000);
    } */


   /* for (float i=1.6, j=0; i<=40, j<24; i=i+1.6, j++){
		setcolors(RED, BLACK);
		clearscreen();
		drawrect(j+1, i, 2, 4, RED);
		setcolors(GREEN, BLACK);
		gotoXY(25-j, i);
		printf("HELLO\n");
		usleep(500000);

	}
	for (float i=40, j=0; i<81 , j<25; i=i+1.6 , j++){
		setcolors(RED, BLACK);
		clearscreen();
		drawrect(25-j, i, 2, 4, RED);
		setcolors(GREEN, BLACK);
		gotoXY(j+1, i);
		printf("HELLO\n");
		usleep(500000);
	}*/



  // printf("The following message will be in YELLOW color\n");
   gotoXY(14, 35);
   setfgcolor(BLUE);
   printf("1900313\n");
   getchar();
   drawbar(30, 30);
   drawbar(50, 30);

   getchar();
 /*  resetcolors();
   clearscreen();
   printf("This line is back to default color\n");*/
}
