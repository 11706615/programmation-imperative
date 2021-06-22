#include "dames.h"

/*	Cette source contient le code propre au jeu de dames.	*/



/*	Les fonctions qui suivent permettent d'obtenir un élément depuis un type.	*/


/*	Cette fonction permet d'obtenir la majuscule associée au caractère reçu.	*/

caractere obtenir_majuscule_depuis_caractere(caractere Caractere)
{
	if (Caractere >= 'a' && Caractere <= 'z')		//	Le caractère reçu est bien une lettre minuscule.
	{
		return Caractere += 'A' - 'a';
	}

	return Caractere;
}

/*	Cette fonction permet d'obtenir la majuscule associée à sa position dans l'alphabet.	*/

caractere obtenir_majuscule_depuis_naturel(naturel Naturel)
{
	if (Naturel < 26)		//	Une lettre peut être affichée.
	{
		return 'A' + Naturel;
	}
	else		//	Aucun caractère ne correspond.
	{
		return ' ';
	}
}

/*	Cette fonction permet d'obtenir un caractère de la chaine.	*/

caractere obtenir_caractere_depuis_chaine(chaine Chaine, naturel Naturel)
{
	if (Naturel < Chaine.Nombre)		//	Le caractère demandé existe.
	{
		return Chaine.Caractere[Naturel];
	}

	return '\0';
}

/*	Cette fonction permet d'obtenir un naturel depuis une chaîne.	*/

naturel obtenir_naturel_depuis_chaine(chaine Chaine)
{
	naturel Retour = 0;
	naturel Naturel = 1;

	for (naturel i = Chaine.Nombre; i > 0; i--)		//	On parcourt la chaîne en partant du dernier élément.
	{
		Retour += Naturel * obtenir_naturel_depuis_caractere(obtenir_caractere_depuis_chaine(Chaine, i - 1));
		Naturel *= 10;
	}

	return Retour;
}

/*	Cette fonction permet d'obtenir un naturel depuis un caractère.	*/

naturel obtenir_naturel_depuis_caractere(caractere Caractere)
{
	if (Caractere >= '0' && Caractere <= '9')		//	Le caractère reçu est bien un chiffre.
	{
		return Caractere - '0';
	}

	return 0;
}

/*	Cette fonction permet d'obtenir un joueur à partir d'un caractère.	*/

joueur obtenir_joueur_depuis_caractere(caractere Caractere)
{
	switch (Caractere)		//	On regarde le caractère reçu.
	{
	case 'N':
		return NOIR;
	case 'n':
		return NOIR;
	case 'b':
		return BLANC;
	case 'B':
		return BLANC;
	default:
		return PERSONNE;
	}
}

/*	Cette fonction permet d'obtenir un type à partir d'un caractère.	*/

type obtenir_type_depuis_caractere(caractere Caractere)
{
	switch (Caractere)		//	On regarde le caactère reçu.
	{
	case 'N':
		return DAME;
	case 'n':
		return PION;
	case 'b':
		return PION;
	case 'B':
		return DAME;
	default:
		return VIDE;
	}
}

/*	Cette fonction permet d'obtenir une pièce à partir d'un caractère et d'une position.	*/

pion obtenir_piece_depuis_caractere(caractere Caractere, position Position)
{
	pion Pion;

	Pion.Joueur = obtenir_joueur_depuis_caractere(Caractere);
	Pion.Type = obtenir_type_depuis_caractere(Caractere);
	Pion.Position = Position;

	return Pion;
}

/*	Cette fonction permet d'obtenir le caractère à afficher en fonction d'une pièce.	*/

caractere obtenir_caractere_depuis_piece(pion Pion)
{
	switch (Pion.Joueur * Pion.Type)		//	On regarde le propriétaire et le type du pion reçu.
	{
	case -2:
		return 'N';
	case -1:
		return 'n';
	case 1:
		return 'b';
	case 2:
		return 'B';
	default:
		return ' ';
	}
}

/*	Cette fonction permet d'obtenir la pièce placée à la position reçue.	*/

