#include "console.h"

/*	Cette source exploite les fonctionnalités de <stdio.h>.
Elle contient des fonctions qui permettent de recevoir des informations ou d'en afficher à travers la console.
Par souci de sécurité, les fonctions liées à scanf ne sont pas utilisées et remplacées par la réception d'une chaîne de caractère.
Cela permet par ailleurs d'autoriser la touche entrée et de réutiliser le contenu de la chaîne pour d'autres conversions.	*/



/*	Les fonctions qui suivent permettent de recevoir des informations depuis la console.	*/


/*	Cette fonction va stocker les caractères de la console dans la chaîne reçue.	*/

retour demander_chaine(chaine * Chaine)
{
	caractere Caractere;

	initialiser_chaine(Chaine);

	while ((Caractere = getchar()) != '\n')		//	On récupère tous les caractères et on les stocke dans la chaîne.
	{
		if (Caractere == EOF)
		{
			return structurer_retour(1, "demander_chaine", "une erreur est survenue lors de la lecture");
		}

		ajouter_caractere(Chaine, Caractere);
	}

	return structurer_retour(0, "demander_chaine", "la fonction s'est correctement terminée");
}



/*	Les fonctions qui suivent permettent d'envoyer des informations vers la console.	*/


/*	Cette fonction affiche le damier.	*/

vide afficher_damier(damier Damier, enregistrement Enregistrement)
{
	printf("\n");

	for (entier i = Damier.Lignes - 1; i >= 0; i--)		//	On parcourt les lignes du damier.
	{
		printf(" %d\t", i);

		for (naturel j = 0; j < Damier.Colonnes; j++)		//	On parcourt les colonnes du damier.
		{
			if ((i + j) % 2 == 0)		//	On tombe sur une case noire.
			{
				printf("| %c ", obtenir_caractere_depuis_piece(Damier.Pion[i][j]));
			}
			else		//	On tombe sur une case blanche.
			{
				printf("||||");
			}
		}

		printf("|\n");
	}

	for (naturel i = 0; i <= Damier.Colonnes; i++)		//	On affiche les informations additionnelles.
	{
		if (i)		//	On affiche les numéros de colonne.
		{
			printf("  %c ", obtenir_majuscule_depuis_naturel(i - 1));
		}
		else		//	On affiche les informations sur la relecture.
		{
			printf("\n > %d\t", Enregistrement.Lecture);
		}
	}

	printf("\n");
}


/*	Cette fonction affiche le damier de l'éditeur.	*/

vide afficher_editeur(damier Damier, naturel Ligne, naturel Colonne)
{
	printf("\n");

	for (entier i = Damier.Lignes - 1; i >= 0; i--)		//	On parcourt les lignes du damier.
	{
		printf("\t");

		for (naturel j = 0; j < Damier.Colonnes; j++)		//	On parcourt les colonnes du damier.
		{
			if ((i + j) % 2 == 0)		//	On tombe sur une case noire.
			{
				if (i == Ligne && j == Colonne)		//	On tombe sur la case à modifier.
				{
					printf("| * ");
				}
				else		//	On tombe sur une case normale.
				{
					printf("| %c ", obtenir_caractere_depuis_piece(Damier.Pion[i][j]));
				}
			}
			else		//	On tombe sur une case blanche.
			{
				printf("||||");
			}
		}

		printf("|\n");
	}

	printf("\n");
}


/*	Cette fonction affiche la liste des déplacements autorisés.	*/

