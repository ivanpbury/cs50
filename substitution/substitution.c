#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool is_valid(string key);

int main(int argc, string argv[])
{
    //Check for invalid key
    string key = argv[1];

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (!is_valid(key))
    {
        printf("Error\n");
        return 1;
    }

    // Convert key to uppercase
    for (int i = 0; i < strlen(key); i++)
    {
        if ((int) key[i] > 90)
        {
            key[i] = (char)((int) key[i] - 32);
        }
    }

    // Get text from user
    string text = get_string("plaintext: ");

    // Transalate text using key
    for (int i = 0; i < strlen(text); i++)
    {
        if ((int) text[i] > 96 && (int) text[i] < 123)
        {
            text[i] = (char((int) key[(int) text[i] - 97]) + 32;
        }
        else if ((int) text[i] > 64 && (int) text[i] < 91)
        {
            text[i] = key[(int) text[i] - 65];
        }
    }

    // Print result
    printf("ciphertext: %s\n", text);
}

// Helper function to check key length and repetition
bool is_valid(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    }
    char used[26];
    for (int i = 0; i < strlen(key); i++)
    {
        if ((int) key[i] < 65 || (int) key[i] > 122 || ((int) key[i] > 90 && (int) key[i] < 97))
        {
            return false;
        }

        for (int j = 0; j < 26; j++)
        {
            if (key[i] == used[j] || (int) key[i] == (int) used[j] + 32 || (int) key[i] == (int) used[j] - 32)
            {
                return false;
            }
        }
        used[i] = key[i];
    }
    return true;
}