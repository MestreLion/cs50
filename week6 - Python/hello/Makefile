# https://cs50.harvard.edu/x/2020/psets/6/hello

pset=6
category=sentimental
target=hello
version=
args=

# ------------------------------------

LDLIBS=-lcs50
CFLAGS=-Wall -Wextra -std=c11 -Og

path=$(patsubst %/,%,${category}/$(target)/$(version))
slug=cs50/problems/2020/x/$(path://=/)

# ------------------------------------

default: run

run: $(target).py
	python3 $(target).py $(args)

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
