/* =========================
   REMOVE BY ID
   ========================= */
#include"header.h"

void removeByID()
{
    FILE *fp;
    FILE *temp;

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

    temp = fopen("temp.dat", "wb");

    if (temp == NULL)
    {
        fclose(fp);
        printf("Error creating temporary file.\n");
        return;
    }

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        if (book.bookID == id)
        {
            found = 1;
            continue;
        }

        fwrite(&book, sizeof(struct Book), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove(BOOK_FILE);
        rename("temp.dat", BOOK_FILE);

        printf("\nBook removed successfully!\n");
    }
    else
    {
        remove("temp.dat");

        printf("\nBook ID not found.\n");
    }
}

