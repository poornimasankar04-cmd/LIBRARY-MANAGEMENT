/* =========================
   ISSUE BOOK
   ========================= */
#include"header.h"

void issueBook()
{
    FILE *bookFile;
    FILE *issueFile;

    struct Book book;
    struct Issue issue;

    int bookID;
    int found = 0;

    printf("\n========== ISSUE BOOK ==========\n");

    printf("Enter Book ID: ");
    scanf("%d", &bookID);
    clearInputBuffer();

    bookFile = fopen(BOOK_FILE, "r+b");

    if (bookFile == NULL)
    {
        printf("No books found.\n");
        return;
    }

    while (fread(&book, sizeof(struct Book), 1, bookFile))
    {
        if (book.bookID == bookID)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Book not found.\n");
        fclose(bookFile);
        return;
    }

    if (book.quantity <= 0)
    {
        printf("Book is not available.\n");
        fclose(bookFile);
        return;
    }

    printf("Enter User ID: ");
    scanf("%d", &issue.userID);
    clearInputBuffer();

    printf("Enter User Name: ");
    fgets(issue.userName,
          USER_NAME_SIZE,
          stdin);

    issue.userName[
        strcspn(issue.userName, "\n")
    ] = '\0';

    if (strlen(issue.userName) == 0)
    {
        printf("User name cannot be empty.\n");
        fclose(bookFile);
        return;
    }

    issue.issueID = getNextIssueID();

    issue.bookID = bookID;

    getCurrentDate(issue.issueDate);

    getDueDate(issue.issueDate,
               issue.dueDate);

    strcpy(issue.returnDate, "-");

    issue.fineAmount = 0;

    issue.returned = 0;

    /*
        Reduce available quantity.
    */

    book.quantity--;

    fseek(bookFile,
          -(long)sizeof(struct Book),
          SEEK_CUR);

    fwrite(&book,
           sizeof(struct Book),
           1,
           bookFile);

    fclose(bookFile);

    /*
        Save issue record.
    */

    issueFile = fopen(ISSUE_FILE, "ab");

    if (issueFile == NULL)
    {
        printf("Error opening issue file.\n");
        return;
    }

    fwrite(&issue,
           sizeof(struct Issue),
           1,
           issueFile);

    fclose(issueFile);

    printf("\n====================================\n");
    printf("       BOOK ISSUED SUCCESSFULLY\n");
    printf("====================================\n");

    printf("Issue ID   : %d\n", issue.issueID);
    printf("Book ID    : %d\n", issue.bookID);
    printf("Book Name  : %s\n", book.title);
    printf("User ID    : %d\n", issue.userID);
    printf("User Name  : %s\n", issue.userName);
    printf("Issue Date : %s\n", issue.issueDate);
    printf("Due Date   : %s\n", issue.dueDate);
}

/* =========================
   CALCULATE LATE DAYS
   ========================= */

int calculateLateDays(char dueDate[],
                      char returnDate[])
{
    int d1, m1, y1;
    int d2, m2, y2;

    struct tm due;
    struct tm returned;

    time_t dueTime;
    time_t returnTime;

    double difference;

    sscanf(dueDate,
           "%d-%d-%d",
           &d1,
           &m1,
           &y1);

    sscanf(returnDate,
           "%d-%d-%d",
           &d2,
           &m2,
           &y2);

    memset(&due, 0, sizeof(struct tm));
    memset(&returned, 0, sizeof(struct tm));

    due.tm_mday = d1;
    due.tm_mon = m1 - 1;
    due.tm_year = y1 - 1900;

    returned.tm_mday = d2;
    returned.tm_mon = m2 - 1;
    returned.tm_year = y2 - 1900;

    dueTime = mktime(&due);
    returnTime = mktime(&returned);

    difference =
        difftime(returnTime, dueTime);

    if (difference <= 0)
        return 0;

    return (int)(difference / (60 * 60 * 24));
}

/* =========================
   RETURN BOOK
   ========================= */

