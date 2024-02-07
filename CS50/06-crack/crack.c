#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check the number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // Get the hashed password from the command-line arguments
    char *hash = argv[1];

    // Define the characters that can be in the password
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // The password will contain no more than 6 characters (including the null terminator)
    char password[6];

    // Initialize the password as an empty string
    password[0] = '\0';

    // Iterate over all possible characters in the password
    for (int i = 0, n = strlen(alphabet); i < n; i++)
    {
        password[0] = alphabet[i];

        for (int j = 0; j < n; j++)
        {
            password[1] = alphabet[j];

            for (int k = 0; k < n; k++)
            {
                password[2] = alphabet[k];

                for (int l = 0; l < n; l++)
                {
                    password[3] = alphabet[l];

                    for (int m = 0; m < n; m++)
                    {
                        password[4] = alphabet[m];

                        // Compare the hashed password with the given hash
                        if (strcmp(crypt(password, "50"), hash) == 0)
                        {
                            // If a match is found, print the password and exit
                            printf("%s\n", password);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    // If no password is found
    printf("Password not found\n");
    return 1;
}
