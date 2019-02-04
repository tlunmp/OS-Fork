/* Ted Anthony L Uy
 * cs2750 PA6
 * 4/4/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>	

void helpMenu();
void forkProcess();


int main (int argc, char *argv[]) {

	char inputFileName[] = "input.dat";
	char outputFileName[] = "output.dat";
	int stackSize = 0;
	
		
	int c;

	while((c = getopt (argc,argv, "hp:o:")) != -1) {

		switch(c) {
			case 'h':
				helpMenu();
				return 1;
			case 'p':
				//inputFileName = optarg;	
				printf("%s", inputFileName);	
				break;
			case 'o':
				printf("is awesome\n" );
				break;	
	
		}


	}

	return 0;
}


void helpMenu() {
		printf("----| Help Menu |----\n");
		printf("-i inputfilename \n");
		printf("-o outputfilename \n");
}

void forkProcess() {


}





