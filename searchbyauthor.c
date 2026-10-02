/* =========================
   SEARCH BY AUTHOR
   ========================= */
#include"header.h"

void searchByAuthor()
{
    FILE *fp;
    struct Book book;

    char author[AUTHOR_SIZE];

    int found = 0;

    printf("\nEnter Author Name: ");
    fgets(author, AUTHOR_SIZE, stdin);
    author[strcspn(author, "\n")] = '\0';

    fp = fopen(BOOK_FILE, "rb");

    if (fp == NULL)
    {
        printf("No books found.\n");
        return;
    }

    printf("\n========== SEARCH RESULTS ==========\n");

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        if (containsIgnoreCase(book.author, author))
        {
            printf("\nBook ID  : %d\n", book.bookID);
            printf("Title    : %s\n", book.title);
            printf("Author   : %s\n", book.author);
            printf("Quantity : %d\n", book.quantity);

            found = 1;
        }
    }

    if (!found)
        printf("No matching books found.\n");

    fclose(fp);
}

/* =========================
   CASE-INSENSITIVE SEARCH
   ========================= */

int containsIgnoreCase(char text[], char search[])
{
    char textCopy[200];
    char searchCopy[200];

    int i;

    strcpy(textCopy, text);
    strcpy(searchCopy, search);

    for (i = 0; textCopy[i] != '\0'; i++)
        textCopy[i] =
            (char)tolower((unsigned char)textCopy[i]);

    for (i = 0; searchCopy[i] != '\0'; i++)
        searchCopy[i] =
            (char)tolower((unsigned char)searchCopy[i]);

    return strstr(textCopy, searchCopy) != NULL;
}

