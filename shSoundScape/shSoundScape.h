//Stephen Hensley
//shSoundScape
//email: shensley.Audio@gmail.com
//		: shensley@berklee.edu
//
//
//all functions, constants, libraries
#define shSoundScape_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <csound.h>
#include <string.h>

//
#define MAX_NOTES 300
#define MAX_LENGTH 240


typedef struct note{
	float startTime;
	float length;
	float pitch;
	float attack;
	float decay;
	float carrier;
	float modulator;
	float reverbSend;
}note;

//function prototypes
uintptr_t performance_function(void* data);
void defineScore(note n[], float noteIndex[][12], int totalDuration, int densityFactor, int numberNotes);
char* writeScore(note notes[], int numberNotes, int totalDuration);

//additional function prototypes
void fillNoteIndex(float noteIndex[][12]);
int numofNotes(int totalDuration, int densityFactor);
void orderArray(float array[], int size);



const char* orc = "sr=44100\n"
  "ksmps=32\n"
  "nchnls=2\n"
  "0dbfs=1\n\n"
  "garvb init 0\n"
  "instr 1\n"
  "ifreq = cpspch(p4)\n"
  "iatt = p5\n"
  "idec = p6\n"
  "icar = p7\n"
  "imod = p8\n"
  "irvbsnd = p9\n"
  "kenv linseg 0, iatt*p3, 0.5, idec*p3, 0\n"
  "afm foscili kenv, ifreq, icar, imod, 5*kenv, 1\n"
  "asig moogladder afm, 12000, 0.74\n"
  "outs asig, asig\n"
  "garvb = garvb + (0.8*asig*irvbsnd)\n"
  "endin\n"
  "instr 99\n"
  "garvb init 0\n"
  "denorm garvb\n"
  "aoutL, aoutR reverbsc garvb, garvb, 0.92, 18000, 44100, 0.8\n"
  "outs aoutL, aoutR\n"
  "clear garvb\n"
  "endin\n";


  