"""
Houses - https://cs50.harvard.edu/x/2020/psets/7/houses
"""

import argparse
import csv
import logging
import os
import sys

from cs50 import SQL


COPYRIGHT = """
Copyright (C) 2020 Rodrigo Silva (MestreLion) <linux@rodrigosilva.com>
License: GPLv3 or later, at your choice. See <http://www.gnu.org/licenses/gpl>
"""

DATABASE = 'students.db'
DBCONN = f'sqlite:///{DATABASE}'

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

    parser.add_argument(dest='csv',  metavar="CSV_FILE",
                        help="Student records CSV file.")

    args = parser.parse_args(argv)
    logging.basicConfig(level=args.loglevel, format='%(levelname)s: %(message)s')
    log.debug(args)
    return args


def load_csv(path):
    records = []
    with open(path) as file:
        # if not for the log: records = tuple(csv.DictReader(file))
        for row in csv.DictReader(file):
            log.debug(row)
            records.append(row)
    return records


def clean_database(db):
    db.execute("DELETE FROM students")
    db.execute("DELETE FROM sqlite_sequence")


def import_records(db, records):
    """Insert each record in the database"""
    for record in records:
        student = convert_record(record)
        log.debug(student)
        sql = ("INSERT INTO students ( first,  middle,  last,  house,  birth) "
               "VALUES               (:first, :middle, :last, :house, :birth)")
        db.execute(sql, **student)


def convert_record(record):
    """Convert a CSV record dict to a dict with database fields"""
    name = record['name'].split()
    if len(name) == 3:
        first, middle, last = name
    else:
        first, last = name
        middle = None
    return {
        'first':  first,
        'middle': middle,
        'last':   last,
        'house':  record['house'],
        'birth':  int(record['birth']),
    }


def main(argv=None):
    args = parse_args(argv)

    log.info("Load CSV records file: %s", args.csv)
    records = load_csv(args.csv)

    log.info("Import records to database: %s", DATABASE)
    db = SQL(DBCONN)
    clean_database(db)
    import_records(db, records)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
