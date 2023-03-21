#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y)) // Macros
#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef struct
{
    int Kundennummer;
    char Name[150];
    char Adresse[200];
    char Telefonnummer[20];
} Kundendaten;

void clearScreen();
void displayMenu();

void inputCustomerData(Kundendaten *customer, int index);
void addKunde(Kundendaten *kunden, unsigned int anzahlKunden);
Kundendaten *findKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer);
void showKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer);
void showAllKunden(Kundendaten *kunden, unsigned int anzahlKunden);
void editKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer);
void deleteKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer);
void saveKundenToFile(Kundendaten *kunden, unsigned int anzahlKunden, const char *filename);
void loadKundenFromFile(Kundendaten *kunden, unsigned int anzahlKunden, const char *filename);

int main()
{
    // Kundendaten kunden[5]; // array of 5 customers
    clearScreen();
    displayMenu();

    unsigned int auswahl = 0, anzahlKunden = 0;
    printf("Enter the number of customers: ");
    (void)scanf("%d", &anzahlKunden);
    printf("\n");

    Kundendaten *kunden = (Kundendaten *)malloc(anzahlKunden * sizeof(Kundendaten)); // allocating memory in the heap
    if (kunden == NULL)
    {
        printf("\nFailed allocating memory in the Heap!");
        exit(1);
    }

    do
    {
        displayMenu();

        printf("Please enter your choice: ");
        (void)scanf("%d", &auswahl);
        while (auswahl < 0 || auswahl > 5)
        {
            printf("Please enter one of the above numbers: ");
            (void)scanf("%d", &auswahl);
        }

        switch (auswahl)
        {
        case 1:
            addKunde(kunden, anzahlKunden);
            break;
        case 2:
            printf("\nPlease enter the customer number of client which you want to search it: ");
            int kundennummer = 0;
            (void)scanf("%d", &kundennummer);

            showKunde(kunden, anzahlKunden, kundennummer);
            break;
        case 3:
            showAllKunden(kunden, anzahlKunden);
            break;
        case 4:
            editKunde(kunden, anzahlKunden, kundennummer);
            break;
        case 5:
            // editKunde();
            break;
        default:
            printf("\n------------------Closing the database!------------------\n");
            break;
        }

    } while (auswahl != 0);

    free(kunden); 
    return 0;
}
void clearScreen()
{
    printf("\033[2J\033[0;0f"); // clear screen and move cursor to top left corner
}

void displayMenu()
{
    printf("\n==================================\n");
    for (int i = 0; i < 2; i++)
    {
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
    printf("|   4. Edit a client.          |\n");
    printf("|   5. Delete a client.            |\n");
    printf("|   0. Exit.                     |\n");
    for (int i = 0; i < 2; i++)
    {
        printf("|                                |\n");
    }
    printf("==================================\n");
}

void inputCustomerData(Kundendaten *customer, int index)
{
    printf("\nEnter the name of the client %d: ", index + 1);
    (void)scanf("%49s", customer->Name);

    printf("\nPlease enter the customer number %d: ", index + 1);
    (void)scanf("%d", &customer->Kundennummer);

    printf("\nEnter the address of the client %d: ", index + 1);
    (void)scanf("%99s", customer->Adresse);

    fflush(stdin);

    printf("\nEnter the number of the client %d: ", index + 1);
    fgets(customer->Telefonnummer, 20, stdin);
    //(void)scanf("%19s", customer->Telefonnummer);
    fflush(stdin);
}

void addKunde(Kundendaten *kunden, unsigned int anzahlKunden)
{
    for (int i = 0; i < anzahlKunden; i++)
    {
        inputCustomerData(&kunden[i], i);
    }
}

Kundendaten *findKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer)
{
    for (int i = 0; i < anzahlKunden; i++)
    {
        if (kunden[i].Kundennummer == kundennummer)
        {
            return &kunden[i];
        }
    }
    return NULL;
}
void showKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer)
{
    printf("\n%-10s | %-15s | %-20s | %-10s\n", "Name", "Customer number", "Address", "Number");
    printf("----------------------------------------------------------------");
    Kundendaten *kunde = findKunde(kunden, anzahlKunden, kundennummer);

    if (kunde)
    {
        printf("\n%-10s | %-15d | %-20s | %-10s\n", kunde->Name, kunde->Kundennummer, kunde->Adresse, kunde->Telefonnummer);
    }
    else
    {
        printf("\nCustomer number not found!\n");
    }
}

void showAllKunden(Kundendaten *kunden, unsigned int anzahlKunden)
{
    printf("\n%-10s | %-15s | %-20s | %-10s\n", "Name", "Customer number", "Address", "Number");
    printf("----------------------------------------------------------------");
    for (int j = 0; j < anzahlKunden; j++)
    {
        printf("\n%-10s | %-15d | %-20s | %-10s", kunden[j].Name, kunden[j].Kundennummer, kunden[j].Adresse, kunden[j].Telefonnummer);
    }
    printf("\n");
}

void editKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer)
{
    Kundendaten *kunde = findKunde(kunden, anzahlKunden, kundennummer);

    if (kunde)
    {
        inputCustomerData(kunde, kundennummer);
    }
    else
    {
        printf("\nCustomer number not found!\n");
    }

}