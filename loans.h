#define MaxLoans 400
typedef struct
{
    char username[40]; // username of the user who has taken a loan
    int id; //id of the book the user has taken
}Loan;

extern Loan *loans[MaxLoans]; // A struct to store the loans
extern int numLoans; // The number of loans currently by all students
extern int requestId; // the id of the book the user wants to borrow

void setLoan(); // Takes a loan out for a student
int returnBook(); // Returns a book on loan
int checkLoan(); // Checks that a book isn't already on loan
int checkStudent(); //Checks that a student doesn't take the same book on loan twice
void readLoans(); //reads the loans from the loans.txt file
void writeLoans(); //Writes the loans to the loans.txt file
void printLoans(); // Prints the loans that the user currently has
