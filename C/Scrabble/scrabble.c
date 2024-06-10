#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char ABC[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

string lower_case(string word);
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    word1 = lower_case(word1);
    word2 = lower_case(word2);
    printf("%s\n", word1);
    printf("%s\n", word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    printf("Score player 1: %i\n", score1);
    printf("Score player 2: %i\n", score2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int n = strlen(ABC);
    int m = strlen(word);
    int score = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (word[i] == ABC[j])
            {
                score = POINTS[j] + score;
            }
        }
    }
    return score;
}

string lower_case(string word)
{
    int n = strlen(word);
    for (int i = 0; i < n; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
            word[i] = word[i] + 32;
    }
    return word;
}
