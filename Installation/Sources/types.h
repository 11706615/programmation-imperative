#pragma once

/*	Cette en-tête contient les définitions de tous les types présents dans le projet.	*/


/*	Traduction des types pour mettre en valeur la langue française.	*/

typedef void vide;
typedef double reel;
typedef int entier;
typedef unsigned int naturel;
typedef char caractere;

/*	Cette énumération permet la création de booléens.	*/

typedef enum booleen_e
{
	NON = 0,
	OUI = 1
}
booleen;

/*	Cette énumération permet de connaître le mode de jeu.	*/

typedef enum etat_e
{
	JEU = 0,
	VICTOIRE = 1,
	EGALITE = 2,
	QUITTER = 3
}
etat;

/*	Cette énumération permet de connaître le joueur qui possède le pion.	*/

typedef enum joueur_e
{
	NOIR = -1,			//	Le pion est de couleur noire.
	PERSONNE = 0,		//	Le pion n'appartient à personne.
	BLANC = 1			//	Le pion est de couleur blanche.
}
joueur;

/*	Cette énumération permet de connaître le type d'un pion.	*/

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
	joueur Joueur;			//	Propriétaire du pion.
	type Type;				//	Type du pion.
	position Position;		//	Position à laquelle se trouve le pion.
}
pion;

/*	Cette structure permet de définir un damier.	*/

typedef struct damier_s
{
	pion ** Pion;			//	Pointeur vers le tableau de pointeurs qui contient les lignes du damier.
	naturel Lignes;			//	Nombre de lignes de ce tableau.
	naturel Colonnes;		//	Nombre de colonnes de ce tableau.
}
damier;

/*	Cette structure contient les positions d'un pion lors de son déplacement.	*/

typedef struct deplacements_s
{
	pion * Pion;			//	Tableau de pions.
	naturel Nombre;			//	Nombre de pions.
	naturel Taille;			//	Taille du tableau.
}
deplacements;

/*	Cette structure contient les prises d'un pion lors de son déplacement.	*/

typedef struct prises_s
{
	pion * Pion;			//	Tableau de pions.
	naturel Nombre;			//	Nombre de pions.
	naturel Taille;			//	Taille du tableau.
}
prises;

/*	Cette structure permet de définir un coup.	*/

typedef struct coup_s
{
	deplacements Deplacements;			//	Positions intermédiaires.
	prises Prises;						//	Pions capturés si c'est le cas.
}
coup;

/*	Cette structure permet de définir une liste de coups.	*/

typedef struct liste_s
{
	coup ** Coup;					//	Tableau qui contient les coups possibles.
	naturel Prises;					//	Total de pions capturés lors d'une rafle.
	naturel Nombre;					//	Nombre de déplacement possibles.
	naturel Taille;					//	Taille du tableau.
}
liste;

/*	Cette structure permet d'enregistrer les informations concernant la partie.	*/

typedef struct enregistrement_s
{
	damier * Damier;			//	Damier de départ.
	naturel * Deplacement;		//	Tableau qui contient le numéro de chaque déplacement choisi.
	booleen Joueur[2];			//	Tableau indiquant qui va jouer (FAUX = ORDI, VRAI = HUMAIN).
	naturel Coups;				//	Nombre de coups consécutifs sans prises ou déplacement de pion.
	naturel Lecture;			//	Point de releture.
	naturel Nombre;				//	Nombre de déplacement effectués.
	naturel Taille;				//	Taille du tableau.
}
enregistrement;

/*	Cette structure permet de stocker les caractères d'une chaînes de caractères.	*/

typedef struct chaine_s
{
	caractere * Caractere;		//	Tableau de caractère.
	naturel Nombre;				//	Nombre de caractères.
	naturel Taille;				//	Taille du tableau.
}
chaine;

/*	Cette structure permet de générer une erreur dans les cas où les arguments reçus ne permettent pas à la fonction de fonctionner.	*/

typedef struct retour_s
{
	entier Type;						//	Identification de l'erreur.
	const caractere * Fonction;			//	Nom de la fonction qui a retourné une erreur.
	const caractere * Description;		//	Description de l'erreur survenue.
}
retour;