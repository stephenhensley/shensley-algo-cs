//shensley
//Test code for passing an array of structs through a function.

#include <stdio.h>
#include <stdlib.h>

typedef struct note{
		float start;
		float length;
	}note;

struct note define(note n[]);

int main(int argc, char** argv){

	

	note n[6];
	for(int i=0;i<6;i++){
		n[i].start = 1.0;
		n[i].length = 1.0;
	}


	

	

	define(n);

	for(int i = 0;i<6;i++)
		printf("%.2f\t%g\n", n[i].start, n[i].length);


	return 0;
}

struct note define(note n[]){

	for(int i = 0;i<6;i++){
		n[i].start = 2*i;
		n[i].length = 3*i;		
	}
	return n[6];
}