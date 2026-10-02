/* =========================
   SEARCH BY ID
   ========================= */
#include"header.h"

void searchByID()
{
    FILE *fp;
    struct Book book;

    int id;
    int found = 0;

    printf("\nEnter Book ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    fp = fopen(BOOK_FILE, "rb");

    if (fp == NULL)
    {
        printf("No books found.\n");
        return;
    }

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        if (book.bookID == id)
        {
            printf("\n========== BOOK DETAILS ==========\n");
            printf("Book ID  : %d\n", book.bookID);
            printf("Title    : %s\n", book.title);
            printf("Author   : %s\n", book.author);
            printf("Quantity : %d\n", book.quantity);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nBook not found.\n");

    fclose(fp);
}
