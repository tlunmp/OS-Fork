#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>	

void helpMenu();
void forkProcess(char *inputFileName, char *outputFileName);


int main (int argc, char *argv[]) {

	char inputFileName[] = "input.dat";
	char outputFileName[] = "output.dat";
	
		
	int c;

	while((c = getopt (argc,argv, "hi:o:")) != -1) {

		switch(c) {
			case 'h':
				helpMenu();
				return 1;
			case 'i':
				strcpy(inputFileName, optarg);
				forkProcess(inputFileName, outputFileName);
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

void forkProcess(char *inputFileName, char *outputFileName) {
	FILE *f = fopen(inputFileName,"r");

	int bufSize = 100;
	int newLineCount = 0;
	int newLineCompare = 0;
	char buffer[bufSize];

	int stackSize = 0;
	
	pid_t childpid = 0;
	pid_t parentid = 0;

	fgets(buffer, bufSize, f);
		newLineCount++;
	fclose(f);
	
	int ptr_limit = atoi(buffer);	
	int ptr_count = 0;

	int insideCounterLimit = 2;
	int insideCounter = 1;
	//printf("%d, newLine count %d", pr_limit, newLineCount);

	FILE *f1 = fopen(inputFileName,"r");

	while(fgets(buffer,bufSize,f1) != NULL){
			
			if (newLineCount == newLineCompare){
				if(insideCounterLimit == insideCounter){
					
					int stack[stackSize]; 	
					
					char *parser;
					parser = strtok(buffer, " ");
					
					FILE *out = fopen(outputFileName, "a");

					int i;
					for(i=0; i < stackSize; i++){
						stack[i] = atoi(parser);
						parser = strtok(NULL, " ");	
					}
						

					int j=0;
					for(j=stackSize-1; j >= 0; j--) {
						fprintf(out, "%d ", stack[j]);
					}
						fprintf(out, "\n");
							
					fclose(out);
					insideCounterLimit += 2;

				} else {
					stackSize = atoi(buffer);	
				}
					insideCounter++;
			} else {
			
				newLineCompare++;

			}

	}	


	

}





