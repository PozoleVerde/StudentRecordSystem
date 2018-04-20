#include <stdio.h>
#include <string.h>

#define firstNameSize 20
#define lastNameSize 20
#define studentsMIN 5
#define studentsMAX 15

void printRecords(char *first, char* last, float score[], int size );
void searchFirst(char *first, char* last, float score[], int size );
void searchLast(char *first, char* last, float score[], int size );
void sortScore(char *first, char* last, float score[], int size );
void sortLastName(char *first, char* last, float score[], int size );
void maxScore(char *first, char* last, float score[], int size );
void minScore(char *first, char* last, float score[], int size );

int main()
{
	printf("\nThis program will store and manage student records through the use of menus.\n\n");
	//determine how many students are in the class

	int classSize;
	printf("How many students are in the class? ");
	scanf("%d",&classSize);


	if(classSize >= studentsMIN && classSize <= studentsMAX) //is class size within range of lab requirements?
	{
		
		//store first names and last names in one 2D character array

		char firstNamesOfStudents[classSize][firstNameSize+2];
		char lastNamesOfStudents[classSize][lastNameSize+2];
		float scoreOfStudents[classSize]; //stores grades
		int i,j;
		
		//populate both arrays with spaces to make table easier
			
		for(i =0; i< classSize; i++)
		{
			for( j = 0; j < firstNameSize+2; j++)
			{
				firstNamesOfStudents[i][j] = ' ';
				lastNamesOfStudents[i][j] = ' ';
			}
		}
			
			
		//get input for names of students and grades
		char buffer;
		scanf("%c",&buffer); //takes in \n so fgets works properly
		
		
		printf("\n\nPLEASE READ: When entering the students name you will be asked to input first name and last name separatly, please: \n");
		printf("\tDO NOT INPUT MIDDLE NAMES\n");
	  printf("\tDO NOT INPUT FIRST NAME AND LAST NAME IN ONE LINE\n");
		printf("\tDO NOT WORRY ABOUT CAPATILIZATION, ALL LETTERS WILL AUTOMATICALLY CAPATILIZED\n");
	  printf("\tSEPARATE THEM WITH A NEW LINE!\n\n");
		
		//student information
		
		for(i = 0; i < classSize; i++)
		{
			
			//firstname
			printf("What is the first name of student %d? ", i+1 ); //first name
			fgets(firstNamesOfStudents[i], firstNameSize+2,stdin);
			for(j = 0; j<firstNameSize+2;j++)
			{
				if(firstNamesOfStudents[i][j] == '\n')
				{
					firstNamesOfStudents[i][j] = '\0';
					break;
				}
			}
			//cleans stdin so fgets for last name doesnt read in excess
			if(firstNamesOfStudents[i][firstNameSize+1] == '\0' && firstNamesOfStudents[i][firstNameSize] != '\n')
			{
				int toss;
				while(((toss = fgetc(stdin))!='\n') && toss!=EOF){
				}
			}
			
			//last name
			
			printf("What is the last name of %s? ", firstNamesOfStudents[i] ); //last name
			fgets(lastNamesOfStudents[i], lastNameSize+2,stdin);
			//cleans stdin so fgets for first name doesnt read in excess
			for(j = 0; j<lastNameSize+2;j++)
			{
				if(lastNamesOfStudents[i][j] == '\n') //fgets stores new line so it must be disposed of
				{
					lastNamesOfStudents[i][j] = '\0'; //cuts name off
					break;
				}
			}
			if(lastNamesOfStudents[i][lastNameSize+1] == '\0' && lastNamesOfStudents[i][lastNameSize] != '\n')
			{
				int toss;
				while( ((toss = fgetc(stdin))!='\n') && toss!=EOF){
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
			char *firstName = firstNamesOfStudents[0];
			char *lastName = lastNamesOfStudents[0];			

			printf("\nThe following commands are used in the program. Input the number of the function you want to input.\n");
			printf("\tFor example, if you want to print records of all students please input 1.\n");

			printf("____________________________________________________________________________ \n");
			printf("|Function Number|                        Description                        |\n");
			printf("|_______________|___________________________________________________________|\n");
			printf("|       1       |Print Records of all students                              |\n");
			printf("|       2       |Find a student(s) through first name                       |\n");
			printf("|       3       |Find a student(s) through last name                        |\n");
			printf("|       4       |List records of students in decending order based on scores|\n");
			printf("|       5       |List records of students in alphabetical order             |\n");
			printf("|       6       |Find student(s) with highest scores                        |\n");
			printf("|       7       |Find student(s) with lowest score                          |\n");
			printf("|       0       |Exit program                                               |\n");
			printf("|_______________|___________________________________________________________|\n");
			printf("\nWhat do you want to do?\n\n");

			int functionNumber;
			scanf("%d",&functionNumber);
			
			//execute function based on switch statement

			switch(functionNumber)
			{
				case 0: 
					printf("\n\nThank you for using the program!\n\nThe program will now exit.\n\n");
					repeatFunction = 0;
					break;
				case 1:
					printRecords(firstName,lastName,scoreOfStudents, classSize);
					break;
				case 2:
					scanf("%c",&buffer);
					searchFirst(firstName,lastName,scoreOfStudents, classSize);
					break;
				case 3:
					scanf("%c",&buffer);
					searchLast(firstName,lastName,scoreOfStudents, classSize);		
					break;
				case 4:
					sortScore(firstName,lastName,scoreOfStudents, classSize);
					break;
				case 5:
					sortLastName(firstName,lastName,scoreOfStudents, classSize);
					break;
				case 6:
					maxScore(firstName,lastName,scoreOfStudents, classSize); //prints students with maximum score
					break;
				case 7:
					minScore(firstName,lastName,scoreOfStudents, classSize); //prints students with lowest score
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
	else if ( classSize > studentsMAX ) //error statements in case class is to big
	{
		printf("\n\nERROR: Your class is too big (>15) for this program\nIf you would like to use the program again please rerun it.");
		printf("\n\n");		
	}
	printf("\n");
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------
//							***Functions down here***
//----------------------------------------------------------------------------------------------------------------------------

/*


	Displays the information of all students in the class.
	
	required inputs:
		1 character pointer of 2D character array for first name
		1 character pointer of 2D character array for last name
		1 float array with scores of students
		1 integer which limits the size
	
	

*/


void printRecords(char *first, char* last, float score[], int size ) //needs to be fixed
{
	int i = 0,j ;
	
	printf("\n\nRECORD OF STUDENTS:\n\n");
	printf("_________________________________________________________\n");
	printf("|     First Name     |      Last Name     |    Score    |\n");
	printf("|____________________|____________________|_____________|\n");

	while(i != size)
	{
		printf("|");	
		printf("%-20.20s",first);
		first+=firstNameSize+2;
		
		printf("|");
		printf("%-20.20s",last);
		last+=lastNameSize+2;
		
		printf("|");
		printf("%13.2f",score[i++]); //handles score of student

		printf("|\n");			   
	}
	printf("|____________________|____________________|_____________|\n");
	//indicater to prove data has been printed
}


/*


	Search students by first name and displays it.
	
	required inputs:
		1 character pointer of 2D character array for first name
		1 character pointer of 2D character array for last name
		1 float array with scores of students
		1 integer which limits the size
	
	

*/

void searchFirst(char *first, char* last, float score[], int size )
{
	char firstName[firstNameSize+2];
	int i;
	for(i =0; i < firstNameSize+2; i++)
	{
		firstName[i] = ' ';
	}
	
	//get user input	
	printf("\nEnter the student's first name you want to search for: ");
	fgets(firstName,firstNameSize+2,stdin);
	//matching with procedure done before
	for(i = 0; i < firstNameSize+2;i++)
	{
		if(firstName[i] == '\n')
		{
			firstName[i] = '\0';
			break;
		}
	}
	//cleans stdin so fgets for last name doesnt read in excess
	if(firstName[firstNameSize+1] == '\0' && firstName[firstNameSize] != '\n')
	{
		int toss;
		while(((toss = fgetc(stdin))!='\n') && toss!=EOF){
		}
	}
	
	
	//capatalize the letters of query search if lower case
	int match = 0;
	for(i = 0; i<  firstNameSize+2; i++)
	{
		if(firstName[i] >= 'a' && firstName[i] <= 'z')
		{
			firstName[i]-=32;
		}
	}

	//error case to see if matches exist
	for(i =0; i< size; i++)
	{
		if(strcmp(firstName,first+((firstNameSize+2)*i)) == 0)
		{
			match = 1;
		}
	}
	
	if(match)
	{
		printf("\n\nSTUDENTS WITH FIRST NAME OF %s:\n\n",firstName);
		printf("_________________________________________________________\n");
		printf("|     First Name     |      Last Name     |    Score    |\n");
		printf("|____________________|____________________|_____________|\n");

		//compare query search to class information by adding individual characters and seeing if they equal 0
		for(i =0; i< size; i++)
		{
			if(strcmp(firstName,first+((firstNameSize+2)*i)) == 0)
			{
				printf("|");	
				printf("%-20.20s",first+((firstNameSize+2)*i));

				printf("|");
				printf("%-20.20s",last+((lastNameSize+2)*i));

				printf("|");
				printf("%13.2f",score[i]); //handles score of student			
				printf("|\n");
			}	
		}
		printf("|____________________|____________________|_____________|\n");
	}else
	{
		printf("\n\nSorry no one in the class has the first name of %s\n\n",firstName); 
	}
}

/*


	Search students by last name and displays it.
	
	required inputs:
		1 character pointer of 2D character array for first name
		1 character pointer of 2D character array for last name
		1 float array with scores of students
		1 integer which limits the size
	
	

*/

void searchLast(char *first, char* last, float score[], int size )
{
	char lastName[lastNameSize+2];
	int i;
	for(i =0; i < lastNameSize+2; i++)
	{
		lastName[i] = ' ';
	}
	
	//get user input	
	printf("\nEnter the student's last name you want to search for: ");
	fgets(lastName,lastNameSize+2,stdin);
	//matching with procedure done before
	for(i = 0; i < lastNameSize+2;i++)
	{
		if(lastName[i] == '\n')
		{
			lastName[i] = '\0';
			break;
		}
	}
	//cleans stdin so fgets for last name doesnt read in excess
	if(lastName[lastNameSize+1] == '\0' && lastName[lastNameSize] != '\n')
	{
		int toss;
		while(((toss = fgetc(stdin))!='\n') && toss!=EOF){
		}
	}
	
	
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
		if(strcmp(lastName,last+((lastNameSize+2)*i)) == 0)
		{
			match = 1;
		}
	}
	
	if(match)
	{
		printf("\n\nSTUDENTS WITH LAST NAME OF %s:\n\n",lastName);
		printf("_________________________________________________________\n");
		printf("|     First Name     |      Last Name     |    Score    |\n");
		printf("|____________________|____________________|_____________|\n");

		//compare query search to class information by adding individual characters and seeing if they equal 0
		for(i =0; i< size; i++)
		{
			if(strcmp(lastName,last+((lastNameSize+2)*i)) == 0)
			{
				printf("|");	
				printf("%-20.20s",first+((firstNameSize+2)*i));

				printf("|");
				printf("%-20.20s",last+((lastNameSize+2)*i));

				printf("|");
				printf("%13.2f",score[i]); //handles score of student			
				printf("|\n");
			}	
		}
		printf("|____________________|____________________|_____________|\n");
	}else
	{
		printf("\n\nSorry no one in the class has the last name of %s\n\n",lastName); 
	}
}	


/*


	Sort the student information by and displays it.
	
	required inputs:
		1 character pointer of 2D character array for first name
		1 character pointer of 2D character array for last name
		1 float array with scores of students
		1 integer which limits the size
	
	

*/

void sortScore(char *first, char* last, float score[], int size )
{
	int i,j;
	
	char swapFirst[firstNameSize + 2];
	char swapLast[lastNameSize + 2]; 
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
				strcpy(swapFirst, first + ( (firstNameSize + 2) * (j+1)) );
				strcpy(first + ( (firstNameSize + 2) * (j+1) ), first + ((firstNameSize + 2) * j ) );
				strcpy(first + ( (firstNameSize + 2) * j), swapFirst );
				
				//swap last
				strcpy(swapLast, last + ( (lastNameSize + 2) * (j+1)) );
				strcpy(last + ( (lastNameSize + 2) * (j+1) ), last + ((lastNameSize + 2) * j ) );
				strcpy(last + ( (lastNameSize + 2) * j), swapLast );				
			}
		}
	}
	
	printf("\n\nSORTED RECORD OF STUDENTS BY SCORE:\n\n");
	printf("_________________________________________________________\n");
	printf("|     First Name     |      Last Name     |    Score    |\n");
	printf("|____________________|____________________|_____________|\n");

	i = 0;
	while(i != size)
	{
		printf("|");	
		printf("%-20.20s",first);
		first+=firstNameSize+2;
		
		printf("|");
		printf("%-20.20s",last);
		last+=lastNameSize+2;
		
		printf("|");
		printf("%13.2f",score[i++]); //handles score of student

		printf("|\n");			   
	}
	printf("|____________________|____________________|_____________|\n");
	//indicater to prove data has been printed
}

/*


	Sort the student information by and displays it.
	
	required inputs:
		1 character pointer of 2D character array for first name
		1 character pointer of 2D character array for last name
		1 float array with scores of students
		1 integer which limits the size
	
	

*/
void sortLastName(char *first, char* last, float score[], int size )
{
	int i,j,z;
	
	char swapFirst[firstNameSize + 2];
	char swapLast[lastNameSize + 2];
	char temp;
	//bubble sort it
	for(i = 0; i< size-1; i++)
	{
		for(j = 0; j< size-1-i; j++)
		{			
			if(strcmp( last + ( (lastNameSize + 2)*j) , last + ((lastNameSize + 2) * (j+1) ) ) > 0)
			{
				//swap score values
				score[j]+=score[j+1];
				score[j+1] = score[j] - score[j+1];
				score[j]-=score[j+1];
				
				//swap first
				strcpy(swapFirst, first + ((firstNameSize + 2) * j) );
				strcpy(first + ((firstNameSize + 2) * j), first + ((firstNameSize + 2) * (j + 1)) );
				strcpy(first + ((firstNameSize + 2) * (j + 1) ), swapFirst );
				
				//swap last
				strcpy(swapLast, last + ((lastNameSize + 2) * j) );
				strcpy(last + ( (lastNameSize + 2) * j ), last + ((lastNameSize + 2) * (j + 1) ) );
				strcpy(last + ( (lastNameSize + 2) * (j + 1) ), swapLast );				
			}
		}
	}
	
	printf("\n\nSORTED RECORD OF STUDENTS BY LAST NAME:\n\n");
	printf("_________________________________________________________\n");
	printf("|     First Name     |      Last Name     |    Score    |\n");
	printf("|____________________|____________________|_____________|\n");

	i = 0;
	while(i != size)
	{
		printf("|");	
		printf("%-20.20s",first);
		first+=firstNameSize+2;
		
		printf("|");
		printf("%-20.20s",last);
		last+=lastNameSize+2;
		
		printf("|");
		printf("%13.2f",score[i++]); //handles score of student

		printf("|\n");			   
	}
	printf("|____________________|____________________|_____________|\n");
	//indicater to prove data has been printed	
	
}

/*


	Searches for Maximum score(s) of student information and displays it.
	
	required inputs:
		1 character pointer of 2D character array for first name
		1 character pointer of 2D character array for last name
		1 float array with scores of students
		1 integer which limits the size
	
	

*/


void maxScore(char *first, char* last, float score[], int size )
{
	int i = 0,j,z = 0;
	float max = score[0];
	
	printf("\n\nStudents With Highest Score:\n\n");
	printf("_________________________________________________________\n");
	printf("|     First Name     |      Last Name     |    Score    |\n");
	printf("|____________________|____________________|_____________|\n");
	
	for(i = 0; i < size; i++) //find maximum 
	{
		if(max < score[i])
		{
			max = score[i];
		}
	}
	i = 0;
	
	for(z = 0; z < size; z++) 
	{
		if(max == score[z])
		{
			printf("|");	
			printf("%-20.20s",first);
			first+=firstNameSize+2;
			printf("|");
			printf("%-20.20s",last);
			last+=lastNameSize+2;
			printf("|");

			printf("%13.2f",score[z]); //handles score of student

			printf("|\n");
		}else
		{
			first+=firstNameSize+2;
			last+=lastNameSize+2;
		}
	}
	printf("|____________________|____________________|_____________|\n");

}


/*


	Searches for Minimum score(s) of student information and displays it.
	
	required inputs:
		1 character pointer of 2D character array for first name
		1 character pointer of 2D character array for last name
		1 float array with scores of students
		1 integer which limits the size
	
	

*/



void minScore(char *first, char* last, float score[], int size )
{
	int i = 0,j,z = 0;
	float min = score[0];
	printf("\n\nStudents With lowest Score:\n\n");
	printf("_________________________________________________________\n");
	printf("|     First Name     |      Last Name     |    Score    |\n");
	printf("|____________________|____________________|_____________|\n");
	
	for(i = 0; i < size; i++) //find maximum 
	{
		if(min > score[i])
		{
			min = score[i];
		}
	}
	i = 0;
	
	for(z = 0; z < size; z++) 
	{
		if(min == score[z])
		{
			printf("|");	
			printf("%-20.20s",first);
			first+=firstNameSize+2;
			
			printf("|");
			printf("%-20.20s",last);
			last+=lastNameSize+2;
			
			printf("|");
			printf("%13.2f",score[z]); //handles score of student

			printf("|\n");
		}else
		{
			first+=firstNameSize+2;
			last+=lastNameSize+2;
		}
	}
	printf("|____________________|____________________|_____________|\n");
	//indicater to prove data has been printed

}
