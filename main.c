#include "book_management.h"
#include "loans.h"
#include "regOrLogin.h"
#include <stdio.h>
#include <stdlib.h>

// ********************************************************************************************************************
/// Place for variables to be assigned

char next[40];
FILE *p;
int requestId = 0;

/// End of Variable assignment
// ********************************************************************************************************************

void menu(){
    printf("Please choose an option\n");
    printf("1) Register an account\n");
    printf("2) Login\n");
    printf("3) Quit\n");
}

void searchBook(){
    printf("Loading search menu...\n");
    printf("Please choose an option:\n");
    printf("1) Find books by title\n");
    printf("2) Find books by author\n");
    printf("3) Find books by year\n");
    printf("4) Return to previous menu\n");
}

void menuStudent(){
    printf("Please choose an option\n");
    printf("1) Borrow a book\n");
    printf("2) Return a book\n");
    printf("3) Search for books\n");
    printf("4) Display for books\n");
    printf("5) Logout\n");
}


int inputChecker(char response[40]){
    char *temp;
    int checker = strtol(response,&temp,10);
    if (checker == 0){
        return 0;
    }else if (checker == 1){
        return 1;
    } else if (checker == 2){
        return 2;
    }else if (checker == 3){
        return 3;
    }else if (checker == 4){
        return 4;
    }else if (checker == 5){
        return 5;
    }else{
        return 0;
    }
}
int  main (int argc, char* argv[])
{
    load_books(p);
    readLoans();
    readUsers();
    int menuChecker = 1;
    while (menuChecker){
        menu();
        //scanf(" %i", &response);
        scanf (" %[^\n]%*c", next);
        if (inputChecker(next) == 1){
            if(registerDetails(1) == -1){
                printf("Registration failed");
            }
        }else if (inputChecker(next) == 2) {
           if(login(1) >= 0){
               int loginMenuChecker = 1;
               if (users[userIndex]->librarian==1){
                   menuChecker = 0;
                   printf("[Welcome back: %s]\n",users[userIndex]->username);
                   while (loginMenuChecker){
                       // get the index of the user who has logged in
                       loginMenu();
                       scanf (" %[^\n]%*c", next);
                       if (inputChecker(next) == 1){
                           if (users[userIndex]->librarian==1){
                               books[numBooks] = (struct Book *) malloc(sizeof (struct Book));
                               add_book(*books[numBooks]);
                           }else{
                               printf("You must be an admin to add a book\n");
                           }
                           // Add a book
                       } else if (inputChecker(next) == 2){
                           if (users[userIndex]->librarian==1){
                               remove_book(*books[numBooks-1]);
                           }else{
                               printf("You must be an admin to add a book\n");
                           }
                           // Remove a book
                       } else if (inputChecker(next) == 3){
                           int optionLoop = 1;
                           while (optionLoop){
                               searchBook();
                               int searchYear = 0;
                               scanf("%s",next);
                               char response1[40];
                               if (inputChecker(next) == 1){
                                   printf("Please enter the title of the book you want to search:\n");
                                   scanf (" %[^\n]%*c", response1);
                                   find_book_by_title(response1);
                                   // Find books by title
                               }else if (inputChecker(next) == 2){
                                   printf("Please enter the author(s) of the book you want to search:\n");
                                   scanf (" %[^\n]%*c", response1);
                                   find_book_by_author(response1);
                                   // Find books by author
                               }else if (inputChecker(next) == 3){
                                   printf("Please enter the year the book you want to search was released:\n");
                                   scanf ("%i", &searchYear);
                                   find_book_by_year(searchYear);
                                   // Find books by year
                               }else if (inputChecker(next) == 4){
                                   optionLoop = 0;
                               }else{
                                   printf("Option not recognised!\n");
                               }

                           }
                           // Search for a book
                       } else if (inputChecker(next) == 4){
                           display_books();
                           // Display all books
                       } else if (inputChecker(next) == 5){
                           printf("Logging out....\n");
                           loginMenuChecker = 0;
                           store_books(p);
                           writeLoans();
                           menuChecker = 1;
                       }
                   }
               }else{
                   printf("[Welcome back: %s]\n",users[userIndex]->username);
                   while (loginMenuChecker){
                       menuStudent();
                       scanf (" %[^\n]%*c", next);
                       if (inputChecker(next) == 1){
                           display_books();
                           printf("Please enter the ID of the book you want to borrow:\n");
                           scanf("%i",&requestId);
                           setLoan();
                       }else if (inputChecker(next) == 2){
                           printf("Here are the books you are currently borrowing:\n");
                           printLoans();
                           printf("\nPlease enter the ID of the book you want to return:\n");
                           scanf("%i",&requestId);
                           if (returnBook() == 1){
                               printf("Book successfully returned!\n");
                           }else{
                               printf("Book could not be found!\n");
                           }

                       }else if (inputChecker(next) == 3){
                           int optionLoop = 1;
                           while (optionLoop) {
                               searchBook();
                               int searchYear = 0;
                               scanf("%s", next);
                               char response1[40];
                               if (inputChecker(next) == 1) {
                                   printf("Please enter the title of the book you want to search:\n");
                                   scanf(" %[^\n]%*c", response1);
                                   find_book_by_title(response1);
                                   // Find books by title
                               } else if (inputChecker(next) == 2) {
                                   printf("Please enter the author(s) of the book you want to search:\n");
                                   scanf(" %[^\n]%*c", response1);
                                   find_book_by_author(response1);
                                   // Find books by author
                               } else if (inputChecker(next) == 3) {
                                   printf("Please enter the year the book you want to search was released:\n");
                                   scanf("%i", &searchYear);
                                   find_book_by_year(searchYear);
                                   // Find books by year
                               } else if (inputChecker(next) == 4) {
                                   optionLoop = 0;
                               } else {
                                   printf("Option not recognised!\n");
                               }
                           }
                       }else if (inputChecker(next) == 4){
                           display_books();

                       }else if (inputChecker(next) == 5){
                           printf("Logging out....\n");
                           loginMenuChecker = 0;
                           store_books(p);
                           writeLoans();
                           menuChecker = 1;
                       }
                   }
               }
           }else{
               printf("Invalid username/password. Please try again!\n");
           }
        } else if (inputChecker(next) == 3) {
            // Quit
            printf("Thank you for using the library!\n");
            printf("Goodbye!");
            menuChecker = 0;
            exit(0);
        } else if (inputChecker(next) == 0){
            printf("Please select a valid option\n");
        }
        // Returns -1 if the option is invalid
    }
}

//

