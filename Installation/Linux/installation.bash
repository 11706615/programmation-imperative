#!/bin/bash

cp "makefile" "../Sources/makefile"
cd ../Sources
make > /dev/null
rm "makefile"
mv "jeu.exe" "../../Dames/jeu.exe"
mv "editeur.exe" "../../Dames/editeur.exe"
cat "../notes.txt"
