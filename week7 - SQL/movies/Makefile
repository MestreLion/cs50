# https://cs50.harvard.edu/x/2020/psets/7/movies

pset=7
target=movies
args=

# ------------------------------------

slug:=cs50/problems/2020/x/$(target)
url:=https://cdn.cs50.net/2019/fall/psets/$(pset)/$(target)/$(target).zip

# ------------------------------------

default: run

$(target).db:
	wget '$(url)'
	unzip $(target).zip
	mv $(target)/* .
	rmdir $(target)
	rm $(target).zip

run: $(target).db
	cat *.sql | sqlite3 $(target).db

purge:
	rm -rf *.db *.sql

check:
	check50 --local $(slug)

style:
	style50 *.sql

submit:
	if [ -n '$(shell git status --porcelain)' ]; then git commit -a; fi
	git push
	echo yes | submit50 $(slug)

verify: check style

cs50: verify submit

all: default cs50

.PHONY: default run purge check style submit verify cs50 all
