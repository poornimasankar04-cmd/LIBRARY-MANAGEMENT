/* =========================
   SAVE
   ========================= */
#include"header.h"
void saveData()
{
    /*
        All modifications are written directly
        to the files.

        Therefore, there is no separate save
        operation required.
    */

    printf("\n====================================\n");
    printf("             SAVE\n");
    printf("====================================\n");

    printf("Book data is saved in : %s\n", BOOK_FILE);
    printf("Issue data is saved in: %s\n", ISSUE_FILE);

    printf("\nAll data has already been saved successfully.\n");
}

