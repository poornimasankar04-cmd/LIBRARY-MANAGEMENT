/* =========================
   REMOVE BY NAME
   ========================= */
#include"header.h"

void removeByName()
{
    FILE *fp;
    FILE *temp;

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

    temp = fopen("temp.dat", "wb");

    if (temp == NULL)
    {
        fclose(fp);
        printf("Error creating temporary file.\n");
        return;
    }

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        if (containsIgnoreCase(book.title, name))
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

        printf("\nBook not found.\n");
    }
}
