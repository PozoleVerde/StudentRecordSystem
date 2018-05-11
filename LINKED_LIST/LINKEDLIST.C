#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define firstNameSize 20
#define lastNameSize 20
#define studentsMIN 5
#define studentsMAX 15

struct Student{
    char firstName[firstNameSize+2];
    char lastName[lastNameSize+2];
    float score;
    char zipcode[32];
	struct Student *next;
};
struct Student *head;

void printRecords(int size);
void addStudent();
void deleteStudent();
void searchZip();
void rangeScore();
void median();

char buffer;

int *sizeptr;

int main(){
	printf("\nThis program will store and manage student records through the use of menus.\n\n");

	int classSize;
	printf("How many students are in the class? ");
	scanf("%d",&classSize);
	scanf("%c",&buffer); //takes in \n so fgets works properly

  sizeptr = &classSize;
  int i,j;
	struct Student *temp;

  if(classSize >= studentsMIN){
		printf("\n\nPLEASE READ: When entering the students name you will be asked to input first name and last name separatly, please: \n");
		printf("\tDO NOT INPUT MIDDLE NAMES\n");
		printf("\tDO NOT INPUT FIRST NAME AND LAST NAME IN ONE LINE\n");
		printf("\tDO NOT WORRY ABOUT CAPATILIZATION, ALL LETTERS WILL AUTOMATICALLY CAPATILIZED\n");
		printf("\tSEPARATE THEM WITH A NEW LINE!\n\n");

		char *ptr;

    //class data
		for(i = 0; i<classSize; i++){
			struct Student *info = (struct Student *) malloc(sizeof(struct Student));

			printf("What is the first name of student %d? ", i+1 );
			fgets(info->firstName, firstNameSize+2,stdin);

			if((ptr = strchr(info->firstName, '\n')))//cleans stdin so fgets for last name doesnt read in excess
				*ptr = 0;
			else{
				scanf("%*[^\n]");
				scanf("%*c");
			}

			for(j = 0; j<firstNameSize+2;j++)	//discard of new line
				if(info->firstName[j] == '\n')
				{
					info->firstName[j] = '\0';
					break;
				}

			printf("What is the last name of %s? ", info->firstName );
			fgets(info->lastName, lastNameSize+2,stdin);

			if((ptr = strchr(info->lastName, '\n')))//cleans stdin so fgets for first name doesnt read in excess
				*ptr = 0;
			else{
				scanf("%*[^\n]");scanf("%*c");
			}

			for(j = 0; j<lastNameSize+2;j++)
				if(info->lastName[j] == '\n') //fgets stores new line so it must be disposed of
				{
					info->lastName[j] = '\0'; //cuts name off
					break;
				}

	    printf("What was %s %s's score? ", info->firstName, info->lastName);
			scanf("%f",&(info->score));
			scanf("%c",&buffer); //takes in new line so that fgets can work propertly

      printf("What was %s %s's zipcode? ", info->firstName, info->lastName);
			fgets(info->zipcode,32,stdin);

      if((ptr = strchr(info->zipcode, '\n')))//cleans stdin so fgets for first name doesnt read in excess
        *ptr = 0;
      else{
        scanf("%*[^\n]");scanf("%*c");
      }
      for(j = 0; j<32;j++)//discard of new line
        if(info->zipcode[j] == '\n')
        {
          info->zipcode[j] = '\0';
          break;
        }

      printf("\n");

      if(i > 0){
        temp->next = info;
        info->next = NULL;
      }
      else
        head = info;

      temp = info;
		}

		for(temp = head; temp!=NULL; temp = temp->next){//autocapatilize all letters to make sorting and searching easier for user
      for(j = 0; j < firstNameSize + 2; j++){
        if(temp->firstName[j] >= 'a' && temp->firstName[j] <= 'z')
  				temp->firstName[j]-=32;
  			if(temp->lastName[j] >= 'a' && temp->lastName[j] <= 'z')
  				temp->lastName[j]-=32;
      }
		}


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
  		printf("|       4       |Search records based on zipcodes                                    |\n");
  		printf("|       5       |Display students whose grades is within a certain range             |\n");
  		printf("|       6       |Find Median Score and print record of students who scored above it  |\n");
  		printf("|       0       |Exit program                                                        |\n");
  		printf("|_______________|____________________________________________________________________|\n");
  		printf("\nWhat do you want to do? ");

  		int functionNumber;
  		scanf("%d",&functionNumber);

  		//execute function based on switch statement
  		switch(functionNumber)
  		{
  			case 0:
  				printf("\nThank you for using the program!\n\nThe program will now exit.\n");
                
                for(i = 0; i < classSize; i++){ //free up the memory
                    temp = head->next;
                    free(head);
                    head = temp; //will result in head = null at end
                }
  				repeatFunction = 0;
  				break;
  			case 1:
  				printRecords(classSize);
  				break;
  			case 2:
  				scanf("%c",&buffer);
  				addStudent();
          printf("\nClass size has increased by 1. New class Size is %d\n\n",++classSize);
  				break;
  			case 3:
  				scanf("%c",&buffer);
  				deleteStudent();
  				break;
  			case 4:
  				scanf("%c",&buffer);
  				searchZip();
  				break;
  			case 5:
  				rangeScore();
  				break;
  			case 6:
  			    median();
  				break;
  			default:
  				printf("\nERROR: You did not enter a valid input. Please try again.\n\n");
  			}
  		}
  	}
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

