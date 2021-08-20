
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes
int countlines (char*);
void writeToFile (char*, char*);
void newUser(char*, char*);
int fileExists(char* filename);
int searchFile (char*, int);
void loginFunc(char*, char*, char*, int*, char*);
void HUD(int, char*);
int hashification(char*);
char* itoa(int, char*, int);

//ident 1 = username, ident 2 = password
//return 1 if string found, 0 if not
//made an int to accomodate future possibility of >2 search identifiers
int searchFile (char* string, int ident) {
  FILE* fp;
  fp = fopen("USERS.txt", "r");
  char temp[512];
  
  //username handling
  if (ident == 1) {
    while(fgets(temp, 512, fp) != NULL) {
      if(strstr(temp, string)) {
        fclose(fp);
        return 1;
      }
    }
    fclose(fp);
    return 0;
  }

  //password handling
  else if (ident == 2) {
    if (strstr(temp,string) != NULL) {
      fclose(fp);
      return 1;
    }
  }
  fclose(fp);
  return 0;
}

//counts the number of lines or "records" in 'filename'
int countlines (char* filename){
    FILE* fp;
    fp = fopen(filename, "r");
    int nlines = 0;
    char c;

    c = fgetc(fp);

    //checks for new line character to determine number of entries
    while (c != EOF){
        c = fgetc(fp);
        if(c == '\n') nlines++;
    }
    return nlines;
}

//appends 'string' to 'filename'
void writeToFile (char* filename, char* string){
    FILE* fp;
    fp = fopen(filename, "a");
    fputs(string, fp);
    fputs("\n", fp);
    fclose(fp);
}

char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

//adds a new user record to 'filename'
void newUser(char* filename, char* exitString){
    char input1[50];
    char input2[50];
    char finalWrite[100] = "";
    
    do {
    printf("Enter Username:\n");
    scanf("%s", input1);
    if (searchFile(input1, 1) == 1) {
      
      printf("\nUsername arleady exists, try again? y/n\n");
      scanf("%s", input1);
    }
    else {
      strcat(finalWrite, input1);

    do{
        printf("Enter Password:\n");
        scanf("%s", input1);

        printf("Verify Password:\n");
        scanf("%s", input2);
    } while(strcmp(input1, input2) != 0);

    strcat(finalWrite, ",");
    itoa(hashification(input1), input1, 10);
    strcat(finalWrite, input1);

    //count amount of current records in file and increments by 1 for new record
    int numRecords = countlines(filename) + 1;

    //convert username, user count, password to USERS.txt format
    sprintf(input1, "%i,", numRecords);
    strcat(input1, finalWrite);

    writeToFile(filename, input1);
    }
      } while(strcmp(input1, exitString) == 0);
      
}

//checks if file exists
int fileExists(char* filename) {
    FILE* fp;

    if (fp == fopen(filename, "r")) {
        fclose(fp);
        return 1;
    }
    else return 0;
}

void loginFunc(char* userInput1, char* userInput2, char* exitString, int* loginStatus, char* username) {
  printf("Enter Username:\n");
  scanf("%s", userInput1);
  strcpy(username, userInput1);

  // encapsulate in commas to prevent password AND user# false positives
  strcat(userInput1, ",");
  char newString[5] = ",";
  strcat(newString,userInput1);

  //copy username in separate variable for repeated password attempts to not fuck it up
  char newStringCopy[20];
  strncpy(newStringCopy, newString, 20);

  //search file with 1 as string type identifier = ,username,
  if (searchFile(newString, 1) == 1) {
    do{
      //reset exitString comparator
      strncpy(userInput2, exitString, 2);
      //reset newStringCopy to original string for failed attempts
      strncpy(newStringCopy, newString, 20);
      
      printf("Username Found. Enter Password:\n");
      scanf("%s", userInput1);
      itoa(hashification(userInput1), userInput1, 10);

      //append password to login string for search
      strcat(newStringCopy,userInput1);

      //search file with 2 as string type identifier = ,username,password
      if (searchFile(newStringCopy, 2) == 0) {
        printf("Invalid Username/Password Combo\nTry again? y/n\n");
        scanf("%s", userInput2);
      }
      else {
        printf("Login Successful af\n");
        *loginStatus += 1;
        
        //break the loop
        strcat(userInput2, "hi");
      }
    } while(strcmp(userInput2, exitString) == 0);
  }
  else if (searchFile(newString, 1) == 0) {
  printf("Invalid Username. Returning to Menu\n");
  }
}

//create function prototype
void HUD (int loginStatus, char* username){
  if (loginStatus == 0) {
    printf("\n<Not Logged In>\n(1) Create File\n(2) Create User\n(3) Login\n(9) Debug\n(0) Exit\n");
  }
  else {
    printf("\n<%s> Logged In\n(1) Create File\n(2) Create User\n(3) Log Off\n(4) Messages\n(9) Debug\n(0) Exit\n", username);
  }
}

int hashification(char* input1){
  int hashAddress = 0;
    int counter;
    for (counter = 0; input1[counter]!='\0'; counter++){
        hashAddress = input1[counter] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
    }
  return hashAddress;
}

int main(){
    int running = 1;
    int loginStatus = 0;
    char userInput1[25];
    char userInput2[25];
    char exitString[5] = "y";
    char username[25];
    char c;
    FILE* fp;

    while(running) {
        HUD(loginStatus, username);
        scanf("%s", userInput1);

        //create file
        if (userInput1[0] == '1') {
            printf("Enter New File Name\n");
            scanf("%s", userInput1);
            if (fileExists(userInput1) == 0) {
                printf("Creating New File. Enter file content: %s\n", userInput2);
                scanf("%s", userInput2);
                writeToFile(userInput1, userInput2);
            }
            else {
                printf("File already Exists.  Returning to Main Menu\n");
            }
        }
       
        //create user
        else if (userInput1[0] == '2') newUser("USERS.txt", exitString);

        //login or logoff
        else if (userInput1[0] == '3') {
          if (loginStatus == 0) {
          loginFunc(userInput1, userInput2, exitString, &loginStatus, username);
          }
          else if (loginStatus == 1) {
            loginStatus = 0;
            printf("\n%s Successfully Logged off\n", username);
          }
        }

        //messages (if logged in only)
        else if (userInput1[0] == '4' & loginStatus ==1) {
          printf("this be placeholder\n");
        }
        
        //debug
        else if (userInput1[0] == '9') {
          scanf("%s",userInput1);
          printf("%d", hashification(userInput1));
        }

        //exit
        else if (userInput1[0] == '0') running = 0;

        
    }

    return 0;
}