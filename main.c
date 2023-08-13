#include "declarations.h"
#define NB_LIGNES 6
#define NB_COLONNES 15
/*int MenuAffichage()
{
    FILE *f;
    char c;
    printf("BIENVENUE DANS LE MONOPOLY\n\n");
    printf("Lancer la Partie\n");
    printf("Regles\n");
    printf("Quitter\n");
    int choixJoueur=0;
    switch(choixJoueur)
    {
        case 1:
            printf("Bonne Partie\n");
            break;
        case 2:
              printf("\n\n\tVoici les regles\n\n\n");
              f=fopen("Regles Monopoly.txt","r");
              while((c=fgetc(f))!=EOF)
              {
                  printf("%c",c);
              }
              fclose(f);
              break;
        case 3:
            printf("Fin de Jeu\n");
            return 0;
            break;
    }
}*/
// Fonction qui permet de remplir le tableau sous forme de carré avec 90 correspondant aux dimensions des lignes et 192 pour les colonnes

void remplissage_Carre(char tabJeu[90][192],int ligneDebut,int colonneDebut)
{
    int i,j;
    for (j=colonneDebut;j<=colonneDebut+17;j++)
       tabJeu[ligneDebut][j] = '*';                          // Au différent coup, il va exécuter le caractère 17 fois dans la boucle for
    for (i=1+ligneDebut;i<=6+ligneDebut;i++)
    {
        tabJeu[i][colonneDebut] = '*';
        for (j=1+colonneDebut;j<=16+colonneDebut;j++)                  // Il affiche une ligne centrale
                 tabJeu[i][j] = ' ';
        tabJeu[i][17+colonneDebut]='*';
    }
    for (j=0+colonneDebut;j<=17+colonneDebut;j++)
       tabJeu[7+ligneDebut][j] = '*';                 // Au différent coup, il va exécuter le caractère * 17 fois dans la boucle for
}

