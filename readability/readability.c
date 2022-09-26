#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    // Get text from user
    string passage = get_string("Text: ");
    int words = 1;
    int sentences = 0;
    int letters = 0;

    // Count words, letters, and sentences
    for (int i = 0; i < strlen(passage); i++)
    {
        if (passage[i] == '!' || passage[i] == '.' || passage[i] == '?')
        {
            sentences++;
        }
        else if (((int) passage[i] > 64 && (int) passage[i] < 91) || ((int) passage[i] > 96 && (int) passage[i] < 123))
        {
            letters++;
        }
        else if (passage[i] == ' ')
        {
            words++;
        }
    }

    // Determine score
    int score = 5.88 * ((float) letters / (float) words) - 29.6 * ((float) sentences / (float) words) - 15.3;

    // Print result
    if (score >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (score < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", score);
    }
}