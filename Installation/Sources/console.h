#pragma once

#include <stdio.h>

#include "dames.h"
#include "systeme.h"
#include "types.h"


typedef FILE fichier;
typedef size_t taille;


/*	Les fonctions qui suivent permettent de recevoir des informations depuis la console.	*/

retour demander_chaine(chaine *);


/*	Les fonctions qui suivent permettent d'envoyer des informations vers la console.	*/

vide afficher_damier(damier, enregistrement);

vide afficher_editeur(damier, naturel, naturel);

vide afficher_coups(liste, enregistrement, joueur);

vide afficher_resultat(etat, joueur);


/*	Les fonctions qui suivent permettent de gérer les fichiers d'enregistrement.	*/

retour exporter_partie(enregistrement *, caractere *);

retour importer_partie(enregistrement *, caractere *);


/*	Les fonctions qui suivent permettent de gérer les éventuelles erreurs du programme.	*/

entier quitter_si_erreur(retour);

entier afficher_si_erreur(retour);