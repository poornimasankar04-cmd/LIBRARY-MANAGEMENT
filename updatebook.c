/* =========================
   UPDATE BOOK MENU
   ========================= */
#include"header.h"

void updateBook()
{
    char choice;

    while (1)
    {
        printf("\n========== UPDATE BOOK DETAILS ==========\n");
        printf("A. By Book ID\n");
        printf("B. By Book Name\n");
        printf("C. Back to Main Menu\n");

        printf("Enter choice: ");
        scanf(" %c", &choice);
        clearInputBuffer();

        choice = toupper(choice);

        switch (choice)
        {
            case 'A':
                updateByID();
                break;

            case 'B':
                updateByName();
                break;

            case 'C':
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}