void printRecords(int size){
	int i = 0;

	if(size > 0)
	{
		struct Student *temp;

    printf("\n\nRECORD OF STUDENTS:\n\n");
  	for(temp = head; temp != NULL; temp = temp->next)
    {
      printf("First Name: ");
			printf("%-20.20s",temp->firstName);

			printf(" , Last Name: ");
			printf("%-20.20s",temp->lastName);

			printf(" , Score: ");
			printf("%-13.2f",temp->score); //handles score of student

			printf(" , Zip Code: ");
			printf("%-s",temp->zipcode);

      printf("\n");
		}
	}
	else
		printf("\nThere are currently no students in the database.\n\n");
}
void addStudent(){
  struct Student *temp;
  int j;
  struct Student *info = (struct Student *) malloc(sizeof(struct Student));
  if(head == NULL) //add at beggining if nothing exists
      head = info;
  else{ //GO TO END
      for(temp = head; temp->next != NULL; temp = temp->next){
    }
    temp->next = info;
  }
  printf("What is the first name of the student ? ");
  fgets(info->firstName, firstNameSize+2,stdin);
  char *ptr;

  if((ptr = strchr(info->firstName, '\n')))//cleans stdin so fgets for last name doesnt read in excess
    *ptr = 0;
  else{
    scanf("%*[^\n]");
    scanf("%*c");
  }

  for(j = 0; j<firstNameSize+2;j++)	//discard of new line
    if(info->firstName[j] == '\n'){
      info->firstName[j] = '\0';
      break;
    }

  printf("What is the last name of %s? ", info->firstName );
  fgets(info->lastName, lastNameSize+2,stdin);

  if((ptr = strchr(info->lastName, '\n')))//cleans stdin so fgets for first name doesnt read in excess
    *ptr = 0;
  else{
    scanf("%*[^\n]");scanf("%*c");
  }

  for(j = 0; j<lastNameSize+2;j++)
    if(info->lastName[j] == '\n') //fgets stores new line so it must be disposed of
    {
      info->lastName[j] = '\0'; //cuts name off
      break;
    }

  printf("What was %s %s's score? ", info->firstName, info->lastName);
  scanf("%f",&(info->score));
  scanf("%c",&buffer); //takes in new line so that fgets can work propertly

  printf("What was %s %s's zipcode? ", info->firstName, info->lastName);
  fgets(info->zipcode,32,stdin);

  if((ptr = strchr(info->zipcode, '\n')))//cleans stdin so fgets for first name doesnt read in excess
    *ptr = 0;
  else{
    scanf("%*[^\n]");scanf("%*c");
  }
  for(j = 0; j<32;j++)//discard of new line
    if(info->zipcode[j] == '\n')
    {
      info->zipcode[j] = '\0';
      break;
    }
  for(j = 0; j < firstNameSize + 2; j++){
        if(info->firstName[j] >= 'a' && info->firstName[j] <= 'z')
  				info->firstName[j]-=32;
  		if(info->lastName[j] >= 'a' && info->lastName[j] <= 'z')
  				info->lastName[j]-=32;
      }

  info->next = NULL;
}
void deleteStudent(){
  char last[lastNameSize+2], *ptr;
  int j;

  if(head == NULL){
      printf("\nThere are no students to delete.\n");
      return;
  }
  printf("\nWhat is the student's last name? ");
  fgets(last, lastNameSize+2, stdin);

  if((ptr = strchr(last, '\n')))//cleans stdin so fgets for first name doesnt read in excess
    *ptr = 0;
  else{
    scanf("%*[^\n]");scanf("%*c");
  }
  for(j = 0; j<lastNameSize+2;j++)
    if( last[j] == '\n') //fgets stores new line so it must be disposed of
      last[j] = '\0'; //cuts name off


  for(j = 0; j < lastNameSize + 2; j++){
    if(last[j] >= 'a' && last[j] <= 'z')
      last[j]-=32;
  }
  printf("\n");

  struct Student *temp, *prev = head;

  int removed = 0;
  for(temp = head; temp != NULL;){
    if(strcmp(temp->lastName, last) == 0){
      removed = 1;
      (*sizeptr)--;
      printf("%s %s has been removed.\n",temp->firstName,temp->lastName);
      //temp = head needed to restart linear search
      if(temp == head){ //determine if thing being removed is header
        head = temp->next;
        free(temp);
        temp = head;
      }else{
        prev->next = temp->next;
        free(temp);
        temp = head;
      }
    }else{
      prev = temp; //update previous value to hold discarded value
      temp = temp->next;
    }
  }
  if(removed)
      printf("New class size is %d\n",*sizeptr);
  else
      printf("No student's were found with last name %s\n",last);
}
void searchZip(){
  if(head == NULL){
      printf("\nThere is nothing to search\n");
      return;
  }
  int j;
  char input[32];


  printf("What is the zipcode you want to search? ");
  fgets(input,32,stdin);
  char *ptr;
  if((ptr = strchr(input, '\n')))//cleans stdin
    *ptr = 0;
  else{
    scanf("%*[^\n]");scanf("%*c");
  }
  for(j = 0; j<32;j++)//discard of new line
    if(input[j] == '\n'){
      input[j] = '\0';
      break;
    }

  struct Student *temp;
  j = 1; //reusing j variable as a found variable

  printf("\n\nSTUDENTS WITH ZIPCODE %s:\n\n",input);
  for(temp = head; temp !=NULL; temp = temp->next)
    if(strcmp(input,temp->zipcode) == 0){
      printf("First Name: ");
      printf("%-20.20s",temp->firstName);

      printf(" , Last Name: ");
      printf("%-20.20s",temp->lastName);

      printf(" , Score: ");
      printf("%-13.2f",temp->score); //handles score of student

      printf(" , Zip Code: ");
      printf("%-s",temp->zipcode);
      printf("\n");
      j = 0;
    }

  if(j)
    printf("No students found that zipcode.\n");

}

