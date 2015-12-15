#!/bin/bash
find . -type f -name "#"\* -exec rm {} \;
git add src
git add maps
git add obj
git add makefile
git add gitit.sh
git add LICENSE
git add README.md
git commit -m  "We got map to almost work"
git push origin master
