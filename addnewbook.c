/* =========================
   ADD NEW BOOK
   ========================= */
#include"header.h"

void addBook()
{
    FILE *fp;
    struct Book book;

    printf("\n========== ADD NEW BOOK ==========\n");

    printf("Enter Book ID: ");
    scanf("%d", &book.bookID);
    clearInputBuffer();

    if (book.bookID <= 0)
    {
        printf("Invalid Book ID.\n");
        return;
    }

    if (bookExists(book.bookID))
    {
        printf("Book ID already exists.\n");
        return;
    }

    printf("Enter Book Name: ");
    fgets(book.title, TITLE_SIZE, stdin);
    book.title[strcspn(book.title, "\n")] = '\0';

    if (strlen(book.title) == 0)
    {
        printf("Book name cannot be empty.\n");
        return;
    }

    printf("Enter Author Name: ");
    fgets(book.author, AUTHOR_SIZE, stdin);
    book.author[strcspn(book.author, "\n")] = '\0';

    if (strlen(book.author) == 0)
    {
        printf("Author name cannot be empty.\n");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &book.quantity);
    clearInputBuffer();

    if (book.quantity <= 0)
    {
        printf("Quantity must be greater than zero.\n");
        return;
    }

    fp = fopen(BOOK_FILE, "ab");

    if (fp == NULL)
    {
        printf("Error opening book file.\n");
        return;
    }

    fwrite(&book, sizeof(struct Book), 1, fp);

    fclose(fp);

    printf("\nBook added successfully!\n");
}

