#include <stdio.h>
#include <string.h>

// Define a structure to hold address book contact information
struct Contact
{
  char firstName[50];      // First name of the contact
  char lastName[50];       // Last name of the contact
  char email[100];         // Email address (must contain '@')
  char phoneNumber[20];    // Phone number (digits only)
  char postalAddress[150]; // Postal address
};

void displayMenu();
void cleanBuffer();
void removeNewLine(char *str);
void displayEntryCreation();
void getInputString(const char *prompt, char *output, int size);
int getIntInput(const char *prompt);
void getValidatedEmail(char *email, int size);
void getValidatedPhone(char *phone, int size);
void createNewEntry();
void printContact(const struct Contact *contact);
void printAllContacts();

#define maxContacts 100
struct Contact contacts[maxContacts];
int contactCount = 0;

// Temporary function so that we can see it works. Only used for the printAllContacts
void printContact(const struct Contact *contact)
{
  printf("\n┌──────────────────────────────────┐");
  printf("\n│           CONTACT CARD          │");
  printf("\n├──────────────────────────────────┤");
  printf("\n│ %-15s %-15s │", contact->firstName, contact->lastName);
  printf("\n│ %-30s │", contact->email);
  printf("\n│ %-30s │", contact->phoneNumber);
  printf("\n│ %-30s │", contact->postalAddress);
  printf("\n└──────────────────────────────────┘\n");
}

// Temporary function to print all contacts saved so far
void printAllContacts()
{
  if (contactCount == 0)
  {
    printf("\nNo contacts available.\n");
    return;
  }

  printf("\n=== ALL CONTACTS (%d) ===\n", contactCount);
  for (int i = 0; i < contactCount; i++)
  {
    printf("\nContact #%d:", i + 1);
    printContact(&contacts[i]);
  }
  printf("=======================\n");
}

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

// Helper for string input
void getInputString(const char *prompt, char *output, int size)
{
  printf("%s", prompt);
  fgets(output, size, stdin);
  removeNewLine(output);
}

// Function to get the user to input a valid email
void getValidatedEmail(char *email, int size)
{
  while (1)
  {
    getInputString("Enter email: ", email, size);
    // Validate if the @ is inside the string
    if (strchr(email, '@') != NULL)
      break;
    else
      printf("Invalid email. Must contain '@'. Try again.\n");
  }
}

// Function to get the user to input a valid phone number
void getValidatedPhone(char *phone, int size)
{
  int phoneNum;

  while (1)
  {
    phoneNum = getIntInput("Enter SPANISH phone number (9 digits only): ");

    // Convert integer to string and store it
    snprintf(phone, size, "%d", phoneNum);

    // Check number length to make sure its a valid phone number
    if (strlen(phone) != 9)
    {
      printf("Invalid phone number length. Try again.\n");
    }
    else
    {
      break;
    }
  }
}

void createNewEntry()
{
  struct Contact newContact;

  printf("\nCreating a new contact entry:\n");

  // This gets the user to input each attribute and validates them using the functions
  getInputString("Enter first name: ", newContact.firstName, sizeof(newContact.firstName));
  getInputString("Enter last name: ", newContact.lastName, sizeof(newContact.lastName));
  getValidatedEmail(newContact.email, sizeof(newContact.email));
  getValidatedPhone(newContact.phoneNumber, sizeof(newContact.phoneNumber));
  getInputString("Enter postal address: ", newContact.postalAddress, sizeof(newContact.postalAddress));

  // Prints contact information
  printf("\nContact created successfully:\n");
  printf("Name: %s %s\n", newContact.firstName, newContact.lastName);
  printf("Email: %s\n", newContact.email);
  printf("Phone: %s\n", newContact.phoneNumber);
  printf("Address: %s\n", newContact.postalAddress);

  // Saves the contact information into the contacts array
  // Also increments the contactsCount (to reach the limit)
  contacts[contactCount++] = newContact;

  // TODO: Save to file or database
}

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
          createNewEntry();
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
      // Temporary have this here for verification
      printAllContacts();
    }

    else
    {
      printf("\nThis is not a valid input, please enter one of the available options.\n");
    }
  }
}