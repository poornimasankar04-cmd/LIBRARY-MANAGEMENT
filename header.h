#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define BOOK_FILE "books.dat"
#define ISSUE_FILE "issued_books.dat"

#define TITLE_SIZE 100
#define AUTHOR_SIZE 100
#define USER_NAME_SIZE 100

#define DUE_DAYS 7
#define FINE_PER_DAY 5

/* =========================
   BOOK STRUCTURE
   ========================= */

struct Book
{
    int bookID;
    char title[TITLE_SIZE];
    char author[AUTHOR_SIZE];
    int quantity;
};

/* =========================
   ISSUE STRUCTURE
   ========================= */

struct Issue
{
    int issueID;
    int bookID;
    int userID;
    char userName[USER_NAME_SIZE];

    char issueDate[11];
    char dueDate[11];
    char returnDate[11];

    float fineAmount;
    int returned;
};

/* =========================
   FUNCTION DECLARATIONS
   ========================= */

void addBook();
void updateBook();
void updateByID();
void updateByName();

void removeBook();
void removeByID();
void removeByName();

void searchBook();
void searchByID();
void searchByName();
void searchByAuthor();

void viewAllBooks();

void issueBook();
void returnBook();
void listIssuedBooks();

void saveData();

int bookExists(int id);
int getNextIssueID();

void getCurrentDate(char date[]);
void getDueDate(char issueDate[], char dueDate[]);

int calculateLateDays(char dueDate[], char returnDate[]);

void clearInputBuffer();
void pauseScreen();

int containsIgnoreCase(char text[], char search[]);
