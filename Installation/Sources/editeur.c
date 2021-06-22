#include "console.h"
#include "dames.h"
#include "types.h"
#include "systeme.h"

#include <stdio.h>


/*	Source principale de l'éditeur.	*/

entier main(entier Arguments, caractere ** Argument)
{
	enregistrement * Enregistrement;
	chaine * Chaine;

	quitter_si_erreur(creer_enregistrement(&Enregistrement));
	quitter_si_erreur(creer_chaine(&Chaine));

	printf("\n 0) Internationale\n 1) Personnalisée\n\n Quelle partie souhaitez-vous créér ? ");
	demander_chaine(Chaine);

	switch (obtenir_naturel_depuis_chaine(*Chaine))
	{
	case 0:
	{
		quitter_si_erreur(allouer_pions(Enregistrement->Damier, 10, 10));
		initialiser_damier(Enregistrement->Damier);
		break;
	}
	default:
	{
		naturel Lignes;
		naturel Colonnes;

		do
		{
			printf("\n Combien de lignes voulez-vous pour votre damier ? ");
			demander_chaine(Chaine);

			Lignes = obtenir_naturel_depuis_chaine(*Chaine);

			printf(" Combien de colonnes voulez-vous pour votre damier ? ");
			demander_chaine(Chaine);

			Colonnes = obtenir_naturel_depuis_chaine(*Chaine);

		} while (afficher_si_erreur(allouer_pions(Enregistrement->Damier, Lignes, Colonnes)));


		printf("\n 0) Traditionnelle\n 1) Personnalisée\n\n Quelle disposition de pions voulez-vous ? ");
		demander_chaine(Chaine);

		switch (obtenir_naturel_depuis_chaine(*Chaine))
		{
		case 0:
		{
			initialiser_damier(Enregistrement->Damier);
			break;
		}

		default:
		{
			for (naturel i = 0; i < Enregistrement->Damier->Lignes; i++)
			{
				for (naturel j = i % 2; j < Enregistrement->Damier->Colonnes; j += 2)
				{
					afficher_editeur(*(Enregistrement->Damier), i, j);

					printf(" Que voulez-vous dans cette case ? ");
					demander_chaine(Chaine);

					afficher_si_erreur(placer_piece(Enregistrement->Damier, obtenir_piece_depuis_caractere(obtenir_caractere_depuis_chaine(*Chaine, 0), structurer_position(i, j))));
				}
			}
		}
		}
	}
	}

	printf("\n Voilà le résultat :\n");
	afficher_damier(*(Enregistrement->Damier), *Enregistrement);

	printf("\n Qui jouera les BLANCS ? ");

	demander_chaine(Chaine);
	Enregistrement->Joueur[0] = verifier_chaine(*Chaine);

	printf(" Qui jouera les NOIRS ? ");

	demander_chaine(Chaine);
	Enregistrement->Joueur[1] = verifier_chaine(*Chaine);

	do
	{
		printf("\n Où voulez-vous l'exporter ? ");
		demander_chaine(Chaine);
	}
	while (afficher_si_erreur(exporter_partie(Enregistrement, Chaine->Caractere)));

	printf("\n C'est fait ! Vous pouvez dès maintenant commencer à jouer. ");
	demander_chaine(Chaine);

	supprimer_chaine(&Chaine);
	supprimer_enregistrement(&Enregistrement);

	return 0;
}