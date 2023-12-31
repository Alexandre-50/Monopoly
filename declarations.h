#ifndef DECLARATION_H_INCLUDED
#define DECLARATION_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct Case Case;
struct Case
{
    char nom1[15];
    char nom2[15];
    int COORD_LIGNE;
    int COORD_COLONNE;
    int prix_achat;
    int prix_maison;
    int loyer[6]; // On met un tableau de int qui contient le montant du loyer en fonction du nombre de Maisons et Hotel
    int Color;
    int Nb_Maison;
    int proprietaire;
};
typedef struct Joueur Joueur;  // On met plusieurs fois la variable Joueur pour pouvoir utiliser dans les diff�rentes fonctions du programme principal
struct Joueur
{
    char nomJoueur[10];
    int couleur;
    int argent;
    int Case;
    int Prison;  // Nombres de tours o� le joueurs est en prison
    int nbDoubles;
    int joueurenJeu;
};
typedef struct ParamJeu ParamJeu;
struct ParamJeu
{
    int NbJoueur;
};
typedef struct Banque Banque;
struct Banque
{
    int argent;

};
#endif // DECLARATION_H_INCLUDED
