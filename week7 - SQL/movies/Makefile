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
	echo '.schema' | sqlite3 $(target).db
	for sql in $$(seq -f '%g.sql' 13); do \
		cmd=$$(grep -- '-- |' $$sql | cut -c6-); \
		if [ -z "$$cmd" ]; then cmd=cat; fi; \
		cat "$$sql"; cat "$$sql" | sqlite3 $(target).db | $$cmd; \
		echo; \
	done

purge:
	rm -rf *.db

# --local check does not seem to work :-(
check:
	check50 $(slug)

submit:
	if [ -n '$(shell git status --porcelain)' ]; then git commit -a; fi
	git push
	echo yes | submit50 $(slug)

verify: check

cs50: verify submit

all: default cs50

.PHONY: default run purge check submit verify cs50 all
