/* =========================
   VIEW ALL BOOKS
   ========================= */
#include"header.h"

void viewAllBooks()
{
    FILE *fp;
    struct Book book;

    int count = 0;

    fp = fopen(BOOK_FILE, "rb");

    if (fp == NULL)
    {
        printf("\nNo books found.\n");
        return;
    }

    printf("\n");
    printf("====================================================================\n");
    printf("                         ALL BOOKS\n");
    printf("====================================================================\n");

    printf("%-10s %-30s %-25s %-10s\n",
           "Book ID",
           "Book Name",
           "Author",
           "Quantity");

    printf("--------------------------------------------------------------------\n");

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        printf("%-10d %-30s %-25s %-10d\n",
               book.bookID,
               book.title,
               book.author,
               book.quantity);

        count++;
    }

    printf("--------------------------------------------------------------------\n");

    printf("Total Books: %d\n", count);

    fclose(fp);
}

/* =========================
   GET CURRENT DATE
   ========================= */

void getCurrentDate(char date[])
{
    time_t now;
    struct tm *current;

    now = time(NULL);

    current = localtime(&now);

    strftime(date, 11, "%d-%m-%Y", current);
}

/* =========================
   GET DUE DATE
   ========================= */

void getDueDate(char issueDate[], char dueDate[])
{
    int day;
    int month;
    int year;

    struct tm date;

    sscanf(issueDate,
           "%d-%d-%d",
           &day,
           &month,
           &year);

    memset(&date, 0, sizeof(struct tm));

    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;

    date.tm_mday += DUE_DAYS;

    mktime(&date);

    strftime(dueDate,
             11,
             "%d-%m-%Y",
             &date);
}

/* =========================
   GET NEXT ISSUE ID
   ========================= */

int getNextIssueID()
{
    FILE *fp;
    struct Issue issue;

    int maxID = 0;

    fp = fopen(ISSUE_FILE, "rb");

    if (fp == NULL)
        return 1;

    while (fread(&issue, sizeof(struct Issue), 1, fp))
    {
        if (issue.issueID > maxID)
            maxID = issue.issueID;
    }

    fclose(fp);

    return maxID + 1;
}
