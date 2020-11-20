#!/bin/bash -eu

usage() {
	echo "Check (and possibly submit) 'hello' from CS50 Problem Set 1"
	echo "Usage: ${0##*/} [--submit]" >&2
	exit
}
for arg in "$@"; do [[ "$arg" == "-h" || "$arg" == "--help" ]] && usage ; done

set -x
check50 --local cs50/problems/2020/x/hello
style50 hello.c


{ set +x; } 2>&-
if ! [[ "${1:-}" == '-s' || "${1:-}" == '--submit' ]]; then
	exit
fi

echo "Do NOT use your password! If prompted for one, create and use a Github Personal Access Token"
set -x
submit50 cs50/problems/2020/x/hello
