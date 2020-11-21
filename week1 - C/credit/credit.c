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

	// Current last digit
	int d;

	while(cc)
	{
		// Get last digit
		d = cc % 10;

		// Update first digits and length
		d2 = d1;
		d1 = d;
		length++;

		// "Shift" the CC number to the right, discarding last digit
		cc -= d;
		cc /= 10;
	}

	if (length > 16)
	{
		printf("INVALID\n");
	}
}
