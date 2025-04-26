#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Define a structure to hold address book contact information
struct Contact
{
  int contactNumber;       // Contact number of the contact
  char firstName[50];      // First name of the contact
  char lastName[50];       // Last name of the contact
  char email[100];         // Email address (must contain '@')
  char phoneNumber[11];    // Phone number
  char postalAddress[150]; // Postal address
};

// Declare functions
void displayMenu();
void cleanBuffer();
void removeNewLine(char *str);
void displayEntryCreation();
void displayReadingMenu();
void getInputString(const char *prompt, char *output, int size);
int getIntInput(const char *prompt);
bool isValidName(const char *name);
bool isValidAddress(const char *address);
void getValidName(const char *prompt, char *output, int size);
void getValidAddress(const char *prompt, char *output, int size);
void getValidatedEmail(char *email, int size);
void getValidatedPhone(char *phone, int size);
void createNewEntry();
void printContact(const struct Contact *contact);
void printAllContacts();
void searchContacts();
void trimTrailingWhitespace(char *str);
void saveContactsToCSV(const char *filename);
void loadContactsFromCSV(const char *filename);
int findContactByNumber(int number);
void deleteContact(int index);
void getValidNameWithEquals(const char *prompt, char *output, int size);
void getValidAddressWithEquals(const char *prompt, char *output, int size);
void getValidEmailWithEquals(const char *prompt, char *output, int size);
void getValidPhoneWithEquals(const char *prompt, char *output, int size);
void editContact(int index);

#define maxContacts 1000
// Array for contacts
struct Contact contacts[maxContacts];
int contactCount = 0;

// Variable to warn user if there are unsaved changes
int unsavedChanges = 0;

// Temporary function so that we can see it works. Only used for the printAllContacts
void printContact(const struct Contact *contact)
{
  printf("\n--------------------------------");
  printf("\nContact Number: %d", contact->contactNumber);
  printf("\nContact First Name: %s", contact->firstName);
  printf("\nContact Last Name: %s", contact->lastName);
  printf("\nContact Email: %s", contact->email);
  printf("\nContact Phone Number: %s", contact->phoneNumber);
  printf("\nContact Postal Address: %s", contact->postalAddress);
  printf("\n--------------------------------\n");
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
}

// Function to display main menu
void displayMenu()
{
  printf("\nWelcome to the main menu\n");
  printf("0 - Close program\n");
  printf("1 - Save an entry\n");
  printf("2 - Retrieve an existing entry\n");
  printf("3 - Save changes\n");
}

// Function to display the menu during entry creation
void displayEntryCreation()
{
  printf("\nWelcome to the entry creation menu\n");
  printf("0 - Return to main menu\n");
  printf("1 - Create a new entry\n");
  printf("2 - Edit an existing entry\n");
}

// Function to display the menu during reading mode
void displayReadingMenu()
{
  printf("\nWelcome to the reading menu\n");
  printf("0 - Return to main menu\n");
  printf("1 - Print out all contacts\n");
  printf("2 - Search for contacts by field and additional criteria\n");
}

