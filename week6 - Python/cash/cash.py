import logging
import sys

import cs50

log = logging.getLogger(__name__)


def get_cents(prompt):
    """Ask user for a monetary (float) value and return it as (integer) cents"""
    f = 0
    # Re-ask if not strictly positive
    while f <= 0:
        f = cs50.get_float(prompt)

    # Convert from float to integer cents
    return round(f * 100)


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")

    # Available coin values. MUST be sorted in DESCENDING value order!
    coins = (25, 10, 5, 1)

    # Change owed, supplied by user, in cents
    cents = get_cents("Change owed: ")

    # Number of coins to be given as change
    total = 0

    # Loop each coin in coins tuple
    for coin in coins:
        i = 0
        while (cents >= coin):
            cents -= coin
            total += 1
            i += 1

        log.info("%2i x $%0.2f", i, coin/100.0)
        coin += 1

    print(total)

    # Sanity check. If this ever happens, the coins list is broken
    # (ie, the country's currency system is poorly designed)
    if cents:
        log.error("Change left: %i cents", cents)
        return 1


if __name__ == "__main__":
    sys.exit(main())
