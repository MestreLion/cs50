# https://cs50.harvard.edu/x/2020/psets/4/filter/less

pset=4
target=filter
version=less

# ------------------------------------

LDLIBS=-lcs50
CFLAGS=-Wall -Wextra -std=c11 -Og

path=$(patsubst %\,%,$(target)/$(version))
slug=cs50/problems/2020/x/$(path)

# ------------------------------------

default: clean $(target) run

$(target): $(target).c
	$(MAKE) -f Makefile $@

$(target).c:
	wget 'https://cdn.cs50.net/2019/fall/psets/$(pset)/$(path)/$(target).zip'
	unzip $(target).zip
	mv $(target)/* .
	rmdir $(target)
	rm $(target).zip

run:
	./$(target) $(args)

clean:
	rm -rf $(target)

purge: clean
	mv makefile .makefile
	rm -rf *
	mv .makefile makefile

check:
	check50 --local $(slug)

style:
	style50 $(target).c

submit:
	if [ -n '$(shell git status --porcelain)' ]; then git commit -a; fi
	git push
	echo yes | submit50 $(slug)

verify: check style

cs50: verify submit

all: default cs50

.PHONY: default run clean purge check style submit verify cs50 all
