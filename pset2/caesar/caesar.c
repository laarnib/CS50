#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cipher(string message, int k);

int main(int argc, string argv[])
{
    string message;
    int k;

    // Get key from the user
    if (argc == 2)
    {
        int argv_length = strlen(argv[1]);

        /* Checks if the key provided is a numeric character. If not, print out
           an error message and exit the program. */
        for (int i = 0; i < argv_length; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        /* If key provided by use is a numeric value, convert the string into
           an integer and then store into the variable k. */
        k = atoi(argv[1]);

        // Get the message or text to be encipher from the user
        message = get_string("plaintext: ");

        // Calls the cipher function to encipher the message
        cipher(message, k);

        // Prints the enciphered text
        printf("ciphertext: %s\n", message);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    return 0;
}

// Enciphers the message using Caesar cipher
void cipher(string message, int k)
{
    // Loop through the message
    for (int i = 0, length = strlen(message); i < length; i++)
    {
        // Check if character is an alphabet
        if (isalpha(message[i]))
        {
            // Checks if the alphabetic character is in uppercase
            if (isupper(message[i]))
            {
                /* Before adding the key, subtract 65 to the letter to convert it
                    into it's alphabetical index. And then add back the 65 after
                    calculating the cipher text to convert it back to it's ASCII
                    equivalent. */
                message[i] = ((message[i] - 65 + k) % 26) + 65;
            }

            // Checks if the alphabetic character is in lowercase
            if (islower(message[i]))
            {
                /* Before adding the key, subtract 97 to the letter to convert it
                    into it's alphabetical index. And then add back the 97 after
                    calculating the cipher text to convert it back to it's ASCII
                    equivalent. */
                message[i] = ((message[i] - 97 + k) % 26) + 97;
            }
        }
        else
        {
            // If character is not an alphabet, leave the character as it is.
            message[i] = message[i];
        }
    }
}
