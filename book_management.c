#include "book_management.h"
#include "loans.h"
#include "regOrLogin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ********************************************************************************************************************
//Start of defining variables

struct Book *books[MaxBooks];
struct BookArray *bA[3];
int numBooks; // number of books currently in the program
char title[40];
char authors[40];
int year =0;
int copies = 0;
int titleCounter = 0;
int yearCounter = 0;
int authorCounter =0;
//End of defining variables
// ********************************************************************************************************************



int store_books(FILE *file){
    file = fopen("../books.txt", "w");
    if (file == NULL) {
        printf("Unable to write to file books.txt\n");
    }else{
        char temYear[10];
        char tempCopies[100];
        for (int i = 0; i < numBooks; i++){
            char output1[400];
            sprintf(output1, "%d", books[i]->id);
            strcat(output1, ";");
            strcat(output1, books[i]->title);
            strcat(output1, ";");
            strcat(output1, books[i]->authors);
            strcat(output1, ";");
            strcpy(temYear,"");
            sprintf(temYear, "%d", books[i]->year);
            strcat(output1,temYear);
            strcat(output1, ";");
            strcpy(tempCopies,"");
            sprintf(tempCopies, "%d", books[i]->copies);
            strcat(output1,tempCopies);
            strcat(output1,"\n");
            fprintf(file, "%s", output1);
        }
        fclose(file);
        return 0;
    }


}

int load_books(FILE *file) {
    file = fopen("../books.txt", "r");
    char input[400];
    if (file == NULL) {
        printf("Unable to read from file books.txt\n");
    } else {
        int line = 0;
        int posCounter = 0;
        while (fgets(input, 400, file)) {
            books[line] = (struct Book *) malloc(sizeof(struct Book));
            char *token = strtok(input, ";");
            posCounter = 0;
            while (token != NULL) {
                if (posCounter == 0) {
                    sscanf(token, "%d", &books[line]->id);
                    //printf("id books array: %i\n",books[line]->id);
                } else if (posCounter == 1) {
                    books[line]->title = (char *) malloc(sizeof(char) * 50);
                    strcpy(books[line]->title, token);
                    //printf("Book title: %s\n",books[line]->title);

                } else if (posCounter == 2) {
                    books[line]->authors = (char *) malloc(sizeof(char) * 50);
                    strcpy(books[line]->authors, token);
                    //printf("Author name:%s\n",books[line]->authors);

                } else if (posCounter == 3) {
                    sscanf(token, "%d", &books[line]->year);
                } else if (posCounter == 4) {
                    sscanf(token, "%d", &books[line]->copies);
                    //printf("copies: %i\n",books[line]->copies);
                }

                posCounter++;
                token = strtok(NULL, ";");

            }
            line++;


        }
        numBooks = line;
        return 0;
    }
    fclose(file);
}

int add_book(struct Book book){
        printf("Enter the title of the book you wish to add:\n");
        scanf (" %[^\n]%*c", title);
        printf("Enter the authors of the book you wish to add:\n");
        scanf (" %[^\n]%*c", authors);
        printf("Enter the year that the book you wish to add was released:\n");
        scanf("%i",&year);
        printf("Enter the number of copies of the book you wish to add:\n");
        scanf("%i",&copies);

        if (year < 0 || year > 2021 || copies <= 0){
            printf("Book copies or year are invalid!\n");
        }else {
            int highest = -1;
            // making sure 2 books don't have the same id
            for (int i = 0; i < numBooks; i++){
                if (books[i]->id > highest){
                    highest = books[i]->id;
                }
            }
            books[numBooks]->id = numBooks+1;
            books[numBooks]->title = (char *) malloc(sizeof(char) * 50);
            books[numBooks]->authors = (char *) malloc(sizeof(char) * 50);
            strcpy(books[numBooks]->title,title);
            strcpy(books[numBooks]->authors,authors);
            books[numBooks]->year = year;
            books[numBooks]->copies = copies;
            printf("Book id %i\n",books[numBooks]->id);
            printf("Book title :%s\n",books[numBooks]->title);
            printf("Book authors: %s\n",books[numBooks]->authors);
            printf("Book year: %i\n",books[numBooks]->year);
            printf("Book copies: %i\n",books[numBooks]->copies);
            numBooks = numBooks+1;
            return 0;
        }
        /*
        book.title = (char *) malloc(sizeof(char) * 50);
        book.authors = (char *) malloc(sizeof(char) * 50);
        book.id = highest+1;
        strcpy(book.title,title);
        printf("Book title (book): %s & title: %s\n",book.title,title);
        strcpy(book.authors,authors);
        book.year = year;
        book.copies = copies;
        books[numBooks]->id = book.id;
        fflush(stdin);
        printf("Book id %i\n",books[numBooks]->id);
        printf("Book title :%s",books[numBooks]->title);
        printf("Book authors: %s",books[numBooks]->authors);
        printf("Book year: %i",books[numBooks]->year);
        printf("Book copies: %i",books[numBooks]->copies);
        */
    }

void display_books(){
    for (int i = 0; i < numBooks; i++) {
        int tempLength = 0;
        if (i == 0) {
            // 40 char gap between title and authors
            // 25 char gap between authors and year
            // 5 char gap elsewhere
            printf("id     Title                                             Authors                                         Year     Copies");
        }
        printf("%i", books[i]->id);
        if (books[i]->id <=9) {
            printf("      ");
        } else {
            printf("     ");
        }
        printf("%s", books[i]->title);
        tempLength = 50 - strlen(books[i]->title);
        for (int a = 0; a <tempLength; a++) {
            printf(" ");
        }
        printf("%s", books[i]->authors);
        tempLength = 48 - strlen(books[i]->authors);
        for (int b = 0; b < tempLength; b++) {
            printf(" ");
        }
        printf("%i", books[i]->year);
        if (books[i]->copies <= 9) {
            printf("       ");
        } else {
            printf("      ");
        }
        printf("%i", books[i]->copies);
        printf("\n");
    }
} // Displays all the books in the Book struct

