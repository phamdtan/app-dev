#include <stdio.h>
#include "sound.h"
#include <math.h>
#include "screen.h"
#include "comm.h"

//function definitions
WAVheader readwavhdr(FILE *fp){
	WAVheader myh;
	fread(&myh, sizeof(myh), 1, fp);
	return myh;
}

void displaywavhdr(WAVheader h){
		printf("Chunk Id: ");
	for(int i=0; i<4; i++){
		printf("%c", h.chunkID[i]);
	}
	printf("\n");
	printf("Chunk size: %d\n", h.chunkSize);
	printf("Number of channels: %d\n", h.numChannels);
	printf("Sample rate: %d\n", h.sampleRate);
	printf("Block align: %d\n", h.blockAlign);
	printf("Bits per sample: %d\n", h.bitsPerSample);
	double duration;
	duration = (double) h.subchunk2Size/h.byteRate;
	printf("Duration: %f seconds\n", duration);
	// -- to be continued
}

void wavdata(WAVheader h, FILE *fp){
	// in this function we will read sound samples from the open file
	// the sample are calculated into decibel value using Root Mean Square
	// (RMS) formula. We will display a 5-sec recorded sound into bar chart
	// our sound file uses sample rate of 16000, for 5 seconds, there are
	// 5*16000 = 80000 samples, we want to display them into 160 bars
	short samples[500];		// to read 500 samples from wav file
	int peaks = 0, flag = 0, max = 70;	// 1st value is to count, 2nd value is to show that you are in a peak
	char postData[100];

	for(int i = 0; i<160; i++){
		fread(samples, sizeof(samples), 1, fp);
		double sum = 0.0;	// accumlate the sum
		for(int j=0; j<500; j++){
			sum = sum + samples[j]*samples[j];
		}
		double re = sqrt(sum/500);
#ifdef SDEBUG
		printf("db[%d] = %f\n", i+1, 20*log10(re));
#else
		// display for re value
		if( (int)20*log10(re) > max )
			max = (int)20*log10(re);
		if( (int)20*log10(re) > 70){
			 setfgcolor(RED);
			if(flag == 0){
				flag = 1;
				peaks++;		// i got a peak
		}
		}
		else {
			setfgcolor(WHITE);
			flag = 0;
		}
		drawbar(i+1, (int)20*log10(re)/3);
#endif
	}
	// display sample rate, duration, no. of peaks on top of the screen
	gotoXY(1,1); printf("Sample Rate: %d\n", h.sampleRate);
	gotoXY(1, 75); printf("Duration: %f s\n", (float)h.subchunk2Size/h.byteRate);
	gotoXY(1, 140); printf("Peaks: %d\n", peaks);
	gotoXY(2, 1); printf("Maximum: %d\n", max);
	sprintf(postData, "peaks=%d&max=%d\n", peaks, max);
	sendpost(URL, postData);
}
// end of file
