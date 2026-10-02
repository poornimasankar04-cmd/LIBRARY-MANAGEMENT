/* =========================
   CHECK BOOK EXISTS
   ========================= */
#include"header.h"

int bookExists(int id)
{
    FILE *fp;
    struct Book book;

    fp = fopen(BOOK_FILE, "rb");

    if (fp == NULL)
        return 0;

    while (fread(&book, sizeof(struct Book), 1, fp))
    {
        if (book.bookID == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}
