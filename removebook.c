/* =========================
   REMOVE BOOK MENU
   ========================= */
#include"header.h"

void removeBook()
{
    char choice;

    while (1)
    {
        printf("\n========== REMOVE BOOK ==========\n");
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
                removeByID();
                break;

            case 'B':
                removeByName();
                break;

            case 'C':
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}