pion obtenir_piece_depuis_damier(damier Damier, position Position)
{
	if (verifier_position(Damier, Position))		//	La position appartient au damier.
	{
		return Damier.Pion[Position.Ligne][Position.Colonne];
	}
	else		// La position n'appartient pas au damier.
	{
		return structurer_piece(PERSONNE, VIDE, Position);
	}
}

/*	Cette fonction permet d'obtenir le joueur placé à la position reçue.	*/

joueur obtenir_joueur_depuis_damier(damier Damier, position Position)
{
	return obtenir_piece_depuis_damier(Damier, Position).Joueur;
}

/*	Cette fonction permet d'obtenir le type placé à la position reçue.	*/

type obtenir_type_depuis_damier(damier Damier, position Position)
{
	return obtenir_piece_depuis_damier(Damier, Position).Type;
}

/*	Cette fonction permet d'obtenir le type placé à la position reçue.	*/

pion obtenir_source_depuis_coup(coup Coup)
{
	return Coup.Deplacements.Pion[0];
}

pion obtenir_destination_depuis_coup(coup Coup)
{
	return Coup.Deplacements.Pion[Coup.Deplacements.Nombre - 1];
}



/*	Les fonctions qui suivent permettent de retourner une structure.	*/


/*	Cette fonction retourne un type position.	*/

position structurer_position(naturel Ligne, naturel Colonne)
{
	position Position;

	Position.Ligne = Ligne;
	Position.Colonne = Colonne;

	return Position;
}

/*	Cette fonction retourne un type pièce.	*/

pion structurer_piece(joueur Joueur, type Type, position Position)
{
	pion Pion;

	Pion.Joueur = Joueur;
	Pion.Type = Type;
	Pion.Position = Position;

	return Pion;
}

/*	Cette fonction retourne un type retour.	*/

retour structurer_retour(entier Type, const caractere * Fonction, const caractere * Description)
{
	retour Retour;

	Retour.Type = Type;
	Retour.Fonction = Fonction;
	Retour.Description = Description;

	return Retour;
}



/*	Les fonctions qui suivent effectuent des vérifications.	*/


/* Cette fonction indique si la position reçue est correcte. */

booleen verifier_position(damier Damier, position Position)
{
	naturel Ligne = Position.Ligne;
	naturel Colonne = Position.Colonne;

	if (Ligne >= 0 && Colonne >= 0 && Ligne < Damier.Lignes && Colonne < Damier.Colonnes && (Ligne + Colonne) % 2 == 0)		//	La position appartient au damier.
	{
		return OUI;
	}
	else		// La position n'appartient pas au damier.
	{
		return NON;
	}
}

/*	Cette fonction indique si la pièce reçue existe.	*/

booleen verifier_piece(pion Pion)
{
	if (Pion.Joueur == PERSONNE || Pion.Type == VIDE)		//	Au moins un des attributs de la pièce indique qu'elle n'existe pas.
	{
		return NON;
	}
	else		//	La pièce existe.
	{
		return OUI;
	}
}

/*	Cette fonction indique si la pièce reçue n'a pas déjà été prise.	*/

booleen verifier_prise(coup Coup, pion Pion)
{
	for (naturel i = 0; i < Coup.Prises.Nombre; i++)		//	On parcourt la liste des prises.
	{
		if (Coup.Prises.Pion[i].Position.Ligne == Pion.Position.Ligne && Coup.Prises.Pion[i].Position.Colonne == Pion.Position.Colonne)		//	La pièce a déjà été prise.
		{
			return NON;
		}
	}

	return OUI;
}

/*	Cette fonction indique si le coup demandé existe.	*/

booleen verifier_coup(liste Liste, naturel Naturel)
{
	if (Naturel < Liste.Nombre)		//	Le nombre saisi est correct.
	{
		return OUI;
	}
	else		//	Le nombre saisi est incorrect.
	{
		return NON;
	}
}

/*	Cette fonction indique si la chaîne reçue contient au moins un caractère.	*/

booleen verifier_chaine(chaine Chaine)
{
	if (Chaine.Nombre)		//	La chaîne comporte des caractères.
	{
		return OUI;
	}
	else		//	La chaîne est vide.
	{
		return NON;
	}
}

/*	Cette fonction indique si la fonction a retourné une erreur ou non.	*/

