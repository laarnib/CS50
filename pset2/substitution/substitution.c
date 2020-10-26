#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validate_key(string key, int key_length);
void encipher(string message, string key);

int main(int argc, string argv[])
{
    string key, message;
    char temp[26];
    int argv_len;
    bool validKey;

    if (argc == 2)
    {
        argv_len = strlen(argv[1]);

        /* Checks if key length has 26 characters. If not, error message is display
            program exits*/
        if (argv_len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < argv_len; i++)
            {
                // Checks if all characters of key is alphabetic
                if (!isalpha(argv[1][i]))
                {
                    printf("Key must contain only non repeating alphabet characters.\n");
                    return 1;
                }

                /* Copy key to a temporary character array. This will be used
                   later to check if there are duplicate characters in the key. */
                temp[i] = argv[1][i];
            }

            // Call the validate_key function to check if key has duplicate characters
            validKey = validate_key(argv[1], argv_len);
            if (validKey)
            {
                key = temp;
            }
            else
            {
                printf("Key must not contain duplicate alphabetic characters.\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Get text to be enciphered from the user
    message = get_string("plaintext: ");

    // Call encipher function to encipher the text
    encipher(message, key);

    // Display enciphered text
    printf("ciphertext: %s\n", message);

    return 0;
}

// Checks key for duplicate characters
bool validate_key(string key, int key_length)
{
    char x;

    // Sort letters of the key using bubblesort
    for (int i = 0; i < key_length; i++)
    {
        for (int j = 0; j < (key_length - i - 1); j++)
        {
            if (key[j] > key[j + 1])
            {
                x = key[j];
                key[j] = key[j + 1];
                key[j + 1] = x;
            }
        }
    }

    // After the key is sorted, find duplicate characters. If found, return 0 and 1 if none.
    for (int i = 0; i < (key_length - 1); i++)
    {
        if (key[i] == key[i + 1])
        {
            return 0;
        }
    }

    return 1;
}


// Enciphers the message
void encipher(string message, string key)
{
    int message_len;

    message_len = strlen(message);
    for (int i = 0, j; i < message_len; i++)
    {
        // Checks if character is alphabetic
        if (isalpha(message[i]))
        {
            // Checks is character is in uppercase
            if (isupper(message[i]))
            {
                // To get the corresponding index of the key, subtract 65 from the character
                j = message[i] - 65;
                message[i] = toupper(key[j]);
            }

            // Checks if character is in lowercase
            if (islower(message[i]))
            {
                j = message[i] - 97;
                message[i] = tolower(key[j]);
            }
        }
        else
        {
            message[i] = message[i]; // If character is non alphabetic, leave as it is.
        }
    }
}
