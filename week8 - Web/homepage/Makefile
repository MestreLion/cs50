# https://cs50.harvard.edu/x/2020/psets/6/dna

track=web
target=homepage
args=

# ------------------------------------

slug:=cs50/problems/2020/x/tracks/$(track)/$(target)
url:=https://cdn.cs50.net/2019/fall/tracks/$(track)/$(target)/$(target).zip

# ------------------------------------

default: run

index.html:
	wget '$(url)'
	unzip $(target).zip
	mv $(target)/* .
	rmdir $(target)
	rm $(target).zip

run: index.html
	python3 -m http.server $(args)

purge:
	rm -rf */

style:
	style50 *.html

submit:
	if [ -n '$(shell git status --porcelain)' ]; then git commit -a; fi
	git push
	echo yes | submit50 $(slug)

verify: style

cs50: verify submit

all: default cs50

.PHONY: default run purge style submit verify cs50 all
