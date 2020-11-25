import logging
import sys

import cs50

log = logging.getLogger(__name__)


def main():
    # Credit card number, from user input
    cc = cs50.get_int("Number: ")

    # First 2 digits (most significant, as in a string)
    d1 = d2 = 0

    # Length of CC number
    length = 0

    # Sum of digits
    sum = 0

    while (cc):
        # Get last digit
        d = cc % 10

        # Add digit to sum, doubled if on odd position (from right to left)
        # Using current (not yet updated) length as position index
        if (length % 2):
            sum += 2 * d

            # Fix the case 2d >= 10, when *digits* should have been added instead
            # So 10 => 1+0 = 1; 12 => 1+2 = 3, 14 => 1+4 = 5, and so on...
            # In all such cases, the difference to fix is always 9
            # (and I bet this is not a coincidence!)
            if (d >= 5):
                sum -= 9
        else:
            sum += d

        # Update first digits and length
        d2 = d1
        d1 = d
        length += 1

        # "Shift" the CC number to the right, discarding last digit
        cc -= d
        cc /= 10

    # Check the sum
    if (sum % 10):
        print("INVALID\n")

    # Check card issuers
    elif (length == 15 and d1 == 3 and (d2 == 4 or d2 == 7)):
        print("AMEX")

    elif (length == 16 and d1 == 5 and (d2 >= 1 and d2 <= 5)):
        print("MASTERCARD\n")

    elif ((length == 16 or length == 13) and d1 == 4):
        print("VISA")

    else:
        print("INVALID")


if __name__ == "__main__":
    sys.exit(main())
