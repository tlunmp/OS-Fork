#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>	

void helpMenu();
int errorCheckFile(char *inputFileName, int ptr_limit, char *argv0Name);
int forkProcess(char *inputFileName, char *outputFileName, int ptr_limiti, char *arg0Name, int newLineCount);

int main (int argc, char *argv[]) {

	char inputFileName[] = "input.dat";
	char outputFileName[] = "output.dat";
	int bufSize = 100;
	char buffer[bufSize];
		
	int newLineCount = 0;
	int c;

	//errorChecker
	int fileErrorCounter = 0;
	int forkNumberLength;
	int forkNumberError = 0;
	char errorMessage[100];
	

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


	if(argc == 2) {
		
		//check if second argument are correct
		if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "-h") == 0) {
		} else {
			fprintf(stderr, "%s: Error: Invalid 2nd Argument must be -i, -o, or -h \n",argv[0]);
			return 0;
		}
	}


	FILE *f = fopen(inputFileName,"r");
	
	// if file open error and return
	if(f == NULL){	
		snprintf(errorMessage, sizeof(errorMessage), "%s: Error", argv[0]);
		perror(errorMessage);
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

	char  errorBuffer[bufSize];
	//checks 
	while(fgets(errorBuffer, bufSize, f2)){
		if(f == NULL){
			snprintf(errorMessage, sizeof(errorMessage), "%s: Error", argv[0]);
			perror(errorMessage);
			return 0;
		}

		int m;
		int flag = 0;
		forkNumberLength = strlen(errorBuffer);	
		for(m=0; m < forkNumberLength; m++){	
			if(errorBuffer[0] == '\n'){
				flag = 0;
			}

			if(isspace(errorBuffer[m]) && !isspace(errorBuffer[m+1])) {										
				flag = 1;
			}
		}

		if(flag == 1) {
			
			forkNumberError++;
		}
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


		//error Checking inside the files
		int errorResult = errorCheckFile(inputFileName,ptr_limit,argv[0]);

		
		if(errorResult == 1) {
			
			//do the fork and pass the argv[0] for errors
			forkProcess(inputFileName,outputFileName, ptr_limit,argv[0],newLineCount);		
		} else {
			fprintf(stderr,"%s: Error: Read File too many argument of stackSize or StackSize is not equal to numbers on the File\n", argv[0]);
			return 0;
		}	
	} else {
		fprintf(stderr,"%s: Error: Read file total fork less than or greather than the file input\n", argv[0]);
		return 0;
	}
	return 0;
}

//forking process
int forkProcess(char *inputFileName, char *outputFileName, int ptr_limit, char *arg0Name, int newLineCount) {
		pid_t childpid = 0;
		int bufSize = 100;
		char buffer[bufSize];
		int stackSize = 0;
		int childArray[ptr_limit];		
		int insideCounterLimit = 2;
		int insideCounter = 1;
		int childCounter =0;
		int i;
		int newLineCompare = 0;
		char errorMessage[100];
		
			//starts the fork
			for (i = 0; i < ptr_limit; i++) {	

				childpid = fork();
				childArray[childCounter] = childpid;
		
				childCounter++;

				//fork Starts
				if(childpid < 0) {
					snprintf(errorMessage, sizeof(errorMessage), "%s: Error", arg0Name);
					perror(errorMessage);	
				} else if (childpid == 0){	
					FILE *f1 = fopen(inputFileName,"r");
					
					//If file cannot find print error
					if(f1 == NULL){
						snprintf(errorMessage, sizeof(errorMessage), "%s: Error", arg0Name);
						perror(errorMessage);
						return 0;
					}

					//scans the file
					while(fgets(buffer,bufSize,f1) != NULL){
				
						//when line reach the second line start the reading
						if (newLineCount == newLineCompare){
					
							//2 line count everytime
							if(insideCounterLimit == insideCounter) {
								
								FILE *out = fopen(outputFileName, "a");
							
								int stack[stackSize]; 	
					
								char *parser;
								parser = strtok(buffer, " ");
								
								//parsing the numbers
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
			if(out1 == NULL){
				snprintf(errorMessage, sizeof(errorMessage), "%s: Error", arg0Name);
				perror(errorMessage);
				return 0;
			}


			fprintf(out1, "All children where: ");
			
			int m;
			for(m = 0; m <ptr_limit; m++ ) {
				fprintf(out1,"%d ", childArray[m]);
			}	

			fprintf(out1,". parent is %d,\n", getpid());
			fclose(out1);


	return 0;

}

//error checking for inside the file
int errorCheckFile(char *inputFileName, int ptr_limit,char *arg0Name ) {
		char errorMessage[100];
		//check if the file numbers are correct or not
		FILE *f3 = fopen(inputFileName, "r");
		if(f3 == NULL){
			snprintf(errorMessage, sizeof(errorMessage), "%s: Error", arg0Name);
			perror(errorMessage);
			return 0;
		}

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

		//read the line for errors
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


	fclose(f3);
	//check if theres errror return 0 if not return 1
	if (ptr_limit == fileStackCounter && stackSizeTotal == fileStackNumberCounter) {	
		return 1;
	} else {
		return 0;
	}

}



//help menu
void helpMenu() {
		printf("---------------------------------------------------------------| Help Menu |--------------------------------------------------------------------------\n");
		printf("-h help menu\n"); 
		printf("-i inputfilename                      | inputfilename is where the filename reads and it will show error if there is no filename found on the directory.\n"); 
		printf("                                      | output filename should be default name is output.dat  where the result is generated.\n");
		printf("-o outputfilename                     | this command will use the default input file which is input.dat\n"); 
		printf("  				      | then create an output result to outputfilename(Which is the user specified name of the file \n"); 
		printf("-i inputfilename -o outputfilename    | this command can use inputfilename (user choose the name)\n");
		printf("				      | generate output to the outputfilename(user choose the outputname) if it doesnt exist create one.\n"); 
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