// Function to safely get an integer input from the user
int getIntInput(const char *prompt)
{
  // Variable to store the user's input
  int input;
  // Variable to store the result of scanf
  int result;

  while (1)
  {
    printf("%s", prompt);
    // Attempt to read an integer from the user
    // scanf returns 1 if it successfully reads an integer
    result = scanf("%d", &input);
    cleanBuffer();

    if (result == 1)
    {
      return input;
    }
    else
    {
      // If the input was invalid (not an integer), print an error message
      printf("\nInvalid input. Please enter a number.\n\n");
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

// Function for string input
void getInputString(const char *prompt, char *output, int size)
{
  printf("%s", prompt);
  fgets(output, size, stdin);
  removeNewLine(output);
}

// Boolean value to check for valid name (at least 2 non space characters)
bool isValidName(const char *name)
{
  // Tracks number of non-space characters
  int nonSpaceCount = 0;

  // Rejects NULL pointers or empty strings
  if (name == NULL || name[0] == '\0')
  {
    return false;
  }

  // Iterate through each character in the string
  for (int i = 0; name[i] != '\0'; i++)
  {
    // Count only non-space characters
    if (!isspace(name[i]))
    {
      nonSpaceCount++;
    }
  }

  // Final check if it returns true then valid
  return (nonSpaceCount >= 2);
}

// Boolean value to check for valid postal address (at least 2 non space characters)
bool isValidAddress(const char *address)
{
  // Tracks number of non-space characters
  int nonSpaceCount = 0;

  // Rejects NULL pointers or empty strings
  if (address == NULL || address[0] == '\0')
  {
    return false;
  }

  // Iterate through each character in the string
  for (int i = 0; address[i] != '\0'; i++)
  {
    // Count only non-space characters
    if (!isspace(address[i]))
    {
      nonSpaceCount++;
    }
  }

  // Final check if it returns true then valid
  return (nonSpaceCount >= 2);
}

// Function to check if the name the user is inputing is valid
void getValidName(const char *prompt, char *output, int size)
{

  while (1)
  {
    // Get input from user
    getInputString(prompt, output, size);

    if (strcmp(output, "-") == 0)
    {
      strncpy(output, "N/A", size);
      break;
    }

    // Validate the input
    if (isValidName(output))
    {
      // Exit loop if valid
      break;
    }

    // Show error message for invalid input
    printf("\nInvalid name! Must contain at least 2 non-space characters.\n\n");
  }
}

// Function to check if the postal address the user is inputing is valid
void getValidAddress(const char *prompt, char *output, int size)
{
  while (1)
  {
    // Get input from user
    getInputString(prompt, output, size);

    if (strcmp(output, "-") == 0)
    {
      strncpy(output, "N/A", size);
      break;
    }

    // Validate the input
    if (isValidAddress(output))
    {
      // Exit loop if valid
      break;
    }

    // Show error message for invalid input
    printf("\nInvalid postal address! Must contain at least 2 non-space characters.\n\n");
  }
}

// Function to get the user to input a valid email
void getValidatedEmail(char *email, int size)
{
  while (1)
  {
    getInputString("Enter email or '-' for N/A: ", email, size);

    if (strcmp(email, "-") == 0)
    {
      strncpy(email, "N/A", size);
      break;
    }

    // Validate if the @ is inside the string
    if (strchr(email, '@') != NULL)
      break;
    else
      printf("\nInvalid email. Must contain '@'. Try again.\n\n");
  }
}

// Function to validate the phone input
void getValidatedPhone(char *phone, int size)
{
  // Temporary buffer for raw input
  char input[20];

  while (1)
  {
    printf("Please enter a SPANISH phone number (9 digits, no leading 0) or '-' for N/A: ");
    fgets(input, sizeof(input), stdin);
    removeNewLine(input);

    // Handle N/A case
    if (strcmp(input, "-") == 0)
    {
      strncpy(phone, "N/A", size);
      break;
    }

    // Validate it's a valid number
    int valid = 1;
    int length = strlen(input);

    // Check length
    if (length != 9)
    {
      valid = 0;
    }

    // Check all characters are digits
    for (int i = 0; i < length; i++)
    {
      if (!isdigit(input[i]))
      {
        valid = 0;
        break;
      }
    }

    // Check it doesn't start with 0
    if (input[0] == '0')
    {
      valid = 0;
    }

    if (valid)
    {
      strncpy(phone, input, size);
      break;
    }
    else
    {
      printf("Invalid phone number. Must be exactly 9 digits, no leading 0, and only numbers.\n");
    }
  }
}

// Function to create a new contact
void createNewEntry()
{
  struct Contact newContact;

  printf("\nCreating a new contact entry:\n");

  // Sets up the unsaved changes flag
  unsavedChanges = 1;

  // This gets the user to input each attribute and validates them using the functions previously created
  newContact.contactNumber = contactCount + 1;
  getValidName("Enter first name or '-' for N/A: ", newContact.firstName, sizeof(newContact.firstName));
  getValidName("Enter last name or '-' for N/A: ", newContact.lastName, sizeof(newContact.lastName));
  getValidatedEmail(newContact.email, sizeof(newContact.email));
  getValidatedPhone(newContact.phoneNumber, sizeof(newContact.phoneNumber));
  getValidAddress("Enter postal address or '-' for N/A: ", newContact.postalAddress, sizeof(newContact.postalAddress));

  // Prints contact information
  printf("\nContact created successfully:\n");
  printf("Contact Number: %d\n", newContact.contactNumber);
  printf("Name: %s %s\n", newContact.firstName, newContact.lastName);
  printf("Email: %s\n", newContact.email);
  printf("Phone: %s\n", newContact.phoneNumber);
  printf("Address: %s\n", newContact.postalAddress);

  // Saves the contact information into the contacts array
  // Also increments the contactsCount (to reach the limit)
  contacts[contactCount++] = newContact;

  // Asks the user if they want to save the contact
  while (1)
  {
    printf("\nDo you want to save this contact to the file? (y/n): ");
    char choice = getchar();
    cleanBuffer();

    if (choice == 'y' || choice == 'Y')
    {
      saveContactsToCSV("contacts.csv");
      printf("\nContact saved successfully\n");
      unsavedChanges = 0;
      break;
    }

    else if (choice == 'n' || choice == 'N')
    {
      printf("\nContact won't be saved\n");
      break;
    }

    else
    {
      printf("\nThis is not a valid input, only 'y' or 'n' are accepted\n");
    }
  }
}

// Function to trim extra characters or space from csv entries
void trimTrailingWhitespace(char *str)
{
  int len = strlen(str);
  while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len - 1] == '\r'))
  {
    str[len - 1] = '\0';
    len--;
  }
}

