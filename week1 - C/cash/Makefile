target=cash
slug=cs50/problems/2020/x/cash

# ------------------------------------

LDLIBS=-lcs50 -lm
CFLAGS=-Wall -Wextra -std=c99 -Og

# ------------------------------------

default: clean $(target) run

run:
	./$(target)

clean:
	rm -rf $(target)

check:
	check50 --local $(slug)

style:
	style50 $(target).c

submit:
	submit50 $(slug)

verify: check style

cs50: verify submit

all: default cs50

.PHONY: default run clean check style submit verify cs50 all