booleen verifier_retour(retour Retour)
{
	if (Retour.Type)		//	Une erreur a été retournée.
	{
		return OUI;
	}
	else		//	Aucune erreur a été retournée.
	{
		return NON;
	}
}



/*	Les fonctions qui suivent vont réaliser une initialisation.	*/


/*	Cette fonction initialise la partie.	*/

vide initialiser_partie(damier * Damier, liste * Liste, enregistrement * Enregistrement, joueur * Joueur, etat * Etat)
{
	copier_damier(Damier, *Enregistrement->Damier);

	Enregistrement->Lecture = 0;

	*Joueur = BLANC;

	*Etat = JEU;

	identifier_coups_joueur(Damier, Liste, *Joueur);
}

/*	Cette fonction initialise le damier reçu avec une configuration classique.	*/

vide initialiser_damier(damier * Damier)
{
	for (naturel i = 0; i < Damier->Lignes; i++)		//	On parcourt les lignes du damier.
	{
		for (naturel j = 0; j < Damier->Colonnes; j++)		//	On parcourt les colonnes du damier.
		{
			if ((i + j) % 2 == 0)		//	On peut placer un pion sur cette case.
			{
				if (i < (Damier->Lignes / 2) - 1)		//	On se trouve dans la partie inférieure du damier.
				{
					Damier->Pion[i][j] = structurer_piece(BLANC, PION, structurer_position(i, j));
				}

				if (i >(Damier->Lignes / 2))		//	On se trouve dans la partie supérieure du damier.
				{
					Damier->Pion[i][j] = structurer_piece(NOIR, PION, structurer_position(i, j));
				}
			}
		}
	}
}

/*	Cette fonction initialise une chaîne.	*/

vide initialiser_chaine(chaine * Chaine)
{
	quitter_si_erreur(allouer_caracteres(Chaine, 1));

	Chaine->Caractere[0] = '\0';

	Chaine->Nombre = 0;
}



/*	Les fonctions qui suivent modifient les pièces du damier.	*/


/*	Cette fonction reçoit des informations et place un pion sur le damier reçu.	*/

retour placer_piece(damier * Damier, pion Pion)
{
	position Position = Pion.Position;

	if (verifier_position(*Damier, Position))
	{
		Damier->Pion[Position.Ligne][Position.Colonne] = Pion;

		return structurer_retour(0, "placer_piece", "la fonction s'est correctement terminée");
	}
	else
	{
		return structurer_retour(1, "placer_piece", "la case reçue ne peut pas contenir de pion");
	}
}

/*	Cette fonction reçoit des informations et retire un pion sur le damier reçu.	*/

retour retirer_piece(damier * Damier, pion Pion)
{
	position Position = Pion.Position;

	if (verifier_position(*Damier, Position))
	{
		Damier->Pion[Position.Ligne][Position.Colonne] = structurer_piece(PERSONNE, VIDE, Position);

		return structurer_retour(0, "retirer_piece", "la fonction s'est correctement terminée");
	}
	else
	{
		return structurer_retour(1, "retirer_piece", "la case reçue ne peut pas contenir de pion");
	}
}



/*	Les fonctions qui suivent effectuent un coup sur le damier.	*/


/*	Cette fonctions va déplacer la pièce.	*/

vide deplacer_piece(damier * Damier, pion Source, pion Destination)
{
	afficher_si_erreur(retirer_piece(Damier, Source));
	afficher_si_erreur(placer_piece(Damier, Destination));
}

/*	Cette fonctions va retirer les prises du damier.	*/

vide retirer_prises(damier * Damier, coup Coup)
{
	for (naturel i = 0; i < Coup.Prises.Nombre; i++)
	{
		afficher_si_erreur(retirer_piece(Damier, Coup.Prises.Pion[i]));
	}
}



/*	Les fonctions qui suivent ajoutent de nouveaux éléments.	*/


/*	Cette fonction ajoute un coup à la liste.	*/

vide ajouter_coup(liste * Liste, coup * Coup)
{
	if (Liste->Prises < Coup->Prises.Nombre)
	{
		liberer_coups(Liste);

		Liste->Prises = Coup->Prises.Nombre;
	}

	if (Liste->Prises == Coup->Prises.Nombre)
	{
		quitter_si_erreur(allouer_coups(Liste, Liste->Taille + 1));

		Liste->Coup[Liste->Nombre++] = Coup;
	}
}

