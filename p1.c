#include <stdio.h>
#include <string.h>

int x = 1;
int y = 1;

void displayMenu();
void cleanBuffer();
void removeNewLine();
void displayEntryCreation();
int getIntInput(const char *prompt);

// Function to display main menu
void displayMenu()
{
  printf("\nWelcome to the main menu\n");
  printf("0 - Close program\n");
  printf("1 - Save an entry\n");
  printf("2 - Retrieve an existing entry\n");
}

// Function to display the menu during entry creation
void displayEntryCreation()
{
  printf("\nWelcome to the entry creation menu\n");
  printf("0 - Return to main menu\n");
  printf("1 - Create a new entry\n");
  printf("2 - Edit an existing entry\n");
}

// Function to safely get an integer input from the user
int getIntInput(const char *prompt)
{
  int input;  // Variable to store the user's input
  int result; // Variable to store the result of scanf (number of successfully matched inputs)

  while (1)
  {
    printf("%s", prompt);
    // Attempt to read an integer from the user
    result = scanf("%d", &input); // scanf returns 1 if it successfully reads an integer
    cleanBuffer();

    if (result == 1)
    {
      return input;
    }
    else
    {
      // If the input was invalid (not an integer), print an error message
      printf("\nInvalid input. Please enter a number.\n");
    }
  }
}

// Function to remove additional characters until a new line is reached
void cleanBuffer()
{
  while (getchar() != '\n')
    ;
}

// Function to remove newline characters from strings
void removeNewLine(char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == '\n')
    {
      str[i] = '\0';

      break;
    }
  }
}

// Def ine a structure to hold address book contact information
struct Contact
{
  char firstName[50];      // First name of the contact
  char lastName[50];       // Last name of the contact
  char email[100];         // Email address (must contain '@')
  char phoneNumber[20];    // Phone number (digits only)
  char postalAddress[150]; // Postal address
};

int main()
{
  int mainInput;
  int entryInput;
  while (1)
  {
    displayMenu();
    // Get validated entry menu input
    mainInput = getIntInput("\nPlease input a number according to the menu: ");

    if (mainInput == 0)
    {
      printf("\nThanks for using our service\n");
      return 0;
    }

    else if (mainInput == 1)
    {
      while (1)
      {
        displayEntryCreation();
        // Get validated main menu input
        entryInput = getIntInput("\nPlease input a number according to the menu: ");

        if (entryInput == 0)
        {
          break;
        }

        else if (entryInput == 1)
        {
          printf("\nYou have selected to create a new entry\n");
        }

        else if (entryInput == 2)
        {
          printf("\nYou have selected to edit an existing entry\n");
        }

        else
        {
          printf("\nThis is not a valid input.\n");
        }
      }
    }

    else if (mainInput == 2)
    {
    }

    else
    {
      printf("\nThis is not a valid input, please enter one of the available options.\n");
    }
  }
}