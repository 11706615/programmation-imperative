PARAMETRES = -Wall -pedantic
FICHIERS = systeme.o console.o dames.o editeur.o jeu.o

tous :		$(FICHIERS)
		gcc -g systeme.o console.o dames.o jeu.o -o jeu.exe
		gcc -g systeme.o console.o dames.o editeur.o -o editeur.exe
		rm $(FICHIERS)

jeu.o :
		gcc -c $(PARAMETRES) jeu.c

editeur.o :
		gcc -c $(PARAMETRES) editeur.c

dames.o :
		gcc -c $(PARAMETRES) dames.c

console.o :
		gcc -c $(PARAMETRES) console.c

systeme.o :
		gcc -c $(PARAMETRES) systeme.c
