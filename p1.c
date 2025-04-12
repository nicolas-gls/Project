// comment

#include <stdio.h>

int x = 1;
int y = 1;

void displayMenu();
void attemptCheck();
void cleanBuffer();
void removeNewLine();

void displayMenu()
{
  printf("\nWelcome to the main menu\n");
  printf("0 - Close program\n");
  printf("1 - Create a new entry\n");
  printf("2 - Retrieve an existing entry\n");
}

void cleanBuffer()
{
  while (getchar() != '\n')
    ;
}

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

int main()
{
  int input;

  while (x == 1)
  {
    displayMenu();
    printf("Please input a number according to the menu: ");
    scanf("%d", &input);
    cleanBuffer();

    if (input == 0)
    {
      printf("Thanks for using our service\n");
      return 0;
    }

    else if (input == 1)
    {
    }

    else if (input == 2)
    {
    }

    else
    {
      printf("This is not a valid input.\n");
    }
  }
}