/*	Cette fonction ajoute un déplacement à un coup.	*/

vide ajouter_deplacement(damier * Damier, liste * Liste, coup * Coup, pion Destination, pion Prise)
{
	damier * DamierSuivant;
	coup * CoupSuivant;

	quitter_si_erreur(creer_damier(&DamierSuivant));
	quitter_si_erreur(creer_coup(&CoupSuivant));

	quitter_si_erreur(allouer_deplacements(CoupSuivant, Coup->Deplacements.Taille + 1));
	quitter_si_erreur(allouer_prises(CoupSuivant, Coup->Prises.Taille + 1));

	CoupSuivant->Deplacements.Nombre = Coup->Deplacements.Nombre;
	CoupSuivant->Prises.Nombre = Coup->Prises.Nombre;

	for (naturel i = 0; i < Coup->Deplacements.Nombre; i++)
	{
		CoupSuivant->Deplacements.Pion[i] = Coup->Deplacements.Pion[i];
	}

	for (naturel i = 0; i < Coup->Prises.Nombre; i++)
	{
		CoupSuivant->Prises.Pion[i] = Coup->Prises.Pion[i];
	}

	CoupSuivant->Deplacements.Pion[CoupSuivant->Deplacements.Nombre++] = Destination;

	if (verifier_piece(Prise))
	{
		CoupSuivant->Prises.Pion[CoupSuivant->Prises.Nombre++] = Prise;

		quitter_si_erreur(allouer_pions(DamierSuivant, Damier->Lignes, Damier->Colonnes));

		copier_damier(DamierSuivant, *Damier);

		deplacer_piece(DamierSuivant, Coup->Deplacements.Pion[Coup->Deplacements.Nombre - 1], Destination);

		identifier_coups_pion(DamierSuivant, Liste, CoupSuivant);

		supprimer_damier(&DamierSuivant);
	}

	ajouter_coup(Liste, CoupSuivant);
}

/*	Cette fonction ajoute un coup à l'enregistrement.	*/

vide ajouter_enregistrement(enregistrement * Enregistrement, naturel Naturel)
{
	if (Enregistrement->Taille <= Enregistrement->Nombre)		//	La taille de l'enregistrement est trop petite.
	{
		quitter_si_erreur(allouer_enregistrements(Enregistrement, Enregistrement->Taille + 16));
	}

	Enregistrement->Deplacement[Enregistrement->Lecture] = Naturel;
	Enregistrement->Lecture++;

	if (Enregistrement->Lecture >= Enregistrement->Nombre)		//	Il ne reste aucun enregistrement à lire, on en ajoute donc un nouveau.
	{
		Enregistrement->Nombre = Enregistrement->Lecture;
	}
}

/*	Cette fonction ajoute un caractère à la chaîne.	*/

vide ajouter_caractere(chaine * Chaine, caractere Caractere)
{
	if (Chaine->Taille == 0)
	{
		quitter_si_erreur(allouer_caracteres(Chaine, 2));
	}

	if (Chaine->Taille <= Chaine->Nombre + 1)
	{
		quitter_si_erreur(allouer_caracteres(Chaine, Chaine->Taille * 2));
	}

	Chaine->Caractere[Chaine->Nombre++] = Caractere;
	Chaine->Caractere[Chaine->Nombre] = '\0';
}



/*	Les fonctions qui suivent identifient les coups possibles sur un damier.	*/


/*	Cette fonction parcourt le damier à la recherche des pièces qui appartiennent au joueur demandé.
A chaque occurence, les coups de cette pièce sont identifiés.	*/

