#include <stdio.h>
#include <cs50.h>

long int get_credit_card_num(void);
int validate_card_num(long int);
void get_credit_card_type(long int);
int count_digits(long int);

int main(void)
{
    long int cardNum;
    int isValid;

    // Gets card number from the user
    cardNum = get_credit_card_num();

    // Checks if the card has a valid credit card number
    isValid = validate_card_num(cardNum);

    // If card is valid, it the card type is printed. Else, INVALID is printed on the screen.
    if (isValid == 1)
    {
        get_credit_card_type(cardNum);
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// Gets the credit card number from the user
long int get_credit_card_num(void)
{
    long int cardNum;

    // Prompts user for a card number until user enters a positive number
    do
    {
        cardNum = get_long("Number: ");
    }
    while (cardNum < 0);

    return cardNum;
}

// Checks if the credit card number is valid
int validate_card_num(long int cardNum)
{
    int isValid, sum, last_2_digits, second_digit;

    sum = 0;
    while (cardNum >= 10)
    {
        // Get the last two digits of the card number
        last_2_digits = cardNum % 100;

        /* Get the second digit and multiply it by 2. If the product has more than one digit,
            add those digits together. */
        second_digit = (last_2_digits / 10) * 2;
        if (second_digit >= 10)
        {
            sum += ((second_digit % 10) + (second_digit / 10));
        }
        else
        {
            sum += second_digit;
        }

        // Add the last digit that wasn't multiplied by 2 to the sum
        sum += (last_2_digits % 10);

        // Removes the last two digits of the card number
        cardNum /= 100;
    }

    // Adds the digit left of the card number. It could be zero or more than zero but less than 10
    sum += cardNum;

    // Checks if the last digit of the sum is zero. If it is, the card is valid.
    if ((sum % 10) == 0)
    {
        isValid = 1;
    }
    else
    {
        isValid = 0;
    }

    return isValid;
}

// Gets the type of the credit card
void get_credit_card_type(long int cardNum)
{
    int digitCount, last_two_digits;

    // Gets the number of digits of the card number
    digitCount = count_digits(cardNum);

    // Gets the last two digits of the card number
    for (int i = 0; i < (digitCount - 2); i++)
    {
        cardNum /= 10;
    }

    last_two_digits = cardNum;

    // Identifies the card type based on the conditions
    if ((last_two_digits == 34 || last_two_digits == 37) && digitCount == 15)
    {
        printf("AMEX\n");
    }
    else if ((last_two_digits >= 51 && last_two_digits <= 55) && digitCount == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (((last_two_digits / 10) == 4) && (digitCount == 13 || digitCount == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Counts the number of digits
int count_digits(long int cardNum)
{
    int counter;

    counter = 0;
    while (cardNum != 0)
    {
        counter++;
        cardNum /= 10;
    }

    return counter;
}
