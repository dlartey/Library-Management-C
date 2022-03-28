#include "loans.h"
#include "book_management.h"
#include "regOrLogin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Start of defining variables

Loan *loans[MaxLoans]; // A struct to store the loans
int numLoans = 0; // The number of loans currently by all students
FILE *l;

// End of defining variables

// Takes a loan out for a student
void setLoan(){
    loans[numLoans] = (Loan *) malloc(sizeof (Loan));

    if (checkLoan() == 1 && checkStudent() == 1){
        strcpy(loans[numLoans]->username,users[userIndex]->username);
        loans[numLoans]->id = requestId;
        numLoans+=1;
        printf("Book %i successfully taken on loan!\n",requestId);
    }else{
        printf("Loan could not be taken out!\n");
    }
}
// Returns a book on loan
// Returns 1 if book is successfully returned, else returns 0 (book wasn't loaned or could not be found)
int returnBook(){
    int tempLoan = -1;
    for (int i = 0; i < numLoans; i++){
        if (strcmp(users[userIndex]->username,loans[i]->username) == 0 && requestId == loans[i]->id){
            tempLoan = i;
            printf("Book ID: %i will now be returned\n",books[tempLoan]->id);
        }

        if (tempLoan >=0 && i != numLoans-1){
            loans[i]->id = loans[i+1]->id;
            strcpy(loans[i]->username,loans[i+1]->username);
        }
        if(tempLoan >=0 && i==numLoans-1){
            free(loans[numLoans-1]->username);
        }
    }

    if (tempLoan == -1){
        return 0;
    }else{
        numLoans = numLoans-1;
        return 1;
    }

}

// Checks that a book isn't already on loan
// Returns 0 if book is loaned out maxmimum times, else returns 1 is book isn't
// returns -1 if book id can't be found
int checkLoan(){
    int copiesChecker = 0;
    int index = -1;
    for (int i = 0; i < numLoans; i++){
        // Check that the book isn't already on loan the max times
        if (loans[i]->id == requestId){
            copiesChecker +=1;
        }
    }


    for (int a = 0; a < numBooks; a++){
        if (books[a]->id == requestId){
            index = a; //stores the index where the book is located if it is on loan
            a = numBooks;
        }

    }
    // Check that the book ID exists
    if (index == -1){
        printf("Index could not be found\n");
        return -1;
    }else{
        if (copiesChecker == books[index]->copies){
            printf("Book already loaned out maximum times!\n");
            return 0;
        }else { // Check that the requested book isn't already booked out the max times
            return 1;
        }
    }
}

// Checks that a student doesn't take the same book on loan twice
// Returns 0 if the book is already on loan to the same user, else returns 1;
int checkStudent(){
    int checker = 0;
    for (int i = 0; i < numLoans; i++){
        // Compare the current logged in user to stored username
        if (strcmp(users[userIndex]->username,loans[i]->username) == 0 && requestId == loans[i]->id){
            checker +=1;
        }
    }
    if (checker > 0){
        printf("You already have this book on loan!\n");
        return 0;
    }else{
        return 1;
    }
}

//reads the loans from the loans.txt file
void readLoans(){
    l = fopen("../loans.txt", "r");
    char input[400];
    if (l == NULL) {
        printf("Unable to read from file loans.txt\n");
    } else {
        int line = 0;
        int posCounter = 0;
        while (fgets(input, 400, l)) {
            loans[line] = (Loan *) malloc(sizeof (Loan));
            char *token = strtok(input, ",");
            posCounter = 0;
            while (token != NULL) {
                if (posCounter == 0) {
                    strcpy(loans[line]->username, token);
                } else if (posCounter == 1) {
                    sscanf(token,"%d", &loans[line]->id);
                }
                posCounter++;
                token = strtok(NULL,",");
            }
            line++;
        }
        numLoans = line;
    }
    fclose(l);
}

//Writes the loans to the loans.txt file
void writeLoans(){
    l = fopen("../loans.txt", "w");
    if (l == NULL) {
        printf("Unable to write to file loans.txt\n");
    } else {
        char tempId[20];
        for (int i = 0; i < numLoans; i++){
            char output2[400];
            strcpy(output2, loans[i]->username);
            strcat(output2, ",");
            strcpy(tempId,"");
            sprintf(tempId, "%d", loans[i]->id);
            strcat(output2,tempId);
            strcat(output2,"\n");
            fprintf(l, "%s", output2);
        }
        fclose(l);
    }
}

// Prints the loans that the user currently has
void printLoans(){
    for (int i = 0; i < numLoans; i++) {
        int tempLength = 0;
        // check for each user

        if (i == 0) {
            // 40 char gap between title and authors
            // 25 char gap between authors and year
            // 5 char gap elsewhere
            printf("id     Title                                     Authors                                 Year");
        }
        if (strcmp(users[userIndex]->username,loans[i]->username) == 0){
            int tempID = 0;
            printf("\n%i", loans[i]->id);
            if (loans[i]->id <=9) {
                printf("      ");
            } else {
                printf("     ");
            }
            for (int a = 0; a < numBooks; a++){
                if (loans[i]->id == books[a]->id){
                    tempID = a;
                    a = numBooks;
                }
            }
            printf("%s", books[tempID]->title);
            tempLength = 42 - strlen(books[tempID]->title);
            for (int b = 0; b <tempLength; b++) {
                printf(" ");
            }
            printf("%s", books[tempID]->authors);
            tempLength = 40 - strlen(books[tempID]->authors);
            for (int c = 0; c < tempLength; c++) {
                printf(" ");
            }
            printf("%i", books[tempID]->year);
        }
        }

}