// https://cs50.harvard.edu/x/2020/psets/1/cash

#include <math.h>
#include <stdio.h>

#include <cs50.h>

// De-facto way to get the length (number of elements) of an array in C
#define alength(arr) (sizeof(arr)/sizeof(arr[0]))

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

    int cents = get_cents();

    int total = 0;

    // "foreach" loop in C, adapted from
    // https://en.wikipedia.org/wiki/Foreach_loop#C
    for (int *c = coins, coin = *c; c < (coins + alength(coins)); coin = *(++c))
    {
        fprintf(stderr, "$0.%02i: ", coin);
        while (cents >= coin)
        {
            cents -= coin;
            total++;
            printf(".");
        }
        fprintf(stderr, "\n");
    }
    printf("%i\n", total);
}
