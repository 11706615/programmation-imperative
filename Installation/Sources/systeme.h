#pragma once

#include <stdlib.h>

#include "console.h"
#include "types.h"


/*	Les fonctions qui suivent permettent de gérer l'évolution du programme.	*/

vide quitter_programme(entier);


/*	Les fonctions qui suivent vont créer dynamiquement un type.	*/

retour creer_damier(damier **);

retour creer_liste(liste **);

retour creer_coup(coup **);

retour creer_enregistrement(enregistrement **);

retour creer_chaine(chaine **);


/*	Les fonctions qui suivent vont allouer dynamiquement le contenu d'un type.	*/

retour allouer_pions(damier *, naturel, naturel);

retour allouer_coups(liste *, naturel);

retour allouer_deplacements(coup *, naturel);

retour allouer_prises(coup *, naturel);

retour allouer_enregistrements(enregistrement *, naturel);

retour allouer_caracteres(chaine *, naturel);


/*	Les fonctions qui suivent vont libérer le contenu d'un type.	*/

vide liberer_pions(damier *);

vide liberer_coups(liste *);

vide liberer_deplacements(coup *);

vide liberer_prises(coup *);

vide liberer_enregistrements(enregistrement *);

vide liberer_caracteres(chaine *);


/*	Les fonctions qui suivent vont supprimer un type.	*/

vide supprimer_damier(damier **);

vide supprimer_liste(liste **);

vide supprimer_coup(coup **);

vide supprimer_enregistrement(enregistrement **);

vide supprimer_chaine(chaine **);