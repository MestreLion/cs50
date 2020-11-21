target=plurality
slug=cs50/problems/2020/x/plurality

# ------------------------------------

LDLIBS=-lcs50
CFLAGS=-Wall -Wextra -std=c11 -Og

# ------------------------------------

default: clean $(target) run

run:
	./$(target) $(args)

clean:
	rm -rf $(target)

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

.PHONY: default run clean check style submit verify cs50 all
