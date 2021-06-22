#include "console.h"
#include "dames.h"
#include "types.h"
#include "systeme.h"


/*	Source principale du jeu.	*/

entier main(entier Nombre, caractere ** Argument)
{
	damier * Damier;
	liste * Liste;
	enregistrement * Enregistrement;
	chaine * Chaine;

	coup * Coup;

	joueur Joueur;
	etat Etat;
	
	naturel Naturel;

	if (Nombre < 2)		//	L'utilisateur doit fournir un fichier créé à l'aide de l'éditeur pour fonctionner.
	{
		quitter_si_erreur(structurer_retour(1, "principale", "utilisez l'éditeur pour créer une partie et donnez l'addresse en argument"));
	}

	quitter_si_erreur(creer_damier(&Damier));
	quitter_si_erreur(creer_liste(&Liste));
	quitter_si_erreur(creer_enregistrement(&Enregistrement));
	quitter_si_erreur(creer_chaine(&Chaine));

	quitter_si_erreur(importer_partie(Enregistrement, Argument[1]));

	allouer_pions(Damier, Enregistrement->Damier->Lignes, Enregistrement->Damier->Colonnes);

	initialiser_partie(Damier, Liste, Enregistrement, &Joueur, &Etat);

	while (Etat == JEU)		//	Boucle du jeu.
	{
		afficher_damier(*Damier, *Enregistrement);
		afficher_coups(*Liste, *Enregistrement, Joueur);

		demander_chaine(Chaine);

		switch (obtenir_majuscule_depuis_caractere(obtenir_caractere_depuis_chaine(*Chaine, 0)))		//	On regarde le caractère reçu.
		{

		case 'R' :		//	L'utilisateur veut revenir au début de la partie.
		{
			initialiser_partie(Damier, Liste, Enregistrement, &Joueur, &Etat);
			break;
		}

		case 'J' :		//	L'utilisateur veut reprendre la partie, on supprime donc les déplacements qui suivent.
		{
			Enregistrement->Nombre = Enregistrement->Lecture;
			break;
		}

		case 'Q' :		//	L'utilisateur veut quitter le jeu.
		{
			Etat = QUITTER;
			break;
		}

		default :		//	On cherche à placer un pion.
		{
			if (Enregistrement->Nombre > Enregistrement->Lecture)		//	On doit continuer à relire l'enregistrement.
			{
				Naturel = Enregistrement->Deplacement[Enregistrement->Lecture];
			}
			else		//	Un joueur doit choisir un déplacement.
			{
				if (Enregistrement->Joueur[(Joueur - 1) / (-2)])		//	Un humain va choisir.
				{
					Naturel = obtenir_naturel_depuis_chaine(*Chaine);
				}
				else		//	Un ordinateur va choisir.
				{
					Naturel = trouver_coup(*Liste, *Damier, Joueur);
				}
			}


			if (verifier_coup(*Liste, Naturel))		//	Le déplacement reçu est correct.
			{
				Coup = Liste->Coup[Naturel];

				if (Coup->Prises.Nombre > 0 || Coup->Deplacements.Pion[0].Type == PION)
				{
					Enregistrement->Coups = 0;
				}
				else
				{
					if (++Enregistrement->Coups >= 25)
					{
						Etat = EGALITE;
					}
				}

				deplacer_piece(Damier, Coup->Deplacements.Pion[0], Coup->Deplacements.Pion[Coup->Deplacements.Nombre - 1]);

				retirer_prises(Damier, *Coup);

				ajouter_enregistrement(Enregistrement, Naturel);

				promouvoir_piece(Damier, Coup->Deplacements.Pion[Coup->Deplacements.Nombre - 1].Position);

				identifier_coups_joueur(Damier, Liste, -Joueur);
					
				if (Liste->Nombre == 0)
				{
					Etat = VICTOIRE;
				}
				else
				{
					Joueur *= -1;
				}
			}
		}

		}
	}

	afficher_damier(*Damier, *Enregistrement);

	afficher_resultat(Etat, Joueur);

	demander_chaine(Chaine);

	quitter_si_erreur(exporter_partie(Enregistrement, Argument[1]));

	supprimer_chaine(&Chaine);
	supprimer_enregistrement(&Enregistrement);
	supprimer_liste(&Liste);
	supprimer_damier(&Damier);

	return 0;
}