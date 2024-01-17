#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>



#define MAX_BIKES 100
#define MAX_STRING_LENGTH 40
#define MENU_CHOICES 7
#define MIN_YEAR 1960
#define MAX_YEAR 2024

void AsciiArt();
void bubbleSort();
void searchBrand();
void searchByColor();
void searchByNumber();
void searchByManufacture();
void searchByYear();
void Menu();
void ShowAll();
void NewRegistration();
void DeleteRegistration();
void RenewRegistration();
void Search();
void SaveDatabase();
void clearInputBuffer();
void printBiggerText();
void printBiggerText2();


void printBiggerText(const char *text) {
    printf("\n\t\t\t");
    while (*text != '\0') {
        printf("%c ", *text);
        text++;
    }
    printf("\n");
}

void printBiggerText2(const char *text) {
    printf("\t\t\t\t");
    while (*text != '\0') {
        printf("%c ", *text);
        text++;
    }
}

void AsciiArt() {
    printf("\t\t>>=================================================================================<<\n");
    printf("\t\t||______ _ _         ___  ___                                                  _   ||\n");
    printf("\t\t||| ___ (_) |        |  \\/  |                                                 | |  ||\n");
    printf("\t\t||| |_/ /_| | _____  | .  . | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_ ||\n");
    printf("\t\t||| ___ \\ | |/ / _ \\ | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|||\n");
    printf("\t\t||| |_/ / |   <  __/ | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_ ||\n");
    printf("\t\t||\\____/|_|_|\\_\\___| \\_|  |_/\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__|||\n");
    printf("\t\t||                                              __/ |                              ||\n");
    printf("\t\t||                                             |___/                               ||\n");
    printf("\t\t||                   ______      _        _                                        ||\n");
    printf("\t\t||                   |  _  \\    | |      | |                                       ||\n");
    printf("\t\t||                   | | | |__ _| |_ __ _| |__   __ _ ___  ___                     ||\n");
    printf("\t\t||                   | | | / _` | __/ _` | '_ \\ / _` / __|/ _ \\                    ||\n");
    printf("\t\t||                   | |/ / (_| | || (_| | |_) | (_| \\__ \\  __/                    ||\n");
    printf("\t\t||                   |___/ \\__,_|\\__\\__,_|_.__/ \\__,_|___/\\___|                    ||\n");
    printf("\t\t>>=================================================================================<<\n");


    const char *message = "Press enter to enter the Main Menu!";
    printBiggerText(message);
    system("pause > nul");
    system("cls");
    Menu();
}


void printCompanies(){



    int i, j = 1, lines;
    char Companies[25];

    FILE *file = fopen("Brands.txt", "r");

    lines = checkFileLines("Brands.txt");

    printf("Enter Bike Brands:\n");

    for(i = 0; i < lines; i++){
        fscanf(file, "%s", &Companies);
        printf("%s", Companies);
        if(i + 1 != lines){
            printf(", ");
        }
        if(j == 9){
            printf("\n");
            j = 0;
        }
        j += 1;
    }
    printf("\n");
    return;

}

void printColors() {
    int i, j = 1, lines;
    char color[20];

    FILE *file = fopen("Colors.txt", "r");

    lines = checkFileLines("Colors.txt");

    printf("Available Colors:\n");

    for (i = 0; i < lines; i++) {
        fscanf(file, "%s", &color);
        printf("%s\t", color);
        if (j == 3) {
            printf("\n");
            j = 0;
        }
        j += 1;
    }
    return;
}


struct Bike {
    int number;
    char color[MAX_STRING_LENGTH];
    char brand[MAX_STRING_LENGTH];
    int year;
};


int compareBikes(const void *a, const void *b) {
    const struct Bike *BikeA = (const struct Bike *)a;
    const struct Bike *BikeB = (const struct Bike *)b;

    if ((*BikeA).number < (*BikeB).number) {
        return -1; 
    } else if ((*BikeA).number > (*BikeB).number) {
        return 1; 
    } else {
        return 0; 
    }
}

