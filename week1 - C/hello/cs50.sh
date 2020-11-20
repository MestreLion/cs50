#!/bin/bash -eu
echo "Do NOT use your password! If prompted for one, create and use a Github Personal Access Token"
set -x
check50 --local cs50/problems/2020/x/hello
style50 hello.c
submit50 cs50/problems/2020/x/hello
