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
void forkProcess(char *inputFileName);


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
				strcpy(inputFileName, optarg);
				forkProcess(inputFileName);
				break;
			case 'o':
				strcpy(outputFileName, optarg);
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

void forkProcess(char *inputFileName) {
	FILE *f = fopen("input.dat","r");

	int bufSize = 100;
	int newLineCount = 0;

	char buffer[bufSize];

	pid_t childpid = 0;
	pid_t parentid = 0;

	fgets(buffer, bufSize, f);
		newLineCount++;
	fclose(f);
	
	int pr_limit = atoi(buffer);	

	printf("%d, newLine count %d", pr_limit, newLineCount);

	

}





