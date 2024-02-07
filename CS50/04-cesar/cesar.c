#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    // Check for correct command-line argument input
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Get the key from the command-line argument
    int key = atoi(argv[1]);

    // Check if the key is a positive integer
    if (key <= 0)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Get the plaintext input from the user
    printf("plaintext: ");
    char plaintext[100];
    fgets(plaintext, 100, stdin);

    // Encrypt the plaintext
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (isalpha(plaintext[i]))
        {
            char shift = isupper(plaintext[i]) ? 'A' : 'a';
            printf("%c", ((plaintext[i] - shift + key) % 26) + shift);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    // Print a newline after the encrypted text
    printf("\n");

    return 0;
}