void remplirTableau(char tabJeu[90][192], int tabJeuColor[90][192],Case caseJeu[40],Joueur Joueur[5],ParamJeu ParamJeu)    // Fonction qui permet de remplir les cases du plateau
{
     int i,j;
    //Joueur[1].Prison=1;                      // Lorsque la variable Joueur vaut 0, le joueur est simplement en visite
    //Joueur[2].Prison=0;                      // Lorsque la variable Joueur vaut 1 ou plus, il est en prison
    for (i=0;i<=89;i++)                      // On prend en compte le nombre de lignes à compter entre 0 et 89 lignes
        for(j=0;j<=191;j++)                  // On prend en compte le nombre de colonnes à compter de 0 à 191 colonnes
        {
        tabJeu[i][j] = ' ';                    // On met un espace dans toute les cases du tableau
        tabJeuColor[i][j]=0;
        }
    for (i=0;i<=39;i++)                      // On met une boucle for pour compter le nombres de cases du plateau
    {
        for (j=0;j<=17;j++)                  // On remet une boucle for pour compter le nombres de lignes du plateau
        {
            tabJeu[caseJeu[i].COORD_LIGNE][caseJeu[i].COORD_COLONNE+j]='*';
            tabJeu[caseJeu[i].COORD_LIGNE+7][caseJeu[i].COORD_COLONNE+j]='*';  // On ajoute 7 pour représenter les côtés des cases de chaque colonnes du plateau
        }
        for (j=0;j<=7;j++)                  // On remet une boucle for pour compter le nombres de colonnes du plateau
        {
            tabJeu[caseJeu[i].COORD_LIGNE+j][caseJeu[i].COORD_COLONNE]='*';
            tabJeu[caseJeu[i].COORD_LIGNE+j][caseJeu[i].COORD_COLONNE+17]='*'; // On ajoute 17 pour représenter les côtés des cases de chaque lignes du plateau
        }
    j=0;
        while (caseJeu[i].nom1[j])       // Tant qu'on est pas arrivé à la fin de la chaîne caseJeu, caseJeu[i] est un nom le caractère nom1 rajoute plusieurs caractères
        {
            tabJeu[caseJeu[i].COORD_LIGNE+2][caseJeu[i].COORD_COLONNE+1+j]=caseJeu[i].nom1[j];   // Dans la colonne 72 à la ligne 171, je vais écrire mon 1er caractère
            j++;
        }
        j=0;
        while (caseJeu[i].nom2[j])
        {            tabJeu[caseJeu[i].COORD_LIGNE+3][caseJeu[i].COORD_COLONNE+1+j]=caseJeu[i].nom2[j];
            j++;
        }

         if (caseJeu[i].prix_achat>0)
        {
            tabJeu[caseJeu[i].COORD_LIGNE+6][caseJeu[i].COORD_COLONNE+7] = caseJeu[i].prix_achat/100 + 48;        // Permet de transformer la fonction int en caractère ASCII
            if (tabJeu[caseJeu[i].COORD_LIGNE+6][caseJeu[i].COORD_COLONNE+7] == '0')
                tabJeu[caseJeu[i].COORD_LIGNE+6][caseJeu[i].COORD_COLONNE+7] = ' ';
            tabJeu[caseJeu[i].COORD_LIGNE+6][caseJeu[i].COORD_COLONNE+8] = caseJeu[i].prix_achat % 100 /10 + 48;   // Affiche le 2eme caractère
            tabJeu[caseJeu[i].COORD_LIGNE+6][caseJeu[i].COORD_COLONNE+9] = caseJeu[i].prix_achat % 10 + 48;       // Affiche le 3eme caractere
            tabJeu[caseJeu[i].COORD_LIGNE+6][caseJeu[i].COORD_COLONNE+10] = '$';                                  // Affiche le 4eme caractere
        }
         for(j=0;j<=15;j++)
        {
            tabJeu[caseJeu[i].COORD_LIGNE+1][caseJeu[i].COORD_COLONNE+1+j]=' ';
            tabJeuColor[caseJeu[i].COORD_LIGNE+1][caseJeu[i].COORD_COLONNE+1+j]=caseJeu[i].Color;
        }
         if (caseJeu[i].Nb_Maison>0 && caseJeu[i].Nb_Maison<5)                                                        // Si le nombres de maisons est supérieure à 0 dans chaques cases du plateau
         {
             j=1;                                                                           // On fixe le numéro maison
             while (j<=caseJeu[i].Nb_Maison)
             {
                 tabJeuColor[caseJeu[i].COORD_LIGNE+4][caseJeu[i].COORD_COLONNE+j*3]=10;    // On colorie 2 cases l'une après l'autre en vert
                 tabJeuColor[caseJeu[i].COORD_LIGNE+4][caseJeu[i].COORD_COLONNE+1+j*3]=10;  // On colorie une autre case  qui feront office de maison
                 j++;
             }
         }
         if (caseJeu[i].Nb_Maison==5)
         {
              tabJeuColor[caseJeu[i].COORD_LIGNE+4][caseJeu[i].COORD_COLONNE+6]=12;          // Un hotel prend 4 cases qui définit la longueur de l'hotel sur le plateau
              tabJeuColor[caseJeu[i].COORD_LIGNE+4][caseJeu[i].COORD_COLONNE+7]=12;
              tabJeuColor[caseJeu[i].COORD_LIGNE+4][caseJeu[i].COORD_COLONNE+8]=12;
              tabJeuColor[caseJeu[i].COORD_LIGNE+4][caseJeu[i].COORD_COLONNE+9]=12;
         }
         if(caseJeu[i].proprietaire!=0)
         {
            tabJeu[caseJeu[i].COORD_LIGNE+6][caseJeu[i].COORD_COLONNE+2] = caseJeu[i].proprietaire+48;    // On affiche le
            tabJeuColor[caseJeu[i].COORD_LIGNE+6][caseJeu[i].COORD_COLONNE+2] = 12;
         }

    }
  for(j=1;j<=ParamJeu.NbJoueur;j++)
    {
        if(Joueur[j].Prison>=1)
        {
          tabJeuColor[caseJeu[Joueur[j].Case].COORD_LIGNE+5][caseJeu[Joueur[j].Case].COORD_COLONNE+3*j]=4;    // On indique que le joueur est en couleur rouge
        }
        tabJeu[caseJeu[Joueur[j].Case].COORD_LIGNE+5][caseJeu[Joueur[j].Case].COORD_COLONNE+3*j]=j+48;     // On met le caractère du joueur 1 ou du joueur 2 dans la case

    }
}
int deplacerJoueur(char tabJeu[90][192],Case caseJeu[40],Joueur Joueur[5],int numJoueur)
{
    int resultatDe1_De2;
    int De1;
    int De2;
    srand(time(NULL));        // On initialise le générateur de nombres aléatoires et permet d'éxécuter certains valeurs aléatoires
    De1=rand()%6+1;
    De2=rand()%6+1;
    resultatDe1_De2=De1+De2;
    printf("\nresultat de lancement des est %d (De1=%d De2=%d)\n",resultatDe1_De2,De1,De2);
    if(De1==De2)
    {
       Joueur[numJoueur].nbDoubles=Joueur[numJoueur].nbDoubles+1;    // Le joueur a fait un double
       if(Joueur[numJoueur].Prison>=1)
       {
           printf("Vous venez de faire un double, vous pouvez sortir\n");
           Joueur[numJoueur].Prison=0;
       }
    }
    else
    {
        Joueur[numJoueur].nbDoubles=0;
        if(Joueur[numJoueur].Prison==3)
        {
            printf("Vous n'avez pas fait de doubles au 3ème tour, vous payer une amende de 50 dollars pour sortir\n");
            Joueur[numJoueur].argent=Joueur[numJoueur].argent-50;
            Joueur[numJoueur].Prison=0;
        }
    }
    if (Joueur[numJoueur].Prison==0)
    {
        if ((resultatDe1_De2+Joueur[numJoueur].Case)<=39)
        {
           Joueur[numJoueur].Case=resultatDe1_De2+Joueur[numJoueur].Case;  // On avance en ajouant + résulat du dé
        }
        else
        {
            Joueur[numJoueur].Case=resultatDe1_De2+Joueur[numJoueur].Case-40; // On avance en ajouant + résulat du dé -40
            Joueur[numJoueur].argent=200+Joueur[numJoueur].argent;
        }
    }
    return resultatDe1_De2;                                                // On fait appelle à cette fonction dans le main
}
int carteChance(Joueur Joueur[5],int numJoueur)
{
    int chance=rand()%(16)+1;
    printf("Vous etes sur la carte Chance\n");
    switch(chance)
    {
    case 1:
        Joueur[numJoueur].Case=39;
        printf("Rendez-vous a la Rue de la Paix\n");
    break;
    case 2:
        Joueur[numJoueur].Case=0;
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+200;
        printf("Avancer jusqu’a la case depart\n");
    break;
    case 3:
        if(Joueur[numJoueur].Case==36)                  // Si le joueur est dans la case 36 pour recevoir les 200 $
            Joueur[numJoueur].argent=Joueur[numJoueur].argent+200;
        Joueur[numJoueur].Case=24;
        printf("Rendez-vous à l’Avenue Henri-Martin. Si vous passez par la case depart, recevez 200 $\n");//FAIT
    break;
    case 4:
        if(Joueur[numJoueur].Case==22 || Joueur[numJoueur].Case==36)       //
            Joueur[numJoueur].argent=Joueur[numJoueur].argent+200;
        Joueur[numJoueur].Case=11;
        printf("Avancez au Boulevard de La Villette. Si vous passez par la case depart, recevez 200 $ \n");//FAIT
    break;
    case 5:
        printf("Vous etes impose pour les reparations de voirie à raison de 30 $ par maison et 90 $ par hotel.\n");//FAIT A MOITIE
    break;
    case 6:
        if(Joueur[numJoueur].Case==22 || Joueur[numJoueur].Case==36)       // Si on est
            Joueur[numJoueur].argent=Joueur[numJoueur].argent+200;
        Joueur[numJoueur].Case=15;
        printf("Avancez jusqu’a la Gare de Lyon. Si vous passez par la case depart, recevez 200 $\n");
    break;
    case 7:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+25;
        printf("Vous avez gagne le prix de mots croises. Recevez 25 $\n");//FAIT
    break;
    case 8:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+15;
        printf("La banque vous verse un dividende de 15 $ \n");//FAIT
    break;
    case 9:

        printf("Vous etes libere de prison. Cette carte peut être conservee jusqu’a ce qu’elle soit utilisee ou vendue.\n");
    break;
    case 10:
        Joueur[numJoueur].Case=Joueur[numJoueur].Case-3;
        printf("Reculez de trois cases\n");
    break;
    case 11:
        Joueur[numJoueur].Prison=1;
        Joueur[numJoueur].Case=10;
        printf("Aller en prison. Rendez-vous directement en prison. Ne franchissez pas par la case depart, ne touchez pas 50 $\n");
    break;
    case 12:

        printf("Faites des reparations dans toutes vos maisons. Versez pour chaque maison 15 $. Versez pour chaque hotel 50$\n");//FAIT
    break;
    case 13:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent-15;
        printf("Amende pour exces de vitesse 15 $\n");//FAIT
    break;
    case 14:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent-60;
        printf("Payez pour frais de scolarite 60 $\n");//FAIT
    break;
    case 15:
         Joueur[numJoueur].argent= Joueur[numJoueur].argent-10;
        printf("Amende pour ivresse 10$\n");//FAIT
    break;
    case 16:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+40;
        printf("Votre immeuble et votre pret rapportent. Vous devez toucher 40 $\n");//FAIT
    break;
    default:
        printf("ERREUR 404");
    break;
    }
    return chance;
}
void communaute(Joueur Joueur[5],int numJoueur,ParamJeu ParamJeu)
{
    int i;
    int chance;
    chance=rand()%(16)+1;
    printf("Vous avez tire une Carte Communaute\n");
    switch(chance)
    {
    case 1:
        Joueur[numJoueur].Case=0;
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+200;
        printf("Placez-vous sur la case depart\n");
    break;
    case 2:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+50;
        printf("Erreur de la banque en votre faveur. Recevez 50 $\n");// fait
    break;
    case 3:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent-25;
        printf("Payez la note du medecin 25 $\n");//FAIT
    break;
    case 4:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+25;
        printf("La vente de votre stock vous rapporte 25 $\n");//FAIT
    break;
    case 5:
        printf("Vous etes libere de prison. Cette carte peut etre conservee jusqu’a ce qu’elle soit utilisee\n");
    break;
    case 6:
        Joueur[numJoueur].Prison=1;
        Joueur[numJoueur].Case=10;
        printf("Aller en prison. Rendez-vous directement à la prison. Ne franchissez pas par la case depart, ne touchez pas 50 $\n");//FAIT
    break;
    case 7:
        Joueur[numJoueur].Case=1;
        printf("Retournez à Belleville\n");
    break;
    case 8:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+30;
        printf("Recevez votre revenu annuel 30 $\n");//FAIT
    break;
    case 9:
        for (i=1;i<=ParamJeu.NbJoueur;i++)
        {
            Joueur[numJoueur].argent=Joueur[numJoueur].argent+10; // Le joueur reçoit 10 dollars de chaque autres joueurs
            Joueur[i].argent=Joueur[i].argent-10;                 // Chaque Joueurs perdent 10 dollars
        }
        printf("C’est votre anniversaire. Chaque joueur doit vous donner 10 $\n");
    break;
    case 10:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+20;
        printf("Les contributions vous remboursent la somme de 20 $\n");//FAIT
    break;
    case 11:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+25;
        printf("Recevez votre interet sur l emprunt, vous gagnez 25 $\n");//FAIT
    break;
    case 12:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent-10;
        printf("Payez votre Police d’Assurance 10 $\n");//FAIT
    break;
    case 13:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent-10;
        printf("Payez une amende de 10 $\n");
    break;
    case 14:
        if(Joueur[numJoueur].Case==2)
            Joueur[numJoueur].Case=5;
        else if(Joueur[numJoueur].Case==17)
            Joueur[numJoueur].Case=25;
        else
            Joueur[numJoueur].Case=35;
        printf("Rendez-vous à la gare la plus proche. Si vous passez par la case depart, recevez 50 $\n");//FAIT
    break;
    case 15:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+10;
        printf("Vous avez gagne le deuxième Prix de Beaute. Recevez 10 $\n");//FAIT
    break;
    case 16:
        Joueur[numJoueur].argent=Joueur[numJoueur].argent+30;
        printf("Vous héritez 30 $\n");//FAIT
    break;
    default:
        printf("ERREUR 404");
    break;
    }
}
void arriveesurCarte(char tabJeu[90][192],Case caseJeu[40],Joueur Joueur[5],int numJoueur,int resultatDe1_De2,ParamJeu ParamJeu)
{
    int numCase;
    int testColor;  // Variable qui permet de compter le nombres de cases possédant la même couleur ou bien le nombres de gares
    int i;
    int loyerGare;
    char achat;
    char toucheEntrer;
    if(Joueur[numJoueur].Case==7 ||Joueur[numJoueur].Case==22 || Joueur[numJoueur].Case==36)
    {
        carteChance(Joueur,numJoueur);
    }
    else if(Joueur[numJoueur].Case==2 ||Joueur[numJoueur].Case==17 || Joueur[numJoueur].Case==33)
    {
        communaute(Joueur,numJoueur,ParamJeu);
    }
    else if(Joueur[numJoueur].Case==30) // Si un joueur atterit sur la Case "Aller en Prison"
    {
       Joueur[numJoueur].Case=10;  // Le joueur va en prison
       Joueur[numJoueur].Prison=1;
    }
    else if(caseJeu[Joueur[numJoueur].Case].prix_achat==0)
    {
        printf("Cette case n'est pas achetable\n");
    }
    else
    {
         if (caseJeu[Joueur[numJoueur].Case].proprietaire==0)   // Si il n'y a pas de propriétaire
         {
            if(caseJeu[Joueur[numJoueur].Case].prix_achat<=Joueur[numJoueur].argent)
            {
                printf("Vous pouvez acheter cette case au prix de %d dollars\n",caseJeu[Joueur[numJoueur].Case].prix_achat);
                printf("Voulez vous acheter ce lieu ? O,N :");
                achat=getchar();
                toucheEntrer=getchar();                               // On part du principe qu'on a appuyé à la fois sur O et entrée, on met un autre getchar qui permet de récupérer le caractère touche entrer et
                                                                      // et le stocké
                if(achat=='O')
                {
                    Joueur[numJoueur].argent=Joueur[numJoueur].argent-caseJeu[Joueur[numJoueur].Case].prix_achat; // L'argent du joueur correspond à la différence de l'argent qu'à le joueur au début et le prix d'achat d'une case
                    caseJeu[Joueur[numJoueur].Case].proprietaire=numJoueur;                                       // La case achetée appartient au joueur qui l'a achetée
                }
            }
            else
            {
                printf("Vous n'avez pas assez d'argent pour acheter ce lieu\n");
            }
         }
         else
         {
            if(caseJeu[Joueur[numJoueur].Case].proprietaire!=numJoueur)        // Si le propriétaire de la case est différent de celui qui est en train de jouer et l'autre joueur va devoir payer un loyer
            {
                printf("Cette case appartient deja au Joueur %d\n",caseJeu[Joueur[numJoueur].Case].proprietaire);
                if(Joueur[numJoueur].Case==28 || Joueur[numJoueur].Case==13)   // Si le joueur est dans la case 28 du plateau qui correspond à la compagnie des eaux ou dans la case Compagnie d'éléctricité
                {
                    if(caseJeu[28].proprietaire==caseJeu[13].proprietaire)
                    {
                    Joueur[numJoueur].argent=Joueur[numJoueur].argent-10*resultatDe1_De2;             // Le joueur devra payer le loyer de la compagnie des eaux qui correspond aux nombre des dés multiplié par 4
                    printf("Vous devez payer %d dollars de loyer au joueur %d\n",10*resultatDe1_De2,caseJeu[Joueur[numJoueur].Case].proprietaire);
                    Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent=Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent+10*resultatDe1_De2;    // Le propriétaire de la case reçoit de l'argent en plus venant du joueur qui doit payer le loyer
                    }
                    else
                    {
                    Joueur[numJoueur].argent=Joueur[numJoueur].argent-4*resultatDe1_De2;             // Le joueur devra payer le loyer de la compagnie des eaux qui correspond aux nombre des dés multiplié par 4
                    printf("Vous devez payer %d dollars de loyer au joueur %d\n",4*resultatDe1_De2,caseJeu[Joueur[numJoueur].Case].proprietaire);
                    Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent=Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent+4*resultatDe1_De2; // Le propriétaire de la case reçoit de l'argent en plus venant du joueur qui doit payer le loyer

                    }
                }
                else if(Joueur[numJoueur].Case==4)
                {
                    Joueur[numJoueur].argent=Joueur[numJoueur].argent-10*resultatDe1_De2; // Le joueur devra payer le loyer de la case Impôt sur le revenu qui correspond aux nombre des dés multiplié par 10
                    printf("Vous devez payer %d dollars de loyer au joueur %d\n",10*resultatDe1_De2,caseJeu[Joueur[numJoueur].Case].proprietaire);
                    Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent=Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent+10*resultatDe1_De2; // Le propriétaire de la case reçoit de l'argent en plus venant du joueur qui doit payer le loyer
                }
                else if(Joueur[numJoueur].Case==5 || Joueur[numJoueur].Case==15 || Joueur[numJoueur].Case==25 || Joueur[numJoueur].Case==35) // Si un joueur est au moins sur une des 4 gares du plateau
                {
                    testColor=0;           // Il va permettre de compter le nombre de gares dont le propriétaire a
                    for (i=5;i<=35;i+=10)  // On crée une boucle qui compte les cases avec les gares de 10 en 10 et où on va voir combien de gares possède le joueur qui est propriétaire
                    {
                        if(caseJeu[i].proprietaire==caseJeu[Joueur[numJoueur].Case].proprietaire) // On teste si le propriétaire à qui le joueur doit payer le loyer possède x gares
                        {
                            testColor=testColor+1; // Si le joueur qui a une gare on ajoutera 1 à testColor si il en a 2 on ajoutera 2 et ainsi de suite
                        }
                    }
                    loyerGare=25;
                    for(i=1;i<testColor;i++)   // On compte le nombre de gares qu'il y'a
                    {
                        loyerGare=loyerGare*2;
                    }
                    printf("Le loyer de la Gare ou le joueur se situe est %d dollars",loyerGare);
                    Joueur[numJoueur].argent=Joueur[numJoueur].argent-loyerGare;   // Le joueur devra payer le loyer au Joueur concerné
                    printf("Vous devez payer %d dollars de loyer au joueur %d\n",loyerGare,caseJeu[Joueur[numJoueur].Case].proprietaire);
                    Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent=Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent+loyerGare; // Le propriétaire de la case reçoit de l'argent en plus venat du joueur qui doit payer le loyer
                }
                else
                {
                     testColor=1;
                     numCase=Joueur[numJoueur].Case;         // La variable numCase corespond à la case où est le joueur
                     for (i=1;i<40;i++)                      // Boucle qui permet de compter toutes les cases pour savoir si le joueur a 3 cartes de même couleur
                    {
                        if(caseJeu[i].Color==caseJeu[numCase].Color) // Est ce que la case à la même couleur que la case où je veux mettre la maison
                        {
                            if (caseJeu[i].proprietaire!=numJoueur)   // Si le joueur n'est pas propriétaire de la case
                            {
                                testColor=0;                         // Le joueur n'est pas propriétaire de toutes les cases de même couleur
                            }
                        }
                    }
                    if(testColor==1)
                    {
                        printf("Comme le joueur a toutes les cases de même couleurs vous dever payer le loyer");
                        Joueur[numJoueur].argent=Joueur[numJoueur].argent-2*caseJeu[Joueur[numJoueur].Case].loyer[caseJeu[Joueur[numJoueur].Case].Nb_Maison];   // Le joueur devra payer le loyer au Joueur concerné
                        printf("Vous devez payer %d dollars de loyer au joueur %d\n",2*caseJeu[Joueur[numJoueur].Case].loyer[caseJeu[Joueur[numJoueur].Case].Nb_Maison],caseJeu[Joueur[numJoueur].Case].proprietaire);
                        Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent=Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent+2*caseJeu[Joueur[numJoueur].Case].loyer[caseJeu[Joueur[numJoueur].Case].Nb_Maison]; // Le propriétaire de la case reçoit de l'argent en plus venat du joueur qui doit payer le loyer
                    }
                    else
                    {
                        Joueur[numJoueur].argent=Joueur[numJoueur].argent-caseJeu[Joueur[numJoueur].Case].loyer[caseJeu[Joueur[numJoueur].Case].Nb_Maison];// Le joueur devra payer le loyer au Joueur concerné
                        printf("Vous devez payer %d dollars de loyer au joueur %d\n",caseJeu[Joueur[numJoueur].Case].loyer[caseJeu[Joueur[numJoueur].Case].Nb_Maison],caseJeu[Joueur[numJoueur].Case].proprietaire);
                        Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent=Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent+caseJeu[Joueur[numJoueur].Case].loyer[caseJeu[Joueur[numJoueur].Case].Nb_Maison]; // Le propriétaire de la case reçoit de l'argent en plus venat du joueur qui doit payer le loyer
                    }
                }

                printf("Vous avez maintenant %d dollars\n",Joueur[numJoueur].argent);    // On affiche la nouvelle cagnotte du Joueur qui a payé le loyer
                printf("Le joueur %d a maintenant %d dollars\n",caseJeu[Joueur[numJoueur].Case].proprietaire,Joueur[caseJeu[Joueur[numJoueur].Case].proprietaire].argent); // On affiche la nuvelle cagnotte du propriétaire
            }
            else
            {
              printf("Cette case vous appartient\n");
            }
         }
    }
    if(Joueur[numJoueur].argent<0) // Si le joueur n'a plus d'argent
    {
       printf("Le Joueur %d a perdu\n",numJoueur);
       Joueur[numJoueur].joueurenJeu=0;
       Joueur[numJoueur].nbDoubles=0;
    }

}
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
         HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
         SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