void returnBook()
{
    FILE *issueFile;
    FILE *bookFile;

    struct Issue issue;
    struct Book book;

    int bookID;
    int userID;

    int found = 0;
    int lateDays;

    char returnDate[11];

    printf("\n========== RETURN BOOK ==========\n");

    printf("Enter Book ID: ");
    scanf("%d", &bookID);
    clearInputBuffer();

    printf("Enter User ID: ");
    scanf("%d", &userID);
    clearInputBuffer();

    issueFile = fopen(ISSUE_FILE, "r+b");

    if (issueFile == NULL)
    {
        printf("No issued books found.\n");
        return;
    }

    while (fread(&issue,
                 sizeof(struct Issue),
                 1,
                 issueFile))
    {
        if (issue.bookID == bookID &&
            issue.userID == userID &&
            issue.returned == 0)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nIssued book record not found.\n");
        fclose(issueFile);
        return;
    }

    /*
        Automatically generate return date.
    */

    getCurrentDate(returnDate);

    strcpy(issue.returnDate,
           returnDate);

    /*
        Calculate late days.
    */

    lateDays =
        calculateLateDays(issue.dueDate,
                          issue.returnDate);

    if (lateDays > 0)
    {
        issue.fineAmount =
            lateDays * FINE_PER_DAY;
    }
    else
    {
        issue.fineAmount = 0;
    }

    issue.returned = 1;

    /*
        Update issue record.
    */

    fseek(issueFile,
          -(long)sizeof(struct Issue),
          SEEK_CUR);

    fwrite(&issue,
           sizeof(struct Issue),
           1,
           issueFile);

    fclose(issueFile);

    /*
        Increase book quantity.
    */

    bookFile = fopen(BOOK_FILE, "r+b");

    if (bookFile == NULL)
    {
        printf("Error opening book file.\n");
        return;
    }

    while (fread(&book,
                 sizeof(struct Book),
                 1,
                 bookFile))
    {
        if (book.bookID == bookID)
        {
            book.quantity++;

            fseek(bookFile,
                  -(long)sizeof(struct Book),
                  SEEK_CUR);

            fwrite(&book,
                   sizeof(struct Book),
                   1,
                   bookFile);

            break;
        }
    }

    fclose(bookFile);

    printf("\n====================================\n");
    printf("       BOOK RETURNED SUCCESSFULLY\n");
    printf("====================================\n");

    printf("Book ID     : %d\n", issue.bookID);
    printf("User ID     : %d\n", issue.userID);
    printf("User Name   : %s\n", issue.userName);
    printf("Issue Date  : %s\n", issue.issueDate);
    printf("Due Date    : %s\n", issue.dueDate);
    printf("Return Date : %s\n", issue.returnDate);
    printf("Late Days   : %d\n", lateDays);
    printf("Fine Amount : Rs. %.2f\n",
           issue.fineAmount);
}

/* =========================
   LIST ISSUED BOOKS
   ========================= */

void listIssuedBooks()
{
    FILE *issueFile;
    FILE *bookFile;

    struct Issue issue;
    struct Book book;

    char title[TITLE_SIZE];

    int found = 0;

    issueFile = fopen(ISSUE_FILE, "rb");

    if (issueFile == NULL)
    {
        printf("\nNo issue records found.\n");
        return;
    }

    printf("\n");
    printf("====================================================================================\n");
    printf("                         LIST OF ISSUED BOOKS\n");
    printf("====================================================================================\n");

    printf("%-7s %-7s %-20s %-8s %-18s %-12s %-12s %-12s %-8s\n",
           "IssueID",
           "BookID",
           "Book Title",
           "UserID",
           "User Name",
           "Issue Date",
           "Due Date",
           "Return Date",
           "Fine");

    printf("------------------------------------------------------------------------------------\n");

    while (fread(&issue,
                 sizeof(struct Issue),
                 1,
                 issueFile))
    {
        /*
            Requirement says "List Issued Books",
            so only currently issued books are displayed.
        */

        if (issue.returned == 0)
        {
            strcpy(title, "Unknown");

            bookFile = fopen(BOOK_FILE, "rb");

            if (bookFile != NULL)
            {
                while (fread(&book,
                             sizeof(struct Book),
                             1,
                             bookFile))
                {
                    if (book.bookID == issue.bookID)
                    {
                        strcpy(title, book.title);
                        break;
                    }
                }

                fclose(bookFile);
            }

            printf("%-7d %-7d %-20.20s %-8d %-18.18s %-12s %-12s %-12s Rs.%-7.2f\n",
                   issue.issueID,
                   issue.bookID,
                   title,
                   issue.userID,
                   issue.userName,
                   issue.issueDate,
                   issue.dueDate,
                   issue.returnDate,
                   issue.fineAmount);

            found = 1;
        }
    }

    if (!found)
        printf("No books are currently issued.\n");

    printf("====================================================================================\n");

    fclose(issueFile);
}

