//Stephen Hensley
//shSoundScape
//email: shensley.Audio@gmail.com
//		: shensley@berklee.edu
//
//
//functions used in main.
//Seperate file for ease of reading and editing.
uintptr_t performance_function(void* data){
  CSOUND* csound = (CSOUND*) data;
  while(csoundPerformKsmps(csound) == 0){
    //as in main: just runs for now. Here for later expansion.
  }
  return 0;
}



void fillNoteIndex(float noteIndex[][12]){
  for (int i = 0;i<4;i++){
    for(int j = 0;j<12;j++){
      noteIndex[i][j] = i+3+(float)j/100;
    }
  }
  return;
}

void orderArray(float array[], int size){
  int pass;
  float hold;
  for(pass = 1;pass<size;pass++){
    for(int i = 0;i<size-1;i++){
      if(array[i]>array[i+1]){
        hold = array[i];
        array[i] = array[i+1];
        array[i+1] = hold;
      }else;
    }
  }
  return;
}

int numofNotes(int tduration, int density){
  int numberNotes = tduration/6*density;
  if(numberNotes>MAX_NOTES){
    numberNotes = MAX_NOTES;
  }else;

  return numberNotes;
}

struct note defineScore(note n[], float noteIndex[4][12], int totalDuration, int densityFactor, int numberNotes){
  srand(time(NULL));
  int i, j;
  int tduration = totalDuration;
  int density = densityFactor;
  //note *n[MAX_NOTES];
  float starts[MAX_NOTES];
  
  for(int i = 0;i<numberNotes;i++){
    (n[i]).startTime = (int)rand()%((int)tduration*100)/100.;
    if((n[i]).startTime > tduration - 2.0)
      (n[i]).startTime = (int)rand()%((int)tduration*100)/100.;
    //printf("starttime %d = %g\n", i, n[i].startTime);
    starts[i] = n[i].startTime;
  }

  orderArray(starts, numberNotes);
  for (int i =0;i<numberNotes;i++){
    (n[i]).startTime = starts[i];
    //printf("starttime %d = %g\n", i, n[i].startTime);
  }

  for(int i = 0; i<numberNotes;i++){
    (n[i]).length = 1+(rand()%((int)tduration-(int)starts[i])*100)/100.;
    (n[i]).pitch = noteIndex[rand()%4][rand()%12];
    (n[i]).attack = (float)(rand()%100)/100.;
    (n[i]).decay = 1-(n[i]).attack;
    if(n[i].decay < 0.01)
    	n[i].decay = 0.01;
    (n[i]).carrier = (float)(rand()%100)/10;
    (n[i]).modulator = (float)(rand()%100)/10;
    (n[i]).reverbSend = (float)(rand()%100)/100.;   
    //printf("%g\t%g\t\n", n[i].startTime, n[i].length); 
  }  
  return n[numberNotes];
}

char* writeScore(note n[], int numberNotes, int totalDuration){
  char* retval = calloc(1024, sizeof(char));
  char note_string[MAX_NOTES*11];

  int j = sprintf(retval, "f1 0 16384 10 1\ni99 0 %d\n", totalDuration);
  for(int i = 0; i<numberNotes;i++){
    int g = sprintf(note_string, "i1 %g %g %g %g %g %g %g %g\n",
      (n[i]).startTime,
      (n[i]).length,
      (n[i]).pitch,
      (n[i]).attack,
      (n[i]).decay,
      (n[i]).carrier,
      (n[i]).modulator,
      (n[i]).reverbSend);
      //printf("%s\t%d\n", note_string, i);
    strncat(retval,note_string,g+j);
  }
  //printf("%s", retval);
  return retval;
}