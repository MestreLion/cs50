// https://cs50.harvard.edu/x/2020/psets/1/credit

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Credit card number, from user input
    long cc = get_long("Number: ");

    // First 2 digits (most significant, as in a string)
    int d1 = 0, d2 = 0;

    // Length of CC number
    int length = 0;

    // Sum of digits
    int sum = 0;

    while (cc)
    {
        // Get last digit
        int d = cc % 10;

        // Add digit to sum, doubled if on odd position (from right to left)
        // Using current (not yet updated) length as position index
        if (length % 2)
        {
            sum += 2 * d;

            // Fix the case 2d >= 10, when *digits* should have been added instead
            // So 10 => 1+0 = 1; 12 => 1+2 = 3, 14 => 1+4 = 5, and so on...
            // In all such cases, the difference to fix is always 9
            // (and I bet this is not a coincidence!)
            if (d >= 5)
            {
                sum -= 9;
            }
        }
        else
        {
            sum += d;
        }

        // Update first digits and length
        d2 = d1;
        d1 = d;
        length++;

        // "Shift" the CC number to the right, discarding last digit
        cc -= d;
        cc /= 10;
    }

    // Check the sum
    if (sum % 10)
    {
        printf("INVALID\n");
    }

    // Check card issuers
    else if (length == 15 && d1 == 3 && (d2 == 4 || d2 == 7))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && d1 == 5 && (d2 >= 1 && d2 <= 5))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 16 || length == 13) && d1 == 4)
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}
