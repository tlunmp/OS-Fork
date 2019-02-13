#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>	

void helpMenu();
int errorCheckFile(char *inputFileName, int ptr_limit);

int main (int argc, char *argv[]) {

	char inputFileName[] = "input.dat";
	char outputFileName[] = "output.dat";
	
		
	int c;

	//getopt command for command line
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
	int forkNumberError = 0;
	int errorChild = 0;
	char errorMessage[100];
	
	// if file open error and return
	if(f == NULL){
		fprintf(stderr,"%s: ", argv[0]);
		perror("Error");
		return 0;
	}


	//gets the fork number
	fgets(buffer, bufSize, f);
		newLineCount++;
	fclose(f);

	//get the length of the buffer to check if there is 2 numbers
	forkNumberLength = strlen(buffer);

	//get number of forks for looping	
	int ptr_limit = atoi(buffer);	
	

	//open files and read all the max lines check if theres is more fork than the first line number, if it is true then display  error
	FILE *f2 = fopen(inputFileName,"r");

	while(fgets(buffer, bufSize, f2)){
		if(f == NULL){
			snprintf(errorMessage, sizeof(errorMessage), "%s: Error", argv[0]);
			perror(errorMessage);
			return 0;
		}

		forkNumberError++;
	
	}
	fclose(f2);

	int forkCompare = (ptr_limit*2)+1;

	//check if the fork are correct	
	if(forkCompare == forkNumberError){

		
		//check if there is 2 numbers terminates
		int o;	
		for(o=0; o < forkNumberLength; o++){
		
			if(isspace(buffer[o])){
				fileErrorCounter++;
			}

		}	

	

		//show error and terminate if there is more numbers
		if(fileErrorCounter > 1) {
			fprintf(stderr,"%s: Error: Read file fork too many argument in Line 1\n", argv[0]);
			return 0;
		}
	
		fileErrorCounter = 0;


		int childArray[ptr_limit];	
	
		int insideCounterLimit = 2;
		int insideCounter = 1;

		int childCounter =0;
		
		int i, line = 0;

		int errorResult = errorCheckFile(inputFileName,ptr_limit);

		printf("%d", errorResult);
		
		if(errorResult == 1) {
			//starts the fork
			for (i = 0; i < ptr_limit; i++) {	

				childpid = fork();
				childArray[childCounter] = childpid;
		
				childCounter++;
				if(childpid < 0) {
					printf("error");
				} else if (childpid == 0){	
					FILE *f1 = fopen(inputFileName,"r");
					if(f1 == NULL){
						snprintf(errorMessage, sizeof(errorMessage), "%s: Error", argv[0]);
						perror(errorMessage);
						return 0;
					}


					while(fgets(buffer,bufSize,f1) != NULL){
				
						//when line reach the second line start the reading
						if (newLineCount == newLineCompare){
					
							//2 line count everytime
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

			//print out the children and parent pid
			FILE *out1 = fopen(outputFileName, "a");
			fprintf(out1, "All children where: ");
			
			int m;
			for(m = 0; m <ptr_limit; m++ ) {
				fprintf(out1,"%d ", childArray[m]);
			}	

			fprintf(out1,". parent is %d,\n", getpid());
			fclose(out1);

		} else {
			return 0;
		}	
	} else {
		printf("error");

	}
	return 0;
}

int errorCheckFile(char *inputFileName, int ptr_limit ) {
		//check if the file numbers are correct or not
		FILE *f3 = fopen(inputFileName, "r");
	
		int bufSize = 100;
		char buffer[bufSize];

		int fileStackCounter = 0;
		int fileStackNumberCounter = 0;
		int insideErrorLimit = 1;
		int insideErrorCounter = 0;
		int newErrorCompare = 0;
		int newLineErrorCount = 1;
		int errorLine = 0;
		int stackSizeError = 0;
		int stackSizeTotal = 0;
		int forkNumberLength = 0;

		while(fgets(buffer,bufSize,f3) != NULL){
			errorLine++;
			if(newLineErrorCount == newErrorCompare) {
				if(insideErrorLimit == insideErrorCounter){
					
					//check if there is 2 numbers terminates
					int o;
					forkNumberLength = strlen(buffer);	
					for(o=0; o < forkNumberLength; o++){	
						if(isspace(buffer[o]) && !isspace(buffer[o+1])) {										
							fileStackNumberCounter++;
						}

					}
					insideErrorLimit +=2;

				} else {
					//check if there is 2 numbers terminates
					int o;
					forkNumberLength = strlen(buffer);	
					for(o=0; o < forkNumberLength; o++){	
						if(isspace(buffer[o]) && !isspace(buffer[o+1])) {										
							fileStackCounter++;
						}

					}
					stackSizeError = atoi(buffer);
					stackSizeTotal += stackSizeError;
				}
				insideErrorCounter++;

			} else {
				newErrorCompare++;

			}		


		}

	
	if (ptr_limit == fileStackCounter && stackSizeTotal == fileStackNumberCounter) {	
		return 1;
	} else {
		return 0;
	}

}


void helpMenu() {
		printf("----| Help Menu |----\n");
		printf("-h help menu"); 
		printf("-i inputfilename  inputfilename is where the filename reads and it will show error if there is no filename found on the directory. output filename should be default name is output.dat  where the result is generated.\n");
		printf("-o outputfilename  this command will use the default input file which is input.dat then create an output result to outputfilename(Which is the user specified name of the file \n"); 
printf("-i inputfilename -o outputfilename     this command can use inputfilename (user choose the name)  and  generate output to the outputfilename(user choose the outputname) if it doesnt exist create one.\n"); 

}

