/* * * * * * * * * * * * * * *
   lab1.c
          -- replicates the grep program in flagless and in -c mode.
             There is no functionality for regex.

   lab1 for CMPSC 474, Spring 2011.
   coded by Luke Kuzmish
 * * * * * * * * * * * * * * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

	int 	countMode = 0;	/* global local, has "-c" been used? */
const 	int 	MAXLINE = 100;  /* lines character length */

/* * * * * * * * * * * * * * *
  function:	readInFile

  parameters:	fileName  	-- char ptr to name of file to grep
		subStr		-- char ptr to substring to grep for

  summary:	Opens fileName in read mode, reads in each line and searches
		for an instance of subStr within the line.  If in count mode
		cycles through the rest of the line for more occurences of
		subStr in the line.

 * * * * * * * * * * * * * * */

int readInFile(char *fileName, char *subStr) { 
	
	FILE	*ptrFile; 
	char	lineIn[MAXLINE + 1];
	int	instanceCount 	= 0;

	ptrFile = fopen(fileName, "r");

	if (ptrFile != NULL) {

		/* search for substring */

		while (fgets(lineIn, (MAXLINE + 1), ptrFile) != NULL) {
		/* while not EOF */
			
			if (strstr(lineIn,subStr) != NULL) {
			/* substring found in current line */

				if (!countMode)
					printf("%s", lineIn);
				else
					++instanceCount;
			}
		} /* while() */

		if (countMode)
			printf("%i\n", instanceCount);
	}

	else {
		puts("File does not exist!\n");
		exit(1);
	}
} /* readInFile() */


int main(int argc, char *argv[]){

	char 	*fileName;
	char	*searchString;

	if (argc<3) {	/* too few arguments error */
		printf("USAGE: lab1 [-c] searchString filename.ext\n");
		exit(1);
	}

	/* check for -c flag */
	if (strcmp(argv[1],"-c") == 0)	countMode = 1;
	
	/* grab fileName and searchString from command line args */
	fileName = argv[argc-1];
	searchString = argv[argc-2];

	readInFile(fileName,searchString);

	exit(0);
}
