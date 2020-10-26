#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentence(string text);
int calc_grade_level(int letters, int words, int sentence);
void print_grade_level(int colemanIndex);

int main(void)
{
    string text;
    int letterCount, wordCount, sentenceCount, colemanIndex;

    text = get_string("Text: ");

    letterCount = count_letters(text);
    wordCount = count_words(text);
    sentenceCount = count_sentence(text);
    colemanIndex = calc_grade_level(letterCount, wordCount, sentenceCount);
    print_grade_level(colemanIndex);

    return 0;
}


// Counts the number of letters
int count_letters(string text)
{
    int count;

    count = 0;
    for (int i = 0, textLength = strlen(text); i < textLength; i++)
    {
        // Checks if the character in the text is an alphabet and if so, increment count
        if (isalpha(text[i]))
        {
            count++;
        }
    }

    return count;
}

// Counts the number of words
int count_words(string text)
{
    int count;

    count = 0;
    for (int i = 0, textLength = strlen(text); i < textLength; i++)
    {
        // Checks for a space, When space is found, increment count
        if (text[i] == ' ')
        {
            count++;
        }
    }

    // Add plus one to count to include the last word of the text
    return (count + 1);
}

// Counts the number of sentences
int count_sentence(string text)
{
    int count;

    count = 0;
    for (int i = 0, textLength = strlen(text); i < textLength; i++)
    {
        // Checks for punctuations that marks the end of a sentence
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }

    return count;
}

// Calculates the Coleman-Liau Index
int calc_grade_level(int letters, int words, int sentence)
{
    int colemanIndex;

    /* Calculates the reading level using the following Coleman-Liau Index formula.
        index = 0.0588 * L - 0.296 * S - 15.8

        where L is the average number of letters per 100 words in the text
              S is the average number of sentences per 100 words in the text. */

    colemanIndex = round(0.0588 * (((float)letters / words) * 100) - 0.296 * (((float)sentence / words) * 100) - 15.8);

    return colemanIndex;
}

void print_grade_level(int colemanIndex)
{
    // Displays the corresponding Grade level based on the Coleman-Liau Index calculation
    if (colemanIndex <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (colemanIndex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", colemanIndex);
    }
}