struct Bike Bikes[MAX_BIKES];

void ShowAll() {
    FILE *file;
    struct Bike Bikes[100];
    int count = 0;
    system("cls");
    file = fopen("Bikes.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(file, "%d %s %s %d", &Bikes[count].number, Bikes[count].color, Bikes[count].brand, &Bikes[count].year) == 4) {
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("No records found!\n");
        return;
    }


    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (Bikes[j].number > Bikes[j + 1].number) {
            	
                struct Bike temp = Bikes[j];
                Bikes[j] = Bikes[j + 1];
                Bikes[j + 1] = temp;
            }
        }
    }

    printf("%-15s %-15s %-15s \t%-5s\n", "Number", "Color", "Brand", "Year");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        printf("%-15d %-15s %-23s %d\n", Bikes[i].number, Bikes[i].color, Bikes[i].brand, Bikes[i].year);
    }

    printf("\nPress Enter to return to the menu...");
    getchar();
    system("pause > nul");
    system("cls");
    Menu();
}


char Companies[MAX_BIKES][MAX_STRING_LENGTH];
char color[MAX_BIKES][MAX_STRING_LENGTH]; 

bool isValidColor(const char *color) {
    FILE *colorFile = fopen("Colors.txt", "r");
    if (colorFile == NULL) {
        printf("Error opening color file!\n");
        return false;
    }

    char fileColor[MAX_STRING_LENGTH];
    bool foundColor = false;
    while (fscanf(colorFile, "%s", fileColor) == 1) {
        if (strcmp(color, fileColor) == 0) {
            foundColor = true;
            break;
        }
    }

    fclose(colorFile);

    if (!foundColor) {
        printf("There is no color named '%s'. Try again!\n", color);
    }

    return foundColor;
}


bool isValidBrand(const char *brand) {
    FILE *brandsFile = fopen("Brands.txt", "r");
    if (brandsFile == NULL) {
        printf("Error opening company file!\n");
        return false;
    }

    char line[MAX_STRING_LENGTH];
    bool foundBrand = false;
    while (fgets(line, sizeof(line), brandsFile)) {
        line[strcspn(line, "\n")] = '\0'; 
        if (strcmp(line, brand) == 0) {
            foundBrand = true;
            break;
        }
    }

    fclose(brandsFile);

    if (!foundBrand) {
        printf("There is no company named '%s'. Try again!\n", brand);
    }

    return foundBrand;
}

struct TempRegistration {
    int number;
    char color[20];
    char brand[20];
    int year;
};

void TempSaveRegistration(struct TempRegistration *tempReg) {
    FILE *tempFile = fopen("temp.txt", "a");
    if (tempFile == NULL) {
        printf("Error opening temp file!\n");
        return;
    }

    fprintf(tempFile, "%-15d %-15s %-15s %d\n", tempReg->number, strupr(tempReg->color), tempReg->brand, tempReg->year);
    fclose(tempFile);

    printf("Registration temporarily saved.\n");
}

