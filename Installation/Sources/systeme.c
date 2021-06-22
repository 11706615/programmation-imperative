#include "systeme.h"

/*	Cette source contient des fonctions qui permettent de g�rer l'interaction avec le syst�me d'exploitation.
La plupart exploitent <stdlib.h> notamment pour l'allocation de m�moire.
D'autres fonctions permettent de g�rer les erreur ou les exceptions qui pourraient survenir.	*/



/*	Les fonctions qui suivent permettent de g�rer l'�volution du programme.	*/


/*	Cette fonction re�oit un entier, quitte le programme et lib�re la m�moire.	*/

vide quitter_programme(entier Entier)
{
	exit(Entier);
}



/*	Les fonctions qui suivent vont cr�er dynamiquement un type.	*/


/*	Cette fonction re�oit l'adresse d'un pointeur vers un damier puis l'alloue.	*/

retour creer_damier(damier ** Damier)
{
	if ((*Damier = (damier *) malloc(sizeof(damier))) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
	{
		return structurer_retour(1, "creer_damier", "l'allocation ne s'est pas d�roul�e correctement");
	}
	else		//	L'allocation s'est d�roul�e correctement.
	{
		(*Damier)->Pion = NULL;

		(*Damier)->Lignes = 0;
		(*Damier)->Colonnes = 0;

		return structurer_retour(0, "creer_damier", "la fonction s'est correctement termin�e");
	}
}

/*	Cette fonction re�oit l'adresse d'un pointeur vers une liste puis l'alloue.	*/

retour creer_liste(liste ** Liste)
{
	if ((*Liste = (liste *) malloc(sizeof(liste))) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
	{
		return structurer_retour(1, "creer_liste", "l'allocation ne s'est pas d�roul�e correctement");
	}
	else		//	L'allocation s'est d�roul�e correctement.
	{
		(*Liste)->Coup = NULL;

		(*Liste)->Prises = 0;
		(*Liste)->Nombre = 0;
		(*Liste)->Taille = 0;

		return structurer_retour(0, "creer_liste", "la fonction s'est correctement termin�e");
	}
}

/*	Cette fonction re�oit l'adresse d'un pointeur vers un coup puis l'alloue.	*/

retour creer_coup(coup ** Coup)
{
	if ((*Coup = (coup *) malloc(sizeof(coup))) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
	{
		return structurer_retour(1, "creer_coup", "l'allocation ne s'est pas d�roul�e correctement");
	}
	else		//	L'allocation s'est d�roul�e correctement.
	{
		(*Coup)->Deplacements.Pion = NULL;
		(*Coup)->Prises.Pion = NULL;

		(*Coup)->Deplacements.Nombre = 0;
		(*Coup)->Deplacements.Taille = 0;

		(*Coup)->Prises.Nombre = 0;
		(*Coup)->Prises.Taille = 0;

		return structurer_retour(0, "creer_coup", "la fonction s'est correctement termin�e");
	}
}

/*	Cette fonction re�oit l'adresse d'un pointeur vers un enregistrement puis l'alloue.	*/

retour creer_enregistrement(enregistrement ** Enregistrement)
{
	if ((*Enregistrement = (enregistrement *) malloc(sizeof(enregistrement))) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
	{
		return structurer_retour(1, "creer_enregistrement", "l'allocation ne s'est pas d�roul�e correctement");
	}
	else		//	L'allocation s'est d�roul�e correctement.
	{
		while (afficher_si_erreur(creer_damier(&(*Enregistrement)->Damier)))		//	La fonction ne peut pas se terminer sans avoir cr�� le damier.

		(*Enregistrement)->Deplacement = NULL;

		(*Enregistrement)->Coups = 0;
		(*Enregistrement)->Lecture = 0;
		(*Enregistrement)->Nombre = 0;
		(*Enregistrement)->Taille = 0;
		
		return structurer_retour(0, "creer_enregistrement", "la fonction s'est correctement termin�e");
	}
}

/*	Cette fonction re�oit l'adresse d'un pointeur vers une chaine puis l'alloue.	*/

retour creer_chaine(chaine ** Chaine)
{
	if ((*Chaine = (chaine *) malloc(sizeof(chaine))) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
	{
		return structurer_retour(1, "creer_chaine", "l'allocation ne s'est pas d�roul�e correctement");
	}
	else		//	L'allocation s'est d�roul�e correctement.
	{
		(*Chaine)->Caractere = NULL;

		(*Chaine)->Nombre = 0;
		(*Chaine)->Taille = 0;

		return structurer_retour(0, "creer_chaine", "la fonction s'est correctement termin�e");
	}
}



/*	Les fonctions qui suivent vont allouer dynamiquement le contenu d'un type.	*/


/*	Cette fonction va allouer de la place pour les pions sur le damier re�u.	*/

retour allouer_pions(damier * Damier, naturel Lignes, naturel Colonnes)
{
	if (Lignes > 1 && Colonnes > 2 && Lignes % 2 == 0 && Colonnes % 2 == 0)		//	Les dimensions re�ues respectent les normes.
	{
		if ((Damier->Pion = (pion **) malloc(sizeof(pion) * Lignes)) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(2, "allouer_pions", "l'allocation des colonnes ne s'est pas d�roul�e correctement");
		}
		else		//	L'allocation s'est d�roul�e correctement.
		{
			Damier->Colonnes = Colonnes;

			for (naturel i = 0; i < Lignes; i++)		//	On alloue un tableau pour chaque ligne de notre tablau de pointeurs.
			{
				if ((Damier->Pion[i] = (pion *) malloc(sizeof(pion) * Colonnes)) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
				{
					return structurer_retour(3, "allouer_pions", "l'allocation d'une ligne ne s'est pas d�roul�e correctement");
				}
				else		//	L'allocation s'est d�roul�e correctement.
				{
					for (naturel j = 0; j < Colonnes; j++)
					{
						Damier->Pion[i][j] = structurer_piece(PERSONNE, VIDE, structurer_position(i, j));
					}
				}
			}

			Damier->Lignes = Lignes;

			return structurer_retour(0, "allouer_pions", "la fonction s'est correctement termin�e");
		}
	}
	else
	{
		return structurer_retour(1, "allouer_pions", "les dimensions re�ues ne sont pas autoris�es");
	}
}

/*	Cette fonction va allouer de la place pour des coups sur la liste re�ue.	*/

retour allouer_coups(liste * Liste, naturel Taille)
{
	if (Liste->Taille)		//	Les coups ont d�j� �t� allou�s.
	{
		coup ** Coup;

		if ((Coup = (coup **) realloc(Liste->Coup, sizeof(coup) * Taille)) == NULL)		//	La r�allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(1, "allouer_coups", "la r�allocation ne s'est pas d�roul�e correctement");
		}
		else		//	La r�allocation s'est d�roul�e correctement.
		{
			Liste->Coup = Coup;

			Liste->Taille = Taille;

			return structurer_retour(0, "allouer_coups", "la fonction s'est correctement termin�e");
		}
	}
	else		//	La liste n'a pas encore �t� allou�e.
	{
		if ((Liste->Coup = (coup **) malloc(sizeof(coup) * Taille)) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(2, "allouer_coups", "l'allocation ne s'est pas d�roul�e correctement");
		}
		else		//	L'allocation s'est d�roul�e correctement.
		{
			Liste->Taille = Taille;

			return structurer_retour(0, "allouer_coups", "la fonction s'est correctement termin�e");
		}
	}
}

/*	Cette fonction va allouer de la place pour les d�placements d'un coup.	*/

retour allouer_deplacements(coup * Coup, naturel Taille)
{
	if (Coup->Deplacements.Taille)		//	Les d�placements ont d�j� �t� allou�s.
	{
		pion * Pion;

		if ((Pion = (pion *)realloc(Coup->Deplacements.Pion, sizeof(pion) * Taille)) == NULL)		//	La r�allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(1, "allouer_deplacements", "la r�allocation ne s'est pas d�roul�e correctement");
		}
		else		//	La r�allocation s'est d�roul�e correctement.
		{
			Coup->Deplacements.Pion = Pion;

			Coup->Deplacements.Taille = Taille;

			return structurer_retour(0, "allouer_deplacements", "la fonction s'est correctement termin�e");
		}
	}
	else		//	Les d�placements n'ont pas encore �t� allou�s.
	{
		if ((Coup->Deplacements.Pion = (pion *)malloc(sizeof(pion) * Taille)) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(2, "allouer_deplacements", "l'allocation ne s'est pas d�roul�e correctement");
		}
		else		//	L'allocation s'est d�roul�e correctement.
		{
			Coup->Deplacements.Taille = Taille;

			return structurer_retour(0, "allouer_deplacements", "la fonction s'est correctement termin�e");
		}
	}
}

/*	Cette fonction va allouer de la place pour les prises d'un coup.	*/

retour allouer_prises(coup * Coup, naturel Taille)
{
	if (Coup->Prises.Taille)		//	Les prises ont d�j� �t� allou�es.
	{
		pion * Pion;

		if ((Pion = (pion *)realloc(Coup->Prises.Pion, sizeof(pion) * Taille)) == NULL)		//	La r�allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(1, "allouer_prises", "la r�allocation ne s'est pas d�roul�e correctement");
		}
		else		//	La r�allocation s'est d�roul�e correctement.
		{
			Coup->Prises.Pion = Pion;

			Coup->Prises.Taille = Taille;

			return structurer_retour(0, "allouer_prises", "la fonction s'est correctement termin�e");
		}
	}
	else		//	Les prises n'ont pas encore �t� allou�es.
	{
		if ((Coup->Prises.Pion = (pion *)malloc(sizeof(pion) * Taille)) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(2, "allouer_prises", "l'allocation ne s'est pas d�roul�e correctement");
		}
		else		//	L'allocation s'est d�roul�e correctement.
		{
			Coup->Prises.Taille = Taille;

			return structurer_retour(0, "allouer_prises", "la fonction s'est correctement termin�e");
		}
	}
}

/*	Cette fonction va allouer de la place pour enregistrer les coups jou�s.	*/

retour allouer_enregistrements(enregistrement * Enregistrement, naturel Taille)
{
	if (Enregistrement->Taille)		//	La liste a d�j� �t� allou�e.
	{
		naturel * Naturel;

		if ((Naturel = (naturel *) realloc(Enregistrement->Deplacement, sizeof(naturel) * Taille)) == NULL)		//	La r�allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(1, "allouer_enregistrements", "la r�allocation ne s'est pas d�roul�e correctement");
		}
		else		//	La r�allocation s'est d�roul�e correctement.
		{
			Enregistrement->Deplacement = Naturel;

			Enregistrement->Taille = Taille;

			return structurer_retour(0, "allouer_enregistrements", "la fonction s'est correctement termin�e");
		}
	}
	else		//	La liste n'a pas encore �t� allou�e.
	{
		if ((Enregistrement->Deplacement = (naturel *) malloc(sizeof(naturel) * Taille)) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(2, "allouer_enregistrements", "l'allocation ne s'est pas d�roul�e correctement");
		}
		else		//	L'allocation s'est d�roul�e correctement.
		{
			Enregistrement->Taille = Taille;

			return structurer_retour(0, "", "la fonction s'est correctement termin�e");
		}
	}
}

/*	Cette fonction va allouer de la place pour les caract�res de la cha�ne.	*/

retour allouer_caracteres(chaine * Chaine, naturel Taille)
{
	if (Chaine->Taille)		//	Les caract�res ont d�j� �t� allou�s.
	{
		caractere * Caractere;

		if ((Caractere = (caractere *) realloc(Chaine->Caractere, sizeof(caractere) * Taille)) == NULL)		//	La r�allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(1, "allouer_caracteres", "la r�allocation ne s'est pas d�roul�e correctement");
		}
		else		//	La r�allocation s'est d�roul�e correctement.
		{
			Chaine->Caractere = Caractere;

			Chaine->Taille = Taille;

			return structurer_retour(0, "allouer_caracteres", "la fonction s'est correctement termin�e");
		}
	}
	else		//	Les caract�res n'ont pas encore �t� allou�s.
	{
		if ((Chaine->Caractere = (caractere *) malloc(sizeof(caractere) * Taille)) == NULL)		//	L'allocation ne s'est pas d�roul�e correctement.
		{
			return structurer_retour(2, "allouer_caracteres", "l'allocation ne s'est pas d�roul�e correctement");
		}
		else		//	L'allocation s'est d�roul�e correctement.
		{
			Chaine->Taille = Taille;

			return structurer_retour(0, "allouer_caracteres", "la fonction s'est correctement termin�e");
		}
	}
}



/*	Les fonctions qui suivent vont lib�rer le contenu d'un type.	*/


/*	Cette fontion re�oit un damier et va lib�rer les pions qu'il contient.	*/

vide liberer_pions(damier * Damier)
{
	if (Damier->Lignes > 0 && Damier->Colonnes > 0)		//	Les pions ont d�j� �t� allou�s.
	{
		for (naturel i = 0; i < Damier->Lignes; i++)		//	On commence par lib�rer chaque ligne du tableau de pointeurs.
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

/*	Cette fonction re�oit une liste et va lib�rer et supprimer les coups qu'elle contient.	*/

vide liberer_coups(liste * Liste)
{
	if (Liste->Taille)		//	La liste a d�j� �t� allou�e.
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

/*	Cette fonction re�oit un coup et va lib�rer les d�placements qu'elle contient.	*/

vide liberer_deplacements(coup * Coup)
{
	if (Coup->Deplacements.Taille)		//	Les d�placements ont d�j� �t� allou�s.
	{
		free(Coup->Deplacements.Pion);
		Coup->Deplacements.Pion = NULL;

		Coup->Deplacements.Nombre = 0;
		Coup->Deplacements.Taille = 0;
	}
}

/*	Cette fonction re�oit un coup et va lib�rer les prises qu'elle contient.	*/

vide liberer_prises(coup * Coup)
{
	if (Coup->Prises.Taille)		//	Les prises ont d�j� �t� allou�es.
	{
		free(Coup->Prises.Pion);
		Coup->Prises.Pion = NULL;

		Coup->Prises.Nombre = 0;
		Coup->Prises.Taille = 0;
	}
}

/*	Cette fonction re�oit un enregistrement et va lib�rer les coups qu'il contient.	*/

vide liberer_enregistrements(enregistrement * Enregistrement)
{
	if (Enregistrement->Taille)		//	Les enregistrements ont d�j� �t� allou�s.
	{
		free(Enregistrement->Deplacement);
		Enregistrement->Deplacement = NULL;

		Enregistrement->Lecture = 0;
		Enregistrement->Nombre = 0;
		Enregistrement->Taille = 0;
	}
}

/*	Cette fonction re�oit une cha�ne et va lib�rer les caract�res qu'elle contient.	*/

vide liberer_caracteres(chaine * Chaine)
{
	if (Chaine->Taille)		//	Les caract�res ont d�j� �t� allou�s.
	{
		free(Chaine->Caractere);
		Chaine->Caractere = NULL;

		Chaine->Nombre = 0;
		Chaine->Taille = 0;
	}
}



/*	Les fonctions qui suivent vont supprimer un type.	*/


/*	Cette fonction va supprimer le damier re�u et son contenu.	*/

vide supprimer_damier(damier ** Damier)
{
	liberer_pions(*Damier);

	free(*Damier);
	*Damier = NULL;
}

/*	Cette fonction va supprimer la liste re�ue et son contenu.	*/

vide supprimer_liste(liste ** Liste)
{
	liberer_coups(*Liste);

	free(*Liste);
	*Liste = NULL;
}

/*	Cette fonction va supprimer le coup re�u et son contenu.	*/

vide supprimer_coup(coup ** Coup)
{
	liberer_deplacements(*Coup);
	liberer_prises(*Coup);

	free(*Coup);
	*Coup = NULL;
}

/*	Cette fonction va supprimer la liste re�ue et son contenu.	*/

vide supprimer_enregistrement(enregistrement ** Enregistrement)
{
	liberer_enregistrements(*Enregistrement);
	supprimer_damier(&(*Enregistrement)->Damier);

	free(*Enregistrement);
	*Enregistrement = NULL;
}

/*	Cette fonction va supprimer la cha�ne re�ue et son contenu.	*/

vide supprimer_chaine(chaine ** Chaine)
{
	liberer_caracteres(*Chaine);

	free(*Chaine);
	*Chaine = NULL;
}