vide identifier_coups_joueur(damier * Damier, liste * Liste, joueur Joueur)
{
	liberer_coups(Liste);

	coup * Coup;

	quitter_si_erreur(creer_coup(&Coup));
	quitter_si_erreur(allouer_deplacements(Coup, 1));

	Coup->Deplacements.Nombre = 1;

	for (naturel i = 0; i < Damier->Lignes; i++)		//	On parcourt les lignes du damier.
	{
		for (naturel j = 0; j < Damier->Colonnes; j++)		//	On parcourt les colonnes du damier.
		{
			if (Damier->Pion[i][j].Joueur == Joueur)		// Le pion appartient au joueur.
			{
				Coup->Deplacements.Pion[0] = Damier->Pion[i][j];

				identifier_coups_pion(Damier, Liste, Coup);
			}
		}
	}

	supprimer_coup(&Coup);
}

/* Cette fonction évalue toutes les possibilités de coup d'une pièce sur le damier reçu.
L'objectif est de parcourir toutes les cases des diagonales situées sur le damier.
Chaque avancée dépend de la case précédante, du joueur qui possède la pièce et de son type. */

vide identifier_coups_pion(damier * Damier, liste * Liste, coup * Coup)
{
	pion Source;
	pion Prise;
	pion Destination;

	joueur Joueur;
	type Type;
	position Position;

	Source = Coup->Deplacements.Pion[Coup->Deplacements.Taille - 1];

	for (entier i = -1; i <= 1; i += 2)		//	On définit la direction horizontale de la diagonale.
	{
		for (entier j = -1; j <= 1; j += 2)		//	On définit la direction verticale de la diagonale.
		{
			Position.Ligne = Source.Position.Ligne + i;
			Position.Colonne = Source.Position.Colonne + j;

			Prise = structurer_piece(PERSONNE, VIDE, Position);

			while (verifier_position(*Damier, Position))		//	La position appartient au damier.
			{
				Joueur = obtenir_joueur_depuis_damier(*Damier, Position);
				Type = obtenir_type_depuis_damier(*Damier, Position);

				Destination = structurer_piece(Source.Joueur, Source.Type, Position);

				if (Source.Joueur == Joueur)		//	Un pion de même couleur a été rencontré.
				{
					break;
				}

				if (verifier_piece(Prise))		//	On a rencontré un pion adverse auparavant.
				{
					if (verifier_prise(*Coup, Prise))
					{
						if (Type)		//	On rencontre de nouveau un pion adverse.
						{
							break;
						}
						else		//	On tombe sur une case libre.
						{
							ajouter_deplacement(Damier, Liste, Coup, Destination, Prise);

							if (Source.Type == PION)		//	Le pion d'origine n'est pas une dame.
							{
								break;
							}
						}
					}
				}
				else		//	On n'a pas encore rencontré de pion adverse.
				{
					if (Type)		//	On rencontre un pion adverse.
					{
						Prise = obtenir_piece_depuis_damier(*Damier, Position);
					}
					else		//	On tombe sur une case vide.
					{
						if (Coup->Prises.Nombre == 0)
						{
							if (Source.Type == PION)		//	Le pion d'origine n'est pas une dame.
							{
								if (Source.Joueur == i)		//	Le pion peut avancer.
								{
									ajouter_deplacement(Damier, Liste, Coup, Destination, Prise);
								}

								break;
							}
							else		//	Le pion d'origine est une dame.
							{
								ajouter_deplacement(Damier, Liste, Coup, Destination, Prise);
							}
						}
						else
						{
							if (Source.Type == PION)		//	Le pion d'origine n'est pas une dame.
							{
								break;
							}
						}
					}
				}

				Position.Ligne += i;
				Position.Colonne += j;
			}
		}
	}
}



/*	Fonctions diverses.	*/


/*	Cette fonction calcule la distance entre deux positions.	*/

naturel calculer_distance_entre_naturels(naturel Naturel1, naturel Naturel2)
{
	if (Naturel1 > Naturel2)
	{
		return Naturel1 - Naturel2;
	}
	else
	{
		return Naturel2 - Naturel1;
	}
}

/*	Cette fonction copie un damier vers un autre.	*/

vide copier_damier(damier * DamierDestination, damier DamierSource)
{
	//quitter_si_erreur(allouer_pions(DamierDestination, DamierSource.Lignes, DamierSource.Colonnes));

	for (naturel i = 0; i < DamierSource.Lignes; i++)		//	On parcourt les lignes du damier.
	{
		for (naturel j = 0; j < DamierSource.Colonnes; j++)		//	On parcourt les colonnes du damier.
		{
			DamierDestination->Pion[i][j] = DamierSource.Pion[i][j];
		}
	}
}

