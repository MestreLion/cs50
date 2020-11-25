"""
DNA - https://cs50.harvard.edu/x/2020/psets/6/dna
"""

import argparse
import csv
import logging
import os
import sys


COPYRIGHT = """
Copyright (C) 2018 Rodrigo Silva (MestreLion) <linux@rodrigosilva.com>
License: GPLv3 or later, at your choice. See <http://www.gnu.org/licenses/gpl>
"""

log = logging.getLogger(os.path.basename(os.path.splitext(__file__)[0]))


def parse_args(argv=None):
    """Command-line argument handling"""
    parser = argparse.ArgumentParser(description=__doc__, epilog=COPYRIGHT)
    parser.add_argument('-v', '--verbose',
                        dest='loglevel',
                        const=logging.DEBUG,
                        default=logging.WARNING,
                        action="store_const",
                        help="Verbose mode, output extra info.")

    parser.add_argument(dest='db',  metavar="DATABASE",
                        help="DNA database CSV file.")

    parser.add_argument(dest='seq', metavar="SEQUENCE",
                        help="DNA sequence TXT file.")

    return parser.parse_args(argv)


def main(argv=None):
    # Basic setup
    args = parse_args(argv)
    logging.basicConfig(level=args.loglevel, format='%(levelname)s: %(message)s')
    log.debug(args)

    # Load Database CSV to database dictionary, with names as keys
    log.info("Load database file: %s", args.db)
    with open(args.db) as file:
        database = {row['name']: {k: row[k] for k in row if k != 'name'}
                    for row in csv.DictReader(file)}
        for person in database.items():
            log.debug(person)

    # Load sequence TXT
    log.info("Load sequence file: %s", args.seq)
    with open(args.seq) as file:
        sequence = file.read()
    log.debug(sequence)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
