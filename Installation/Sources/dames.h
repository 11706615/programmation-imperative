#pragma once

#include "console.h"
#include "systeme.h"
#include "types.h"



/*	Les fonctions qui suivent permettent d'obtenir un élément depuis un type.	*/

caractere obtenir_majuscule_depuis_caractere(caractere);

caractere obtenir_majuscule_depuis_naturel(naturel);

naturel obtenir_naturel_depuis_caractere(caractere);

caractere obtenir_caractere_depuis_piece(pion);

joueur obtenir_joueur_depuis_caractere(caractere);

type obtenir_type_depuis_caractere(caractere);

pion obtenir_piece_depuis_caractere(caractere, position);

pion obtenir_piece_depuis_damier(damier, position);

joueur obtenir_joueur_depuis_damier(damier, position);

type obtenir_type_depuis_damier(damier, position);

pion obtenir_source_depuis_coup(coup);

pion obtenir_destination_depuis_coup(coup);

caractere obtenir_caractere_depuis_chaine(chaine, naturel);

naturel obtenir_naturel_depuis_chaine(chaine);


/*	Les fonctions qui suivent permettent de retourner une structure.	*/

position structurer_position(naturel, naturel);

pion structurer_piece(joueur, type, position);

retour structurer_retour(entier, const caractere *, const caractere *);


/*	Les fonctions qui suivent effectuent des vérifications.	*/

booleen verifier_position(damier, position);

booleen verifier_piece(pion);

booleen verifier_prise(coup, pion);

booleen verifier_coup(liste, naturel);

booleen verifier_chaine(chaine);

booleen verifier_retour(retour);


/*	Les fonctions qui suivent vont réaliser une initialisation.	*/

vide initialiser_partie(damier *, liste *, enregistrement *, joueur *, etat *);

vide initialiser_damier(damier *);

vide initialiser_chaine(chaine *);


/*	Les fonctions qui suivent modifient le damier.	*/

retour placer_piece(damier *, pion);

retour retirer_piece(damier *, pion);

/*	Les fonctions qui suivent effectuent un coup sur le damier.	*/

vide deplacer_piece(damier *, pion, pion);

vide retirer_prises(damier *, coup);


/*	Les fonctions qui suivent ajoutent de nouveaux éléments.	*/

vide ajouter_enregistrement(enregistrement *, naturel);

vide ajouter_coup(liste *, coup *);

vide ajouter_deplacement(damier *, liste *, coup *, pion, pion);

vide ajouter_caractere(chaine *, caractere);


/*	Ces fonctions identifient les déplacements possibles sur un damier.	*/

vide identifier_coups_joueur(damier *, liste *, joueur);

vide identifier_coups_pion(damier *, liste *, coup *);


/*	Fonctions diverses.	*/

naturel calculer_distance_entre_naturels(naturel, naturel);

naturel trouver_coup(liste, damier, joueur);

vide copier_damier(damier *, damier);

retour promouvoir_piece(damier *, position);