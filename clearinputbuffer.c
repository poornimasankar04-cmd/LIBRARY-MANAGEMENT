/* =========================
   CLEAR INPUT BUFFER
   ========================= */
#include"header.h"

void clearInputBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c !=EOF)
    {
    }
}

/* =========================
   PAUSE
   ========================= */

void pauseScreen()
{
    printf("\nPress Enter to continue...");
    getchar();
}

