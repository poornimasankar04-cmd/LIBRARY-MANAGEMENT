
/* =========================
   SEARCH BOOK MENU
   ========================= */
#include"header.h"

void searchBook()
{
    char choice;

    while (1)
    {
        printf("\n========== SEARCH BOOK ==========\n");
        printf("A. By Book ID\n");
        printf("B. By Book Name\n");
        printf("C. By Author Name\n");
        printf("D. Back to Main Menu\n");

        printf("Enter choice: ");
        scanf(" %c", &choice);
        clearInputBuffer();

        choice = toupper(choice);

        switch (choice)
        {
            case 'A':
                searchByID();
                break;

            case 'B':
                searchByName();
                break;

            case 'C':
                searchByAuthor();
                break;

            case 'D':
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}

