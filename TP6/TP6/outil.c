#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : JAOUHAR                     Prénom : ABDELLAH                        */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;
	idx = rep->nb_elts; 
	if (rep->nb_elts < MAX_ENREG)
	{
		modif = true;
		rep->tab[rep->nb_elts] = enr;
		rep->nb_elts++;
		return (OK);
	}
	else 
		return(ERROR);

#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		     if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = false;
			return(OK);
		}

	}


#endif

#endif



} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire* rep, int indice) {
		if (rep->nb_elts >= 1 && indice < rep->nb_elts)		
		{			
			for (int i = indice; i < rep->nb_elts - 1; i++)
			{
				rep->tab[i] = rep->tab[i + 1];
			}
			rep->nb_elts--;
			modif = true;
		}
		return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

int supprimer_un_contact_dans_rep_liste(Repertoire* rep, SingleLinkedListElem* elem) {

	int ret = DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0);
}
#endif
#endif


/**********************************************************************/
/*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
/* ex Dupont, Jean                 0320304050                         */
/**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici
	printf("%s, %s, %s", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{

	printf("%s", enr.nom);
	for (int i = strlen(enr.nom); i < MAX_NOM; i++) {
		printf(" ");
	}
	printf("|");
	printf("%s", enr.prenom);
	for (int i = strlen(enr.prenom); i < MAX_NOM; i++) {
		printf(" ");
	}
	printf("|");
	printf("%s\n", enr.tel);
	return;

} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	if (enr1.nom == NULL || enr1.prenom == NULL || enr1.tel == NULL || enr2.nom == NULL || enr2.prenom == NULL || enr2.tel == NULL)
	{
		printf("Probleme dans l'enregistrement");
		return false;
	}
	for (int i = 0; i < MAX_NOM; i++)
	{
		if (tolower(enr1.nom[i]) < tolower(enr2.nom[i]))
			return true;
		if (tolower(enr1.nom[i]) > tolower(enr2.nom[i]))
			return false;
	}
	for (int i = 0; i < MAX_NOM; i++)
	{
		if (tolower(enr1.prenom[i]) < tolower(enr2.prenom[i]))
			return true;
		if (tolower(enr1.prenom[i]) > tolower(enr2.prenom[i]))
			return false;
	}
}

/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire* rep)
{

#ifdef IMPL_TAB
	for (int j = 0; j < rep->nb_elts; j++) {
		for (int i = 0; i < rep->nb_elts - 1 - j; i++) {
			if (est_sup(rep->tab[i + 1], rep->tab[i]) == false) {
				printf("ECHANGE %s %s\n", rep->tab[i].nom, rep->tab[i + 1].nom);
				Enregistrement tmp = rep->tab[i + 1];
				rep->tab[i + 1] = rep->tab[i];
				rep->tab[i] = tmp;
			}
		}
	}




#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire* rep, char nom[], int ind)
{
	int i = ind;
	int ind_fin;

	char tmp_nom[MAX_NOM];
	char tmp_nom2[MAX_NOM];	
	bool trouve = false;


#ifdef IMPL_TAB
	/////
	ind_fin = rep->nb_elts;
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);
	_strupr_s(tmp_nom, strlen(tmp_nom) + 1);
	while (trouve == false && i < ind_fin) {

		strncpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom, _TRUNCATE);
		_strupr_s(tmp_nom2, strlen(tmp_nom2) + 1);
		if (strcmp(tmp_nom, tmp_nom2) == 0) trouve = true;
		else i++;
}

#else
#ifdef IMPL_LIST
	ind_fin = rep->nb_elts;
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);    // On copie le nom dans "tmp_nom", et on le passe en majuscule.
	_strupr_s(tmp_nom, strlen(tmp_nom) + 1);
	while (trouve == false && i < ind_fin) {				  // On va le comparer à chaque nom du répertoire, jusqu'au dernier!

		strncpy_s(tmp_nom2, _countof(tmp_nom2), GetElementAt(rep->liste, i)->pers.nom, _TRUNCATE);   // On copie dans "tmp_nom2" le nom du répertoire et on le passe en majuscule.
		_strupr_s(tmp_nom2, strlen(tmp_nom2) + 1);
		if (strcmp(tmp_nom, tmp_nom2) == 0) trouve = true;	  // Comparaison de la chaine de charactere: on retourne true si c'est le même!
		else i++;	// Sinon on passe au suivant!
	}

#endif
#endif

	return((trouve) ? i : -1);

} /* fin rechercher_nom */
  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char* s)
{
	int size = strlen(s);

	for (int i = 0; i < size; i++)
	{
		if (isalnum(s[i]) == false)
		{
			int a = i;
			while (s[a + 1] != '\0') {
				*(s + a) = *(s + a + 1);
				a++;
			}
		}
	}

	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	FILE* Fic_rep;					/* le fichier */
	errno_t err;
	char buffer[sizeof(Enregistrement) + 1]; //Création du buffer qui va contenir les informations
#ifdef IMPL_TAB
	err = fopen_s(&Fic_rep, nom_fichier, "w");
	if (err != 0 || Fic_rep == NULL) { return ERROR; } //Verification de l'existance et de la bonne ouverture du fichier
	for (int i = 0; i < rep->nb_elts; i++)
	{
		sprintf_s(buffer, sizeof(buffer), "%s%c%s%c%s\n", rep->tab[i].nom, SEPARATEUR, rep->tab[i].prenom, SEPARATEUR, rep->tab[i].tel); //Stock la serie de caractères dans le buffer
		fputs(buffer, Fic_rep); //On print le buffer dans le txt
}
	if (feof(Fic_rep)) {
		fclose(Fic_rep); //on ferme le fichier
	}
#else
#ifdef IMPL_LIST
	if (fopen_s(&fic_rep, nom_fichier, "w") != 0 || fic_rep == NULL) {   //on vérifie que le fichier est ouvert
		err = ERROR;
		return err;
	}
	for (int i = 0; i < rep->nb_elts; i++) {      //pour tous les éléments du tableau
		fprintf(fic_rep, "%s%c", GetElementAt(rep->liste, i)->pers.nom, SEPARATEUR);           //on écrit dans le fichier les informations du contact
		fprintf(fic_rep, "%s%c", GetElementAt(rep->liste, i)->pers.prenom, SEPARATEUR);
		fprintf(fic_rep, "%s\n", GetElementAt(rep->liste, i)->pers.tel);

	}
	if (feof(fic_rep)) {
		fclose(fic_rep);
	}
#endif
#endif

  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

	int charger(Repertoire * rep, char nom_fichier[])
	{
		FILE* fic_rep;					/* le fichier */
		errno_t err;
		int num_rec = 0;						/* index sur enregistrements */
		int long_max_rec = sizeof(Enregistrement);
		char buffer[sizeof(Enregistrement) + 1];
		int idx = 0;

		char* char_nw_line;

		_set_errno(0);
		if (((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL))
		{
			return(err);
		}
		else
		{
			while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
			{
				if (fgets(buffer, long_max_rec, fic_rep) != NULL)
				{
					/* memorisation de l'enregistrement lu dans le tableau */
					buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */
					char* char_nw_line;
					if ((char_nw_line = strchr(buffer, '\n')) != NULL)
						*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

    #ifdef IMPL_TAB
					int idx = 0;
					int num_rec = 0;
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;							/* on saute le separateur */
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
						{
							idx++;
							if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
								num_rec++;		/* element à priori correct, on le comptabilise */
						}
					}
    #else 
    #ifdef IMPL_LIST
					Enregistrement enr;
					if (lire_champ_suivant(buffer, &idx, enr.nom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;							/* on saute le separateur */
						if (lire_champ_suivant(buffer, &idx, enr.prenom, MAX_NOM, SEPARATEUR) == OK)
						{
							idx++;
							if (lire_champ_suivant(buffer, &idx, enr.tel, MAX_TEL, SEPARATEUR) == OK)
								//ajouter_un_contact_dans_rep(rep, enr);
								InsertElementAt(rep->liste, rep->liste->size, enr);
							num_rec++;		

						}
					}									

#endif
#endif




				}

			}
			rep->nb_elts = num_rec;
			fclose(fic_rep);
			return(OK);
		}


	} /* fin charger */