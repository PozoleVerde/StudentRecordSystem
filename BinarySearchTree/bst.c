#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define firstNameSize 20
#define lastNameSize 20
#define studentsMIN 5
#define studentsMAX 15

struct Student{
  int ID;
  char firstName[firstNameSize+2];
  char lastName[lastNameSize+2];
  float score;
  char zipcode[32];
  struct Student *left;
  struct Student *right;
};
int zipfound = 0;
char buffer;
int *sizeptr;
int k = 0;
void sort(float arr[], int n);
void swap(float *x, float *y);
int found(struct Student *root,int id);
struct Student *NewNode(int id);
struct Student *insert(int id, struct Student *root);
float findMedian(float arr[],int n);
void deleteAll(struct Student *root);

void printRecords(struct Student *root,int size);
struct Student *addStudent(struct Student *root);
struct Student *deleteStudent(struct Student *root, char info[]);
void searchZip(struct Student *root, char *zip);
void rangeScore(struct Student *root, float min, float max);
void median(struct Student *root, float med);
void BSTtoARR(struct Student *root, float num[]);

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
    struct Student *root = NULL;
		printf("\n\nPLEASE READ: When entering the students name you will be asked to input first name and last name separatly, please: \n");
		printf("\tDO NOT INPUT MIDDLE NAMES\n");
		printf("\tDO NOT INPUT FIRST NAME AND LAST NAME IN ONE LINE\n");
		printf("\tDO NOT WORRY ABOUT CAPATILIZATION, ALL LETTERS WILL AUTOMATICALLY CAPATILIZED\n");
		printf("\tSEPARATE THEM WITH A NEW LINE!\n\n");

    //class data
		for(i = 0; i < classSize;){
      int id;
      printf("What is the student's ID Number? ");
      scanf("%d",&id);
      scanf("%c",&buffer);
      if(1000 <= id && id <= 1100)
        if(!found(root,id)){
          root = insert(id,root);
          i++;
        }else
          printf("ID number %d already exists. Please try again.\n",id);
      
      else
        printf("Sorry the ID is invalid. Range must be between 1000 and 1100.\n");
		}

  	int repeatFunction = 1;
  	while(repeatFunction){
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
  		switch(functionNumber){
  			case 0:
  				printf("\nThank you for using the program!\n\nThe program will now exit.\n");
          deleteAll(root);
          root = NULL;
  				repeatFunction = 0;
  				break;
  			case 1:
          printf("\n\nRECORD OF STUDENTS:\n\n");
  				printRecords(root, classSize);
  				break;
        case 2:
  				scanf("%c",&buffer);
  				root = addStudent(root);
          printf("\nClass size has increased by 1. New class Size is %d\n\n",++(*sizeptr));
  				break;
        
  			case 3:
          {
            scanf("%c",&buffer);
            char info[lastNameSize+2];
            printf("Enter the last name of the student: ");
            fgets(info, lastNameSize+2,stdin);
            char *ptr;
            if((ptr = strchr(info, '\n')))//cleans stdin so fgets for first name doesnt read in excess
              *ptr = 0;
            else{
              scanf("%*[^\n]");
              scanf("%*c");
            }
            for(i = 0; i < lastNameSize + 2; i++)
              if(info[i] == '\n'){ //fgets stores new line so it must be disposed of
                info[i] = '\0'; //cuts name off
                break;
              }
            for(i = 0; i < lastNameSize + 2; i++){
              if(info[i] >= 'a' && info[i] <= 'z')
                info[i]-=32;
            }
            for(i = 0; i < classSize + 1; i++)
              root = deleteStudent(root, info);
            if(!zipfound)
              printf("\nNo students were deleted.\n");
            zipfound = 0;
          }
  				break;
  			case 4:
  				{
            scanf("%c",&buffer);
            char input[32];
            printf("What is the zipcode you want to search? ");
            fgets(input,32,stdin);
            char *ptr;
            if((ptr = strchr(input, '\n')))//cleans stdin
              *ptr = 0;
            else{
              scanf("%*[^\n]");scanf("%*c");
            }
            for(j = 0; j < 32; j++)//discard of new line
              if(input[j] == '\n'){
                input[j] = '\0';
                break;
              }
            printf("\n\nSTUDENTS WITH ZIPCODE %s:\n\n",input);
            searchZip(root, input);
            if(!zipfound)
              printf("\nNo one exist with the zipcode %s.\n",input);
            zipfound = 0;
          }
  				break;
  			case 5:
          {
            float max,min;int valid = 0;
            while(!valid){ 
              printf("Enter the maximum: ");
              scanf("%f",&max);
              printf("Enter the minimum: ");
              scanf("%f", &min);
              if(max < min)
                printf("Not valid, please try again. Minimum cannot be greater than maximum.\n");
              else 
                valid = 1;
            } 
            printf("\nSTUDENTS WITHIN THE RANGE OF [%.2f , %.2f]:\n\n",min,max);
            rangeScore(root,min,max);
            if(!zipfound)
              printf("\nNo one is within the range of [%.2f,%.2f].\n",min,max);
            zipfound = 0;
          }
  				break;
  			case 6:
          {
            float grade [*sizeptr];
            BSTtoARR(root, grade);
            sort(grade, *sizeptr);
            printf("\nSTUDENTS WITH A SCORE ABOVE THE MEDIAN %.2f:\n\n",findMedian(grade,*sizeptr));
            k = 0;
            median(root,findMedian(grade,*sizeptr));
            k = 0;
          }
  				break;
  			default:
  				printf("\nERROR: You did not enter a valid input. Please try again.\n\n");
  			}
  		}
  	}
  //error cases
	else if (classSize < studentsMIN){ //error statements in case class is to small
			printf("\n\nERROR: You must enter at least 5 students.\nIf you would like to use the program again please rerun it.");
			printf("\n\n");
	}

  printf("\n");
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------
//                        	***Functions down here***
//----------------------------------------------------------------------------------------------------------------------------

