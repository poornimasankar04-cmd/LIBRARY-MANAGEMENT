/* =========================
   UPDATE BY NAME
   ========================= */
#include"header.h"

void updateByName()
{
    FILE *fp;
    struct Book book;

    char name[TITLE_SIZE];
    int found = 0;

    printf("\nEnter Book Name: ");
    fgets(name, TITLE_SIZE, stdin);
    name[strcspn(name, "\n")] = '\0';

    fp = fopen(BOOK_FILE, "r+b");

    if (fp == NULL)
    {
        printf("No books found.\n");
        return;
    }

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        if (containsIgnoreCase(book.title, name))
        {
            found = 1;

            printf("\nBook Found\n");
            printf("Book ID  : %d\n", book.bookID);
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
        printf("\nBook not found.\n");

    fclose(fp);
}

