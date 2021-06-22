#include "systeme.h"

/*	Cette source contient des fonctions qui permettent de gérer l'interaction avec le système d'exploitation.
La plupart exploitent <stdlib.h> notamment pour l'allocation de mémoire.
D'autres fonctions permettent de gérer les erreur ou les exceptions qui pourraient survenir.	*/



/*	Les fonctions qui suivent permettent de gérer l'évolution du programme.	*/


/*	Cette fonction reçoit un entier, quitte le programme et libère la mémoire.	*/

vide quitter_programme(entier Entier)
{
	exit(Entier);
}



/*	Les fonctions qui suivent vont créer dynamiquement un type.	*/


/*	Cette fonction reçoit l'adresse d'un pointeur vers un damier puis l'alloue.	*/

retour creer_damier(damier ** Damier)
{
	if ((*Damier = (damier *) malloc(sizeof(damier))) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
	{
		return structurer_retour(1, "creer_damier", "l'allocation ne s'est pas déroulée correctement");
	}
	else		//	L'allocation s'est déroulée correctement.
	{
		(*Damier)->Pion = NULL;

		(*Damier)->Lignes = 0;
		(*Damier)->Colonnes = 0;

		return structurer_retour(0, "creer_damier", "la fonction s'est correctement terminée");
	}
}

/*	Cette fonction reçoit l'adresse d'un pointeur vers une liste puis l'alloue.	*/

retour creer_liste(liste ** Liste)
{
	if ((*Liste = (liste *) malloc(sizeof(liste))) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
	{
		return structurer_retour(1, "creer_liste", "l'allocation ne s'est pas déroulée correctement");
	}
	else		//	L'allocation s'est déroulée correctement.
	{
		(*Liste)->Coup = NULL;

		(*Liste)->Prises = 0;
		(*Liste)->Nombre = 0;
		(*Liste)->Taille = 0;

		return structurer_retour(0, "creer_liste", "la fonction s'est correctement terminée");
	}
}

/*	Cette fonction reçoit l'adresse d'un pointeur vers un coup puis l'alloue.	*/

retour creer_coup(coup ** Coup)
{
	if ((*Coup = (coup *) malloc(sizeof(coup))) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
	{
		return structurer_retour(1, "creer_coup", "l'allocation ne s'est pas déroulée correctement");
	}
	else		//	L'allocation s'est déroulée correctement.
	{
		(*Coup)->Deplacements.Pion = NULL;
		(*Coup)->Prises.Pion = NULL;

		(*Coup)->Deplacements.Nombre = 0;
		(*Coup)->Deplacements.Taille = 0;

		(*Coup)->Prises.Nombre = 0;
		(*Coup)->Prises.Taille = 0;

		return structurer_retour(0, "creer_coup", "la fonction s'est correctement terminée");
	}
}

/*	Cette fonction reçoit l'adresse d'un pointeur vers un enregistrement puis l'alloue.	*/

retour creer_enregistrement(enregistrement ** Enregistrement)
{
	if ((*Enregistrement = (enregistrement *) malloc(sizeof(enregistrement))) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
	{
		return structurer_retour(1, "creer_enregistrement", "l'allocation ne s'est pas déroulée correctement");
	}
	else		//	L'allocation s'est déroulée correctement.
	{
		while (afficher_si_erreur(creer_damier(&(*Enregistrement)->Damier)))		//	La fonction ne peut pas se terminer sans avoir créé le damier.

		(*Enregistrement)->Deplacement = NULL;

		(*Enregistrement)->Coups = 0;
		(*Enregistrement)->Lecture = 0;
		(*Enregistrement)->Nombre = 0;
		(*Enregistrement)->Taille = 0;
		
		return structurer_retour(0, "creer_enregistrement", "la fonction s'est correctement terminée");
	}
}

/*	Cette fonction reçoit l'adresse d'un pointeur vers une chaine puis l'alloue.	*/

retour creer_chaine(chaine ** Chaine)
{
	if ((*Chaine = (chaine *) malloc(sizeof(chaine))) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
	{
		return structurer_retour(1, "creer_chaine", "l'allocation ne s'est pas déroulée correctement");
	}
	else		//	L'allocation s'est déroulée correctement.
	{
		(*Chaine)->Caractere = NULL;

		(*Chaine)->Nombre = 0;
		(*Chaine)->Taille = 0;

		return structurer_retour(0, "creer_chaine", "la fonction s'est correctement terminée");
	}
}



/*	Les fonctions qui suivent vont allouer dynamiquement le contenu d'un type.	*/


/*	Cette fonction va allouer de la place pour les pions sur le damier reçu.	*/

retour allouer_pions(damier * Damier, naturel Lignes, naturel Colonnes)
{
	if (Lignes > 1 && Colonnes > 2 && Lignes % 2 == 0 && Colonnes % 2 == 0)		//	Les dimensions reçues respectent les normes.
	{
		if ((Damier->Pion = (pion **) malloc(sizeof(pion) * Lignes)) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(2, "allouer_pions", "l'allocation des colonnes ne s'est pas déroulée correctement");
		}
		else		//	L'allocation s'est déroulée correctement.
		{
			Damier->Colonnes = Colonnes;

			for (naturel i = 0; i < Lignes; i++)		//	On alloue un tableau pour chaque ligne de notre tablau de pointeurs.
			{
				if ((Damier->Pion[i] = (pion *) malloc(sizeof(pion) * Colonnes)) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
				{
					return structurer_retour(3, "allouer_pions", "l'allocation d'une ligne ne s'est pas déroulée correctement");
				}
				else		//	L'allocation s'est déroulée correctement.
				{
					for (naturel j = 0; j < Colonnes; j++)
					{
						Damier->Pion[i][j] = structurer_piece(PERSONNE, VIDE, structurer_position(i, j));
					}
				}
			}

			Damier->Lignes = Lignes;

			return structurer_retour(0, "allouer_pions", "la fonction s'est correctement terminée");
		}
	}
	else
	{
		return structurer_retour(1, "allouer_pions", "les dimensions reçues ne sont pas autorisées");
	}
}

/*	Cette fonction va allouer de la place pour des coups sur la liste reçue.	*/

retour allouer_coups(liste * Liste, naturel Taille)
{
	if (Liste->Taille)		//	Les coups ont déjà été alloués.
	{
		coup ** Coup;

		if ((Coup = (coup **) realloc(Liste->Coup, sizeof(coup) * Taille)) == NULL)		//	La réallocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(1, "allouer_coups", "la réallocation ne s'est pas déroulée correctement");
		}
		else		//	La réallocation s'est déroulée correctement.
		{
			Liste->Coup = Coup;

			Liste->Taille = Taille;

			return structurer_retour(0, "allouer_coups", "la fonction s'est correctement terminée");
		}
	}
	else		//	La liste n'a pas encore été allouée.
	{
		if ((Liste->Coup = (coup **) malloc(sizeof(coup) * Taille)) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(2, "allouer_coups", "l'allocation ne s'est pas déroulée correctement");
		}
		else		//	L'allocation s'est déroulée correctement.
		{
			Liste->Taille = Taille;

			return structurer_retour(0, "allouer_coups", "la fonction s'est correctement terminée");
		}
	}
}

/*	Cette fonction va allouer de la place pour les déplacements d'un coup.	*/

retour allouer_deplacements(coup * Coup, naturel Taille)
{
	if (Coup->Deplacements.Taille)		//	Les déplacements ont déjà été alloués.
	{
		pion * Pion;

		if ((Pion = (pion *)realloc(Coup->Deplacements.Pion, sizeof(pion) * Taille)) == NULL)		//	La réallocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(1, "allouer_deplacements", "la réallocation ne s'est pas déroulée correctement");
		}
		else		//	La réallocation s'est déroulée correctement.
		{
			Coup->Deplacements.Pion = Pion;

			Coup->Deplacements.Taille = Taille;

			return structurer_retour(0, "allouer_deplacements", "la fonction s'est correctement terminée");
		}
	}
	else		//	Les déplacements n'ont pas encore été alloués.
	{
		if ((Coup->Deplacements.Pion = (pion *)malloc(sizeof(pion) * Taille)) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(2, "allouer_deplacements", "l'allocation ne s'est pas déroulée correctement");
		}
		else		//	L'allocation s'est déroulée correctement.
		{
			Coup->Deplacements.Taille = Taille;

			return structurer_retour(0, "allouer_deplacements", "la fonction s'est correctement terminée");
		}
	}
}

/*	Cette fonction va allouer de la place pour les prises d'un coup.	*/

retour allouer_prises(coup * Coup, naturel Taille)
{
	if (Coup->Prises.Taille)		//	Les prises ont déjà été allouées.
	{
		pion * Pion;

		if ((Pion = (pion *)realloc(Coup->Prises.Pion, sizeof(pion) * Taille)) == NULL)		//	La réallocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(1, "allouer_prises", "la réallocation ne s'est pas déroulée correctement");
		}
		else		//	La réallocation s'est déroulée correctement.
		{
			Coup->Prises.Pion = Pion;

			Coup->Prises.Taille = Taille;

			return structurer_retour(0, "allouer_prises", "la fonction s'est correctement terminée");
		}
	}
	else		//	Les prises n'ont pas encore été allouées.
	{
		if ((Coup->Prises.Pion = (pion *)malloc(sizeof(pion) * Taille)) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(2, "allouer_prises", "l'allocation ne s'est pas déroulée correctement");
		}
		else		//	L'allocation s'est déroulée correctement.
		{
			Coup->Prises.Taille = Taille;

			return structurer_retour(0, "allouer_prises", "la fonction s'est correctement terminée");
		}
	}
}

/*	Cette fonction va allouer de la place pour enregistrer les coups joués.	*/

retour allouer_enregistrements(enregistrement * Enregistrement, naturel Taille)
{
	if (Enregistrement->Taille)		//	La liste a déjà été allouée.
	{
		naturel * Naturel;

		if ((Naturel = (naturel *) realloc(Enregistrement->Deplacement, sizeof(naturel) * Taille)) == NULL)		//	La réallocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(1, "allouer_enregistrements", "la réallocation ne s'est pas déroulée correctement");
		}
		else		//	La réallocation s'est déroulée correctement.
		{
			Enregistrement->Deplacement = Naturel;

			Enregistrement->Taille = Taille;

			return structurer_retour(0, "allouer_enregistrements", "la fonction s'est correctement terminée");
		}
	}
	else		//	La liste n'a pas encore été allouée.
	{
		if ((Enregistrement->Deplacement = (naturel *) malloc(sizeof(naturel) * Taille)) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(2, "allouer_enregistrements", "l'allocation ne s'est pas déroulée correctement");
		}
		else		//	L'allocation s'est déroulée correctement.
		{
			Enregistrement->Taille = Taille;

			return structurer_retour(0, "", "la fonction s'est correctement terminée");
		}
	}
}

/*	Cette fonction va allouer de la place pour les caractères de la chaîne.	*/

retour allouer_caracteres(chaine * Chaine, naturel Taille)
{
	if (Chaine->Taille)		//	Les caractères ont déjà été alloués.
	{
		caractere * Caractere;

		if ((Caractere = (caractere *) realloc(Chaine->Caractere, sizeof(caractere) * Taille)) == NULL)		//	La réallocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(1, "allouer_caracteres", "la réallocation ne s'est pas déroulée correctement");
		}
		else		//	La réallocation s'est déroulée correctement.
		{
			Chaine->Caractere = Caractere;

			Chaine->Taille = Taille;

			return structurer_retour(0, "allouer_caracteres", "la fonction s'est correctement terminée");
		}
	}
	else		//	Les caractères n'ont pas encore été alloués.
	{
		if ((Chaine->Caractere = (caractere *) malloc(sizeof(caractere) * Taille)) == NULL)		//	L'allocation ne s'est pas déroulée correctement.
		{
			return structurer_retour(2, "allouer_caracteres", "l'allocation ne s'est pas déroulée correctement");
		}
		else		//	L'allocation s'est déroulée correctement.
		{
			Chaine->Taille = Taille;

			return structurer_retour(0, "allouer_caracteres", "la fonction s'est correctement terminée");
		}
	}
}



/*	Les fonctions qui suivent vont libérer le contenu d'un type.	*/


/*	Cette fontion reçoit un damier et va libérer les pions qu'il contient.	*/

vide liberer_pions(damier * Damier)
{
	if (Damier->Lignes > 0 && Damier->Colonnes > 0)		//	Les pions ont déjà été alloués.
	{
		for (naturel i = 0; i < Damier->Lignes; i++)		//	On commence par libérer chaque ligne du tableau de pointeurs.
		{
			free(Damier->Pion[i]);
			Damier->Pion[i] = NULL;
		}

		free(Damier->Pion);
		Damier->Pion = NULL;

		Damier->Lignes = 0;
		Damier->Colonnes = 0;
	}
}

/*	Cette fonction reçoit une liste et va libérer et supprimer les coups qu'elle contient.	*/

vide liberer_coups(liste * Liste)
{
	if (Liste->Taille)		//	La liste a déjà été allouée.
	{
		for (naturel i = 0; i < Liste->Nombre; i++)
		{
			supprimer_coup(&Liste->Coup[i]);
		}

		free(Liste->Coup);
		Liste->Coup = NULL;

		Liste->Prises = 0;
		Liste->Nombre = 0;
		Liste->Taille = 0;
	}
}

/*	Cette fonction reçoit un coup et va libérer les déplacements qu'elle contient.	*/

vide liberer_deplacements(coup * Coup)
{
	if (Coup->Deplacements.Taille)		//	Les déplacements ont déjà été alloués.
	{
		free(Coup->Deplacements.Pion);
		Coup->Deplacements.Pion = NULL;

		Coup->Deplacements.Nombre = 0;
		Coup->Deplacements.Taille = 0;
	}
}

/*	Cette fonction reçoit un coup et va libérer les prises qu'elle contient.	*/

vide liberer_prises(coup * Coup)
{
	if (Coup->Prises.Taille)		//	Les prises ont déjà été allouées.
	{
		free(Coup->Prises.Pion);
		Coup->Prises.Pion = NULL;

		Coup->Prises.Nombre = 0;
		Coup->Prises.Taille = 0;
	}
}

/*	Cette fonction reçoit un enregistrement et va libérer les coups qu'il contient.	*/

vide liberer_enregistrements(enregistrement * Enregistrement)
{
	if (Enregistrement->Taille)		//	Les enregistrements ont déjà été alloués.
	{
		free(Enregistrement->Deplacement);
		Enregistrement->Deplacement = NULL;

		Enregistrement->Lecture = 0;
		Enregistrement->Nombre = 0;
		Enregistrement->Taille = 0;
	}
}

/*	Cette fonction reçoit une chaîne et va libérer les caractères qu'elle contient.	*/

vide liberer_caracteres(chaine * Chaine)
{
	if (Chaine->Taille)		//	Les caractères ont déjà été alloués.
	{
		free(Chaine->Caractere);
		Chaine->Caractere = NULL;

		Chaine->Nombre = 0;
		Chaine->Taille = 0;
	}
}



/*	Les fonctions qui suivent vont supprimer un type.	*/


/*	Cette fonction va supprimer le damier reçu et son contenu.	*/

vide supprimer_damier(damier ** Damier)
{
	liberer_pions(*Damier);

	free(*Damier);
	*Damier = NULL;
}

/*	Cette fonction va supprimer la liste reçue et son contenu.	*/

vide supprimer_liste(liste ** Liste)
{
	liberer_coups(*Liste);

	free(*Liste);
	*Liste = NULL;
}

/*	Cette fonction va supprimer le coup reçu et son contenu.	*/

vide supprimer_coup(coup ** Coup)
{
	liberer_deplacements(*Coup);
	liberer_prises(*Coup);

	free(*Coup);
	*Coup = NULL;
}

/*	Cette fonction va supprimer la liste reçue et son contenu.	*/

vide supprimer_enregistrement(enregistrement ** Enregistrement)
{
	liberer_enregistrements(*Enregistrement);
	supprimer_damier(&(*Enregistrement)->Damier);

	free(*Enregistrement);
	*Enregistrement = NULL;
}

/*	Cette fonction va supprimer la chaîne reçue et son contenu.	*/

vide supprimer_chaine(chaine ** Chaine)
{
	liberer_caracteres(*Chaine);

	free(*Chaine);
	*Chaine = NULL;
}