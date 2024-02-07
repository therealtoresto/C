#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int shift(char c);

int main(int argc, char *argv[])
{
    // Check for the presence of the keyword in the command line
    if (argc != 2)
    {
        printf("Usage: %s keyword\n", argv[0]);
        return 1;
    }

    // Check if the keyword consists only of letters
    char *keyword = argv[1];
    for (int i = 0, n = strlen(keyword); i < n; i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("Usage: %s keyword\n", argv[0]);
            return 1;
        }
    }

    // Get the plaintext input from the user
    printf("plaintext: ");
    char plaintext[100];
    fgets(plaintext, 100, stdin);

    // Encrypt the plaintext
    printf("ciphertext: ");
    for (int i = 0, j = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            // Get the shift value for the current character of the keyword
            int key = shift(keyword[j]);

            // Encrypt the character using the key
            char encrypted = (plaintext[i] + key - (isupper(plaintext[i]) ? 'A' : 'a')) % 26 + (isupper(plaintext[i]) ? 'A' : 'a');

            // Print the encrypted character
            printf("%c", encrypted);

            // Increment the keyword index only for letters
            j = (j + 1) % strlen(keyword);
        }
        else
        {
            // Print the character without changes
            printf("%c", plaintext[i]);
        }
    }

    // Print a newline after the encrypted text
    printf("\n");

    return 0;
}

// Function to compute the shift value for a character of the keyword
int shift(char c)
{
    return toupper(c) - 'A';
}
