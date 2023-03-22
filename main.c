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

/* It clears the screen and moves the cursor to the top left corner. */
void clearScreen();
void displayMenu();

void inputCustomerData(Kundendaten *customer, int index);
void addKunde(Kundendaten *kunden, unsigned int anzahlKunden);
Kundendaten *findKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer);
void showKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer);
void showAllKunden(Kundendaten *kunden, unsigned int anzahlKunden);
void editKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer);
void deleteKunde(Kundendaten *kunden, unsigned int *anzahlKunden, int kundennummer);
void saveKundenToFile(Kundendaten *kunden, unsigned int *anzahlKunden, const char *filename);
void loadKundenFromFile(Kundendaten *kunden, unsigned int *anzahlKunden, const char *filename);
void sortKunden_ascending_order(Kundendaten *kunden, unsigned int *anzahlKunden);
//void printKunden_ascending_order(Kundendaten *kunden, unsigned int *anzahlKunden);
void sortKunden_descending_order(Kundendaten *kunden, unsigned int *anzahlKunden);
//void printKunden_descending_order(Kundendaten *kunden, unsigned int *anzahlKunden);

int main()
{
    clearScreen();
    displayMenu();

    const char filename[] = "Customer_list.txt";

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
        while (auswahl < 0 || auswahl > 9)
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
            printf("\nPlease enter the customer number of client which you want to edit it: ");
            int kundennumber = 0;
            (void)scanf("%d", &kundennumber);

            editKunde(kunden, anzahlKunden, kundennumber);
            break;
        case 5:
            printf("\nPlease enter the customer number of client which you want to delete it: ");
            int kundennum = 0;
            (void)scanf("%d", &kundennum);

            deleteKunde(kunden, &anzahlKunden, kundennum);
            break;
        case 6:
            saveKundenToFile(kunden, &anzahlKunden, filename);
            break;
        case 7:
            loadKundenFromFile(kunden, &anzahlKunden, filename);
            break;
        case 8:
            sortKunden_ascending_order(kunden, &anzahlKunden);
            //printKunden_ascending_order(kunden, &anzahlKunden);
            break;
        case 9:
            sortKunden_descending_order(kunden, &anzahlKunden);
            //printKunden_descending_order(kunden, &anzahlKunden);
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

/**
 * It displays a menu.
 */
void displayMenu()
{
    printf("\n=============================================\n");
    for (int i = 0; i < 2; i++)
    {
        printf("|                                           |\n");
    }
    printf("|       ----------------------              |\n");
    printf("|       Welcome to the database!            |\n");
    printf("|       ----------------------              |\n");
    printf("|                                           |\n");
    printf("|       This program will create a          |\n");
    printf("|       database of clients.                |\n");
    printf("|                                           |\n");
    printf("|       1. Add a client to the              |\n");
    printf("|          database.                        |\n");
    printf("|       2. Show a specific client.          |\n");
    printf("|       3. Show all clients.                |\n");
    printf("|       4. Edit a client.                   |\n");
    printf("|       5. Delete a client.                 |\n");
    printf("|       6. Save clients to File.            |\n");
    printf("|       7. Load clients from File.          |\n");
    printf("|       8. Sort clients ascending.          |\n");
    printf("|       9. Sort clients descending          |\n");
    printf("|       0. Exit.                            |\n");
    for (int i = 0; i < 2; i++)
    {
        printf("|                                           |\n");
    }
    printf("=============================================\n");
}

/**
 * The function takes a pointer to a struct and an index as parameters, and then prompts the user to
 * enter data for the struct at the given index
 * 
 * @param customer pointer to the structure
 * @param index the index of the customer in the array
 */
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

/**
 * It takes a pointer to an array of Kundendaten structs and an integer, and then it loops through the
 * array and calls a function to fill in the data for each struct
 * 
 * @param kunden pointer to an array of Kundendaten structs
 * @param anzahlKunden The number of customers
 */
void addKunde(Kundendaten *kunden, unsigned int anzahlKunden)
{
    for (int i = 0; i < anzahlKunden; i++)
    {
        inputCustomerData(&kunden[i], i);
    }
}

/**
 * It returns a pointer to a Kundendaten struct if the given kundennummer is found in the array of
 * Kundendaten structs, otherwise it returns NULL
 * 
 * @param kunden pointer to the first element of the array of Kundendaten
 * @param anzahlKunden The number of customers in the array
 * @param kundennummer The customer number to search for
 * 
 * @return A pointer to the first element of the array.
 */
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
/**
 * It prints the customer data of a customer with a given customer number
 * 
 * @param kunden pointer to the first element of the array
 * @param anzahlKunden The number of customers
 * @param kundennummer The customer number to search for
 */
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

/**
 * It prints out the customer data in a table
 * 
 * @param kunden pointer to the array of structs
 * @param anzahlKunden The number of customers
 */
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

/**
 * It takes a pointer to a Kundendaten struct, an unsigned int, and an int, and if the int is found in
 * the array of Kundendaten structs, it calls a function to edit the data of the struct
 * 
 * @param kunden pointer to the first element of the array of Kundendaten
 * @param anzahlKunden The number of customers in the array
 * @param kundennummer The customer number
 */
void editKunde(Kundendaten *kunden, unsigned int anzahlKunden, int kundennummer)
{
    Kundendaten *kunde = findKunde(kunden, anzahlKunden, kundennummer);

    if (kunde)
    {
        inputCustomerData(kunde, kundennummer * 0);
    }
    else
    {
        printf("\nCustomer number not found!\n");
    }
}

/**
 * It deletes a customer from the array of customers
 * 
 * @param kunden The array of customers
 * @param anzahlKunden The number of customers
 * @param kundennummer The customer number to be deleted
 * 
 * @return the index of the customer in the array.
 */
void deleteKunde(Kundendaten *kunden, unsigned int *anzahlKunden, int kundennummer)
{
    // Kundendaten *kunde = findKunde(kunden, anzahlKunden, kundennummer);

    int index = -1;
    for (int i = 0; i < *anzahlKunden; i++)
    {
        if (kunden[i].Kundennummer == kundennummer)
        {
            index = i;
            break;
        }
        else
        {
            printf("\nCustomer not found!");
        }
    }
    // If the customer is not found, return
    if (index == -1)
    {
        return;
    }
    // Shift all the subsequent customers one position to the left
    for (int i = index; i < *anzahlKunden - 1; i++)
    {
        kunden[i] = kunden[i + 1];
    }
    // Updating the number of customers
    (*anzahlKunden)--;
}

/**
 * It opens a file, writes some data to it, and then closes the file
 * 
 * @param kunden pointer to the array of Kundendaten structs
 * @param anzahlKunden The number of customers
 * @param filename The name of the file to open.
 */
void saveKundenToFile(Kundendaten *kunden, unsigned int *anzahlKunden, const char *filename)
{
    FILE *f = fopen(filename, "a");
    if (f == NULL)
    {
        printf("Error opening %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < *anzahlKunden; i++)
    {
        fprintf(f, "%-10s | %-15d | %-20s | %-10s\n", kunden[i].Name, kunden[i].Kundennummer, kunden[i].Adresse, kunden[i].Telefonnummer);
    }

    fclose(f);
}

/**
 * It reads the contents of a file into an array of structs
 * 
 * @param kunden pointer to the array of Kundendaten structs
 * @param anzahlKunden number of customers
 * @param filename The name of the file to open.
 */
void loadKundenFromFile(Kundendaten *kunden, unsigned int *anzahlKunden, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Error opening %s\n", filename);
        exit(1);
    }

    printf("\n%-10s | %-15s | %-20s | %-10s\n", "Name", "Customer number", "Address", "Number");
    fread(kunden, sizeof(Kundendaten), *anzahlKunden, f);
    for (int i = 0; i < *anzahlKunden; i++)
    {
        printf("\n%-10s | %-15d | %-20s | %-10s", kunden[i].Name, kunden[i].Kundennummer, kunden[i].Adresse, kunden[i].Telefonnummer);
    }
    fclose(f);
}

/**
 * It sorts the array of structs in ascending order based on the customer number
 * 
 * @param kunden an array of Kundendaten structs
 * @param anzahlKunden number of customers
 */
void sortKunden_ascending_order(Kundendaten *kunden, unsigned int *anzahlKunden)
{
    for (int i = 0; i < *anzahlKunden; i++)
    {
        for (int j = 0; j < *anzahlKunden - i - 1; j++)
        {
            if (kunden[j].Kundennummer > kunden[j + 1].Kundennummer)
            {
                Kundendaten temp = kunden[j];
                kunden[j] = kunden[j + 1];
                kunden[j + 1] = temp;
            }
        }
    }
}

// void printKunden_ascending_order(Kundendaten *kunden, unsigned int *anzahlKunden)
// {
//     for (int i = 0; i < *anzahlKunden; i++)
//     {
//         for (int j = 0; j < *anzahlKunden; i++)
//         {
//             printf("\n%-10s | %-15d | %-20s | %-10s", kunden[i].Name, kunden[i].Kundennummer, kunden[i].Adresse, kunden[i].Telefonnummer);
//         }
//     }
// }

/**
 * It sorts the array of structs in descending order by the customer number
 * 
 * @param kunden an array of Kundendaten structs
 * @param anzahlKunden The number of customers
 */
void sortKunden_descending_order(Kundendaten *kunden, unsigned int *anzahlKunden)
{
    for (int i = 0; i < *anzahlKunden; i++)
    {
        for (int j = 0; j < *anzahlKunden - i - 1; j++)
        {
            if (kunden[j].Kundennummer < kunden[j + 1].Kundennummer)
            {
                Kundendaten temp = kunden[j];
                kunden[j] = kunden[j + 1];
                kunden[j + 1] = temp;
            }
        }
    }
}

// void printKunden_descending_order(Kundendaten *kunden, unsigned int *anzahlKunden)
// {
//     for (int i = 0; i < *anzahlKunden; i++)
//     {
//         for (int j = 0; j < *anzahlKunden; i++)
//         {
//             printf("\n%-10s | %-15d | %-20s | %-10s", kunden[i].Name, kunden[i].Kundennummer, kunden[i].Adresse, kunden[i].Telefonnummer);
//         }
//     }
// }