// DISCLAIMER for some reason it works even if we use "," inside the input
// REMMEBER TO DELETE THESE TWO COMMENTS BEFORE HANDING IN
//////
//////
//////
//////
//////
//////
//////
//////
//////
//////
//////
//////
//////
//////

// Function to load contacts from a CSV file into the contacts array
void loadContactsFromCSV(const char *filename)
{
  // Opens the csv file in reading mode
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    // If file can't be opened, show warning and return
    printf("Warning: Could not open %s. Starting with empty contact list.\n", filename);
    return;
  }

  // Buffer to hold each line read from the file
  char line[512];
  // Track current line number (for skipping header)
  int lineNumber = 0;

  // Read file line by line until end of file or max contacts reached
  while (fgets(line, sizeof(line), file) && contactCount < maxContacts)
  {
    // Skip the first line (header row)
    if (lineNumber++ == 0)
      continue; // Skip header with column names

    // Temporary contact to hold parsed data
    struct Contact newContact;
    // Pointer for string tokens
    char *token;

    // Parse contact number (first field)
    token = strtok(line, ",");
    // Skip line if missing data
    if (!token)
      continue;
    // Convert string to integer and add to contact
    newContact.contactNumber = atoi(token);

    // Parse first name (second field)
    token = strtok(NULL, ",");
    if (!token)
      continue;
    // Add first name to contact
    strncpy(newContact.firstName, token, sizeof(newContact.firstName));
    trimTrailingWhitespace(newContact.firstName);

    // Parse last name (third field)
    token = strtok(NULL, ",");
    if (!token)
      continue;
    strncpy(newContact.lastName, token, sizeof(newContact.lastName));
    trimTrailingWhitespace(newContact.lastName);

    // Parse email (fourth field)
    token = strtok(NULL, ",");
    if (!token)
      continue;
    strncpy(newContact.email, token, sizeof(newContact.email));
    trimTrailingWhitespace(newContact.email);

    // Parse phone number (fifth field)
    token = strtok(NULL, ",");
    if (!token)
      continue;
    strncpy(newContact.phoneNumber, token, sizeof(newContact.phoneNumber));
    trimTrailingWhitespace(newContact.phoneNumber);

    // Parse address (sixth field)
    token = strtok(NULL, ",\n");
    if (!token)
      continue;
    strncpy(newContact.postalAddress, token, sizeof(newContact.postalAddress));
    trimTrailingWhitespace(newContact.postalAddress);

    // Add the parsed contact to the contacts array and increment the contactCount
    contacts[contactCount++] = newContact;
  }

  // Closes the file once all the data has been read and saved to the array of strucutres
  fclose(file);

  // Informs the user that the contacts have been loaded into the program safely
  printf("\nLoaded %d contacts from %s\n", contactCount, filename);
}

