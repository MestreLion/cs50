# https://cs50.harvard.edu/x/2020/psets/7/houses

pset=7
target=houses
args=Gryffindor

# ------------------------------------

slug:=cs50/problems/2020/x/$(target)
url:=https://cdn.cs50.net/2019/fall/psets/$(pset)/$(target)/$(target).zip

# ------------------------------------

default: clean run

students.db:
	wget '$(url)'
	unzip $(target).zip
	mv $(target)/* .
	rmdir $(target)
	rm $(target).zip

import: students.db
	python3 import.py characters.csv

roster: students.db
	python3 roster.py $(args)

run: import roster

clean: students.db
	echo 'DELETE FROM students; DELETE FROM sqlite_sequence' | sqlite3 students.db

purge:
	rm -rf *.csv *.db

style:
	style50 *.py

# --local check does not seem to work :-(
check:
	check50 $(slug)

submit:
	if [ -n '$(shell git status --porcelain)' ]; then git commit -a; fi
	git push
	echo yes | submit50 $(slug)

verify: style check

cs50: verify submit

all: default cs50

.PHONY: default import roster run purge style check submit verify cs50 all
