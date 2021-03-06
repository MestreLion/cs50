# https://cs50.harvard.edu/x/2020/psets/4/filter/less

# This is intentionally named 'makefile' instead of 'Makefile', so it is not
# replaced by CS50's 'Makefile' from distribution code zip, and also take
# precedence over it when invoked by GNU (and possibly others) make

pset=4
target=filter
version=less

# ------------------------------------

LDLIBS=-lcs50
CFLAGS=-Wall -Wextra -std=c11 -Og

path=$(patsubst %\,%,$(target)/$(version))
slug=cs50/problems/2020/x/$(path)

# ------------------------------------

default: run

$(target): clean *.c
	$(MAKE) -f Makefile $@

$(target).c:
	wget 'https://cdn.cs50.net/2019/fall/psets/$(pset)/$(path)/$(target).zip'
	unzip $(target).zip
	mv $(target)/* .
	rmdir $(target)
	rm $(target).zip

run: $(target)
	./$(target) $(args)

clean:
	rm -rf $(target)

purge: clean
	mv makefile .makefile
	rm -rf *
	mv .makefile makefile

images: clean $(target)
	mkdir -p output
	for i in images/*.bmp; do \
		ln -sf -- ../"$$i" output/"$$(basename "$${i%.*}")"._.bmp; \
	done
	for f in grayscale sepia reflect blur; do \
		for i in images/*.bmp; do \
			./$(target) -$$(printf %.1s "$$f") "$$i" \
				output/"$$(basename "$${i%.*}")".$${f}.bmp; \
		done; \
		sleep 1; \
	done

check:
	check50 --local $(slug)

style:
	style50 *.c

submit:
	if [ -n '$(shell git status --porcelain)' ]; then git commit -a; fi
	git push
	echo yes | submit50 $(slug)

verify: check style

cs50: verify submit

all: default cs50

.PHONY: default run clean purge images check style submit verify cs50 all