// Function to search for contacts
void searchContacts()
{
  while (1)
  {
    printf("\nWhich field do you want to search by\n");
    printf("0 - Return to reading menu\n");
    printf("1 - Contact Number\n");
    printf("2 - First Name\n");
    printf("3 - Last Name\n");
    printf("4 - Email\n");
    printf("5 - Phone Number\n");
    printf("6 - Postal Address\n");

    int choice = getIntInput("Please enter your choice: ");

    char searchTerm[100];
    // Flag to track if any contacts were found
    int foundCount = 0;
    // Array to store contacts from search
    int foundIndexes[1000];

    // Return to reading menu
    if (choice == 0)
    {
      break;
    }

    // Search by contact number
    else if (choice == 1)
    {
      int contactNumber = getIntInput("\nEnter the Contact Number to search for: ");
      if (contactNumber <= 0)
      {
        printf("Invalid contact number. Must be positive.\n");
        continue;
      }

      for (int i = 0; i < contactCount; i++)
      {
        if (contacts[i].contactNumber == contactNumber)
        {
          foundIndexes[foundCount++] = i;
        }
      }
    }

    // Search by first name
    else if (choice == 2)
    {
      getInputString("\nEnter the First Name (or starting characters): ", searchTerm, sizeof(searchTerm));
      for (int i = 0; i < contactCount; i++)
      {
        if (strncasecmp(contacts[i].firstName, searchTerm, strlen(searchTerm)) == 0)
        {
          foundIndexes[foundCount++] = i;
        }
      }
    }
    // Search by last name
    else if (choice == 3)
    {
      getInputString("\nEnter the Last Name (or starting characters): ", searchTerm, sizeof(searchTerm));
      for (int i = 0; i < contactCount; i++)
      {
        if (strncasecmp(contacts[i].lastName, searchTerm, strlen(searchTerm)) == 0)
        {
          foundIndexes[foundCount++] = i;
        }
      }
    }

    // Search by email
    else if (choice == 4)
    {
      getInputString("\nEnter the Email (or starting characters): ", searchTerm, sizeof(searchTerm));
      for (int i = 0; i < contactCount; i++)
      {
        if (strncasecmp(contacts[i].email, searchTerm, strlen(searchTerm)) == 0)
        {
          foundIndexes[foundCount++] = i;
        }
      }
    }

    // Search by phone number
    else if (choice == 5)
    {
      getInputString("\nEnter the Phone Number (or starting digits): ", searchTerm, sizeof(searchTerm));
      for (int i = 0; i < contactCount; i++)
      {
        if (strncasecmp(contacts[i].phoneNumber, searchTerm, strlen(searchTerm)) == 0)
        {
          foundIndexes[foundCount++] = i;
        }
      }
    }

    // Search by postal address
    else if (choice == 6)
    {
      getInputString("\nEnter the Postal Address (or starting characters): ", searchTerm, sizeof(searchTerm));
      for (int i = 0; i < contactCount; i++)
      {
        if (strncasecmp(contacts[i].postalAddress, searchTerm, strlen(searchTerm)) == 0)
        {
          foundIndexes[foundCount++] = i;
        }
      }
    }

    else
    {
      printf("\nInvalid choice.\n");
      continue;
    }

    // Inform the user if there are no entries found
    if (foundCount == 0)
    {
      printf("\nNo matching contacts found.\n");
      continue;
    }

    // Prints out partial information about contacts found
    while (1)
    {
      printf("\nFound %d matching contacts:\n", foundCount);
      for (int i = 0; i < foundCount; i++)
      {
        int idx = foundIndexes[i];
        printf("%d - Contact #%d: ", i + 1, contacts[idx].contactNumber);

        if (choice == 1) // Contact Number
        {
          printf("%d\n", contacts[idx].contactNumber);
        }
        else if (choice == 2) // First Name
        {
          printf("%s\n", contacts[idx].firstName);
        }
        else if (choice == 3) // Last Name
        {
          printf("%s\n", contacts[idx].lastName);
        }
        else if (choice == 4) // Email
        {
          printf("%s\n", contacts[idx].email);
        }
        else if (choice == 5) // Phone Number
        {
          printf("%s\n", contacts[idx].phoneNumber);
        }
        else if (choice == 6) // Postal Address
        {
          printf("%s\n", contacts[idx].postalAddress);
        }
      }
      printf("0 - Return to search menu\n");

      // Offers the option to display more information
      int selection = getIntInput("Enter number to view full contact details (or 0 to go back): ");

      if (selection == 0)
      {
        break;
      }
      else if (selection >= 1 && selection <= foundCount)
      {
        int selectedIndex = foundIndexes[selection - 1];
        printContact(&contacts[selectedIndex]);
      }
      else
      {
        printf("\nInvalid selection. Try again.\n");
      }
    }
  }
}

// Function to rewrite the csv file with current data in contacts array (save contacts to csv)
void saveContactsToCSV(const char *filename)
{
  // Opens file and returns error if file can't be opened
  FILE *file = fopen(filename, "w");
  if (!file)
  {
    printf("Error: Could not open file %s for writing.\n", filename);
    return;
  }

  // Starts rewriting the file by setting the headers
  fprintf(file, "Contact Number,First Name,Last Name,Email,Phone Number,Postal Address\n");

  // Loop until contactCount is reached rewriting each row
  for (int i = 0; i < contactCount; i++)
  {
    fprintf(file, "%d,%s,%s,%s,%s,%s\n",
            contacts[i].contactNumber,
            contacts[i].firstName,
            contacts[i].lastName,
            contacts[i].email,
            contacts[i].phoneNumber,
            contacts[i].postalAddress);
  }

  fclose(file);
}