void rangeScore(){
    if(head == NULL){
        printf("\nThere are no students to search.\n");
        return;
    }
    float min, max;
    int bubble;
    struct Student *temp, *ahead = NULL, *swap = (struct Student *)malloc(sizeof(struct Student));
    do{
        bubble = 0;
        for(temp = head;temp->next != ahead;temp = temp->next){
            if(temp->score < temp->next->score){
            bubble = 1;
            strcpy(swap->firstName, temp->next->firstName);
            strcpy(swap->lastName, temp->next->lastName);
            swap->score = temp->next->score;
            strcpy(swap->zipcode, temp->next->zipcode);

            strcpy(temp->next->firstName,temp->firstName);
            strcpy(temp->next->lastName,temp->lastName);
            temp->next->score = temp->score;
            strcpy(temp->next->zipcode, temp->zipcode);

            strcpy(temp->firstName, swap->firstName);
            strcpy(temp->lastName, swap->lastName);
            temp->score = swap->score;
            strcpy(temp->zipcode,swap->zipcode);
            }
    }
    ahead = temp;
    }while(bubble);

    
    printf("Enter the minimum: ");
    scanf("%f", &min);
    printf("Enter the maximum: ");
    scanf("%f",&max);

    if(min >=max){
        printf("\nERROR: The minimum is larger than the maximum.\nPlease try again.\n");
        return;
    }
    int within = 0;
    printf("\nSTUDENTS WITHIN THE RANGE OF [%.2f , %.2f]:\n\n",min,max);
    for(temp = head; temp != NULL; temp = temp->next)
    {
        if(temp->score >= min && temp->score <=max){
            within = 1;
            printf("First Name: ");
            printf("%-20.20s",temp->firstName);

            printf(" , Last Name: ");
            printf("%-20.20s",temp->lastName);

            printf(" , Score: ");
            printf("%-13.2f",temp->score); //handles score of student

            printf(" , Zip Code: ");
            printf("%-s",temp->zipcode);

            printf("\n");
        }
    }    
    if(!within)
        printf("There are no students within that range.\n");
}

