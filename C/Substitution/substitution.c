#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char abc[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char ABC[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char lower_case(char word);
char upper_case(char word);
int non_repeated(string key);
int non_alphabetic_characters(string key);

int main(int argc, string argv[])
{
    // Validate the key
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int length = strlen(argv[1]);
    string key = argv[1];

    // Validate the key length
    if (length < 26 || length > 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int validate_non_alphabetic_characters;
    int validate_non_repeated;

    // Validate for non-alphabetic characters
    validate_non_alphabetic_characters = non_alphabetic_characters(key);
    // Validate for repeated characters
    validate_non_repeated = non_repeated(key);

    printf("%i\n", validate_non_alphabetic_characters);
    printf("%i\n", validate_non_repeated);

    if (validate_non_alphabetic_characters < 26)
    {
        printf("Key must contain only alphabetic characters.\n");
        return 1;
    }
    else if (validate_non_repeated > 0)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    else if (validate_non_repeated == 0 && validate_non_alphabetic_characters == 26)
    {
        // Get plain text
        string plain_text = get_string("plaintext: ");
        int length_plaintext = strlen(plain_text);
        printf("ciphertext: ");

        // Encipher text
        for (int i = 0; i < length_plaintext; i++)
        {
            for (int j = 0; j < length; j++)
            {
                if (plain_text[i] >= 'A' && plain_text[i] <= 'Z')
                {
                    if (plain_text[i] == ABC[j])
                    {
                        plain_text[i] = upper_case(key[j]);
                        break;
                    }
                }

                else if (plain_text[i] >= 'a' && plain_text[i] <= 'z')
                {
                    if (plain_text[i] == abc[j])
                    {
                        plain_text[i] = lower_case(key[j]);
                        break;
                    }
                }
                else
                {
                    plain_text[i] = plain_text[i];
                }
            }
        }
        // Print ciphertext
        printf("%s\n", plain_text);
    }
    return 0;
}

char lower_case(char word)
{
    if (word >= 'A' && word <= 'Z')
    {
        word = word + 32;
    }
    return word;
}

char upper_case(char word)
{
    if (word >= 'a' && word <= 'z')
    {
        word = word - 32;
    }
    return word;
}

int non_repeated(string key)
{
    int validate = 0;
    int aux;
    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = 0; j < strlen(key); j++)
        {
            if (i == j)
            {
                validate = validate - 1;
            }
            if (lower_case(key[i]) == lower_case(key[j]))
            {
                validate = validate + 1;
            }
        }
    }
    return validate;
}

int non_alphabetic_characters(string key)
{
    int validate = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = 0; j < strlen(ABC); j++)
        {
            if (key[i] == ABC[j] || key[i] == abc[j])
            {
                validate = validate + 1;
            }
        }
    }
    return validate;
}