// Function to find a contact by number
int findContactByNumber(int number)
{
  for (int i = 0; i < contactCount; i++)
  {
    if (contacts[i].contactNumber == number)
    {
      // Return index if found
      return i;
    }
  }
  // Return -1 if not found
  return -1;
}

// Function to delete a contact
void deleteContact(int index)
{
  if (index < 0 || index >= contactCount)
  {
    printf("Invalid contact index!\n");
    return;
  }

  // Shift all contact numbers after this one down by one
  for (int i = index; i < contactCount - 1; i++)
  {
    contacts[i] = contacts[i + 1];
    // Decrement contact numbers
    contacts[i].contactNumber--;
  }

  contactCount--;
  unsavedChanges = 1;
  printf("\nContact deleted successfully.\n");
  printf("Remember to save your changes before exiting the program\n");
}

// Similar to validname function but includes the option to maintain previous data with '='
void getValidNameWithEquals(const char *prompt, char *output, int size)
{
  char temp[150];
  while (1)
  {
    getInputString(prompt, temp, sizeof(temp));

    // Keep current value
    if (strcmp(temp, "=") == 0)
    {
      return;
    }
    else if (strcmp(temp, "-") == 0)
    {
      strncpy(output, "N/A", size);
      return;
    }
    else if (isValidName(temp))
    {
      strncpy(output, temp, size);
      return;
    }
    printf("Invalid name! Must contain at least 2 non-space characters.\n");
  }
}
// Similar to validaddress function but includes the option to maintain previous data with '='
void getValidAddressWithEquals(const char *prompt, char *output, int size)
{
  char temp[150];
  while (1)
  {
    getInputString(prompt, temp, sizeof(temp));

    if (strcmp(temp, "=") == 0)
    {
      return;
    }
    else if (strcmp(temp, "-") == 0)
    {
      strncpy(output, "N/A", size);
      return;
    }
    else if (isValidAddress(temp))
    {
      strncpy(output, temp, size);
      return;
    }
    printf("Invalid address! Must contain at least 2 non-space characters.\n");
  }
}
// Similar to previous functions
void getValidEmailWithEquals(const char *prompt, char *output, int size)
{
  char temp[150];
  while (1)
  {
    getInputString(prompt, temp, sizeof(temp));

    if (strcmp(temp, "=") == 0)
    {
      return;
    }
    else if (strcmp(temp, "-") == 0)
    {
      strncpy(output, "N/A", size);
      return;
    }
    else if (strchr(temp, '@') != NULL)
    {
      strncpy(output, temp, size);
      return;
    }
    printf("Invalid email! Must contain '@'.\n");
  }
}

// Similar to previous functions
void getValidPhoneWithEquals(const char *prompt, char *output, int size)
{
  char temp[20];

  while (1)
  {
    printf("%s", prompt);
    fgets(temp, sizeof(temp), stdin);
    removeNewLine(temp);

    // Maintain current value
    if (strcmp(temp, "=") == 0)
    {
      return;
    }
    // Set N/A value
    else if (strcmp(temp, "-") == 0)
    {
      strncpy(output, "N/A", size);
      return;
    }
    else
    // Checks to see if number entered by the user is valid
    {
      int valid = 1;
      if (strlen(temp) != 9)
        valid = 0;
      for (int i = 0; i < strlen(temp); i++)
      {
        if (!isdigit(temp[i]))
          valid = 0;
      }
      if (temp[0] == '0')
        valid = 0;

      if (valid)
      {
        strncpy(output, temp, size);
        return;
      }
      printf("Invalid phone! Must be 9 digits, no leading 0.\n");
    }
  }
}