vide afficher_coups(liste Liste, enregistrement Enregistrement, joueur Joueur)
{
	pion Source;
	pion Destination;

	naturel Naturel;

	coup Coup;

	if (Enregistrement.Nombre > Enregistrement.Lecture)		//	On doit continuer à relire l'enregistrement.
	{
		Naturel = Enregistrement.Deplacement[Enregistrement.Lecture];

		if (verifier_coup(Liste, Naturel))		//	Le nombre reçu est correct.
		{
			Coup = *Liste.Coup[Naturel];

			Source = obtenir_source_depuis_coup(Coup);
			Destination = obtenir_destination_depuis_coup(Coup);

			if (Joueur == BLANC)		//	Cas du joueur BLANC.
			{
				printf("\n BLANC joue %c%d", obtenir_majuscule_depuis_naturel(Source.Position.Colonne), Source.Position.Ligne);
			}

			if (Joueur == NOIR)		//	Cas du joueur NOIR.
			{
				printf("\n NOIR joue %c%d", obtenir_majuscule_depuis_naturel(Source.Position.Colonne), Source.Position.Ligne);
			}

			for (naturel i = 1; i < Coup.Deplacements.Nombre; i++)		//	On affiche les positions successives.
			{
				printf(" -> %c%d", obtenir_majuscule_depuis_naturel(Coup.Deplacements.Pion[i].Position.Colonne), Coup.Deplacements.Pion[i].Position.Ligne);
			}

			printf(". ");
		}
		else		//	Le nombre reçu a été corrompu.
		{
			printf("\n Erreur de relecture. ");
		}
	}
	else		//	Un joueur doit choisir un déplacement.
	{
		if (Enregistrement.Joueur[(Joueur - 1) / (-2)])		//	Un humain va choisir.
		{
			printf("\n Liste des coups autorisés :\n\n");

			for (naturel i = 0; i < Liste.Nombre; i++)		//	On parcourt la liste des déplacements.
			{
				Coup = *Liste.Coup[i];

				Source = Coup.Deplacements.Pion[0];
				Destination = Coup.Deplacements.Pion[Liste.Coup[i]->Deplacements.Nombre - 1];

				if (Liste.Coup[i]->Prises.Nombre == 0)		//	Il n'y a pas eu de capture.
				{
					printf(" %d)\t%c%d va en %c%d.\n", i, obtenir_majuscule_depuis_naturel(Source.Position.Colonne), Source.Position.Ligne, obtenir_majuscule_depuis_naturel(Destination.Position.Colonne), Destination.Position.Ligne);
				}
				else		//	Au moins un pion a été pris.
				{
					printf(" %d)\t%c%d", i, obtenir_majuscule_depuis_naturel(Source.Position.Colonne), Source.Position.Ligne);

					for (naturel j = 0; j < Liste.Coup[i]->Prises.Nombre; j++)		//	On affiche les étapes de la rafle.
					{
						printf(", prend %c%d et va en %c%d", obtenir_majuscule_depuis_naturel(Coup.Prises.Pion[j].Position.Colonne), Coup.Prises.Pion[j].Position.Ligne, obtenir_majuscule_depuis_naturel(Coup.Deplacements.Pion[j + 1].Position.Colonne), Coup.Deplacements.Pion[j + 1].Position.Ligne);
					}

					printf(".\n");
				}
			}

			if (Joueur == BLANC)		//	Cas du joueur BLANC.
			{
				printf("\n Que doit faire le joueur BLANC ? ");
			}

			if (Joueur == NOIR)		//	Cas du joueur NOIR.
			{
				printf("\n Que doit faire le joueur NOIR ? ");
			}
		}
		else		//	Un ordinateur va choisir.
		{
			printf("\n L'IA va choisir un coup à jouer. ");
		}
	}
}


/*	Cette fonctions affiche le résultat de la partie.	*/

vide afficher_resultat(etat Etat, joueur Joueur)
{
	printf("\n");

	switch (Etat)		//	On regarde comment s'est terminée la partie.
	{

	case VICTOIRE :		//	La partie s'est terminée sur une victoire.
	{
		if (Joueur == BLANC)		//	Cas du joueur BLANC.
		{
			printf(" La partie a été remportée par le joueur BLANC !\n");
		}

		if (Joueur == NOIR)		//	Cas du joueur NOIR.
		{
			printf(" La partie a été remportée par le joueur NOIR !\n");
		}

		break;
	}

	case EGALITE :		//	La partie s'est terminée sur une égalité.
	{
		printf(" La partie s'est terminée sur une égalité car aucun des adversaires n'a été en mesure de prendre l'avantage.\n");

		break;
	}

	default :		//	La partie a été interrompue ou corrompue.
	{
		printf(" La partie a été interrompue.\n");
	}

	}

	printf("\n Elle peut être relue ou reprise depuis le fichier d'origine. ");
}



/*	Les fonctions qui suivent permettent de gérer les fichiers d'enregistrement.	*/


/*	Cette fonction permet d'exporter une partie vers un fichier binaire.	*/

