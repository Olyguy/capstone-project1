/***********************************************
 * Written by: Joseph Freitas, Juan Jose Dominguez, Arianna Bermudez, Erkan Kerem Altundal  
 * Date Written: 6/18/2023
 * Purpose: Battleship Game 
 * ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

typedef struct CORD
{
    int y;
    int x;
} CORD;

void displayAnyGrid(char anyGrid[10][10], char shipZSunk, char shipYSunk, char shipXSunk, char shipWSunk, char shipVSunk);
int getUserInput(CORD *userInput, int *misilesFired);
int printRandoms(int lower, int upper, int count);
void placeShips(int shipSize, CORD shipName[], char dataGrid[10][10], char shipLetter);
void generateDataGrid(char dataGrid[10][10], CORD shipZCords[2], CORD shipYCords[3], CORD shipXCords[3], CORD shipWCords[4], CORD shipVCords[5]);
int registerInput(char dataGrid[10][10], char displayGrid[10][10], int yCord, int xCord, int *shipZHits, int *shipYHits, int *shipXHits, int *shipWHits, int *shipVHits, CORD shipZCords[2], CORD shipYCords[3], CORD shipXCords[3], CORD shipWCords[4], CORD shipVCords[5], char *shipZSunk, char *shipYSunk, char *shipXSunk, char *shipWSunk, char *shipVSunk);
void saveGame(char dataGrid[10][10], char displayGrid[10][10], CORD shipZCords[2], CORD shipYCords[3], CORD shipXCords[3], CORD shipWCords[4], CORD shipVCords[5], int shipZHits, int shipYHits, int shipXHits, int shipWHits, int shipVHits, char shipZSunk, char shipYSunk, char shipXSunk, char shipWSunk, char shipVSunk);
void loadGame(char dataGrid[10][10], char displayGrid[10][10], CORD shipZCords[2], CORD shipYCords[3], CORD shipXCords[3], CORD shipWCords[4], CORD shipVCords[5], int *shipZHits, int *shipYHits, int *shipXHits, int *shipWHits, int *shipVHits, char *shipZSunk, char *shipYSunk, char *shipXSunk, char *shipWSunk, char *shipVSunk);

void displayAnyGrid(char anyGrid[10][10], char shipZSunk, char shipYSunk, char shipXSunk, char shipWSunk, char shipVSunk)
{


    printf("   ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%c |", 'A' + i);
        for (int j = 0; j < 10; j++)
        {
            printf("%c|", anyGrid[i][j]);
        }
        printf("\n");
    }
    // EVERYTHING BELOW SEES IF THE SHIP IS SUNK OR NOT AND DISPLAYS EACH TIME GRID IS DISPLAYED
    printf("\nZebra Ship:    ");
    switch (shipZSunk)
    {
    case 'N':
        printf("Floating");
        break;
    case 'Y':
        printf("Sunk");
        break;
    }

    printf("\nYellow Ship:   ");
    switch (shipYSunk)
    {
    case 'N':
        printf("Floating");
        break;
    case 'Y':
        printf("Sunk");
        break;
    }

    printf("\nXRay Ship:     ");
    switch (shipXSunk)
    {
    case 'N':
        printf("Floating");
        break;
    case 'Y':
        printf("Sunk");
        break;
    }

    printf("\nWestern Ship:  ");
    switch (shipWSunk)
    {
    case 'N':
        printf("Floating");
        break;
    case 'Y':
        printf("Sunk");
        break;
    }

    printf("\nVictory Ship:  ");
    switch (shipVSunk)
    {
    case 'N':
        printf("Floating\n");
        break;
    case 'Y':
        printf("Sunk\n");
        break;
    }
}

int getUserInput(CORD *userInput, int *misilesFired)
{


    char letterValue, numberValue, response[3]; // Variables needed only in this function. Gets organized into CORD STRUCT
    int xValue, yValue;

    while (1) // Turns entire function into infinite loop. Only breaks out if all values are good/valid
    {
        printf("\nEnter position on board to fire (Or enter QQ to end/save game): \n"); // Makes char array response and stores response
        scanf(" %s", &response);

        if (response[0] == 'Q') // Ends program if user submits "QQ", will have save data function later
        {                       // Whole function will need to pass dataArray and displayArray eventually to save
            if (response[1] == 'Q')
            {
                printf("Saving data, ending program");
                return (1);
            }
        }

        letterValue = response[0];               // puts array response[0] into char variable "letterValue"
        numberValue = response[1] + response[2]; // puts array response[1+2} into char variable "numberValue"

        xValue = numberValue - '0'; // puts/transforms char variable numberValue to integer variable "xValue"

        // CHECKS SIZE OF xValue, if it doesn't pass it loops function over again until good value
        if (0 > xValue)
        {
            printf("\nNumber value out of range, please try again\n", xValue);
            continue;
        }
        else if (xValue > 9)
        {
            printf("\nNumber value out of range, please try again\n", xValue);
            continue;
        }

        // CHAR VARIABLE "letterValue" WHICH IS STILL A LETTER DECIDES WHAT "yValue" SHOULD BE
        //(if A, make value 0, if C make value 2 etc) ALSO CHECKS TO MAKE SURE USER SUBMITTED A VALID LETTER

        if (letterValue == 'A')
        {
            yValue = 0;
            break;
        }
        else if (letterValue == 'B')
        {
            yValue = 1;
            break;
        }
        else if (letterValue == 'C')
        {
            yValue = 2;
            break;
        }
        else if (letterValue == 'D')
        {
            yValue = 3;
            break;
        }
        else if (letterValue == 'E')
        {
            yValue = 4;
            break;
        }
        else if (letterValue == 'F')
        {
            yValue = 5;
            break;
        }
        else if (letterValue == 'G')
        {
            yValue = 6;
            break;
        }
        else if (letterValue == 'H')
        {
            yValue = 7;
            break;
        }
        else if (letterValue == 'I')
        {
            yValue = 8;
            break;
        }
        else if (letterValue == 'J')
        {
            yValue = 9;
            break;
        }
        else
        {
            printf("\nLetter value out of range, please try again (CAPS SENSITIVE)\n");
        }
    }

    (*userInput).y = yValue;
    (*userInput).x = xValue;
    (*misilesFired) = (*misilesFired) + 1; // Adds counter to missilesFired, used in main to show total shots fired. Will only update if valid cord is given
    return (0);
}

int printRandoms(int lower, int upper, int count) // Used in generateDataGrid to get random numbers not only for direction but cordinate values
{


    int i;
    for (i = 0; i < count; i++)
    {
        int num = (rand() % (upper - lower + 1)) + lower;
        return (num);
    }
}

void placeShips(int shipSize, CORD shipName[], char dataGrid[10][10], char shipLetter)
{


    int i, rnum, xyArray[2];
    srand(time(0));

    while (1)
    {
        // Generate random coordinates
        for (i = 0; i < 2; i++)
        {
            rnum = rand() % 10;
            xyArray[i] = rnum;
        }

        CORD randomCord;
        randomCord.y = xyArray[0];
        randomCord.x = xyArray[1];

        // Check if the starting position is valid
        if (dataGrid[randomCord.y][randomCord.x] != 'M')
        {
            continue;
        }

        // Initialize flag variable
        int shipPlaced = 1;

        // Place ship based on random direction
        int randomNumberDirection = rand() % 4 + 1;
        switch (randomNumberDirection)
        {
        case 1: // Up
            for (i = 0; i < shipSize; i++)
            {
                if (randomCord.y - i < 0 || dataGrid[randomCord.y - i][randomCord.x] != 'M')
                {
                    shipPlaced = 0;
                    break;
                }
                shipName[i].y = randomCord.y - i;
                shipName[i].x = randomCord.x;
            }
            break;
        case 2: // Right
            for (i = 0; i < shipSize; i++)
            {
                if (randomCord.x + i >= 10 || dataGrid[randomCord.y][randomCord.x + i] != 'M')
                {
                    shipPlaced = 0;
                    break;
                }
                shipName[i].y = randomCord.y;
                shipName[i].x = randomCord.x + i;
            }
            break;
        case 3: // Down
            for (i = 0; i < shipSize; i++)
            {
                if (randomCord.y + i >= 10 || dataGrid[randomCord.y + i][randomCord.x] != 'M')
                {
                    shipPlaced = 0;
                    break;
                }
                shipName[i].y = randomCord.y + i;
                shipName[i].x = randomCord.x;
            }
            break;
        case 4: // Left
            for (i = 0; i < shipSize; i++)
            {
                if (randomCord.x - i < 0 || dataGrid[randomCord.y][randomCord.x - i] != 'M')
                {
                    shipPlaced = 0;
                    break;
                }
                shipName[i].y = randomCord.y;
                shipName[i].x = randomCord.x - i;
            }
            break;
        }

        // If ship placement was successful, break the loop
        if (shipPlaced)
        {
            for (i = 0; i < shipSize; i++)
            {
                dataGrid[shipName[i].y][shipName[i].x] = shipLetter;
            }
            break;
        }
    }
}

void generateDataGrid(char dataGrid[10][10], CORD shipZCords[2], CORD shipYCords[3], CORD shipXCords[3], CORD shipWCords[4], CORD shipVCords[5])
{

    placeShips(2, shipZCords, dataGrid, 'Z');

    placeShips(3, shipYCords, dataGrid, 'Y');

    placeShips(3, shipXCords, dataGrid, 'X');

    placeShips(4, shipWCords, dataGrid, 'W');

    placeShips(5, shipVCords, dataGrid, 'V');
}

int registerInput(char dataGrid[10][10], char displayGrid[10][10], int yCord, int xCord, int *shipZHits, int *shipYHits, int *shipXHits, int *shipWHits, int *shipVHits, CORD shipZCords[2], CORD shipYCords[3], CORD shipXCords[3], CORD shipWCords[4], CORD shipVCords[5], char *shipZSunk, char *shipYSunk, char *shipXSunk, char *shipWSunk, char *shipVSunk)
{


    char value;
    int i = 0;
    value = dataGrid[yCord][xCord]; // declares values
    int response;

    if (value == 'M') // if value of datagrid == M then display M on display board
    {
        displayGrid[yCord][xCord] = value;
    }

    if (value != 'M') // if value of datagrid is not M, then display H on display board and then figure out which "ship" it is, add a "hit" to the ship(etc) counter, and once the entire ship is hit replace the "H"'s of the ship with the ship letter
    {
        displayGrid[yCord][xCord] = 'H';
        switch (value)
        {

        case 'Z':
            *shipZHits = *shipZHits + 1;
            if (*shipZHits == 2)
            {
                for (i = 0; i < 2; i++)
                {
                    displayGrid[shipZCords[i].y][shipZCords[i].x] = 'Z';
                }
                *shipZSunk = 'Y';
            }
            break;

        case 'Y':
            *shipYHits = *shipYHits + 1;
            if (*shipYHits == 3)
            {
                for (i = 0; i < 3; i++)
                {
                    displayGrid[shipYCords[i].y][shipYCords[i].x] = 'Y';
                }
                *shipYSunk = 'Y';
            }
            break;

        case 'X':
            *shipXHits = *shipXHits + 1;
            if (*shipXHits == 3)
            {
                for (i = 0; i < 3; i++)
                {
                    displayGrid[shipXCords[i].y][shipXCords[i].x] = 'X';
                }
                *shipXSunk = 'Y';
            }
            break;

        case 'W':
            *shipWHits = *shipWHits + 1;
            if (*shipWHits == 4)
            {
                for (i = 0; i < 4; i++)
                {
                    displayGrid[shipWCords[i].y][shipWCords[i].x] = 'W';
                }
                *shipWSunk = 'Y';
            }
            break;

        case 'V':
            *shipVHits = *shipVHits + 1;
            if (*shipVHits == 5)
            {
                for (i = 0; i < 5; i++)
                {
                    displayGrid[shipVCords[i].y][shipVCords[i].x] = 'V';
                }
                *shipVSunk = 'Y';
            }
            break;
        }

        if ((*shipZSunk == 'Y') && (*shipYSunk == 'Y') && (*shipXSunk == 'Y') && (*shipWSunk == 'Y') && (*shipVSunk == 'Y')) // Checks to see if player won using ship(etc)sunk variable
        {
            displayAnyGrid(displayGrid, *shipZSunk, *shipYSunk, *shipXSunk, *shipWSunk, *shipVSunk);

            printf("\nYOU WON YIPPE\n\nWould you like to start a new game?"); // Entire section below decides if player wishes to exit or start new game, returns value (1) which is used in main to reset all values for a new game
            while (1)
            {
                printf("\nEnter 1 if you wish to exit or 2 to start another game:");
                scanf(" %d", &response);

                if (response == 1)
                {
                    printf("\nEnding program. Thanks for playing!\n");
                    exit(1);
                }
                else if (response == 2)
                {
                    printf("\nStarting new game!\n");
                    return (1);
                }
                else
                {
                    printf("\nInvalid input, please try again with either 1 or 2\n");
                }
            }
        }
    }
}

void saveGame(char dataGrid[10][10], char displayGrid[10][10], CORD shipZCords[2], CORD shipYCords[3], CORD shipXCords[3], CORD shipWCords[4], CORD shipVCords[5], int shipZHits, int shipYHits, int shipXHits, int shipWHits, int shipVHits, char shipZSunk, char shipYSunk, char shipXSunk, char shipWSunk, char shipVSunk)
{


    FILE *ptr;
    ptr = fopen("SaveDataForBattleship.bin", "wb");
    if (ptr == NULL)
    {
        printf("\nData was not able to save\n");
        exit(-1);
    }

    fwrite(dataGrid, sizeof(char), 100, ptr);
    fwrite(displayGrid, sizeof(char), 100, ptr);

    fwrite(shipZCords, sizeof(struct CORD), 2, ptr);
    fwrite(shipYCords, sizeof(struct CORD), 3, ptr);
    fwrite(shipXCords, sizeof(struct CORD), 3, ptr);
    fwrite(shipWCords, sizeof(struct CORD), 4, ptr);
    fwrite(shipVCords, sizeof(struct CORD), 5, ptr);

    fwrite(&shipZHits, sizeof(int), 1, ptr);
    fwrite(&shipYHits, sizeof(int), 1, ptr);
    fwrite(&shipXHits, sizeof(int), 1, ptr);
    fwrite(&shipWHits, sizeof(int), 1, ptr);
    fwrite(&shipVHits, sizeof(int), 1, ptr);

    fwrite(&shipZSunk, sizeof(char), 1, ptr);
    fwrite(&shipYSunk, sizeof(char), 1, ptr);
    fwrite(&shipXSunk, sizeof(char), 1, ptr);
    fwrite(&shipWSunk, sizeof(char), 1, ptr);
    fwrite(&shipVSunk, sizeof(char), 1, ptr);

    fclose(ptr);

    printf("\nGame saved successfully.\n");
}

void loadGame(char dataGrid[10][10], char displayGrid[10][10], CORD shipZCords[2], CORD shipYCords[3], CORD shipXCords[3], CORD shipWCords[4], CORD shipVCords[5], int *shipZHits, int *shipYHits, int *shipXHits, int *shipWHits, int *shipVHits, char *shipZSunk, char *shipYSunk, char *shipXSunk, char *shipWSunk, char *shipVSunk)
{


    FILE *ptr;
    ptr = fopen("SaveDataForBattleship.bin", "rb");
    if (ptr == NULL)
    {
        printf("\nData was not able to be loaded\n");
        exit(-1);
    }

    fread(dataGrid, sizeof(char), 100, ptr);
    fread(displayGrid, sizeof(char), 100, ptr);

    fread(shipZCords, sizeof(struct CORD), 2, ptr);
    fread(shipYCords, sizeof(struct CORD), 3, ptr);
    fread(shipXCords, sizeof(struct CORD), 3, ptr);
    fread(shipWCords, sizeof(struct CORD), 4, ptr);
    fread(shipVCords, sizeof(struct CORD), 5, ptr);

    fread(shipZHits, sizeof(int), 1, ptr);
    fread(shipYHits, sizeof(int), 1, ptr);
    fread(shipXHits, sizeof(int), 1, ptr);
    fread(shipWHits, sizeof(int), 1, ptr);
    fread(shipVHits, sizeof(int), 1, ptr);

    fread(shipZSunk, sizeof(char), 1, ptr);
    fread(shipYSunk, sizeof(char), 1, ptr);
    fread(shipXSunk, sizeof(char), 1, ptr);
    fread(shipWSunk, sizeof(char), 1, ptr);
    fread(shipVSunk, sizeof(char), 1, ptr);

    fclose(ptr);

    printf("\nSave data has been reloaded\n");
}

int main()
{


    // Makes 2D array base with all "M's"
    char dataGrid[10][10];
    memset(dataGrid, 'M', sizeof(dataGrid));

    char displayGrid[10][10];
    memset(displayGrid, '.', sizeof(displayGrid));

    CORD shipZCords[2], shipYCords[3], shipXCords[3], shipWCords[4], shipVCords[5];           // cords for ship placements, decided when generating board
    int shipZSize = 2, shipYSize = 3, shipXSize = 3, shipWSize = 4, shipVSize = 5;            // sizes of ship, used to know how big to make ship when generating board and when ship has been sunk (When shipSize == shipHits)
    int shipZHits = 0, shipYHits = 0, shipXHits = 0, shipWHits = 0, shipVHits = 0;            // keeps track of how many times ship has been hit
    char shipZSunk = 'N', shipYSunk = 'N', shipXSunk = 'N', shipWSunk = 'N', shipVSunk = 'N'; // keeps track if ship is sunk or not "N" for no, "Y" for yes
    int misilesFired = 0;

    // Uses dataGrid[] and generates randomly located ships
    // Also gets values of all ship cordinates, to be-
    // -used later when displaying "H/Hit" to the letter of the ship "Z/ZShip"
    generateDataGrid(dataGrid, shipZCords, shipYCords, shipXCords, shipWCords, shipVCords);

    CORD userInput;
    int quitGame; // VARIABLES FOR LOADING DATA ETC AND CORDS FOR CORDS
    int response;

    while (1) // This while statement decides/loads whether a new game is to start or to load a previous game, Could put in function but passing all these values is a pain
    {
        printf("\nWould you like to load any saved data (If exists)?\nEnter 1 to load data, or 2 to start a new game: \n");
        scanf(" %d", &response);

        if (response == 1)
        {
            printf("Loading saved data...\n");
            loadGame(dataGrid, displayGrid, shipZCords, shipYCords, shipXCords, shipWCords, shipVCords, &shipZHits, &shipYHits, &shipXHits, &shipWHits, &shipVHits, &shipZSunk, &shipYSunk, &shipXSunk, &shipWSunk, &shipVSunk);
            break;
        }
        else if (response == 2)
        {
            printf("Starting brand new game/save...\n");
            break;
        }
        else
        {
            printf("Invalid input, please try again with either 1 or 2\n");
        }
    }

    displayAnyGrid(displayGrid, shipZSunk, shipYSunk, shipXSunk, shipWSunk, shipVSunk); // Just displays grid at beggining of each game

    while (1) // This is the main while loop, gets userInput, figures out what cord was hit, what the value was at that cord, and then updates the display grid. Repeats till end of game
    {
        quitGame = getUserInput(&userInput, &misilesFired);
        if (quitGame == 1)
        {
            saveGame(dataGrid, displayGrid, shipZCords, shipYCords, shipXCords, shipWCords, shipVCords, shipZHits, shipYHits, shipXHits, shipWHits, shipVHits, shipZSunk, shipYSunk, shipXSunk, shipWSunk, shipVSunk);
            exit(1);
        }

        if ((registerInput(dataGrid, displayGrid, userInput.y, userInput.x, &shipZHits, &shipYHits, &shipXHits, &shipWHits, &shipVHits, shipZCords, shipYCords, shipXCords, shipWCords, shipVCords, &shipZSunk, &shipYSunk, &shipXSunk, &shipWSunk, &shipVSunk) == 1))
        {
            // Entire if "loop" checks each time an input is recorded, and "registerInput" will only return value "1" if the user requests to start a new game after winning
            // So everything in here will pretty much reset any value record. With "generateDataGrid" also resetting or generatting new ship(ETC)Cords for all ships. FULL RESET
            memset(displayGrid, '.', sizeof(displayGrid));
            memset(dataGrid, 'M', sizeof(dataGrid));
            shipZSize = 2, shipYSize = 3, shipXSize = 3, shipWSize = 4, shipVSize = 5;
            shipZHits = 0, shipYHits = 0, shipXHits = 0, shipWHits = 0, shipVHits = 0;
            shipZSunk = 'N', shipYSunk = 'N', shipXSunk = 'N', shipWSunk = 'N', shipVSunk = 'N';
            misilesFired = 0;
            generateDataGrid(dataGrid, shipZCords, shipYCords, shipXCords, shipWCords, shipVCords);
        }

        // displayAnyGrid(dataGrid, shipZSunk, shipYSunk, shipXSunk, shipWSunk, shipVSunk);    // displays data grid for testing, need to delete final submission

        displayAnyGrid(displayGrid, shipZSunk, shipYSunk, shipXSunk, shipWSunk, shipVSunk); // displays display grid, KEEP
        printf("\nMissiles Fired: %d\n", misilesFired);
    }

    return 0;
}