// Function to edit contacts
void editContact(int index)
{
  // Checks if the contact exists
  if (index < 0 || index >= contactCount)
  {
    printf("Invalid contact index!\n");
    return;
  }

  printf("\nEditing contact #%d\n", contacts[index].contactNumber);
  printf("Enter '=' to keep current value or '-' to set as N/A\n");

  char temp[150];

  // Edit first name
  printf("Current first name: %s\n", contacts[index].firstName);
  getValidNameWithEquals("Enter new first name (= to keep, - for N/A): ", contacts[index].firstName, sizeof(contacts[index].firstName));

  // Edit last name
  printf("Current last name: %s\n", contacts[index].lastName);
  getValidNameWithEquals("Enter new last name (= to keep, - for N/A): ", contacts[index].lastName, sizeof(contacts[index].lastName));

  // Edit email
  printf("Current email: %s\n", contacts[index].email);
  getValidEmailWithEquals("Enter new email (= to keep, - for N/A): ", contacts[index].email, sizeof(contacts[index].email));

  // Edit phone
  printf("Current phone: %s\n", contacts[index].phoneNumber);
  getValidPhoneWithEquals("Enter new phone (= to keep, - for N/A): ", contacts[index].phoneNumber, sizeof(contacts[index].phoneNumber));

  // Edit address
  printf("Current address: %s\n", contacts[index].postalAddress);
  getValidAddressWithEquals("Enter new address (= to keep, - for N/A): ", contacts[index].postalAddress, sizeof(contacts[index].postalAddress));

  unsavedChanges = 1;
  printf("\nContact updated successfully.\n");
  printf("Remember to save your changes before you close the program\n");
}

int main()
{
  // Open and load csv file data into contacts array
  const char *filename = "contacts.csv";
  loadContactsFromCSV(filename);

  int mainInput;
  int entryInput;

  while (1)
  {
    displayMenu();
    // Get validated entry menu input
    mainInput = getIntInput("\nPlease input a number according to the menu: ");

    // Begins process to close program
    if (mainInput == 0)
    {
      // If there are any unsaved changes the user has the option to save them before closing
      if (unsavedChanges)
      {
        printf("\nYou have unsaved changes!\n");
        printf("0 - Return to main menu\n");
        printf("1 - Save and exit\n");
        printf("2 - Exit without saving\n");

        while (1)
        {
          int choice = getIntInput("\nPlease input your choice to continue: ");
          // The user can decide to return to the main menu
          if (choice == 0)
          {
            break;
          }

          else if (choice == 1)
          {
            saveContactsToCSV("contacts.csv");
            unsavedChanges = 0;
            printf("\nContacts saved successfully\n");
            printf("Thanks for using our service\n");
            return 0;
          }

          else if (choice == 2)
          {
            printf("\nExiting without saving changes\n");
            printf("Thanks for using our service\n");
            return 0;
          }

          else
          {
            printf("\n This is not a valid input\n");
          }
        }
        continue;
      }
      // If there aren't any unsaved changes the program will close directly
      else
      {
        printf("\nThanks for using our service\n");
        return 0;
      }
    }

    else if (mainInput == 1)
    {
      while (1)
      {
        displayEntryCreation();
        // Get validated main menu input
        entryInput = getIntInput("Please input a number according to the menu: ");

        // Return to main menu
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
          int searchNumber = getIntInput("Enter contact number to edit: ");
          int foundIndex = findContactByNumber(searchNumber);

          // If contact isn't found returns
          if (foundIndex == -1)
          {
            printf("Contact not found!\n");
            continue;
          }

          printf("\nContact found:\n");
          printContact(&contacts[foundIndex]);

          // Allows the user to edit or delete the contact
          printf("\nOptions:\n");
          printf("0 - Return\n");
          printf("1 - Edit this contact\n");
          printf("2 - Delete this contact\n");

          int action = getIntInput("Choose action: ");

          if (action == 1)
          {
            editContact(foundIndex);
          }

          else if (action == 2)
          {
            deleteContact(foundIndex);
          }

          // Allows user to return to menu
          else if (action == 0)
          {
            printf("Operation cancelled.\n");
          }

          else
          {
            printf("\nInvalid choice!\n");
          }
        }

        else
        {
          printf("\nThis is not a valid input.\n");
        }
      }
    }

    else if (mainInput == 2)
    {
      int readInput;
      while (1)
      {
        displayReadingMenu();
        readInput = getIntInput("Please input a number according to the menu: ");

        if (readInput == 0)
        {
          break;
        }
        else if (readInput == 1)
        {
          printAllContacts();
        }
        else if (readInput == 2)
        {
          searchContacts();
        }
        else
        {
          printf("\nThis is not a valid input.\n");
        }
      }
    }

    // Allows the user to save all current contacts/changes in the array to the csv file
    else if (mainInput == 3)
    {
      saveContactsToCSV("contacts.csv");
      unsavedChanges = 0;
      printf("\nContacts saved!\n\n");
    }

    else
    {
      printf("\nThis is not a valid input, please enter one of the available options.\n");
    }
  }
}