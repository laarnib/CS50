#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_change_owed(void);
int calcMinCoinCount(float changeOwed);

int main(void)
{
    float change;
    int numOfCoins;

    numOfCoins = 0;

    // Get change owed
    change = get_change_owed();
    numOfCoins = calcMinCoinCount(change);

    printf("%i\n", numOfCoins);

    return 0;
}

// Gets a valid change from the user
float get_change_owed(void)
{
    float change;

    // Prompt for change until user enters a positive value
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    return change;
}


// Calculates the minimum number of coins that the change can be made
int calcMinCoinCount(float changeOwed)
{
    int cents, coinCount;

    coinCount = 0;

    // Convert the change to cents.
    cents = (int)(round(changeOwed * 100));

    // Calculates the fewest number of coins that the change can be made
    while (cents != 0)
    {
        // Checks if quarters can be used to provide the change
        if (cents >= 25)
        {
            coinCount = coinCount + (cents / 25);
            cents = cents % 25;
        }

        // Checks if dimes can be used to provide the change
        if (cents >= 10)
        {
            coinCount = coinCount + (cents / 10);
            cents = cents % 10;
        }

        // Checks if nickels can be used to provide the change
        if (cents >= 5)
        {
            coinCount = coinCount + (cents / 5);
            cents = cents % 5;
        }

        // Checks if pennies can be used to provide the change
        if (cents >= 1)
        {
            coinCount = coinCount + cents;
            cents = cents % 1;
        }
    }

    return coinCount;
}
