// https://cs50.harvard.edu/x/2020/psets/1/cash

#include <math.h>
#include <stdio.h>

#include <cs50.h>

// Simple, conventional way to get the length (number of elements) of an array in C
#define length(array) (sizeof(array)/sizeof(array[0]))

// Ask user for a monetary (float) value and return it as (integer) cents
int get_cents(void)
{
    float f;
    do
    {
        f = get_float("Change owed: ");
    }
    // Re-ask if not strictly positive
    while (!(f > 0));

    // Convert from float to integer cents
    return round(f * 100);
}


int main(void)
{
    // Available coin values. MUST be sorted in DESCENDING value order!
    int coins[] = {25, 10, 5, 1};
    int len = length(coins);

    // Change owed, supplied by user, in cents
    int cents = get_cents();

    // Number of coins to be given as change
    int total = 0;

    // Loop each coin in coins array. <coin> is a pointer, so use as *coin
    int *coin = coins;
    while (len--)
    {
        int i = 0;
        while (cents >= *coin)
        {
            cents -= *coin;
            total++;
            i++;
        }
        fprintf(stderr, "%2i x $%0.2f\n", i, *coin/100.0);
        coin++;
    }
    printf("%i\n", total);

    // Sanity check. If this ever happens, the coins list is broken
    // (ie, the country's currency system is poorly designed)
    if (cents)
    {
        fprintf(stderr, "Change left: %i cents\n", cents);
        return 1;
    }
}