void NewRegistration() {
    FILE *file;
    int number, year;
    char color[20], brand[20];
    bool found = false;

    printf("Already In Use Bike Numbers:\n");

    file = fopen("Bikes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int tempNumber;
    while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
        printf("%d", tempNumber);
        if (fgetc(file) != EOF) {
            printf(", ");
        }
    }

    fclose(file);

    printf("\nEnter Bike number or press 0 to go back to Menu: ");
    scanf("%d", &number);

    if (number == 0) {
        system("cls");
        printf("Exiting...");
        Sleep(500);
        system("cls");
        Menu();
        return;
    }

    while (number < 1000 || number > 9999) {
        printf("The Bike number %d is not a number that can be registered, register a number between 1000 to 9999\n", number);
        sleep(1);
        printf("Press any key to try again!\n");
        system("pause > nul");
        system("cls");
        NewRegistration();
        return;
    }

    file = fopen("Bikes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
        if (tempNumber == number) {
            printf("The Bike number %d already exists.\n", number);
            found = true;
            system("pause");
            system("cls");
            Menu();
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("\n");
        printColors();
        do {
            printf("\n");
            printf("Enter Bike color: ");
            scanf("%s", color);
        } while (!isValidColor(color));

        do {
            printf("\n");
            printCompanies();
            printf("\nEnter Bike brand: ");
            scanf("%s", brand);
        } while (!isValidBrand(brand));

        
        do {
            printf("\nEnter Bike year of manufacture: ");
            if (scanf("%d", &year) != 1) {
                printf("Enter a legitimate numeric Bike year!\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer(); 

            if (year < 1960 || year > 2024) {
                printf("Enter a legitimate Bike year between 1960 and 2024!\n");
            }
        } while (year < 1960 || year > 2024);

		fclose(file);
        FILE *file = fopen("NewEntry.txt", "a");
        if (file == NULL) {
            printf("Error opening file!\n");
            return;
        }

        int saveChoice;
        printf("Do you want to save this registration? (Press 6 to save, 0 to discarded): ");
        scanf("%d", &saveChoice);

        if (saveChoice == 6) {
            fprintf(file, "%-15d %-15s %-15s %d\n", number, strupr(color), strupr(brand), year);
            fclose(file);

            printf("Registration added successfully to temp, Go to Menu to update.\n");
        } else {
            printf("Registration discarded.\n");
        }
        system("pause");
        system("cls");
        Menu();
    }
}



void bubbleSort(int arr[], int n) {
	int i,j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}



int deleteMenu(int *BikeNumbers, int lines) {
    int i, action;
    bool found = false;
    int *arrayNumber = (int *)malloc(lines * sizeof(int));

    if (arrayNumber == NULL) {
        printf("Memory allocation failed!\n");
        return -1; 
    }

    system("cls");
    printf("Registration Delete\n");
    printf("--------------------\n");

    for (i = 0; i < lines; i++) {
        arrayNumber[i] = BikeNumbers[i];
    }

    printf("Available Registrations:\n");
    for (i = 0; i < lines; i++) {
        printf("%d", arrayNumber[i]);
        if (i + 1 != lines) {
            printf(", ");
            if ((i + 1) % 4 == 0) {
                printf("\n");
            }
        }
    }
    printf("\n--------------------\n");

    do {
        printf("Pick a number: ");
        scanf("%d", &action); 

        found = false; 
        for (i = 0; i < lines; i++) {
            if (action == BikeNumbers[i]) {
                found = true;
                printf("Deleted registration with number \"%d\"\n", action);
                break;
            }
        }
        if (!found) {
            printf("There is no registration named \"%d\"\n", action);
        }
    } while (!found); 

    free(arrayNumber);
    return action;
}

struct Bike Bikes[MAX_BIKES];


int countFileLines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return -1; 
    }

    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

int checkFileLines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return -1; 
    }

    int lines = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

bool isBikeNumberExists(int number) {
    FILE *file = fopen("Bikes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return false;
    }

    int tempNumber, year;
    char color[20], brand[20];
    while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
        if (tempNumber == number) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void DeleteRegistration() {
    int number, i, numberRefresh, lines;

    FILE *file = fopen("Bikes.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int tempNumber, year;
    char color[20], brand[20];
    int found = 0;

    int maxLines = 100;
    int *BikeNumbers = malloc(maxLines * sizeof(int)); 

    for (i = 0; i < maxLines; i++) {
        if (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
            BikeNumbers[i] = tempNumber;
        } else {
            break;
        }
    }

    fclose(file);

    bubbleSort(BikeNumbers, i); 

    printf("Available Bike Numbers (Ascending Order):\n");
    
    			
	int j;
    for (j = 0; j < i; j++) {
        printf("%d", BikeNumbers[j]);

        if (j < i - 1) {
            printf(", ");
        }
    }

    free(BikeNumbers); 

    printf("\nEnter Bike number to delete or Enter 0 to go back to the menu: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        return;
    }

    if (number == 0) {
        system("cls");
        printf("Exiting...");
        Sleep(500);
        system("cls");
        Menu();
        return;
    }

    file = fopen("Bikes.txt", "r");
    FILE *tempFile = fopen("Temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files!\n");
        return;
    }
    
    bool confirmDeletion = false;

    while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
        if (tempNumber != number) {
            fprintf(tempFile, "%-15d %-15s %-15s %d\n", tempNumber, color, brand, year);
        } else {
            found = true;
            confirmDeletion = true;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        remove("temp.txt");
        printf("Bike number %d not found!\n", number);
    } else {
        if (confirmDeletion) {
            char confirmChoice;
            printf("If you want to save the deletion of number %d press (6). If you don't, press (0): ", number);
            scanf(" %c", &confirmChoice);
            if (confirmChoice == '6') {
                remove("Bikes.txt");
                rename("temp.txt", "Bikes.txt");
                printf("Bike number %d deleted successfully.\n", number);
                usleep(500000);
            } else if (confirmChoice == '0') {
                remove("temp.txt");
                usleep(500000);
                printf("Deletion canceled for Bike number %d.\n", number);
            }
            else 
                printf("Enter A Valid Answer\n");
                Sleep(500);
                printf("Going Back to Menu...");
                Sleep(500);
                system("cls");
                Menu();
        }
    }


    char continueChoice;
    do {
        printf("Do you want to delete another registration? (Y/N): ");
        scanf(" %c", &continueChoice);
        if (continueChoice == 'Y' || continueChoice == 'y') {
            system("cls");
            DeleteRegistration(); 
        } else if (continueChoice == 'N' || continueChoice == 'n') {
            system("cls");
            Menu();
        } else {
            printf("Invalid input. Please enter (Y/N).\n");
        }
    } while (!(continueChoice == 'Y' || continueChoice == 'y' || continueChoice == 'N' || continueChoice == 'n'));
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void RenewRegistration() {
    int number, newNumber, i, numberRefresh, lines;

    FILE *file = fopen("Bikes.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int tempNumber, year;
    char color[20], brand[20];
    bool found = false;

    int maxLines = 100; 
    int *BikeNumbers = malloc(maxLines * sizeof(int)); 

    for (i = 0; i < maxLines; i++) {
        if (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
            BikeNumbers[i] = tempNumber;
        } else {
            break;
        }
    }

    fclose(file);

    bubbleSort(BikeNumbers, i); 

    printf("Available Bike Numbers (Ascending Order):\n");
    
	int j;
    for (j = 0; j < i; j++) {
        printf("%d", BikeNumbers[j]);

        if (j < i - 1) {
            printf(", ");
        }
    }

    free(BikeNumbers);
    printf("\nEnter Bike number to renew Or Press 0 to go back to the menu: ");
    scanf("%d", &number);

    if (number == 0) {
        system("cls");
        printf("Exiting...\n");
        Sleep(500);
        system("cls");
        Menu();
        return;
    }

    file = fopen("Bikes.txt", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        printf("Error opening files!\n");
        fclose(file);
        return;
    }

    lines = checkFileLines("Bikes.txt");

    for (i = 0; i < lines; i++) {
        fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year);
        if (tempNumber == number) {
            numberRefresh = i;
            found = true;
        }
    }

    if (!found) {
        printf("Bike number %d not found!\n", number);
        fclose(file);
        fclose(tempFile);
        remove("temp.txt");
        system("pause");
        system("cls");
        NewRegistration();
        return;
    }



    if (found) {
        printf("Enter new Bike number (4 digits only): ");
        if (scanf("%d", &newNumber) != 1 || getchar() != '\n' || newNumber < 1000 || newNumber > 9999) {
            printf("Invalid input. Please enter a valid 4-digit number.\n");
            system("pause");
            remove("temp.txt");
            fclose(file);
            fclose(tempFile);
            system("cls");
            Menu();
            return;
            
        }

        if (isBikeNumberExists(newNumber)) {
            printf("Bike number %d already exists in the records.\n", newNumber);
            system("pause");
            fclose(file);
            fclose(tempFile);
            remove("temp.txt");
            system("cls");
            Menu();
            
            return;
        }

        do {
            printf("\n");
            printColors();
            printf("Enter new Bike color: ");
            scanf("%s", color);
        } while (!isValidColor(color));

        do {
            printf("\n");
            printCompanies();
            printf("Enter new Bike brand: ");
            scanf("%s", brand);
        } while (!isValidBrand(brand));

        do {
            printf("\n");
            printf("Enter new Bike year of manufacture: ");
            if (scanf("%d", &year) != 1 || getchar() != '\n' || year < 1960 || year > 2024) {
                printf("Invalid input. Please enter a valid numeric year.\n");
                remove("temp.txt");
                system("pause");
                system("cls");
                Menu();
                fclose(file);
                fclose(tempFile);
                return;
            }

        } while (year < 1960 || year > 2024);
    } 

    char tempColor[20];
    char tempBrand[25];
    int tempYear;

    fseek(file, 0, SEEK_SET);

    for (i = 0; i < lines; i++) {
        fscanf(file, "%d %s %s %d", &tempNumber, tempColor, tempBrand, &tempYear);
        if (i != numberRefresh) {
            fprintf(tempFile, "%-15d %-15s %-15s %d\n", tempNumber, strupr(tempColor), tempBrand, tempYear);
        } else {
            fprintf(tempFile, "%-15d %-15s %-15s %d\n", newNumber, strupr(color), brand, year);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("Bikes.txt");
    rename("temp.txt", "Bikes.txt");

    
    char saveChoice;
    printf("Do you want to save this renewal? Press 6 or 0 to disBiked: ");
    scanf(" %c", &saveChoice);

    if (saveChoice == '6') {
        SaveDatabase();
        printf("Changes saved to the database.\n");
    } else {
        remove("temp.txt");
        printf("Changes discared.\n");
    }

    system("pause");
    system("cls");
    Menu();
}






void DisplayBikesAndReturnToSearch() {
    ShowAll();
    printf("\nPress Enter to continue...");
    system("cls");
    Search(); 
}

void searchByYear(){
    int searchYear;
    char symbol;

    printf("Enter year followed by < or >: ");
    scanf("%d%c", &searchYear, &symbol);

    FILE *file = fopen("Bikes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int tempNumber, year;
    char color[20], brand[20];

    printf("\nBikes ");
    if (symbol == '<') {
        printf("below %d:\n", searchYear);
        while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
            if (year < searchYear) {
    printf("Number: %d\n", tempNumber);
    printf("Color: %s\n", color);
    printf("Manufacturer: %s\n", brand);
    printf("Year Acquired: %d\n\n", year);
            }
        }
    } else if (symbol == '>') {
        printf("above %d:\n", searchYear);
        while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
            if (year > searchYear) {
    printf("Number: %d\n", tempNumber);
    printf("Color: %s\n", color);
    printf("Manufacturer: %s\n", brand);
    printf("Year Acquired: %d\n\n", year);
            }
        }
    } else {
        system("cls");
        printf("Invalid input.\n");
    }

    fclose(file);
    system("pause");
    system("cls");
    Menu();
    return;
}

void searchByManufacture() {
    char searchBrand[20];
    printf("Enter Brand to search for (Uppercase Only): ");
    scanf("%s", searchBrand);
    system("cls");
    FILE *file = fopen("Bikes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int tempNumber, year;
    char color[20], brand[20];

   
    int BikesFound = 0;

    while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
        if (strcmp(brand, searchBrand) == 0) {
            BikesFound = 1;  
            printf("\n");
            printf("-----------------------\n");
            printf("Number: %d\n", tempNumber);
            printf("Color: %s\n", color);
            printf("Manufacturer: %s\n", brand);
            printf("Year Acquired: %d\n", year);
            printf("-----------------------\n\n");
        }
    }

    fclose(file);

    if (BikesFound) {
        printf("Bikes with manufacturer '%s':\n\n", searchBrand);
    } else {
        printf("No Bikes named '%s' exist in the Database.\n", searchBrand);
    }

    system("pause");
    system("cls");
    Search();
    return;
}



void searchByNumber() {
    FILE *file = fopen("Bikes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int searchNumber;
    char symbol;

    printf("Enter number followed by < or >: ");

    if (scanf("%d%c", &searchNumber, &symbol) != 2 || (symbol != '<' && symbol != '>')) {
        printf("Invalid input format. Please enter a valid number followed by < or >. Press Enter To Continue\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fclose(file);
        system("cls");
        Menu();
        return;
    }

    if (searchNumber < 0 || (symbol != '<' && symbol != '>')) {
        printf("Invalid input format. Please enter a valid number followed by < or >.\n");
        getchar();
        fclose(file);
        system("pause");
        system("cls");
        Menu();
        return;
    }

    printf("\nEntries found:\n");

    int tempNumber, year;
    char color[20], brand[20];
    while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
        if ((symbol == '<' && tempNumber < searchNumber) || (symbol == '>' && tempNumber > searchNumber)) {
            printf("\n");
            printf("-----------------------\n");
            printf("Number: %d\n", tempNumber);
            printf("Color: %s\n", color);
            printf("Manufacturer: %s\n", brand);
            printf("Year Acquired: %d\n", year);
            printf("-----------------------\n\n");
        }
    }

    fclose(file);
    system("pause");
    system("cls");
    Menu();
}


void searchByColor() {
    FILE *file = fopen("Bikes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char color[20];
    char uniqueColors[100][20];
    int uniqueColorCount = 0;

    printf("Available Colors:\n");

    int tempNumber, year;
    char brand[20];
    while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
        bool colorExists = false;
        int i;
        for (i = 0; i < uniqueColorCount; ++i) {
            if (strcasecmp(uniqueColors[i], color) == 0) {
                colorExists = true;
                break;
            }
        }
        if (!colorExists) {
            strcpy(uniqueColors[uniqueColorCount], color);
            printf("%s\n", uniqueColors[uniqueColorCount]);
            uniqueColorCount++;
        }
    }

    fclose(file);

    printf("Enter Color : ");
    char searchColor[MAX_STRING_LENGTH];
    scanf("%s", searchColor);

    int inputLength = strlen(searchColor);
    
	int i;
    for (i = 0; searchColor[i] != '\0'; i++) {
        searchColor[i] = toupper(searchColor[i]);
    }

    file = fopen("Bikes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    bool entriesFound = false; 

    while (fscanf(file, "%d %s %s %d", &tempNumber, color, brand, &year) == 4) {
        if (strncmp(searchColor, color, inputLength) == 0) {
            if (!entriesFound) {

                printf("\nEntries found:\n");
                entriesFound = true; 
            }
            printf("\n");
            printf("-----------------------\n");
            printf("Number: %d\n", tempNumber);
            printf("Color: %s\n", color);
            printf("Manufacturer: %s\n", brand);
            printf("Year Acquired: %d\n", year);
            printf("-----------------------\n\n");
        }   
    }

    fclose(file);

    if (!entriesFound) {
        printf("\n");
        printf("-----------------");
        printf("\nNo Entries Found!\n");
        printf("-----------------\n");
    }

    system("pause");
    system("cls");
    Menu();
}




void Search() {
    int choice, i;
    printf("Search Options:\n");
    printf("1. Search By Plate Number (< or >)\n");
    printf("2. Search By Color \n");
    printf("3. Search By Brand\n");
    printf("4. Search By Year Acquired\n");
    printf("0. Go back to Menu\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
       case 1:
      {
    searchByNumber();
    break;
}
        case 2: 
        {
    searchByColor();
    break;
}
        case 3: 
        {
    searchByManufacture();
    break;
}
        case 4:
        {
    searchByYear();
    break;
}
        case 0:
            system("cls");
            printf("Going Back To Menu..");
            sleep(1);
            system("cls");
            Menu();
        return;

        break;
        default:
            system("cls");
            printf("Invalid choice. Please try again.\n");
            system("pause");
            system("cls");
            Search();
        return;
    }
}

void SaveDatabase() {
    FILE *sourceFile, *targetFile, *entryFile;

   
    sourceFile = fopen("Bikes.txt", "r");
    if (sourceFile == NULL) {
        printf("Error opening source file!\n");
        return;
    }

    
    targetFile = fopen("TempBikes.txt", "w");
    if (targetFile == NULL) {
        fclose(sourceFile);
        printf("Error opening target file!\n");
        return;
    }

   
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), sourceFile) != NULL) {
        fputs(buffer, targetFile);
    }

    
    fclose(sourceFile);
    fclose(targetFile);

   
    remove("Bikes.txt");
    rename("TempBikes.txt", "Bikes.txt");

    
    entryFile = fopen("NewEntry.txt", "r");
    if (entryFile != NULL) {
        int number = 0;
        char color[20] = {0};
        char brand[25] = {0};
        int year = 0;

        
        sourceFile = fopen("Bikes.txt", "a");
        if (sourceFile == NULL) {
            fclose(entryFile);
            printf("Error opening source file for appending!\n");
            return;
        }

        
        fscanf(entryFile, "%d %s %s %d", &number, color, brand, &year);
        fprintf(sourceFile, "%-15d %-15s %-15s %d\n", number, color, brand, year);

        
        fclose(sourceFile);
        fclose(entryFile);

       
        remove("NewEntry.txt");
    }

    system("cls");

    printf("Database updated successfully.\n");

    system("pause");
    system("cls");
    Menu();
}

void Menu() {
    int choice;
    
    do {
        
        printf("\t\t --------------------------------------------------------------------------\n");
        printf("\t\t|                               MAIN MENU                                   | \n");
        printf("\t\t|  1. Show All                                           `   `.             | \n");
        printf("\t\t|  2. Enter New Registration       <```--...       .---.//  < `.            | \n");
        printf("\t\t|  3. Delete a Registration         `..     `.___ /       ___`.'            | \n");
        printf("\t\t|  4. Renew a Registration             _`_ .      `      .'\\__              | \n");
        printf("\t\t|  5. Search                         .'---`.`.          / .'---`.           | \n");
        printf("\t\t|  6. Update the Database           /.'  _`.\_\        / /.'\\ `.\              | \n");
        printf("\t\t|                                  ||  <__||_|        | ||  ~  ||           | \n");
        printf("\t\t|  0. Exit                          \`.___.'/ /________\ \`.___.'/             | \n");
        printf("\t\t|                                   `.___.'              `.___.'            | \n");
        printf(" \t\t -------------------------------------------------------------------------- \n");
        
        const char *message = "Please Make A Choice: ";
    printBiggerText2(message);          
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                ShowAll();
                break;
            case 2:
                NewRegistration();
                break;
            case 3:
                DeleteRegistration();
                break;
            case 4:
                RenewRegistration();
                break; 
            case 5:
                Search();
                break;  
            case 6:
                system("cls");
                SaveDatabase();
                break;           
            case 0:
                printf("Exiting...\n");
                    sleep(1);
                    exit(0);
                break;      
            default:
                system("cls");
                printf("Invalid choice. Please try again.\n");
                Sleep(500);
                system("cls");
        }
        while(getchar() != '\n'); 
    }
    while(choice < 0 || (choice > MENU_CHOICES - 1 && choice != 0));
                   
}

int main() {
    AsciiArt();
    return 0;
}

//Copyright (c) 2024, Dimitris Mitsios. All rights Reserved