#define MaxUsers 400
typedef struct
{
    char firstName[30];
    char lastName[30];
    char username[30];
    char password[30];
    char email[30];
    int librarian;
}User;

extern User *users[MaxUsers];
extern char fName[30];
extern char lName[30];
extern char uName[30];
extern char pWord[30];
extern char address[30];
extern int numUsers;
extern int userIndex;

int login(int checker);
int registerDetails(int check);
void readUsers();
void loginMenu();