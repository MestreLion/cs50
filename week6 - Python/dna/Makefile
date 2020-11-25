# https://cs50.harvard.edu/x/2020/psets/6/dna

pset=6
target=dna
args=databases/large.csv sequences/1.txt

# ------------------------------------

slug:=cs50/problems/2020/x/$(target)
url:=https://cdn.cs50.net/2019/fall/psets/$(pset)/$(target)/$(target).zip

# ------------------------------------

default: run

databases/:
	wget '$(url)'
	unzip $(target).zip
	mv $(target)/* .
	rmdir $(target)
	rm $(target).zip

run: databases/
	python3 $(target).py $(args)

purge:
	rm -rf */

check:
	check50 --local $(slug)

style:
	style50 *.py

submit:
	if [ -n '$(shell git status --porcelain)' ]; then git commit -a; fi
	git push
	echo yes | submit50 $(slug)

verify: check style

cs50: verify submit

all: default cs50

.PHONY: default run check style submit verify cs50 all