void median(){
  struct Student *temp,*ahead = NULL,*swap = (struct Student *) malloc(sizeof(struct Student));
  //sort data
  if(head == NULL){
      printf("\nNo students in database.\n");
      return;
  }
  int bubble;
  do{
    bubble = 0;
    for(temp = head;temp->next != ahead;temp = temp->next){
        if(temp->score < temp->next->score){
        bubble = 1;
        strcpy(swap->firstName, temp->next->firstName);
        strcpy(swap->lastName, temp->next->lastName);
        swap->score = temp->next->score;
        strcpy(swap->zipcode, temp->next->zipcode);

        strcpy(temp->next->firstName,temp->firstName);
        strcpy(temp->next->lastName,temp->lastName);
        temp->next->score = temp->score;
        strcpy(temp->next->zipcode, temp->zipcode);

        strcpy(temp->firstName, swap->firstName);
        strcpy(temp->lastName, swap->lastName);
        temp->score = swap->score;
        strcpy(temp->zipcode,swap->zipcode);
        }
    }
    ahead = temp;
  }while(bubble);
  
  float median;
  int i;
  temp = head;

  if(((*sizeptr)) % 2 == 0){
      for(i = 0; i < (*sizeptr)/2 - 1; i++)
          temp = temp->next;
      median = (temp->score + temp->next->score)/2.0;
  }else{
      for(i = 0; i < ((*sizeptr)/2 ); i++)
          temp = temp->next;
      
      median = temp->score;
  }
      printf("\nSTUDENTS WITH A SCORE ABOVE THE MEDIAN %.2f:\n\n",median);
    
  for(temp = head; temp != NULL; temp = temp->next)
  {
      if(temp->score > median)
      {
                printf("First Name: ");
                printf("%-20.20s",temp->firstName);

                printf(" , Last Name: ");
                printf("%-20.20s",temp->lastName);

                printf(" , Score: ");
                printf("%-13.2f",temp->score); //handles score of student

                printf(" , Zip Code: ");
                printf("%-s",temp->zipcode);

                printf("\n");
      }
   }
  


  free(swap);
}