/*	Cette fonction reçoit une position et détermine si la pièce qui s'y trouve peut être promue, et la proumouvoie le cas échéant.	*/

retour promouvoir_piece(damier * Damier, position Position)
{
	if (verifier_position(*Damier, Position))		//	La position appartient bien au damier.
	{
		joueur Joueur = obtenir_joueur_depuis_damier(*Damier, Position);
		type Type = obtenir_type_depuis_damier(*Damier, Position);

		if ((Type == PION) && ((Joueur == BLANC && Position.Ligne == Damier->Lignes - 1) || (Joueur == NOIR && Position.Ligne == 0)))		//	Le pion peut être promu.
		{
			Damier->Pion[Position.Ligne][Position.Colonne].Type = DAME;
		}

		return structurer_retour(0, "promouvoir_piece", "la fonction s'est correctement terminée");
	}
	else		//	La position n'appartient pas au damier.
	{
		return structurer_retour(1, "promouvoir_piece", "la position reçue n'appartien pas au damier");
	}
}

/*	Cette fonction permet à l'IA de trouver un coup générique orienté vers la défence.	*/

naturel trouver_coup(liste Liste, damier Damier, joueur Joueur)
{
	damier * DamierSuivant;
	liste * ListeSuivante;

	booleen Ajouter;

	pion Source;
	pion Destination;

	naturel MeilleurChoix;
	entier MeilleurePrise;
	entier MeilleurDeplacement;
	naturel MeilleureLigne;
	naturel MeilleureColonne;

	naturel Choix;
	entier Prise;
	entier Deplacement;
	naturel Ligne;
	naturel Colonne;

	afficher_si_erreur(creer_damier(&DamierSuivant));
	afficher_si_erreur(creer_liste(&ListeSuivante));

	allouer_pions(DamierSuivant, Damier.Lignes, Damier.Colonnes);

	for (Choix = 0; Choix < Liste.Nombre; Choix++)
	{
		Ajouter = NON;

		Source = obtenir_source_depuis_coup(*Liste.Coup[Choix]);
		Destination = obtenir_destination_depuis_coup(*Liste.Coup[Choix]);

		copier_damier(DamierSuivant, Damier);

		deplacer_piece(DamierSuivant, Source, Destination);
		retirer_prises(DamierSuivant, *Liste.Coup[Choix]);

		identifier_coups_joueur(DamierSuivant, ListeSuivante, -Joueur);

		Prise = ListeSuivante->Prises;
		Deplacement = ListeSuivante->Nombre;

		if (Source.Joueur == BLANC)
		{
			Ligne = calculer_distance_entre_naturels(0, Source.Position.Ligne);
		}
		else
		{
			Ligne = calculer_distance_entre_naturels(Damier.Lignes - 1, Source.Position.Ligne);
		}

		Colonne = calculer_distance_entre_naturels(Damier.Colonnes / 2, Source.Position.Colonne);

		if (Choix == 0)
		{
			Ajouter = OUI;
		}
		else
		{
			if (Prise < MeilleurePrise)
			{
				Ajouter = OUI;
			}
			else
			{
				if (Prise == MeilleurePrise)
				{
					if (Deplacement < MeilleurDeplacement)
					{
						Ajouter = OUI;
					}
					else
					{
						if (Deplacement == MeilleurDeplacement && Source.Type == PION)
						{
							if (Ligne > MeilleureLigne)
							{
								Ajouter = OUI;
							}
							else
							{
								if (Ligne == MeilleureLigne)
								{
									if (Colonne < MeilleureColonne)
									{
										Ajouter = OUI;
									}
								}
							}		
						}
					}
				}
			}
		}

		if (Ajouter)
		{
			MeilleurChoix = Choix;
			MeilleurePrise = Prise;
			MeilleurDeplacement = Deplacement;
			MeilleureLigne = Ligne;
			MeilleureColonne = Colonne;
		}
	}

	supprimer_damier(&DamierSuivant);
	supprimer_liste(&ListeSuivante);

	return MeilleurChoix;
}