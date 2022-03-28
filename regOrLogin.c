#include "regOrLogin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ********************************************************************************************************************
// Place for variables

FILE *p;
User *users[MaxUsers];
int numUsers = 0;
int userIndex = 0;
char fName[30];
char lName[30];
char uName[30];
char pWord[30];
char address[30];
int numUsers;

// End of variables
// ********************************************************************************************************************

// Writes a new user from resgistration to the files
void writeUsers() {
    p = fopen("../details.txt", "a");
    char output[200];
    if (p == NULL) {
        printf("Unable to write to file details.txt\n");
    } else {
        strcpy(output,"\n");
        strcat(output, fName);
        strcat(output, " ");
        strcat(output, lName);
        strcat(output, " ");
        strcat(output, uName);
        strcat(output, " ");
        strcat(output, pWord);
        strcat(output, " ");
        strcat(output, address);
        strcat(output, " ");
        strcat(output, "2");
        fprintf(p, "%s", output);
        fclose(p);

        users[numUsers] = (User *)malloc(sizeof (User));
        strcpy(users[numUsers]->firstName, fName);
        strcpy(users[numUsers]->lastName, lName);
        strcpy(users[numUsers]->username, uName);
        strcpy(users[numUsers]->password, pWord);
        strcpy(users[numUsers]->email, address);
        users[numUsers]->librarian = 2;
        numUsers += 1;
    }
}

// Interface for the login menu
void loginMenu(){
    printf("Please choose an option\n");
    printf("1) Add a book\n");
    printf("2) Remove a book\n");
    printf("3) Search for books\n");
    printf("4) Display all books\n");
    printf("5) Log out\n");
}

// Reads users from the details.txt file
void readUsers(){
    FILE *p;
    p = fopen("../details.txt","r");
    char input[200];
    int line = 0;
    int posCounter = 0;
    while (fgets(input,200,p)){
       // printf("Line number = %i\n",line);
        users[line] = (User *) malloc(sizeof (User));
        char *token = strtok(input," ");
        posCounter = 0;
        while (token != NULL){
            // create a separate counter here
            //printf("Poscounter = %i\n",posCounter);
            //printf( "%s\n", token );
            if (posCounter == 0){
                strcpy(users[line]->firstName,token);
            }else if (posCounter == 1){
                strcpy(users[line]->lastName,token);

            }else if (posCounter == 2){
                strcpy(users[line]->username,token);

            }else if (posCounter == 3){
                strcpy(users[line]->password,token);

            }else if (posCounter == 4){
                strcpy(users[line]->email,token);

            }else if (posCounter == 5){
                sscanf(token,"%d",&users[line]->librarian);

            }
            posCounter++;
            token = strtok(NULL, " ");
        }
        line ++;
        numUsers = line;
        //printf("******************\n");
    }
    fclose(p);

}

// Checks that the user's registration details are valid
int registerDetails(int check){
    int atCounter = 0; // counter for checking @ sign in email
    int duplicateUser = 0; // counter for checking username isn't duplicate
    printf("Enter first name\n");
    scanf("%s",&fName);
    printf("Enter first name\n");
    scanf("%s",&lName);
    printf("Enter username\n");
    scanf("%s",&uName);
    printf("Enter password\n");
    scanf("%s",&pWord);
    printf("Enter email address\n");
    scanf("%s",&address);

    for (int i = 0; i < strlen(address); i++){
        if (address[i] == '@'){ // checks there is a @ sign in user email
            atCounter = atCounter+1;
        }
    }

    for (int i = 0; i < numUsers; i++){ // check how to get number of users
        if (strcmp(users[i]->username,uName) == 0){
            duplicateUser+=1; // checks that the username isn't duplicate
        }
    }

    if (atCounter == 0){
        printf("Invalid email address");
        check  = -1;
    }
    if (duplicateUser > 0){
        printf("Username taken!\n");
        check = -1;
    }
    if (check != -1){
        writeUsers();
    }
    return check;
}

// Method for checking that the user's login details are valid
int login(int checker){
    printf("Enter username\n");
    scanf("%s",&uName);
    printf("Enter password\n");
    scanf("%s",&pWord);
    int count = -1;

    for (int i = 0; i < numUsers; i++){
        if (strcmp(users[i]->username,uName)== 0 && strcmp(users[i]->password,pWord) == 0){
            count = i;
            userIndex = i;
            i = numUsers;
        }
    }
    return count;
}