retour exporter_partie(enregistrement * Enregistrement, caractere * Caractere)
{
	fichier * Fichier;

	taille Taille = 0;

	naturel Lignes = Enregistrement->Damier->Lignes;
	naturel Colonnes = Enregistrement->Damier->Colonnes;
	naturel Nombre = Enregistrement->Nombre;

	if ((Fichier = fopen(Caractere, "wb")) == NULL)		//	Le fichier n'a pas pû être ouvert.
	{
		return structurer_retour(1, "exporter_partie", "le fichier n'a pas pû être ouvert");
	}
	
	Taille += fwrite(&Lignes, sizeof(naturel), 1, Fichier);
	Taille += fwrite(&Colonnes, sizeof(naturel), 1, Fichier);
	Taille += fwrite(&Nombre, sizeof(naturel), 1, Fichier);

	for (naturel i = 0; i < Lignes; i++)		//	On écrit chaque ligne du damier.
	{
		Taille += fwrite(Enregistrement->Damier->Pion[i], sizeof(pion), Colonnes, Fichier);
	}

	Taille += fwrite(Enregistrement->Deplacement, sizeof(naturel), Nombre, Fichier);
	Taille += fwrite(Enregistrement->Joueur, sizeof(booleen), 2, Fichier);

	if (fclose(Fichier) == EOF)		//	Le fichier n'a pas pû être fermé.
	{
		return structurer_retour(2, "exporter_partie", "le fichier n'a pas pû être fermé");
	}

	if (Taille != 5 + Enregistrement->Nombre + Lignes * Colonnes)		//	Une retour est survenue lors de l'écriture dans le fichier.
	{
		if (remove(Caractere) == 0)		//	Le fichier corrompu a été supprimé.
		{
			return structurer_retour(3, "exporter_partie", "l'exportation a échoué");
		}
		else		//	Le fichier corrompu n'a pas été supprimé.
		{
			return structurer_retour(4, "exporter_partie", "l'exportation a échoué et le fichier n'a pas pû être supprimé");
		}
	}

	return structurer_retour(0, "exporter_partie", "l'exportation s'est correctement terminée");
}

/*	Cette fonction permet d'importer une partie depuis un fichier binaire.	*/

retour importer_partie(enregistrement * Enregistrement, caractere * Caractere)
{
	fichier * Fichier;

	taille Taille = 0;

	naturel Lignes;
	naturel Colonnes;
	naturel Nombre;

	if ((Fichier = fopen(Caractere, "rb")) == NULL)		//	Le fichier n'a pas pû être ouvert.
	{
		return structurer_retour(1, "importer_partie", "le fichier n'a pas pû être ouvert");
	}

	Taille += fread(&Lignes, sizeof(naturel), 1, Fichier);
	Taille += fread(&Colonnes, sizeof(naturel), 1, Fichier);
	Taille += fread(&Nombre, sizeof(naturel), 1, Fichier);

	quitter_si_erreur(allouer_pions(Enregistrement->Damier, Lignes, Colonnes));
	quitter_si_erreur(allouer_enregistrements(Enregistrement, Nombre));

	Enregistrement->Nombre = Nombre;

	for (naturel i = 0; i < Lignes; i++)		//	On lit chaque ligne du damier.
	{
		Taille += fread(Enregistrement->Damier->Pion[i], sizeof(pion), Colonnes, Fichier);
	}

	Taille += fread(Enregistrement->Deplacement, sizeof(naturel), Nombre, Fichier);
	Taille += fread(Enregistrement->Joueur, sizeof(booleen), 2, Fichier);

	if (fclose(Fichier) == EOF)		//	Le fichier n'a pas pû être fermé.
	{
		return structurer_retour(2, "importer_partie", "le fichier n'a pas pû être fermé");
	}

	if (Taille != 5 + Enregistrement->Nombre + Lignes * Colonnes)		//	Une erreur est survenue lors de la lecture dans le fichier.
	{
		if (remove(Caractere) == 0)		//	Le fichier corrompu a été supprimé.
		{
			return structurer_retour(3, "importer_partie", "l'importation a échoué");
		}
		else		//	Le fichier corrompu n'a pas été supprimé.
		{
			return structurer_retour(4, "exporter_partie", "l'importation a échoué et le fichier n'a pas pû être supprimé");
		}
	}

	return structurer_retour(0, "importer_partie", "l'importation s'est correctement terminée");
}



/*	Les fonctions qui suivent permettent de gérer les éventuelles erreurs du programme.	*/


/*	Cette fonction affiche les informations si une erreur est survenue et quitte le programme.	*/

entier quitter_si_erreur(retour Retour)
{
	if (Retour.Type)		//	Une erreur a été retournée.
	{
		chaine * Chaine;

		quitter_si_erreur(creer_chaine(&Chaine));

		fprintf(stderr, "\n[%d] Une erreur critique provoquant l'arrêt du programme est survenue dans la fonction %s : %s. ", Retour.Type, Retour.Fonction, Retour.Description);

		demander_chaine(Chaine);

		supprimer_chaine(&Chaine);

		quitter_programme(Retour.Type);
	}

	return Retour.Type;
}

/*	Cette fonction affiche les informations si une erreur est survenue.	*/

entier afficher_si_erreur(retour Retour)
{
	if (Retour.Type)		//	Une erreur a été retournée.
	{
		chaine * Chaine;

		quitter_si_erreur(creer_chaine(&Chaine));

		fprintf(stderr, "\n[%d] Une erreur est survenue dans la fonction %s : %s. ", Retour.Type, Retour.Fonction, Retour.Description);

		demander_chaine(Chaine);

		supprimer_chaine(&Chaine);
	}

	return Retour.Type;
}