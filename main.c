#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
  int   Kundennummer;
  char  Name[150];
  char  Adresse[200];
  char  Telefonnummer[15];
}Kundendaten;

void clearScreen();
void displayMenu();

void addKunde(Kundendaten *kunden, int *anzahlKunden);
void showKunde(Kundendaten *kunden, int anzahlKunden, int kundennummer);
void showAllKunden(Kundendaten *kunden, int anzahlKunden);
int searchKunde(Kundendaten *kunden, int anzahlKunden, int kundennummer);
void editKunde(Kundendaten *kunden, int anzahlKunden, int kundennummer);
void deleteKunde(Kundendaten *kunden, int *anzahlKunden, int kundennummer);
void saveKundenToFile(Kundendaten *kunden, int anzahlKunden, const char *filename);
void loadKundenFromFile(Kundendaten *kunden, int *anzahlKunden, const char *filename);

int main()
{
    Kundendaten kunden[5];
    clearScreen();
    unsigned int auswahl = 0;

    do
    {
        displayMenu();

        printf("Please enter your choice: ");
        scanf("%d", &auswahl);
        while (auswahl < 0 || auswahl > 5)
        {
            printf("Please enter one of the above numbers: ");
            scanf("%d", &auswahl);
        }
        
        switch (auswahl)
        {
        case 1:
            //addKunde();
            break;
        case 2:
            //showKunde();
            break;
        case 3: 
            //showAllKunden();
            break;
        case 4:
            //searchKunde();
            break;
        case 5:
            //editKunde();
            break;
        default:
            printf("\n------------------Closing the database!------------------\n");
            break;
        }

    } while (auswahl != 0);

    return 0;
}
void clearScreen()
{
    printf("\033[2J\033[0;0f"); // clear screen and move cursor to top left corner
}

void displayMenu()
{
    printf("==================================\n");
    for (int i = 0; i < 2; i++) {
        printf("|                                |\n");
    }
    printf("|   ----------------------       |\n");
    printf("|   Welcome to the database!     |\n");
    printf("|   ----------------------       |\n");
    printf("|                                |\n");
    printf("|   This program will create a   |\n");
    printf("|   database of clients.         |\n");
    printf("|                                |\n");
    printf("|   1. Add a client to the       |\n");
    printf("|      database.                 |\n");
    printf("|   2. Show a specific client.   |\n");
    printf("|   3. Show all clients.         |\n");
    printf("|   4. Search a client.          |\n");
    printf("|   5. Edit a client.            |\n");
    printf("|   0. Exit.                     |\n");
    for (int i = 0; i < 2; i++) {
        printf("|                                |\n");
    }
    printf("==================================\n");
}