void afficherTableau(char tabJeu[90][192],int tabJeuColor[90][192])
{
    int i,j;
    for (i=0;i<=79;i++)
    {
        for(j=0;j<=191;j++)
        {
            Color(15,tabJeuColor[i][j]);         // On fait appelle la variable tabJeuColor où on fait appelle aux i et j
            printf("%c",tabJeu[i][j]);          // On écrit le caractère à la position lui correspondant [0,0]
        }
        printf("\n");
    }
}
void remplirCases(Case caseJeu[40])
{
    int i;
    for (i=0;i<=39;i++)                   // On crée une boucle où on affiche rien dans les maisons, les hotels et propriétaires dans les cases du plateau
    {
       caseJeu[i].Nb_Maison=0;
       caseJeu[i].proprietaire=0;
       caseJeu[i].Color=0;
    }
    strcpy(caseJeu[0].nom1,"   Depart     ");       // On affiche la chaine de caractères Depart
    strcpy(caseJeu[0].nom2,"              ");
    caseJeu[0].prix_achat=0;
    caseJeu[0].prix_maison=0;
    caseJeu[0].loyer[0]=0;
    caseJeu[0].loyer[1]=0;
    caseJeu[0].loyer[2]=0;
    caseJeu[0].loyer[3]=0;
    caseJeu[0].loyer[4]=0;
    caseJeu[0].loyer[5]=0;
    caseJeu[0].Color=0;
    caseJeu[0].COORD_LIGNE=70;                  // On affiche les coordonnées des lignes
    caseJeu[0].COORD_COLONNE=170;               // On affiche les coordonnées des colonnes*/
    strcpy(caseJeu[1].nom1,"  BOULEVARD DE");   // On affiche la chaine de caractères Boulevard de Belleville
    strcpy(caseJeu[1].nom2,"  BELLEVILLE");
    caseJeu[1].prix_achat=60;                  // On affiche son prix d'achat
    caseJeu[1].prix_maison=50;
    caseJeu[1].loyer[0]=2;                     // On affiche le loyer de l
    caseJeu[1].loyer[1]=10;
    caseJeu[1].loyer[2]=30;
    caseJeu[1].loyer[3]=90;
    caseJeu[1].loyer[4]=160;
    caseJeu[1].loyer[5]=250;
    caseJeu[1].Color=8;
    caseJeu[1].COORD_LIGNE=70;                 // On affiche les coordonnées des lignes
    caseJeu[1].COORD_COLONNE=153;              // On affiche les coordonnées des colonnes
    strcpy(caseJeu[2].nom1,"    CAISSE DE ");  // On affiche la chaine de caractères Caisse de Communaute
    strcpy(caseJeu[2].nom2,"   COMMUNAUTE");
    caseJeu[2].prix_achat=0;
    caseJeu[2].prix_maison=0;
    caseJeu[2].loyer[0]=0;
    caseJeu[2].loyer[1]=0;
    caseJeu[2].loyer[2]=0;
    caseJeu[2].loyer[3]=0;
    caseJeu[2].loyer[4]=0;
    caseJeu[2].loyer[5]=0;
    caseJeu[2].Color=0;
    caseJeu[2].COORD_LIGNE=70;                  // On affiche les coordonnées des lignes
    caseJeu[2].COORD_COLONNE=136;               // On affiche les coordonnées des colonnes
    strcpy(caseJeu[3].nom1,"       RUE");      // On affiche la chaine de caractères Rue Lecourbe
    strcpy(caseJeu[3].nom2,"    LECOURBE");
    caseJeu[3].prix_achat=60;                  // On affiche son prix d'achat
    caseJeu[3].prix_maison=50;
    caseJeu[3].loyer[0]=4;
    caseJeu[3].loyer[1]=20;
    caseJeu[3].loyer[2]=60;
    caseJeu[3].loyer[3]=180;
    caseJeu[3].loyer[4]=320;
    caseJeu[3].loyer[5]=450;
    caseJeu[3].Color=8;
    caseJeu[3].COORD_LIGNE=70;                  // On affiche les coordonnées des lignes
    caseJeu[3].COORD_COLONNE=119;               // On affiche les coordonnées des colonnes
    strcpy(caseJeu[4].nom1,"   IMPOT SUR");     // On affiche la chaine de caractères Impot sur le revenu
    strcpy(caseJeu[4].nom2,"   LE REVENU");
    caseJeu[4].prix_achat=200;                  // On affiche son prix d'achat
    caseJeu[4].prix_maison=0;
    caseJeu[4].loyer[0]=0;
    caseJeu[4].loyer[1]=0;
    caseJeu[4].loyer[2]=0;
    caseJeu[4].loyer[3]=0;
    caseJeu[4].loyer[4]=0;
    caseJeu[4].loyer[5]=0;
    caseJeu[4].Color=0;
    caseJeu[4].COORD_LIGNE=70;                  // On affiche les coordonnées des lignes
    caseJeu[4].COORD_COLONNE=102;               // On affiche les coordonnées des colonnes
    strcpy(caseJeu[5].nom1,"    GARE DE");      // On affiche la chaine de caractères Gare de Montparnasse
    strcpy(caseJeu[5].nom2,"  MONTPARNASSE");
    caseJeu[5].prix_achat=200;                  // On affiche son prix d'achat
    caseJeu[5].prix_maison=0;
    caseJeu[5].loyer[0]=25;
    caseJeu[5].loyer[1]=0;
    caseJeu[5].loyer[2]=0;
    caseJeu[5].loyer[3]=0;
    caseJeu[5].loyer[4]=0;
    caseJeu[5].loyer[5]=0;
    caseJeu[5].Color=0;
    caseJeu[5].COORD_LIGNE=70;                  // On affiche les coordonnées des lignes
    caseJeu[5].COORD_COLONNE=85;                // // On affiche les coordonnées des colonnes
    strcpy(caseJeu[6].nom1,"     RUE DE");      // On affiche la chaine de caractères Rue de Vaugirard
    strcpy(caseJeu[6].nom2,"    VAUGIRARD");
    caseJeu[6].prix_achat=100;                  // On affiche son prix d'achat
    caseJeu[6].prix_maison=50;
    caseJeu[6].loyer[0]=6;
    caseJeu[6].loyer[1]=30;
    caseJeu[6].loyer[2]=90;
    caseJeu[6].loyer[3]=270;
    caseJeu[6].loyer[4]=400;
    caseJeu[6].loyer[5]=550;
    caseJeu[6].Color=11;
    caseJeu[6].COORD_LIGNE=70;                  // On affiche les coordonnées des lignes
    caseJeu[6].COORD_COLONNE=68;                // On affiche les coordonnées des colonnes
    strcpy(caseJeu[7].nom1,"     CHANCE");      // On affiche la chaine de caractères Chance
    strcpy(caseJeu[7].nom2,"     ");
    caseJeu[7].prix_achat=0;
    caseJeu[7].prix_maison=0;
    caseJeu[7].loyer[0]=0;
    caseJeu[7].loyer[1]=0;
    caseJeu[7].loyer[2]=0;
    caseJeu[7].loyer[3]=0;
    caseJeu[7].loyer[4]=0;
    caseJeu[7].loyer[5]=0;
    caseJeu[7].Color=0;
    caseJeu[7].COORD_LIGNE=70;                  // On affiche les coordonnées des lignes
    caseJeu[7].COORD_COLONNE=51;                // On affiche les coordonnées des colonnes
    strcpy(caseJeu[8].nom1,"    RUE DE");       // On affiche la chaine de caractères Rue de Courcelles
    strcpy(caseJeu[8].nom2,"  COURCELLES");
    caseJeu[8].prix_achat=100;                  // On affiche son prix d'achat
    caseJeu[8].prix_maison=50;
    caseJeu[8].loyer[0]=6;
    caseJeu[8].loyer[1]=30;
    caseJeu[8].loyer[2]=90;
    caseJeu[8].loyer[3]=270;
    caseJeu[8].loyer[4]=400;
    caseJeu[8].loyer[5]=550;
    caseJeu[8].Color=11;
    caseJeu[8].COORD_LIGNE=70;                  // // On affiche les coordonnées des lignes
    caseJeu[8].COORD_COLONNE=34;                // On affiche les coordonnées des colonnes
    strcpy(caseJeu[9].nom1," AVENUE DE LA");    // On affiche la chaine de caractères Avenue de la Republique
    strcpy(caseJeu[9].nom2,"  REPUBLIQUE");
    caseJeu[9].prix_achat=120;                  // On affiche son prix d'achat
    caseJeu[9].prix_maison=50;
    caseJeu[9].loyer[0]=8;
    caseJeu[9].loyer[1]=40;
    caseJeu[9].loyer[2]=100;
    caseJeu[9].loyer[3]=300;
    caseJeu[9].loyer[4]=450;
    caseJeu[9].loyer[5]=600;
    caseJeu[9].Color=11;
    caseJeu[9].COORD_LIGNE=70;                  // On affiche les coordonnées des lignes
    caseJeu[9].COORD_COLONNE=17;                // On affiche les coordonnées des colonnes
    strcpy(caseJeu[10].nom1,"     PRISON   ");     // On affiche la chaine de caractères Aller en Prison
    strcpy(caseJeu[10].nom2,"              ");
    caseJeu[10].prix_achat=0;
    caseJeu[10].prix_maison=0;
    caseJeu[10].loyer[0]=0;
    caseJeu[10].loyer[1]=0;
    caseJeu[10].loyer[2]=0;
    caseJeu[10].loyer[3]=0;
    caseJeu[10].loyer[4]=0;
    caseJeu[10].loyer[5]=0;
    caseJeu[10].Color=0;
    caseJeu[10].COORD_LIGNE=70;                   // On affiche les coordonnées des lignes
    caseJeu[10].COORD_COLONNE=0;                  // On affiche les coordonnées des colonnes
    strcpy(caseJeu[11].nom1,"  BOULEVARD DE");    // On affiche la chaine de caractères Boulevard de la Villette
    strcpy(caseJeu[11].nom2,"  LA VILLETTE");
    caseJeu[11].prix_achat=140;                   // On affiche son prix d'achat
    caseJeu[11].prix_maison=100;
    caseJeu[11].loyer[0]=10;
    caseJeu[11].loyer[1]=50;
    caseJeu[11].loyer[2]=150;
    caseJeu[11].loyer[3]=450;
    caseJeu[11].loyer[4]=625;
    caseJeu[11].loyer[5]=750;
    caseJeu[11].Color=13;
    caseJeu[11].COORD_LIGNE=63;                    // On affiche les coordonnées des lignes
    caseJeu[11].COORD_COLONNE=0;                   // On affiche les coordonnées des colonnes
    strcpy(caseJeu[12].nom1,"   COMPAGNIE");       // On affiche la chaine de caractères Compagnie d'Electricité
    strcpy(caseJeu[12].nom2,"   ELECTRICITE");
    caseJeu[12].prix_achat=0;
    caseJeu[12].prix_maison=0;
    caseJeu[12].loyer[0]=0;
    caseJeu[12].loyer[1]=0;
    caseJeu[12].loyer[2]=0;
    caseJeu[12].loyer[3]=0;
    caseJeu[12].loyer[4]=0;
    caseJeu[12].loyer[5]=0;
    caseJeu[12].Color=0;
    caseJeu[12].COORD_LIGNE=56;                    // On affiche les coordonnées des lignes
    caseJeu[12].COORD_COLONNE=0;                   // On affiche les coordonnées des colonnes
    strcpy(caseJeu[13].nom1,"    RUE DE");         // On affiche la chaine de caractères Rue de Neuilly
    strcpy(caseJeu[13].nom2,"    NEUILLY");
    caseJeu[13].prix_achat=140;                    // On affiche son prix d'achat
    caseJeu[13].prix_maison=100;
    caseJeu[13].loyer[0]=10;
    caseJeu[13].loyer[1]=50;
    caseJeu[13].loyer[2]=150;
    caseJeu[13].loyer[3]=450;
    caseJeu[13].loyer[4]=625;
    caseJeu[13].loyer[5]=750;
    caseJeu[13].Color=13;
    caseJeu[13].COORD_LIGNE=49;                     // On affiche les coordonnées des lignes
    caseJeu[13].COORD_COLONNE=0;                    // On affiche les coordonnées des colonnes
    strcpy(caseJeu[14].nom1,"    RUE DE");          // On affiche la chaine de caractères Rue de Paradis
    strcpy(caseJeu[14].nom2,"    PARADIS");
    caseJeu[14].prix_achat=200;                     // On affiche son prix d'achat
    caseJeu[14].prix_maison=100;
    caseJeu[14].loyer[0]=12;
    caseJeu[14].loyer[1]=60;
    caseJeu[14].loyer[2]=180;
    caseJeu[14].loyer[3]=500;
    caseJeu[14].loyer[4]=700;
    caseJeu[14].loyer[5]=900;
    caseJeu[14].Color=13;
    caseJeu[14].COORD_LIGNE=42;                     // On affiche les coordonnées des lignes
    caseJeu[14].COORD_COLONNE=0;                    // On affiche les coordonnées des colonnes
    strcpy(caseJeu[15].nom1,"    GARE DE");         // On affiche la chaine de caractères Gare de Lyon
    strcpy(caseJeu[15].nom2,"     LYON");
    caseJeu[15].prix_achat=200;                     // On affiche son prix d'achat
    caseJeu[15].prix_maison=0;
    caseJeu[15].loyer[0]=25;
    caseJeu[15].loyer[1]=0;
    caseJeu[15].loyer[2]=0;
    caseJeu[15].loyer[3]=0;
    caseJeu[15].loyer[4]=0;
    caseJeu[15].loyer[5]=0;
    caseJeu[15].Color=0;
    caseJeu[15].COORD_LIGNE=35;                      // On affiche les coordonnées des lignes
    caseJeu[15].COORD_COLONNE=0;                     // On affiche les coordonnées des colonnes
    strcpy(caseJeu[16].nom1,"     AVENUE");          // On affiche la chaine de caractères Avenue Mozart
    strcpy(caseJeu[16].nom2,"     MOZART");
    caseJeu[16].prix_achat=180;                      // On affiche son prix d'achat
    caseJeu[16].prix_maison=100;
    caseJeu[16].loyer[0]=14;
    caseJeu[16].loyer[1]=70;
    caseJeu[16].loyer[2]=200;
    caseJeu[16].loyer[3]=550;
    caseJeu[16].loyer[4]=750;
    caseJeu[16].loyer[5]=950;
    caseJeu[16].Color=6;
    caseJeu[16].COORD_LIGNE=28;                       // On affiche les coordonnées des lignes
    caseJeu[16].COORD_COLONNE=0;                      // On affiche les coordonnées des colonnes
    strcpy(caseJeu[17].nom1,"   CAISSE DE");          // On affiche la chaine de caractères Caisse de Communauté
    strcpy(caseJeu[17].nom2,"  COMMUNAUTE");
    caseJeu[17].prix_achat=0;
    caseJeu[17].prix_maison=0;
    caseJeu[17].loyer[0]=0;
    caseJeu[17].loyer[1]=0;
    caseJeu[17].loyer[2]=0;
    caseJeu[17].loyer[3]=0;
    caseJeu[17].loyer[4]=0;
    caseJeu[17].loyer[5]=0;
    caseJeu[17].Color=0;
    caseJeu[17].COORD_LIGNE=21;                        // On affiche les coordonnées des lignes
    caseJeu[17].COORD_COLONNE=0;                       // On affiche les coordonnées des colonnes
    strcpy(caseJeu[18].nom1,"    BOULEVARD");          // On affiche la chaine de caractères Boulevard Saint Michel
    strcpy(caseJeu[18].nom2,"   SAINT-MICHEL");
    caseJeu[18].prix_achat=100;                        // On affiche son prix d'achat
    caseJeu[18].prix_maison=100;
    caseJeu[18].loyer[0]=14;
    caseJeu[18].loyer[1]=0;
    caseJeu[18].loyer[2]=0;
    caseJeu[18].loyer[3]=0;
    caseJeu[18].loyer[4]=0;
    caseJeu[18].loyer[5]=0;
    caseJeu[18].Color=6;
    caseJeu[18].COORD_LIGNE=14;                        // On affiche les coordonnées des lignes
    caseJeu[18].COORD_COLONNE=0;                       // On affiche les coordonnées des colonnes
    strcpy(caseJeu[19].nom1,"     PLACE ");         // On affiche la chaine de caractères Place Pigalle
    strcpy(caseJeu[19].nom2,"    PIGALLE");
    caseJeu[19].prix_achat=120;                        // On affiche son prix d'achat
    caseJeu[19].prix_maison=100;
    caseJeu[19].loyer[0]=16;
    caseJeu[19].loyer[1]=80;
    caseJeu[19].loyer[2]=220;
    caseJeu[19].loyer[3]=600;
    caseJeu[19].loyer[4]=800;
    caseJeu[19].loyer[5]=1000;
    caseJeu[19].Color=6;
    caseJeu[19].COORD_LIGNE=7;                         // On affiche les coordonnées des lignes
    caseJeu[19].COORD_COLONNE=0;                       // On affiche les coordonnées des colonnes
    strcpy(caseJeu[20].nom1,"     PARC ");         // On affiche la chaine de caractères Parc Gratuit
    strcpy(caseJeu[20].nom2,"   GRATUIT");
    caseJeu[20].prix_achat=0;
    caseJeu[20].prix_maison=0;
    caseJeu[20].loyer[0]=0;
    caseJeu[20].loyer[1]=0;
    caseJeu[20].loyer[2]=0;
    caseJeu[20].loyer[3]=0;
    caseJeu[20].loyer[4]=0;
    caseJeu[20].loyer[5]=0;
    caseJeu[20].Color=0;
    caseJeu[20].COORD_LIGNE=0;                         // On affiche les coordonnées des lignes
    caseJeu[20].COORD_COLONNE=0;                       // On affiche les coordonnées des colonnes
     strcpy(caseJeu[21].nom1,"   AVENUE ");        // On affiche la chaine de caractères Avenue Matignon
     strcpy(caseJeu[21].nom2,"  MATIGNON");
    caseJeu[21].prix_achat=220;                       // On affiche son prix d'achat
    caseJeu[21].prix_maison=150;
    caseJeu[21].loyer[0]=18;
    caseJeu[21].loyer[1]=90;
    caseJeu[21].loyer[2]=250;
    caseJeu[21].loyer[3]=700;
    caseJeu[21].loyer[4]=875;
    caseJeu[21].loyer[5]=1050;
    caseJeu[21].Color=4;
    caseJeu[21].COORD_LIGNE=0;                        // On affiche les coordonnées des lignes
    caseJeu[21].COORD_COLONNE=17;                     // On affiche les coordonnées des colonnes
    strcpy(caseJeu[22].nom1,"     CHANCE");           // On affiche la chaine de caractères Chance
    strcpy(caseJeu[22].nom2,"    ");
    caseJeu[22].prix_achat=0;
    caseJeu[22].prix_maison=0;
    caseJeu[22].loyer[0]=0;
    caseJeu[22].loyer[1]=0;
    caseJeu[22].loyer[2]=0;
    caseJeu[22].loyer[3]=0;
    caseJeu[22].loyer[4]=0;
    caseJeu[22].loyer[5]=0;
    caseJeu[22].Color=0;
    caseJeu[22].COORD_LIGNE=0;                        // On affiche les coordonnées des lignes
    caseJeu[22].COORD_COLONNE=34;                     // On affiche les coordonnées des colonnes
    strcpy(caseJeu[23].nom1,"   BOULEVARD");          // On affiche la chaine de caractères Boulevard Malhserbes
    strcpy(caseJeu[23].nom2,"   MALHERBES");
    caseJeu[23].prix_achat=220;                       // On affiche son prix d'achat
    caseJeu[23].prix_maison=150;
    caseJeu[23].loyer[0]=18;
    caseJeu[23].loyer[1]=90;
    caseJeu[23].loyer[2]=250;
    caseJeu[23].loyer[3]=700;
    caseJeu[23].loyer[4]=875;
    caseJeu[23].loyer[5]=1050;
    caseJeu[23].Color=4;
    caseJeu[23].COORD_LIGNE=0;                         // On affiche les coordonnées des lignes
    caseJeu[23].COORD_COLONNE=51;                      // On affiche les coordonnées des colonnes
    strcpy(caseJeu[24].nom1,"     AVENUE");            // On affiche la chaine de caractères Avenue Henri Martin
    strcpy(caseJeu[24].nom2,"  HENRI-MARTIN");
    caseJeu[24].prix_achat=200;                        // On affiche le prix d'achat
    caseJeu[24].prix_maison=150;
    caseJeu[24].loyer[0]=20;
    caseJeu[24].loyer[1]=100;
    caseJeu[24].loyer[2]=300;
    caseJeu[24].loyer[3]=750;
    caseJeu[24].loyer[4]=925;
    caseJeu[24].loyer[5]=1100;
    caseJeu[24].Color=4;
    caseJeu[24].COORD_LIGNE=0;                         // On affiche les coordonnées des lignes
    caseJeu[24].COORD_COLONNE=68;                      // On affiche les coordonnées des colonnes
    strcpy(caseJeu[25].nom1,"    GARE DU");            // On affiche la chaine de caractères Gare du Nord
    strcpy(caseJeu[25].nom2,"      NORD");
    caseJeu[25].prix_achat=200;                        // On affiche le prix d'achat
    caseJeu[25].prix_maison=0;
    caseJeu[25].loyer[0]=25;
    caseJeu[25].loyer[1]=0;
    caseJeu[25].loyer[2]=0;
    caseJeu[25].loyer[3]=0;
    caseJeu[25].loyer[4]=0;
    caseJeu[25].loyer[5]=0;
    caseJeu[25].Color=0;
    caseJeu[25].COORD_LIGNE=0;                         // On affiche les coordonnées des lignes
    caseJeu[25].COORD_COLONNE=85;                      // On affiche les coordonnées des colonnes
    strcpy(caseJeu[26].nom1,"    FAUBOURG");           // On affiche la chaine de caractères Faubourg Saint Honore
    strcpy(caseJeu[26].nom2,"  SAINT-HONORE");
    caseJeu[26].prix_achat=260;                        // On affiche le prix d'achat
    caseJeu[26].prix_maison=150;
    caseJeu[26].loyer[0]=22;
    caseJeu[26].loyer[1]=110;
    caseJeu[26].loyer[2]=330;
    caseJeu[26].loyer[3]=800;
    caseJeu[26].loyer[4]=975;
    caseJeu[26].loyer[5]=1150;
    caseJeu[26].Color=14;
    caseJeu[26].COORD_LIGNE=0;                         // On affiche les coordonnées des lignes
    caseJeu[26].COORD_COLONNE=102;                     // On affiche les coordonnées des colonnes
    strcpy(caseJeu[27].nom1,"    PLACE DE ");          // On affiche la chaine de caractères Place de la Bourse
    strcpy(caseJeu[27].nom2,"    LA BOURSE");
    caseJeu[27].prix_achat=260;                        // On affiche le prix d'achat
    caseJeu[27].prix_maison=150;
    caseJeu[27].loyer[0]=22;
    caseJeu[27].loyer[1]=110;
    caseJeu[27].loyer[2]=330;
    caseJeu[27].loyer[3]=800;
    caseJeu[27].loyer[4]=975;
    caseJeu[27].loyer[5]=1150;
    caseJeu[27].Color=14;
    caseJeu[27].COORD_LIGNE=0;                          // On affiche les coordonnées des lignes
    caseJeu[27].COORD_COLONNE=119;                      // On affiche les coordonnées des colonnes
    strcpy(caseJeu[28].nom1,"  COMPAGNIE DES");         // On affiche la chaine de caractères Compagnie des eaux
    strcpy(caseJeu[28].nom2,"      EAUX");
    caseJeu[28].prix_achat=150;                          // On affiche le prix d'achat
    caseJeu[28].prix_maison=0;
    caseJeu[28].loyer[0]=0;
    caseJeu[28].loyer[1]=0;
    caseJeu[28].loyer[2]=0;
    caseJeu[28].loyer[3]=0;
    caseJeu[28].loyer[4]=0;
    caseJeu[28].loyer[5]=0;
    caseJeu[28].Color=0;
    caseJeu[28].COORD_LIGNE=0;                            // On affiche les coordonnées des lignes
    caseJeu[28].COORD_COLONNE=136;                        // On affiche les coordonnées des colonnes
    strcpy(caseJeu[29].nom1,"     RUE     ");           // On affiche la chaine de caractères rue de la Fayette
    strcpy(caseJeu[29].nom2," LA FAYETTE  ");
    caseJeu[29].prix_achat=150;                           // On affiche le prix d'achat
    caseJeu[29].prix_maison=150;
    caseJeu[29].loyer[0]=24;
    caseJeu[29].loyer[1]=120;
    caseJeu[29].loyer[2]=360;
    caseJeu[29].loyer[3]=850;
    caseJeu[29].loyer[4]=1025;
    caseJeu[29].loyer[5]=1200;
    caseJeu[29].Color=14;
    caseJeu[29].COORD_LIGNE=0;                            // On affiche les coordonnées des lignes
    caseJeu[29].COORD_COLONNE=153;                        // On affiche les coordonnées des colonnes
    strcpy(caseJeu[30].nom1,"  ALLER EN");               // On affiche la chaine de caractères Aller en prison
    strcpy(caseJeu[30].nom2,"   PRISON ");
    caseJeu[30].prix_achat=0;
    caseJeu[30].prix_maison=0;
    caseJeu[30].loyer[0]=0;
    caseJeu[30].loyer[1]=0;
    caseJeu[30].loyer[2]=0;
    caseJeu[30].loyer[3]=0;
    caseJeu[30].loyer[4]=0;
    caseJeu[30].loyer[5]=0;
    caseJeu[30].Color=0;
    caseJeu[30].COORD_LIGNE=0;                           // On affiche les coordonnées des lignes
    caseJeu[30].COORD_COLONNE=170;                       // On affiche les coordonnées des colonnes
    strcpy(caseJeu[31].nom1,"   AVENUE DE");             // On affiche la chaine de caractères Avenue De Bertille
    strcpy(caseJeu[31].nom2,"    BERTILLE");
    caseJeu[31].prix_achat=300;                          // On affiche son prix d'achat
    caseJeu[31].prix_maison=0;
    caseJeu[31].loyer[0]=26;
    caseJeu[31].loyer[1]=130;
    caseJeu[31].loyer[2]=390;
    caseJeu[31].loyer[3]=900;
    caseJeu[31].loyer[4]=1100;
    caseJeu[31].loyer[5]=1275;
    caseJeu[31].Color=2;
    caseJeu[31].COORD_LIGNE=7;                           // On affiche les coordonnées des lignes
    caseJeu[31].COORD_COLONNE=170;                       // On affiche les coordonnées des colonnes
    strcpy(caseJeu[32].nom1,"    AVENUE");               // On affiche la chaine de caractères Avenue Foch
    strcpy(caseJeu[32].nom2,"     FOCH");
    caseJeu[32].prix_achat=300;
    caseJeu[32].prix_maison=200;
    caseJeu[32].loyer[0]=26;
    caseJeu[32].loyer[1]=130;
    caseJeu[32].loyer[2]=390;
    caseJeu[32].loyer[3]=900;
    caseJeu[32].loyer[4]=1100;
    caseJeu[32].loyer[5]=1275;
    caseJeu[32].Color=2;
    caseJeu[32].COORD_LIGNE=14;                         // On affiche les coordonnées des lignes
    caseJeu[32].COORD_COLONNE=170;                      // On affiche les coordonnées dees colonnes
    strcpy(caseJeu[33].nom1,"   CAISSE DE ");           // On affiche la chaine de caractères Caisse de Communauté
    strcpy(caseJeu[33].nom2,"   COMMUNAUTE");
    caseJeu[33].prix_achat=0;
    caseJeu[33].prix_maison=0;
    caseJeu[33].loyer[0]=28;
    caseJeu[33].loyer[1]=150;
    caseJeu[33].loyer[2]=450;
    caseJeu[33].loyer[3]=1000;
    caseJeu[33].loyer[4]=1200;
    caseJeu[33].loyer[5]=1400;
    caseJeu[33].Color=0;
    caseJeu[33].COORD_LIGNE=21;                         // On affiche les coordonnées des lignes
    caseJeu[33].COORD_COLONNE=170;                      // On affiche les coordonnées des colonnes
    strcpy(caseJeu[34].nom1,"    BOULEVARD ");          // On affiche la chaine de caractères Boulevard des Capucines
    strcpy(caseJeu[34].nom2,"  DES CAPUCINES");
    caseJeu[34].prix_achat=320;                         // On affiche le prix d'achat
    caseJeu[34].prix_maison=200;
    caseJeu[34].loyer[0]=28;
    caseJeu[34].loyer[1]=0;
    caseJeu[34].loyer[2]=0;
    caseJeu[34].loyer[3]=0;
    caseJeu[34].loyer[4]=0;
    caseJeu[34].loyer[5]=0;
    caseJeu[34].Color=2;
    caseJeu[34].COORD_LIGNE=28;                        // On affiche les coordonnées des lignes
    caseJeu[34].COORD_COLONNE=170;                     // On affiche les coordonnées des colonnes
    strcpy(caseJeu[35].nom1,"      GARE ");            // On affiche la chaine de caractères Gare Saint Lazare
    strcpy(caseJeu[35].nom2,"  SAINT-LAZARE");
    caseJeu[35].prix_achat=200;                        // On affiche le prix d'achat
    caseJeu[35].prix_maison=0;
    caseJeu[35].loyer[0]=25;
    caseJeu[35].loyer[1]=0;
    caseJeu[35].loyer[2]=0;
    caseJeu[35].loyer[3]=0;
    caseJeu[35].loyer[4]=0;
    caseJeu[35].loyer[5]=0;
    caseJeu[35].Color=0;
    caseJeu[35].COORD_LIGNE=35;                         // On affiche les coordonnées des lignes
    caseJeu[35].COORD_COLONNE=170;                      // On affiche les coordonées des colonnes
    strcpy(caseJeu[36].nom1,"    CHANCE");              // On affiche la chaine de caractères Chance
    strcpy(caseJeu[36].nom2,"  ");
    caseJeu[36].prix_achat=0;
    caseJeu[36].prix_maison=0;
    caseJeu[36].loyer[0]=0;
    caseJeu[36].loyer[1]=0;
    caseJeu[36].loyer[2]=0;
    caseJeu[36].loyer[3]=0;
    caseJeu[36].loyer[4]=0;
    caseJeu[36].loyer[5]=0;
    caseJeu[36].Color=0;
    caseJeu[36].COORD_LIGNE=42;                        // On affiche les coordonnées des lignes
    caseJeu[36].COORD_COLONNE=170;                     // On affiche les coordonnées des colonnes
    strcpy(caseJeu[37].nom1,"      AVENUE ");          // On affiche la chaine de caractères Avenue Champ Elysees
    strcpy(caseJeu[37].nom2,"  CHAMPS-ELYSEES");
    caseJeu[37].prix_achat=350;                        // On affiche le prix d'achat
    caseJeu[37].prix_maison=200;
    caseJeu[37].loyer[0]=35;
    caseJeu[37].loyer[1]=175;
    caseJeu[37].loyer[2]=500;
    caseJeu[37].loyer[3]=1100;
    caseJeu[37].loyer[4]=1300;
    caseJeu[37].loyer[5]=1500;
    caseJeu[37].Color=1;
    caseJeu[37].COORD_LIGNE=49;                        // On affiche les coordonnées des lignes
    caseJeu[37].COORD_COLONNE=170;                     // On affiche les coordonnées des colonnes
    strcpy(caseJeu[38].nom1,"    TAXE DE");            // On affiche la chaine de caractères Taxe de Luxe
    strcpy(caseJeu[38].nom2,"      LUXE");
    caseJeu[38].prix_achat=0;
    caseJeu[38].prix_maison=0;
    caseJeu[38].loyer[0]=0;
    caseJeu[38].loyer[1]=0;
    caseJeu[38].loyer[2]=0;
    caseJeu[38].loyer[3]=0;
    caseJeu[38].loyer[4]=0;
    caseJeu[38].loyer[5]=0;
    caseJeu[38].Color=0;
    caseJeu[38].COORD_LIGNE=56;                        // On affiche les coordonnées des lignes
    caseJeu[38].COORD_COLONNE=170;                     // On affiche les coordonnées des colonnes
    strcpy(caseJeu[39].nom1,"     RUE DE");            // On affiche la chaine de caractères Rue de la paix
    strcpy(caseJeu[39].nom2,"     LA PAIX");
    caseJeu[39].prix_achat=170;                         // On affiche le prix d'achat
    caseJeu[39].prix_maison=200;
    caseJeu[39].loyer[0]=50;                          // On fixe le loyer de base de la case
    caseJeu[39].loyer[1]=200;                           // On fixe le loyer de la 1ère maison
    caseJeu[39].loyer[2]=600;                           // On fixe le loyer de la 2ème maison
    caseJeu[39].loyer[3]=1400;                           // On fixe le loyer de la 3ème maison
    caseJeu[39].loyer[4]=1700;                          // On fixe le loyer de la 4ème maison
    caseJeu[39].loyer[5]=2000;                           // On fixe le loyer de l'Hotel
    caseJeu[39].Color=1;
    caseJeu[39].COORD_LIGNE=63;                         // On affiche les coordonnées des lignes
    caseJeu[39].COORD_COLONNE=170;                      // On affiche les coordonnées des colonnes
}

