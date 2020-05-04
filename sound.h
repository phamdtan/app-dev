// this header file contains constant definitions and function declarations
// for processing sound, specifically .wav.files.
// #define SDEBUG

typedef struct{
	char chunkID[4];		//shouldbe always "RIFF"
	int chunkSize;			//indicates how big sound data is
	char format[4];			//should be always "WAVE"
	char subchunk1ID[4];	//should be always "fmt "
	int subchunk1Size;		//should be 16 for PCM data
	short audioFormat;		//should be 1 for Linear sample
	short numChannels;		//1 for mono, 2 for stereo
	int sampleRate;			//could be 44100, 16000, 8000
	int byteRate;			//can be calculated
	short blockAlign;		//how many bytes in one block
	short bitsPerSample;	//how many bits in one sample
	char subchunk2ID[4];	//should be always "data"
	int subchunk2Size;		//how many bytes exactly for data part
}WAVheader;


// function delarations
WAVheader readwavhdr(FILE *fp);
void displaywavhdr(WAVheader h);
void wavdata(WAVheader h, FILE *fp);


