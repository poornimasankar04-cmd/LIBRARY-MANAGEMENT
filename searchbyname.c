/* =========================
   SEARCH BY NAME
   ========================= */
#include"header.h"

void searchByName()
{
    FILE *fp;
    struct Book book;

    char name[TITLE_SIZE];

    int found = 0;

    printf("\nEnter Book Name: ");
    fgets(name, TITLE_SIZE, stdin);
    name[strcspn(name, "\n")] = '\0';

    fp = fopen(BOOK_FILE, "rb");

    if (fp == NULL)
    {
        printf("No books found.\n");
        return;
    }

    printf("\n========== SEARCH RESULTS ==========\n");

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        if (containsIgnoreCase(book.title, name))
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
