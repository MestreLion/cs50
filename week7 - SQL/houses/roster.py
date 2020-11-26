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

    parser.add_argument(dest='house',  metavar="HOUSE",
                        help="List roster of students belonging to HOUSE")

    args = parser.parse_args(argv)
    logging.basicConfig(level=args.loglevel, format='%(levelname)s: %(message)s')
    log.debug(args)
    return args


def list_students(db, house):
    sql = "SELECT * FROM students WHERE house = :house ORDER BY last, first"
    log.debug(sql)
    for student in db.execute(sql, house=house):
        student['name'] = ' '.join(student[name]
                                   for name in ('first', 'middle', 'last')
                                   if student[name] is not None)
        print("{name}, born {birth}".format(**student))


def main(argv=None):
    args = parse_args(argv)

    log.info("Students from house: %s", args.house)
    db = SQL(DBCONN)
    list_students(db, args.house)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