void printRecords(struct Student *root, int size){
    if(root == NULL){
      return;
    }
    printRecords(root->left,size);
    
    printf("ID: ");
    printf("%-4d",root->ID);
    printf(" , First Name: ");
    printf("%-20.20s",root->firstName);
    printf(" , Last Name: ");
    printf("%-20.20s",root->lastName);
    printf(" , Score: ");
    printf("%-13.2f",root->score);
    printf(" , Zip Code: ");
    printf("%-s",root->zipcode);
    printf("\n");

    printRecords(root->right,size);
}
struct Student *addStudent(struct Student *root){
  int id, i = 0;
  while(i != 1){
    printf("What is the student's ID Number? ");
    scanf("%d",&id);
    scanf("%c",&buffer);
    if(1000 <= id && id <= 1100)
      if(!found(root,id)){
        root = insert(id,root);
        i++;
      }else
        printf("ID number %d already exists. Please try again.\n",id);  
    else
      printf("Sorry the ID is invalid. Range must be between 1000 and 1100.\n");
  }
  return root;
}
struct Student *deleteStudent(struct Student *root, char info[]){
  if(*sizeptr < 0){
    printf("There is nothing to delete.\n");
    return root;
  }
  if(root == NULL)
    return root;

  root->left = deleteStudent(root->left,info);
  root->right = deleteStudent(root->right,info); 
  
  if(strcmp(root->lastName,info) == 0){
    (*sizeptr)--;
    zipfound = 1;
    printf("%s %s was deleted. New class size is %d\n",root->firstName,root->lastName,*sizeptr);
    
    if(root->left == NULL && root->right == NULL){
      free(root);
      root = NULL;
    }else if(root->left == NULL){
      struct Student *temp = root;
      root = root->right;
      free(temp);
    }else if(root->right == NULL){
      struct Student *temp = root;
      root = root->left;
      free(temp);
    }else{
      struct Student *temp;
      for(temp = root; temp->left != NULL; temp = temp->left);
      root->ID = temp->ID;
      strcpy(root->firstName, temp->firstName);
      strcpy(root->lastName, temp->lastName);
      root->score = temp->score;
      strcpy(root->zipcode,temp->zipcode);
      root->right = deleteStudent(root->right,info);
   }
   return root;
  }
  
