#include "console.h"

/*	Cette source exploite les fonctionnalit�s de <stdio.h>.
Elle contient des fonctions qui permettent de recevoir des informations ou d'en afficher � travers la console.
Par souci de s�curit�, les fonctions li�es � scanf ne sont pas utilis�es et remplac�es par la r�ception d'une cha�ne de caract�re.
Cela permet par ailleurs d'autoriser la touche entr�e et de r�utiliser le contenu de la cha�ne pour d'autres conversions.	*/



/*	Les fonctions qui suivent permettent de recevoir des informations depuis la console.	*/


/*	Cette fonction va stocker les caract�res de la console dans la cha�ne re�ue.	*/

retour demander_chaine(chaine * Chaine)
{
	caractere Caractere;

	initialiser_chaine(Chaine);

	while ((Caractere = getchar()) != '\n')		//	On r�cup�re tous les caract�res et on les stocke dans la cha�ne.
	{
		if (Caractere == EOF)
		{
			return structurer_retour(1, "demander_chaine", "une erreur est survenue lors de la lecture");
		}

		ajouter_caractere(Chaine, Caractere);
	}

	return structurer_retour(0, "demander_chaine", "la fonction s'est correctement termin�e");
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
		if (i)		//	On affiche les num�ros de colonne.
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


/*	Cette fonction affiche le damier de l'�diteur.	*/

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
				if (i == Ligne && j == Colonne)		//	On tombe sur la case � modifier.
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


/*	Cette fonction affiche la liste des d�placements autoris�s.	*/

vide afficher_coups(liste Liste, enregistrement Enregistrement, joueur Joueur)
{
	pion Source;
	pion Destination;

	naturel Naturel;

	coup Coup;

	if (Enregistrement.Nombre > Enregistrement.Lecture)		//	On doit continuer � relire l'enregistrement.
	{
		Naturel = Enregistrement.Deplacement[Enregistrement.Lecture];

		if (verifier_coup(Liste, Naturel))		//	Le nombre re�u est correct.
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
		else		//	Le nombre re�u a �t� corrompu.
		{
			printf("\n Erreur de relecture. ");
		}
	}
	else		//	Un joueur doit choisir un d�placement.
	{
		if (Enregistrement.Joueur[(Joueur - 1) / (-2)])		//	Un humain va choisir.
		{
			printf("\n Liste des coups autoris�s :\n\n");

			for (naturel i = 0; i < Liste.Nombre; i++)		//	On parcourt la liste des d�placements.
			{
				Coup = *Liste.Coup[i];

				Source = Coup.Deplacements.Pion[0];
				Destination = Coup.Deplacements.Pion[Liste.Coup[i]->Deplacements.Nombre - 1];

				if (Liste.Coup[i]->Prises.Nombre == 0)		//	Il n'y a pas eu de capture.
				{
					printf(" %d)\t%c%d va en %c%d.\n", i, obtenir_majuscule_depuis_naturel(Source.Position.Colonne), Source.Position.Ligne, obtenir_majuscule_depuis_naturel(Destination.Position.Colonne), Destination.Position.Ligne);
				}
				else		//	Au moins un pion a �t� pris.
				{
					printf(" %d)\t%c%d", i, obtenir_majuscule_depuis_naturel(Source.Position.Colonne), Source.Position.Ligne);

					for (naturel j = 0; j < Liste.Coup[i]->Prises.Nombre; j++)		//	On affiche les �tapes de la rafle.
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
			printf("\n L'IA va choisir un coup � jouer. ");
		}
	}
}


/*	Cette fonctions affiche le r�sultat de la partie.	*/

vide afficher_resultat(etat Etat, joueur Joueur)
{
	printf("\n");

	switch (Etat)		//	On regarde comment s'est termin�e la partie.
	{

	case VICTOIRE :		//	La partie s'est termin�e sur une victoire.
	{
		if (Joueur == BLANC)		//	Cas du joueur BLANC.
		{
			printf(" La partie a �t� remport�e par le joueur BLANC !\n");
		}

		if (Joueur == NOIR)		//	Cas du joueur NOIR.
		{
			printf(" La partie a �t� remport�e par le joueur NOIR !\n");
		}

		break;
	}

	case EGALITE :		//	La partie s'est termin�e sur une �galit�.
	{
		printf(" La partie s'est termin�e sur une �galit� car aucun des adversaires n'a �t� en mesure de prendre l'avantage.\n");

		break;
	}

	default :		//	La partie a �t� interrompue ou corrompue.
	{
		printf(" La partie a �t� interrompue.\n");
	}

	}

	printf("\n Elle peut �tre relue ou reprise depuis le fichier d'origine. ");
}



/*	Les fonctions qui suivent permettent de g�rer les fichiers d'enregistrement.	*/


/*	Cette fonction permet d'exporter une partie vers un fichier binaire.	*/

retour exporter_partie(enregistrement * Enregistrement, caractere * Caractere)
{
	fichier * Fichier;

	taille Taille = 0;

	naturel Lignes = Enregistrement->Damier->Lignes;
	naturel Colonnes = Enregistrement->Damier->Colonnes;
	naturel Nombre = Enregistrement->Nombre;

	if ((Fichier = fopen(Caractere, "wb")) == NULL)		//	Le fichier n'a pas p� �tre ouvert.
	{
		return structurer_retour(1, "exporter_partie", "le fichier n'a pas p� �tre ouvert");
	}
	
	Taille += fwrite(&Lignes, sizeof(naturel), 1, Fichier);
	Taille += fwrite(&Colonnes, sizeof(naturel), 1, Fichier);
	Taille += fwrite(&Nombre, sizeof(naturel), 1, Fichier);

	for (naturel i = 0; i < Lignes; i++)		//	On �crit chaque ligne du damier.
	{
		Taille += fwrite(Enregistrement->Damier->Pion[i], sizeof(pion), Colonnes, Fichier);
	}

	Taille += fwrite(Enregistrement->Deplacement, sizeof(naturel), Nombre, Fichier);
	Taille += fwrite(Enregistrement->Joueur, sizeof(booleen), 2, Fichier);

	if (fclose(Fichier) == EOF)		//	Le fichier n'a pas p� �tre ferm�.
	{
		return structurer_retour(2, "exporter_partie", "le fichier n'a pas p� �tre ferm�");
	}

	if (Taille != 5 + Enregistrement->Nombre + Lignes * Colonnes)		//	Une retour est survenue lors de l'�criture dans le fichier.
	{
		if (remove(Caractere) == 0)		//	Le fichier corrompu a �t� supprim�.
		{
			return structurer_retour(3, "exporter_partie", "l'exportation a �chou�");
		}
		else		//	Le fichier corrompu n'a pas �t� supprim�.
		{
			return structurer_retour(4, "exporter_partie", "l'exportation a �chou� et le fichier n'a pas p� �tre supprim�");
		}
	}

	return structurer_retour(0, "exporter_partie", "l'exportation s'est correctement termin�e");
}

/*	Cette fonction permet d'importer une partie depuis un fichier binaire.	*/

retour importer_partie(enregistrement * Enregistrement, caractere * Caractere)
{
	fichier * Fichier;

	taille Taille = 0;

	naturel Lignes;
	naturel Colonnes;
	naturel Nombre;

	if ((Fichier = fopen(Caractere, "rb")) == NULL)		//	Le fichier n'a pas p� �tre ouvert.
	{
		return structurer_retour(1, "importer_partie", "le fichier n'a pas p� �tre ouvert");
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

	if (fclose(Fichier) == EOF)		//	Le fichier n'a pas p� �tre ferm�.
	{
		return structurer_retour(2, "importer_partie", "le fichier n'a pas p� �tre ferm�");
	}

	if (Taille != 5 + Enregistrement->Nombre + Lignes * Colonnes)		//	Une erreur est survenue lors de la lecture dans le fichier.
	{
		if (remove(Caractere) == 0)		//	Le fichier corrompu a �t� supprim�.
		{
			return structurer_retour(3, "importer_partie", "l'importation a �chou�");
		}
		else		//	Le fichier corrompu n'a pas �t� supprim�.
		{
			return structurer_retour(4, "exporter_partie", "l'importation a �chou� et le fichier n'a pas p� �tre supprim�");
		}
	}

	return structurer_retour(0, "importer_partie", "l'importation s'est correctement termin�e");
}



/*	Les fonctions qui suivent permettent de g�rer les �ventuelles erreurs du programme.	*/


/*	Cette fonction affiche les informations si une erreur est survenue et quitte le programme.	*/

entier quitter_si_erreur(retour Retour)
{
	if (Retour.Type)		//	Une erreur a �t� retourn�e.
	{
		chaine * Chaine;

		quitter_si_erreur(creer_chaine(&Chaine));

		fprintf(stderr, "\n[%d] Une erreur critique provoquant l'arr�t du programme est survenue dans la fonction %s : %s. ", Retour.Type, Retour.Fonction, Retour.Description);

		demander_chaine(Chaine);

		supprimer_chaine(&Chaine);

		quitter_programme(Retour.Type);
	}

	return Retour.Type;
}

/*	Cette fonction affiche les informations si une erreur est survenue.	*/

entier afficher_si_erreur(retour Retour)
{
	if (Retour.Type)		//	Une erreur a �t� retourn�e.
	{
		chaine * Chaine;

		quitter_si_erreur(creer_chaine(&Chaine));

		fprintf(stderr, "\n[%d] Une erreur est survenue dans la fonction %s : %s. ", Retour.Type, Retour.Fonction, Retour.Description);

		demander_chaine(Chaine);

		supprimer_chaine(&Chaine);
	}

	return Retour.Type;
}