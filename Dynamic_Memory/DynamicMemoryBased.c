#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define firstNameSize 20
#define lastNameSize 20
#define studentsMIN 5
#define studentsMAX 15

void printRecords(char **first, char** last, float *score, int size );
void addRecords(char ***first, char*** last, float **score, int *size );
void deleteRecords(char ***first, char*** last, float **score, int *size );
void searchLast(char **first, char** last, float *score, int size );
void sortScore(char **first, char** last, float *score, int size );
void sortLastName(char **first, char** last, float *score, int size );
void medianScore(char **first, char** last, float *score, int size );

char buffer;

int main()
{


	printf("\nThis program will store and manage student records through the use of menus.\n\n");
	//determine how many students are in the class

	int classSize;
	printf("How many students are in the class? ");
	scanf("%d",&classSize);
	int i,j;

	if(classSize >= studentsMIN) //is class size within range of lab requirements?
	{
			//store first names and last names in one 2D character array
      char **firstNamesOfStudents = (char **) calloc(classSize,sizeof(char *)); //holds addresses of first names
      char **lastNamesOfStudents = (char **) calloc(classSize,sizeof(char *)); //holds addresses of last names
      float *scoreOfStudents = (float *) calloc(classSize,sizeof(float)); //stores grades

      //populate both arrays with spaces to make table easier
      for(i =0; i< classSize; i++)
      {
          firstNamesOfStudents[i] = ( char *) calloc(firstNameSize+2, sizeof(char));
          lastNamesOfStudents[i] = (char *) calloc(lastNameSize+2, sizeof(char));
	    }

			//get input for names of students and grades
			scanf("%c",&buffer); //takes in \n so fgets works properly

			printf("\n\nPLEASE READ: When entering the students name you will be asked to input first name and last name separatly, please: \n");
			printf("\tDO NOT INPUT MIDDLE NAMES\n");
			printf("\tDO NOT INPUT FIRST NAME AND LAST NAME IN ONE LINE\n");
			printf("\tDO NOT WORRY ABOUT CAPATILIZATION, ALL LETTERS WILL AUTOMATICALLY CAPATILIZED\n");
			printf("\tSEPARATE THEM WITH A NEW LINE!\n\n");

			//student information
			for(i = 0; i < classSize; i++)
			{
			 	char *ptr;
				//firstname
				printf("What is the first name of student %d? ", i+1 ); //first name
				fgets(firstNamesOfStudents[i], firstNameSize+2,stdin);

			 //cleans stdin so fgets for last name doesnt read in excess
			 if((ptr = strchr(firstNamesOfStudents[i], '\n')))
			 {
				 *ptr = 0;
			 }
			 else
			 {
					scanf("%*[^\n]");scanf("%*c");
			 }
					//discard of new line
					for(j = 0; j<firstNameSize+2;j++)
			 {
				 if(firstNamesOfStudents[i][j] == '\n')
				 {
					 firstNamesOfStudents[i][j] = '\0';
					 break;
				 }
			 }

					printf("What is the last name of %s? ", firstNamesOfStudents[i] ); //last name
					fgets(lastNamesOfStudents[i], lastNameSize+2,stdin);
					//cleans stdin so fgets for first name doesnt read in excess
				if((ptr = strchr(lastNamesOfStudents[i], '\n')))
			 {
	*ptr = 0;
			 }
			 else{
					scanf("%*[^\n]");scanf("%*c");
			 }

					for(j = 0; j<lastNameSize+2;j++)
					{
							if(lastNamesOfStudents[i][j] == '\n') //fgets stores new line so it must be disposed of
							{
									lastNamesOfStudents[i][j] = '\0'; //cuts name off
									break;
							}
					}

					//score
					printf("What was %s %s's score? ",firstNamesOfStudents[i],lastNamesOfStudents[i]); //gets the student's score
					scanf("%f",&scoreOfStudents[i]);
					scanf("%c",&buffer); //takes in new line so that fgets can work propertly
					printf("\n");
			}

			//autocapatilize all letters to make sorting and searching easier for user
			for(i = 0; i<  classSize; i++)
			{
					for(j = 0; j < (firstNameSize+2); j++)
					{
							if(firstNamesOfStudents[i][j] >= 'a' && firstNamesOfStudents[i][j] <= 'z')
							{
									firstNamesOfStudents[i][j]-=32;
							}
							if(lastNamesOfStudents[i][j] >= 'a' && lastNamesOfStudents[i][j] <= 'z')
							{
									lastNamesOfStudents[i][j]-=32;
							}
					}
			}

					//Shows the list of commands for user
			int repeatFunction = 1;
			while(repeatFunction)
			{
					printf("\nThe following commands are used in the program. Input the number of the function you want to input.\n");
					printf("\tFor example, if you want to print records of all students please input 1.\n");

					printf("______________________________________________________________________________________\n");
					printf("|Function Number|                            Description                             |\n");
					printf("|_______________|____________________________________________________________________|\n");
					printf("|       1       |Print Records of all students                                       |\n");
					printf("|       2       |Add a new record to database                                        |\n");
					printf("|       3       |Delete record(s) of student based on last name                      |\n");
					printf("|       4       |Search records based on last name of students                       |\n");
					printf("|       5       |Sort and List records of students based on score in descending order|\n");
					printf("|       6       |Sort records by last name in alphabetical order                     |\n");
					printf("|       7       |Find Median Score and print record of students who scored above it  |\n");
					printf("|       0       |Exit program                                                        |\n");
					printf("|_______________|____________________________________________________________________|\n");
					printf("\nWhat do you want to do?\n\n");

					int functionNumber;
					scanf("%d",&functionNumber);

					//execute function based on switch statement
					switch(functionNumber)
					{
						case 0:
								for(i = 0; i < classSize; i++)
								{
										free(firstNamesOfStudents[i]);
										free(lastNamesOfStudents[i]);
								}
								free(firstNamesOfStudents);
								free(lastNamesOfStudents);
								free(scoreOfStudents);
								printf("\n\nThank you for using the program!\n\nThe program will now exit.\n\n");
								repeatFunction = 0;
								break;
						case 1:
								printRecords(firstNamesOfStudents,lastNamesOfStudents,scoreOfStudents, classSize);
								break;
						case 2:
								scanf("%c",&buffer);
								addRecords(&firstNamesOfStudents,&lastNamesOfStudents,&scoreOfStudents, &classSize);
								break;
						case 3:
								scanf("%c",&buffer);
								deleteRecords(&firstNamesOfStudents,&lastNamesOfStudents,&scoreOfStudents, &classSize);
								break;
						case 4:
								scanf("%c",&buffer);
								searchLast(firstNamesOfStudents,lastNamesOfStudents,scoreOfStudents, classSize);
								break;
						case 5:
								sortScore(firstNamesOfStudents,lastNamesOfStudents,scoreOfStudents, classSize);
								break;
						case 6:
								sortLastName(firstNamesOfStudents,lastNamesOfStudents,scoreOfStudents, classSize); //prints students with maximum score
								break;
						case 7:
								medianScore(firstNamesOfStudents,lastNamesOfStudents,scoreOfStudents, classSize);//prints students with lowest score
								break;
						default:
								printf("\nERROR: You did not enter a valid input. Please try again.\n\n");
					} //end of switch

			}//end of menu repeating loop
	}//end of conditional statement
			//error cases
	else if ( classSize < studentsMIN) //error statements in case class is to small
	{
			printf("\n\nERROR: You must enter at least 5 students.\nIf you would like to use the program again please rerun it.");
			printf("\n\n");
	}
	printf("\n");
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------
//                        	***Functions down here***
//----------------------------------------------------------------------------------------------------------------------------

/*


	Displays the information of all students in the class.

	required inputs:
			1 character pointer of 2D character array for first name
			1 character pointer of 2D character array for last name
			1 float array with scores of students
			1 integer which limits the size



*/


void printRecords(char **first, char** last, float *score, int size ) //needs to be fixed
{
	int i = 0;
	if(size >0)
	{
		printf("\n\nRECORD OF STUDENTS:\n\n");

		while(i != size)
		{
				printf("First Name: ");
				printf("%-20.20s",first[i]);

				printf(" , Last Name: ");
				printf("%-20.20s",last[i]);

				printf(" , Score:");
				printf("%13.2f",score[i++]); //handles score of student

				printf("\n");
		}
	}
	else
	printf("\nThere are currently no students in the database.\n\n");
}


/*


	Adds a record for a student

	required inputs:
			1 character pointer of 2D character array for first name
			1 character pointer of 2D character array for last name
			1 float array with scores of students
			1 integer which limits the size



*/

void addRecords(char ***first, char*** last, float **score, int *size )
{
	(*size)++;
	printf("\nnew class size is %d\n\n", *size);
	*first = (char **) realloc(*first , (*size) * sizeof(char*));
	*last = (char **) realloc(*last , (*size) * sizeof(char*));
	*score = (float *) realloc(*score , (*size) * sizeof(float));			
	//add a row to database ie new name
	
	(*first)[(*size)-1] = (char *) calloc(firstNameSize + 2 , sizeof(char));
	(*last)[(*size)-1] = (char *) calloc(lastNameSize + 2 , sizeof(char));


	//user input
	printf("What is the first name of the new student? ");
	fgets((*first)[(*size)-1],firstNameSize + 2,stdin);
	char *ptr;
	int j,i;
	//clean in case of a overflow.
	if((ptr = strchr((*first)[(*size)-1], '\n')))
		*ptr = 0;
	else
		{scanf("%*[^\n]");scanf("%*c");}
	
	 //discard of new line
	for(j = 0; j<firstNameSize+2;j++)
	{
	  if((*first)[(*size)-1][j] == '\n')
	  {
      	(*first)[(*size)-1][j] = '\0';
		break;
	  }
	}

	printf("What is %s's last name? ",(*first)[(*size)-1]);
	fgets((*last)[(*size)-1],lastNameSize+2,stdin);
	
	//clean in case of a overflow.
	if((ptr = strchr((*last)[(*size)-1], '\n')))
		*ptr = 0;
	else
		{scanf("%*[^\n]");scanf("%*c");}

	 //discard of new line
	for(j = 0; j<lastNameSize+2;j++)
	{
	  if((*last)[(*size)-1][j] == '\n')
	  {
	    (*last)[(*size)-1][j] = '\0';
	    break;
	  }
	}
	
	//capatalize and format names
	printf("what is the score of %s %s? ", (*first)[(*size)-1],(*last)[(*size)-1]);
	scanf("%f",&((*score)[(*size)-1]));


 	for(j = 0; j < (firstNameSize+2); j++)
	{
		if( (*first)[(*size)-1][j] >= 'a' && (*first)[(*size)-1][j] <= 'z')
			(*first)[(*size)-1][j]-=32;
		if( (*last)[(*size)-1][j] >= 'a' && (*last)[(*size)-1][j] <= 'z')
			(*last)[(*size)-1][j]-=32;
	}



	printf("\n\nOK! The new student information has been added.\n");
}
/*


	Deletes student information based on last name.

	required inputs:
			1 character pointer of 2D character array for first name
			1 character pointer of 2D character array for last name
			1 float array with scores of students
			1 integer which limits the size



*/


void deleteRecords(char ***first, char ***last, float **score, int *size )
{
	char *search = (char *) calloc(lastNameSize+2, sizeof(char)), *ptr;
	int j;
	
	printf("\nWhat is the last name? ");
	fgets(search,lastNameSize+2,stdin);
	
	//clean in case of a overflow.
	if((ptr = strchr(search, '\n')))
		*ptr = 0;
	else
		{scanf("%*[^\n]");scanf("%*c");}

	 //discard of new line
	for(j = 0; j<lastNameSize+2;j++)
	{
	  if(search[j] == '\n')
	  {
	    search[j] = '\0';
	    break;
	  }
	}
	printf("\n");
	for(j = 0; j < (lastNameSize+2); j++)
	{
		if( search[j] >= 'a' && search[j] <= 'z')
			search[j]-=32;	
	}
	char *temp = (char *) calloc(firstNameSize+2,sizeof(char)); 
	int counter = 0;
	j = 0;
	int *a = &j;
	while (*a < *size)
	{
		if(strcmp(search, (*last)[*a]) == 0)
		{
			counter++;
			strcpy(temp,(*last)[*a]);
			strcpy((*last)[*a],(*last)[(*size)-1]);
			strcpy((*last)[(*size)-1],temp);

			strcpy(temp,(*first)[*a]);
			strcpy((*first)[*a],(*first)[(*size)-1]);
			strcpy((*first)[(*size)-1],temp);

			(*score)[*a]+= (*score)[(*size)-1];
			(*score)[(*size)-1]= (*score)[*a] -(*score)[(*size)-1];
			(*score)[*a] -= (*score)[(*size)-1];			
		
			printf("Student: %s %s has been removed from database\n",(*first)[(*size)-1], (*last)[(*size)-1]);
			free((*last)[(*size)-1]);
			free((*first)[(*size)-1]);

			(*size)--;
			*last = (char**) realloc(*last, (*size)*sizeof(char*));
			*first = (char**) realloc(*first, (*size)*sizeof(char*));
			*score = (float*) realloc(*score, (*size)*sizeof(float));
			
			*a = 0; //go back to beginning
		}else
			(*a)++; //else go to next string

	}
	if(counter == 0)
		printf("Sorry, no student has that last name.\n");
	else
		printf("\n%d students were removed.\n",counter);
	free(temp);
	free(search);
	
}
/*


	Search students by last name and displays it.

	required inputs:
			1 character pointer of 2D character array for first name
			1 character pointer of 2D character array for last name
			1 float array with scores of students
			1 integer which limits the size



*/

void searchLast(char **first, char **last, float *score, int size )
{
	char *lastName = (char *)calloc(lastNameSize+2,sizeof(char));
	int i;


	//get user input
	printf("\nEnter the student's last name you want to search for: ");
	fgets(lastName,lastNameSize+2,stdin);
	//matching with procedure done before
		char *ptr;
			 if((ptr = strchr(lastName, '\n')))
			 {
				 *ptr = 0;
			 }
			 else{
					scanf("%*[^\n]");scanf("%*c");
			 }
	for(i = 0; i < lastNameSize+2;i++)
	{
			if(lastName[i] == '\n')
			{
					lastName[i] = '\0';
					break;
			}
	}

	//cleans stdin so fgets for last name doesnt read in excess
	clearerr(stdin);

	//capatalize the letters of query search if lower case
	int match = 0;
	for(i = 0; i<  lastNameSize+2; i++)
	{
			if(lastName[i] >= 'a' && lastName[i] <= 'z')
			{
					lastName[i]-=32;
			}
	}

	//error case to see if matches exist
	for(i =0; i< size; i++)
	{
			if(strcmp(lastName,last[i]) == 0)
			{
					match = 1;
			}
	}

	if(match)
	{
			printf("\n\nSTUDENTS WITH LAST NAME OF %s:\n\n",lastName);

			//compare query search to class information by adding individual characters and seeing if they equal 0
			for(i =0; i< size; i++)
			{
					if(strcmp(lastName,last[i]) == 0)
					{
							printf("First Name: ");
							printf("%-20.20s",first[i]);

							printf(" , Last Name: ");
							printf("%-20.20s",last[i]);

							printf(" , Score:");
							printf("%13.2f",score[i]); //handles score of student
							printf("|\n");
					}
			}
	}else
	{
			printf("\n\nSorry no one in the class has the last name of %s\n\n",lastName);
	}
}


/*


	Sort the student information by score and displays it.

	required inputs:
			1 character pointer of 2D character array for first name
			1 character pointer of 2D character array for last name
			1 float array with scores of students
			1 integer which limits the size



*/

void sortScore(char **first, char **last, float *score, int size )
{
	int i,j;

	char *swapFirst = (char *) calloc (firstNameSize + 2, sizeof(char));
	char *swapLast = (char *) calloc(lastNameSize + 2, sizeof(char));
	//bubble sort it
	for(i = 0; i< size-1; i++)
	{
			for(j = 0; j< size-1-i; j++)
			{
					if(score[j] < score[j+1])
					{
							//swap score values
							score[j]+=score[j+1];
							score[j+1] = score[j] - score[j+1];
							score[j]-=score[j+1];

							//swap first
							strcpy(swapFirst, first[j+1] );
							strcpy(first[j+1] , first[j] );
							strcpy(first[j], swapFirst );

							//swap last
							strcpy(swapLast, last[j+1] );
							strcpy(last[j+1] , last[j] );
							strcpy(last[j], swapLast );
					}
			}
	}
	free(swapFirst);
	free(swapLast);

	printf("\n\nSORTED RECORD OF STUDENTS BY SCORE:\n\n");

	i = 0;
	while(i != size)
	{
					printf("First Name: ");
					printf("%-20.20s",first[i]);

					printf(" , Last Name: ");
					printf("%-20.20s",last[i]);

					printf(" , Score:");
					printf("%13.2f",score[i++]); //handles score of student

					printf("\n");
	}

	//indicater to prove data has been printed
}

/*


	Sort the student information by last name and displays it.

	required inputs:
			1 character pointer of 2D character array for first name
			1 character pointer of 2D character array for last name
			1 float array with scores of students
			1 integer which limits the size



*/
void sortLastName(char **first, char **last, float *score, int size )
{
	int i,j;

	char *swapFirst = (char *) calloc (firstNameSize + 2, sizeof(char));
	char *swapLast = (char *) calloc(lastNameSize + 2, sizeof(char));

	//bubble sort it
	for(i = 0; i< size-1; i++)
	{
			for(j = 0; j< size-1-i; j++)
			{
					if(strcmp(last[j] , last[j+1])   > 0)
					{
							//swap score values
							score[j]+=score[j+1];
							score[j+1] = score[j] - score[j+1];
							score[j]-=score[j+1];

							//swap first
							strcpy(swapFirst, first[j+1] );
							strcpy(first[j+1] , first[j] );
							strcpy(first[j], swapFirst );

							//swap last
							strcpy(swapLast, last[j+1] );
							strcpy(last[j+1] , last[j] );
							strcpy(last[j], swapLast );
					}
			}
	}
	free(swapFirst);
	free(swapLast);
	printf("\n\nSORTED RECORD OF STUDENTS BY LAST NAME:\n\n");

	i = 0;
	while(i != size)
	{
					printf("First Name: ");
					printf("%-20.20s",first[i]);

					printf(" , Last Name: ");
					printf("%-20.20s",last[i]);

					printf(" , Score:");
					printf("%13.2f",score[i++]); //handles score of student

					printf("\n");
	}

}


/*


	Searches for Median score and then displays student information above the median and displays it.

	required inputs:
		1 character pointer of 2D character array for first name
		1 character pointer of 2D character array for last name
		1 float array with scores of students
		1 integer which limits the size



*/



void medianScore(char **first, char **last, float *score, int size )
{
	//reuse sorting code from other function
	int i,j,median;

	char *swapFirst = (char *) calloc (firstNameSize + 2, sizeof(char));
	char *swapLast = (char *) calloc(lastNameSize + 2, sizeof(char));
	//bubble sort it
	for(i = 0; i< size-1; i++)
	{
			for(j = 0; j< size-1-i; j++)
			{
					if(score[j] < score[j+1])
					{
							//swap score values
							score[j]+=score[j+1];
							score[j+1] = score[j] - score[j+1];
							score[j]-=score[j+1];

							//swap first
							strcpy(swapFirst, first[j+1] );
							strcpy(first[j+1] , first[j] );
							strcpy(first[j], swapFirst );

							//swap last
							strcpy(swapLast, last[j+1] );
							strcpy(last[j+1] , last[j] );
							strcpy(last[j], swapLast );
					}
			}
	}
	free(swapFirst);
	free(swapLast);

	//find median score
	median = size/2;
	if(size % 2 != 0) //if size is odd then it is middle value
	{
		printf("MEDIAN SCORE IS %f\nTHESE ARE THE STUDENTS WITH A SCORE ABOVE %f: \n\n",score[median],score[median]);
		for(i =0; i != size; i++)
		{
			if(score[median] < score[i])
				{
					printf("First Name: ");
					printf("%-20.20s",first[i]);

					printf(" , Last Name: ");
					printf("%-20.20s",last[i]);

					printf(" , Score:");
					printf("%13.2f",score[i]); //handles score of student

					printf("\n");
				}
		}
	}else
	{
		printf("MEDIAN SCORE IS %f\nTHESE ARE THE STUDENTS WITH A SCORE ABOVE %f: \n\n",( score[median] + score[median-1]) / 2.0, (score[median] + score[median-1]) / 2.0);
		for(i =0; i != size; i++)
		{
			if( (score[median] + score[median-1]) / 2.0 < score[i])
			{
				printf("First Name: ");
				printf("%-20.20s",first[i]);

				printf(" , Last Name: ");
				printf("%-20.20s",last[i]);

				printf(" , Score:");
				printf("%13.2f",score[i]); //handles score of student

				printf("\n");
			}
		}
	}
}