  root->right = deleteStudent(root->right,info);
  return root;
}
void searchZip(struct Student *root, char *input){
  if(*sizeptr < 0){
    printf("There is nothing to search.\n");
    return;
  }
  if(root == NULL)
    return;
  searchZip(root->left,input);
  if(strcmp(root->zipcode,input) == 0){
    zipfound = 1;
    printf("ID: ");
    printf("%-4d",root->ID);
    printf(" , First Name: ");
    printf("%-20.20s",root->firstName);
    printf(" , Last Name: ");
    printf("%-20.20s",root->lastName);
    printf(" , Score: ");
    printf("%-13.2f",root->score);
    printf(" , Zip Code: ");
    printf("%-s",root->zipcode);
    printf("\n");
  }
  searchZip(root->right,input);
}
void rangeScore(struct Student *root, float min, float max){
  if(*sizeptr < 0){
    printf("\nThere is nothing to display.\n");
    return;
  }
  if(root == NULL)
    return;
  rangeScore(root->left,min,max);
  if(root->score >= min && root->score <= max){
    zipfound = 1;
    printf("ID: ");
    printf("%-4d",root->ID);
    printf(" , First Name: ");
    printf("%-20.20s",root->firstName);
    printf(" , Last Name: ");
    printf("%-20.20s",root->lastName);
    printf(" , Score: ");
    printf("%-13.2f",root->score);
    printf(" , Zip Code: ");
    printf("%-s",root->zipcode);
    printf("\n");
  }
  rangeScore(root->right,min,max);
}
void median(struct Student *root, float med){
  if(*sizeptr < 0){
    printf("\nThere is nothing to display.\n");
    return;
  }
  if(root == NULL)
    return;
  median(root->left, med);
  if(root->score > med){
    zipfound = 1;
    printf("ID: ");
    printf("%-4d",root->ID);
    printf(" , First Name: ");
    printf("%-20.20s",root->firstName);
    printf(" , Last Name: ");
    printf("%-20.20s",root->lastName);
    printf(" , Score: ");
    printf("%-13.2f",root->score);
    printf(" , Zip Code: ");
    printf("%-s",root->zipcode);
    printf("\n");
  }
  median(root->right,med);
}


void BSTtoARR(struct Student *root, float num[]){
  if(root == NULL)
    return;
  BSTtoARR(root->left, num);
  num[k++] = root->score;
  BSTtoARR(root->right, num);
}
void swap(float *x, float *y){
  float temp;
  temp = *x;
  *x = *y;
  *y = temp;
}
void sort(float arr[], int n){
  int i,j;
  for(i = 0; i < n; i++) //binary sort scores
    for(j = 0; j < n -1 - i; j++)
      if(arr[j] > arr[j+1]){
        swap(&arr[j], &arr[j+1]);
      }
}
float findMedian(float arr[],int n){
  if(n % 2 == 0)
    return ( arr[n/2] + arr[n/2 - 1]) / 2.0;
  else 
    return arr[n/2];
}
int found(struct Student *root,int id){
  if(root == NULL)
    return 0;
  if(root->ID == id)
    return 1;
  else if(root->ID < id)
    return found(root->right, id);
  else
    return found(root->left, id);
}
struct Student *NewNode(int id){
  struct Student *info = (struct Student *) malloc( sizeof(struct Student) );
  info->ID = id;
  
  printf("What is the first name of the student? ");
  fgets(info->firstName, firstNameSize+2,stdin);

  char *ptr;
  if((ptr = strchr(info->firstName, '\n')))//cleans stdin so fgets for last name doesnt read in excess
    *ptr = 0;
  else{
    scanf("%*[^\n]");
    scanf("%*c");
  }
  int i;
  for(i = 0; i < firstNameSize + 2; i++)	//discard of new line
    if(info->firstName[i] == '\n'){
      info->firstName[i] = '\0';
      break;
    }

  printf("What is the last name of %s? ", info->firstName );
  fgets(info->lastName, lastNameSize+2,stdin);

  if((ptr = strchr(info->lastName, '\n')))//cleans stdin so fgets for first name doesnt read in excess
    *ptr = 0;
  else{
    scanf("%*[^\n]");
    scanf("%*c");
  }

  for(i = 0; i < lastNameSize + 2; i++)
    if(info->lastName[i] == '\n'){ //fgets stores new line so it must be disposed of
      info->lastName[i] = '\0'; //cuts name off
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
  for(i = 0; i < 32; i++)//discard of new line
    if(info->zipcode[i] == '\n'){
      info->zipcode[i] = '\0';
      break;
    }

  printf("\n");
  info->right = NULL;
  info->left = NULL;
  for(i = 0; i < firstNameSize + 2; i++){
    if(info->firstName[i] >= 'a' && info->firstName[i] <= 'z')
      info->firstName[i]-=32;
    if(info->lastName[i] >= 'a' && info->lastName[i] <= 'z')
      info->lastName[i]-=32;
  }
  return info;
}
struct Student *insert(int id, struct Student *root){
  if(root == NULL)
    return NewNode(id);
  else if(root->ID >= id)
    root->left = insert(id, root->left);
  else
    root->right = insert(id, root->right);
  return root;
}
void deleteAll(struct Student *root){
  if(root == NULL)
    return;
  deleteAll(root->left);
  deleteAll(root->right);
  free(root);
}

