#!/bin/bash
git add README.md
git add gameobject.hpp
git add gameobject.cpp
git add actor.cpp
git add player.cpp
git add npc.cpp
git add goblin.cpp
git add item.cpp
git add potion.cpp
git add equipment.cpp
git add sword.cpp
git add wall.cpp
git add map.cpp
rm -r martins
mkdir martins
cp makefile martins/makefile
cp gitpull.sh martins/gitpull.sh
cp gitit.sh martins/gitit.sh
git add martins
rm -r martins
git commit -m  "Martins Commit"
git push origin master