int remove_book(struct Book book){

        // Get input from the user about which book to remove
        printf("Please enter book title\n");
        scanf (" %[^\n]%*c", title);
        printf("Please enter book author(s)\n");
        scanf (" %[^\n]%*c", authors);
        printf("Please enter the year the book was released\n");
        scanf("%i",&year);

        // Check that the book isn't on loan
        int tempIndex = -1;
        int onLoan = 0;

        //Loop through all the books and find a matching book
        for (int i = 0; i < numBooks; i++){
            if (strcmp(books[i]->title,title) == 0 && strcmp(books[i]->authors,authors) == 0 && books[i]->year == year){
                tempIndex=i;
            }
            for (int b = 0; b < numLoans; b++){
                if (tempIndex !=-1){
                    if (books[tempIndex]->id == loans[b]->id){
                        onLoan = 1;
                    }
                }
            }

            //Move other books to n-1 position if tempindex has been assigned a value(book to remove has been found)
            if (tempIndex>=0 && i!=numBooks-1 && onLoan == 0){
                //Copy each element, e.g. books[i]->id = books[i+1]->id;
                books[i]->id = books[i+1]->id;
                books[i]->year = books[i+1]->year;
                books[i]->copies = books[i+1]->copies;
                strcpy(books[i]->authors,books[i+1]->authors);
                strcpy(books[i]->title,books[i+1]->title);
            }
            if(tempIndex>=0 && i==numBooks-1 && onLoan == 0){
                free(books[numBooks-1]->authors);
                free(books[numBooks-1]->title);
                free(books[numBooks-1]);
            }
        }
        if (tempIndex == -1 || onLoan == 1){
            printf("Book can't be removed!\n");
        }else{
            numBooks = numBooks-1;
            printf("Book removed!\n");
            return 0;
        }
    }

struct BookArray find_book_by_author (const char *author) {
    bA[1] = (struct BookArray *) malloc(sizeof(struct BookArray));
    int authC = 0;
    for (int i = 0; i < numBooks; i++) {
        // use strstr to compare, and if true use a counter to set it valid and write to array in bookarray
        if (strstr(books[i]->authors, author)) {
            if (authC == 0){
                bA[1]->array = (struct Book *) malloc(sizeof(struct Book) * numBooks);
            }
            authC+=1;
            bA[1]->array[authorCounter] = *books[i];
            authorCounter+=1;
            bA[1]->length = authorCounter;
        }
    }
    if (authC ==0){
        bA[1]->array = NULL;
        bA[1]->length = 0;
    }
    bookArraySearch(1);
    return *bA[1];
}

struct BookArray find_book_by_year (unsigned int year) {
    bA[2] = (struct BookArray *) malloc(sizeof(struct BookArray));
    int yearC = 0;
    for (int i = 0; i < numBooks; i++) {
        // use strstr to compare, and if true use a counter to set it valid and write to array in bookarray
        if (books[i]->year == year) {
            if (yearC == 0){
                bA[2]->array = (struct Book *) malloc(sizeof(struct Book) * numBooks);
            }
            yearC+=1;
            bA[2]->array[yearCounter] = *books[i];
            yearCounter += 1;
            bA[2]->length = yearCounter;
        }
    }
    if (yearC ==0){
        bA[2]->array = NULL;
        bA[2]->length = 0;
    }
    bookArraySearch(2);
    return *bA[2];
}

struct BookArray find_book_by_title (const char *title){
    bA[0] = (struct BookArray *) malloc(sizeof (struct BookArray));
    int titleC = 0; // counter for checking if a title exists
    for (int i = 0; i< numBooks; i++){
        // use strstr to compare, and if true use a counter to set it valid and write to array in bookarray
        if (strstr(books[i]->title,title)){
            if (titleC == 0){
                bA[0]->array = (struct Book *) malloc(sizeof(struct Book) * numBooks);
            }
            titleC +=1;
            bA[0]->array[titleCounter] = *books[i];
            printf("%s\n",bA[0]->array[titleCounter].title);
            titleCounter+=1;
            bA[0]->length = titleCounter;
        }
    }
    if (titleC ==0){
        bA[0]->array = NULL;
        bA[0]->length = 0;
    }else{
        bookArraySearch(0);
    }
    return *bA[0];
}

void bookArraySearch(int index){
    for (int i = 0; i < bA[index]->length; i++){
        int tempLength = 0;
        if (i == 0) {
            // 40 char gap between title and authors
            // 25 char gap between authors and year
            // 5 char gap elsewhere
            printf("id     Title                                     Authors                                 Year     Copies");
        }
        printf("\n%i", bA[index]->array[i].id);
        if (bA[index]->array[i].id <=9) {
            printf("      ");
        } else {
            printf("     ");
        }
        printf("%s", bA[index]->array[i].title);
        tempLength = 42 - strlen(bA[index]->array[i].title);
        for (int a = 0; a <tempLength; a++) {
            printf(" ");
        }
        printf("%s", bA[index]->array[i].authors);
        tempLength = 40 - strlen(bA[index]->array[i].authors);
        for (int b = 0; b < tempLength; b++) {
            printf(" ");
        }
        printf("%i", bA[index]->array[i].year);
        if (bA[index]->array[i].copies <= 9) {
            printf("       ");
        } else {
            printf("      ");
        }
        printf("%i", bA[index]->array[i].copies);
        if (i == (bA[index]->length) -1){
            printf("\n");
        }
    }
}//Prints the books from search