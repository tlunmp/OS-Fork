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
				break;
			case 'o':
				strcpy(outputFileName, optarg);
				break;	
	
		}


	}

	FILE *f = fopen(inputFileName,"r");

	int bufSize = 100;
	int newLineCount = 0;
	int newLineCompare = 0;
	char buffer[bufSize];

	int stackSize = 0;
	
	pid_t childpid = 0;

	//errorChecker
	int fileErrorCounter = 0;
	int forkNumberLength;

	if(f == NULL){
		fprintf(stderr,"%s: ", argv[0]);
		perror("Error");
		return 0;
	}


	fgets(buffer, bufSize, f);
		if(f == NULL){
			printf("%s", argv[0]);
			perror("Error");
			return 0;
		}

		newLineCount++;
	fclose(f);

	forkNumberLength = strlen(buffer);
	
	//check if there is 2 numbers terminates
	int o;	
	for(o=0; o < forkNumberLength; o++){
		
		if(isspace(buffer[o])){
			fileErrorCounter++;
		}

	}	


	//show error and terminate if there is more numbers
	if(fileErrorCounter > 1) {
		fprintf(stderr,"%s: Error: Read file fork too many argument\n", argv[0]);
		return 0;
	}
	


	int ptr_limit = atoi(buffer);	

	int childArray[ptr_limit];	
	
	int insideCounterLimit = 2;
	int insideCounter = 1;

	int childCounter =0;
	

	
	int i;

	for (i = 0; i < ptr_limit; i++) {	

		childpid = fork();

	
		childArray[childCounter] = childpid;
		
		childCounter++;
		if(childpid < 0) {
			printf("error");
		} else if (childpid == 0){	
			FILE *f1 = fopen(inputFileName,"r");
			if(f1 == NULL){

				printf("%s", argv[0]);
				perror("Error");
				return 0;
			}

			while(fgets(buffer,bufSize,f1) != NULL){
					
				if (newLineCount == newLineCompare){
					
					
					if(insideCounterLimit == insideCounter) {
								
						FILE *out = fopen(outputFileName, "a");
							
						int stack[stackSize]; 	
					
						char *parser;
						parser = strtok(buffer, " ");

						int i;
						for(i=0; i < stackSize; i++){
							stack[i] = atoi(parser);
							parser = strtok(NULL, " ");	
						}

						fprintf(out, "%d: ", getpid());
						
						int j=0;
						for(j=stackSize-1; j >= 0; j--) {
							fprintf(out, "%d ", stack[j]);
						}
						fprintf(out, "\n");
				
						break;
					} else { 
						stackSize = atoi(buffer);
						insideCounter++;
					}
					
				} else {

					newLineCompare++;
				}
			}
	
			fclose(f1);
			exit(0);
		} else {
			int status;		
			wait(&status);
			newLineCount += 2;
		}	
		

			
	}

	
		FILE *out1 = fopen(outputFileName, "a");
		fprintf(out1, "All children where: ");
			
		int m;
		for(m = 0; m <ptr_limit; m++ ) {
			fprintf(out1,"%d ", childArray[m]);
		}	

		fprintf(out1,". parent is %d,\n", getpid());
		fclose(out1);
	return 0;
}


void helpMenu() {
		printf("----| Help Menu |----\n");
		printf("-i inputfilename \n");
		printf("-o outputfilename \n");
}