void InitialiserTabCouleur(int tabJeuColor[90][192])
{
     int i,j;
    for (i=0;i<=89;i++)
    {
        for(j=0;j<=191;j++)
            tabJeuColor[i][j]=0;          // On écrit le caractère à la position lui correspondant [0,0] où le fond sera en noir
    }
}

void testClavier()
{
    char ch =' ';                 // Si on ne met rien, on ne sait pas ce que contient la variable ch
    char ch2 = ' ';
    while(ch!='N')
    {
         printf("Veuillez saisir un caractere");
         ch=getchar();                         // permet de récupérer le caractère saisie
         printf("Le caractere est %c\n",ch);
         ch2=getchar();                       // permet de récupérer l'entrée
    }
}
void acheterMaison(char tabJeu[90][192],Case caseJeu[40],Joueur Joueur[5],int numJoueur)
{
    int i,testColor;
    int numCase;
    char c;
    printf("Sur quelles cases voulez vous acheter une maison ?");
    scanf("%d",&numCase);
    printf("Vous voulez mettre une maison sur la case %d\n",numCase);
    testColor=1;                                    // La variable dit que le joueur est propriétaire de toutes les cases de cette couleur
    if(caseJeu[numCase].proprietaire==numJoueur)   // Si un joueur est propriétaire de la case où il est
    {
        for (i=1;i<40;i++)                      // Boucle qui permet de compter toutes les cases pour savoir si le joueur a 3 cartes de même couleur
        {
           if(caseJeu[i].Color==caseJeu[numCase].Color) // Est ce que la case à la même couleur que la case où je veux mettre la maison
           {
               if (caseJeu[i].proprietaire!=numJoueur)   // Si le joueur n'est pas propriétaire de la case
                {
                    testColor=0;                         // Le joueur n'est pas propriétaire de toutes les cases de même couleur
                }
           }
        }
        if(testColor==1)
        {
           if(Joueur[numJoueur].argent>=caseJeu[numCase].prix_maison)  // on peut acheter un maison de plus ou hotel
           {
               if(caseJeu[numCase].Nb_Maison<5)
               {
                    caseJeu[numCase].Nb_Maison=caseJeu[numCase].Nb_Maison+1;    // On ajoute une maison dans la case où on veut la metttre
                    Joueur[numJoueur].argent=Joueur[numJoueur].argent-caseJeu[numCase].prix_maison; // On paye la maison
               }
               else
               {
                   printf("Vous avez deja un hotel sur cette case, vous ne pouvez plus rien acheter\n");
               }

           }
           else
           {
               printf("Vous ne pouvez pas acheter de maison car vous n'avez pas assez d'argent\n");
           }

        }
        else
        {
            printf("Vous ne pouvez pas mettre de maisons car vous n'êtes pas propriéatire des cases de la même couleur\n");
        }

    }
    else
    {
      printf("Vous ne pouvez pas mettre de maisons dans cette case car vous n'etes pas proprietaire\n");
    }
    do
    {
        c = getchar();                  // On met dans la variable c les caractères saisie dans le buffer
    } while (c != '\n' && c != EOF);   // On vide le buffer avec tous les caractères comme le \n

}
int main()
{
    int resultatDe;
    int numJoueur;
    char continuerJouer='O';
    char toucheEntrer=' ';
    int tabJeuColor[90][192]; // On crée un second tableau pour définir les couleurs de chaques cases
    char tabJeu[90][192];   // On crée un tableau représentant les dimensions totales du plateau de jeu
    Case caseJeu[40];
    Joueur Joueur[5];
    ParamJeu ParamJeu;
    do{
       printf("Combien de joueurs jouent ? : ");
       continuerJouer=getchar();
       toucheEntrer=getchar();
       printf("continuer de jouer =<%c>\n",continuerJouer);
    }while(continuerJouer<'2' || continuerJouer>'4');
    ParamJeu.NbJoueur=continuerJouer-48;   // nombre total de Joueurs table ascii
    continuerJouer='O';
    for(numJoueur=1;numJoueur<=4;numJoueur++) // Boucle qui initialiser ces variables à 0
    {
        strcpy(Joueur[numJoueur].nomJoueur,"nom du joueur");
        Joueur[numJoueur].argent=0;
        Joueur[numJoueur].joueurenJeu=0;
        Joueur[numJoueur].Case=0;
        Joueur[numJoueur].couleur=0;
        Joueur[numJoueur].nbDoubles=0;
        Joueur[numJoueur].Prison=0;
    }
    for(numJoueur=1;numJoueur<=ParamJeu.NbJoueur;numJoueur++) // Boucle qui permet d'initialiser les variables des Joueurs en jeu
    {
        Joueur[numJoueur].argent=200;
        Joueur[numJoueur].joueurenJeu=1;  // Si le joueur continue de jouer à la partie sinon il arrête de jouer
    }
    InitialiserTabCouleur(tabJeuColor);
    remplirCases(caseJeu);
    printf("\n\n\n\n\n\n DEBUT DU JEU \n");
    numJoueur=1;                      // On commence au Joueur 1 la partie
    while(continuerJouer=='O'||continuerJouer=='o')
    {
        printf("C'est au tour du Joueur %d de jouer",numJoueur);
        if(Joueur[numJoueur].Prison==1 ||Joueur[numJoueur].Prison==2) // Nombres de Tours en Prison
        {
            printf("Voulez vous payer 50 dollars pour sortir de prison ?\n");
            continuerJouer=getchar();
            toucheEntrer=getchar();
            printf("Le joueur a tape >%c<\n",continuerJouer);
            if(continuerJouer=='O')
            {
               printf("Le joueur %d est sorti de prison car il a paye\n",numJoueur);
               Joueur[numJoueur].argent=Joueur[numJoueur].argent-50;
               Joueur[numJoueur].Prison=0; // Le joueur est sorti
            }
            else
            {
                Joueur[numJoueur].Prison=Joueur[numJoueur].Prison+1;
            }
        }
        resultatDe=deplacerJoueur(tabJeu,caseJeu,Joueur,numJoueur);  // On lance la fonction deplacé Joueur et le return de la fonction ira dans résultat De qui equivaut au résultat Dé1 et Dé2
        remplirTableau(tabJeu,tabJeuColor,caseJeu,Joueur,ParamJeu); // On appelle la variable tabJeu pour remplir le tableau
        afficherTableau(tabJeu,tabJeuColor);
        printf("Le Joueur %d a %d dollars\n",numJoueur,Joueur[numJoueur].argent);
        arriveesurCarte(tabJeu,caseJeu,Joueur,numJoueur,resultatDe,ParamJeu);
        if(Joueur[numJoueur].Prison==1)
        {
            printf("Le Joueur %d va en prison car il a atterit sur la case Aller en Prison\n",numJoueur);
            Joueur[numJoueur].nbDoubles=0; // Le joueur ne peut plus rejouer même avec un double avant
        }
        if(Joueur[1].joueurenJeu+Joueur[2].joueurenJeu+Joueur[3].joueurenJeu+Joueur[4].joueurenJeu==1) // Dans le cas où il ne reste plus que un joueur qui joue
        {
            printf("Il n'y a plus que vous qui joue vous avez gagne");
            return 0;
        }
        do {
        printf("Voulez vous continuer a jouer ? O, N, M(Acheter Maison) : ");
        continuerJouer=getchar();
        toucheEntrer=getchar();
        } while (continuerJouer!='o' && continuerJouer!='O' && continuerJouer!='n' && continuerJouer!='N' && continuerJouer!='m' && continuerJouer!='M' );
        if (continuerJouer=='M' || continuerJouer=='m')
        {
            acheterMaison(tabJeu,caseJeu,Joueur,numJoueur); // On achète une maison en utilisant les variables
            continuerJouer='O';                             // et on continue à jouer
        }
        if(Joueur[numJoueur].nbDoubles==0)               // Si un joueur n'a pas fait un double
        {
             numJoueur=numJoueur+1;                      // On passe au Joueur suivant
            if (numJoueur>ParamJeu.NbJoueur)                 // Si le numéro du joueur qui joue est supérieure aux nombres de joueurs maximum
            {
                numJoueur=1;                                // On recommence à partir du joueur 1
            }
            while(Joueur[numJoueur].joueurenJeu==0)     // Tant qu'il n'y a pas de joueur qui joue
            {
                numJoueur=numJoueur+1;                      // On passe au Joueur suivant
                if (numJoueur>ParamJeu.NbJoueur)                 // Si le numéro du joueur qui joue est supérieure aux nombres de joueurs maximum
                {
                   numJoueur=1;                                // On recommence à partir du joueur 1
                }
            }
        }
    }
    printf("Fin de Jeu\n");
    return 0;
}
