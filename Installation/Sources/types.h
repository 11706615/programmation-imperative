#pragma once

/*	Cette en-t�te contient les d�finitions de tous les types pr�sents dans le projet.	*/


/*	Traduction des types pour mettre en valeur la langue fran�aise.	*/

typedef void vide;
typedef double reel;
typedef int entier;
typedef unsigned int naturel;
typedef char caractere;

/*	Cette �num�ration permet la cr�ation de bool�ens.	*/

typedef enum booleen_e
{
	NON = 0,
	OUI = 1
}
booleen;

/*	Cette �num�ration permet de conna�tre le mode de jeu.	*/

typedef enum etat_e
{
	JEU = 0,
	VICTOIRE = 1,
	EGALITE = 2,
	QUITTER = 3
}
etat;

/*	Cette �num�ration permet de conna�tre le joueur qui poss�de le pion.	*/

typedef enum joueur_e
{
	NOIR = -1,			//	Le pion est de couleur noire.
	PERSONNE = 0,		//	Le pion n'appartient � personne.
	BLANC = 1			//	Le pion est de couleur blanche.
}
joueur;

/*	Cette �num�ration permet de conna�tre le type d'un pion.	*/

typedef enum type_e
{
	VIDE = 0,		//	Le pion n'existe pas.
	PION = 1,		//	Le pion n'est pas promu.
	DAME = 2		//	Le pion est promu.
}
type;

/*	Cete structure permet de donner une position sur le damier.	*/

typedef struct position_s
{
	naturel Ligne;			//	Ligne sur laquelle se trouve le pion.
	naturel Colonne;		//	Colonne sur laquelle se trouve le pion.
}
position;

/*	Cette structure contient les informations d'un pion.	*/

typedef struct pion_s
{
	joueur Joueur;			//	Propri�taire du pion.
	type Type;				//	Type du pion.
	position Position;		//	Position � laquelle se trouve le pion.
}
pion;

/*	Cette structure permet de d�finir un damier.	*/

typedef struct damier_s
{
	pion ** Pion;			//	Pointeur vers le tableau de pointeurs qui contient les lignes du damier.
	naturel Lignes;			//	Nombre de lignes de ce tableau.
	naturel Colonnes;		//	Nombre de colonnes de ce tableau.
}
damier;

/*	Cette structure contient les positions d'un pion lors de son d�placement.	*/

typedef struct deplacements_s
{
	pion * Pion;			//	Tableau de pions.
	naturel Nombre;			//	Nombre de pions.
	naturel Taille;			//	Taille du tableau.
}
deplacements;

/*	Cette structure contient les prises d'un pion lors de son d�placement.	*/

typedef struct prises_s
{
	pion * Pion;			//	Tableau de pions.
	naturel Nombre;			//	Nombre de pions.
	naturel Taille;			//	Taille du tableau.
}
prises;

/*	Cette structure permet de d�finir un coup.	*/

typedef struct coup_s
{
	deplacements Deplacements;			//	Positions interm�diaires.
	prises Prises;						//	Pions captur�s si c'est le cas.
}
coup;

/*	Cette structure permet de d�finir une liste de coups.	*/

typedef struct liste_s
{
	coup ** Coup;					//	Tableau qui contient les coups possibles.
	naturel Prises;					//	Total de pions captur�s lors d'une rafle.
	naturel Nombre;					//	Nombre de d�placement possibles.
	naturel Taille;					//	Taille du tableau.
}
liste;

/*	Cette structure permet d'enregistrer les informations concernant la partie.	*/

typedef struct enregistrement_s
{
	damier * Damier;			//	Damier de d�part.
	naturel * Deplacement;		//	Tableau qui contient le num�ro de chaque d�placement choisi.
	booleen Joueur[2];			//	Tableau indiquant qui va jouer (FAUX = ORDI, VRAI = HUMAIN).
	naturel Coups;				//	Nombre de coups cons�cutifs sans prises ou d�placement de pion.
	naturel Lecture;			//	Point de releture.
	naturel Nombre;				//	Nombre de d�placement effectu�s.
	naturel Taille;				//	Taille du tableau.
}
enregistrement;

/*	Cette structure permet de stocker les caract�res d'une cha�nes de caract�res.	*/

typedef struct chaine_s
{
	caractere * Caractere;		//	Tableau de caract�re.
	naturel Nombre;				//	Nombre de caract�res.
	naturel Taille;				//	Taille du tableau.
}
chaine;

/*	Cette structure permet de g�n�rer une erreur dans les cas o� les arguments re�us ne permettent pas � la fonction de fonctionner.	*/

typedef struct retour_s
{
	entier Type;						//	Identification de l'erreur.
	const caractere * Fonction;			//	Nom de la fonction qui a retourn� une erreur.
	const caractere * Description;		//	Description de l'erreur survenue.
}
retour;