"""
DNA - https://cs50.harvard.edu/x/2020/psets/6/dna
"""

import argparse
import csv
import logging
import os
import sys


COPYRIGHT = """
Copyright (C) 2020 Rodrigo Silva (MestreLion) <linux@rodrigosilva.com>
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

    parser.add_argument('-a', '--alternative',
                        dest='find_match',
                        const=find_match_hard,
                        default=find_match_easy,
                        action="store_const",
                        help="Use alternative find_match() function.")

    parser.add_argument(dest='db',  metavar="DATABASE",
                        help="DNA database CSV file.")

    parser.add_argument(dest='seq', metavar="SEQUENCE",
                        help="DNA sequence TXT file.")

    return parser.parse_args(argv)


def find_match_easy(database, sequence):
    for person, genes in database.items():
        log.debug("Profiling %s:", person)
        for gene, repetitions in genes.items():
            if (
                (gene * (repetitions) not in sequence) or
                (gene * (repetitions + 1) in sequence)
            ):
                log.debug("- Failed for %02s x %r", repetitions, gene)
                break
            log.debug("- Found %02s x %r", repetitions, gene)
        else:
            return person


def find_match_hard(database, sequence):
    pass


def main(argv=None):
    # Basic setup
    args = parse_args(argv)
    logging.basicConfig(level=args.loglevel, format='%(levelname)s: %(message)s')
    log.debug(args)

    # Load Database CSV to database dictionary, with names as keys
    log.info("Load database file: %s", args.db)
    with open(args.db) as file:
        database = {}
        for row in csv.DictReader(file):
            person = row['name']
            database[person] = {k: int(v) for k, v in row.items() if k != 'name'}
            log.debug("%-9s: %s", person, database[person])

    # Load sequence TXT
    log.info("Load sequence file: %s", args.seq)
    with open(args.seq) as file:
        sequence = file.read()
    log.debug(sequence)

    # Find the bad guy!
    log.info("Looking for a match...")
    print(args.find_match(database, sequence) or "No match")


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
