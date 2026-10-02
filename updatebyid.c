/* =========================
   UPDATE BY ID
   ========================= */
#include"header.h"

void updateByID()
{
    FILE *fp;
    struct Book book;

    int id;
    int found = 0;

    printf("\nEnter Book ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    fp = fopen(BOOK_FILE, "r+b");

    if (fp == NULL)
    {
        printf("No books found.\n");
        return;
    }

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        if (book.bookID == id)
        {
            found = 1;

            printf("\nCurrent Book Details\n");
            printf("Title    : %s\n", book.title);
            printf("Author   : %s\n", book.author);
            printf("Quantity : %d\n", book.quantity);

            printf("\nEnter New Book Name: ");
            fgets(book.title, TITLE_SIZE, stdin);
            book.title[strcspn(book.title, "\n")] = '\0';

            printf("Enter New Author Name: ");
            fgets(book.author, AUTHOR_SIZE, stdin);
            book.author[strcspn(book.author, "\n")] = '\0';

            printf("Enter New Quantity: ");
            scanf("%d", &book.quantity);
            clearInputBuffer();

            if (book.quantity <= 0)
            {
                printf("Invalid quantity.\n");
                fclose(fp);
                return;
            }

            fseek(fp, -(long)sizeof(struct Book), SEEK_CUR);

            fwrite(&book, sizeof(struct Book), 1, fp);

            printf("\nBook updated successfully!\n");

            break;
        }
    }

    if (!found)
        printf("\nBook ID not found.\n");

    fclose(fp);
}

