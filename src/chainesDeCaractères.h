#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Noeud{
    int val;
    struct Noeud* suiv;
    struct Noeud* prec;
    unsigned int id;
} noeud;

typedef struct Dstring{
    unsigned int nbEl;
    struct Noeud* currentEl;
} dstring;
/*Structure de chaine de caractère doublement chainee circulaire*/

dstring* creerChaine();
void ajouterChar(dstring* pchaine,int c, int sens);
// void retirerEl(dstring* pchaine, int sens);
// void affichage(dstring* sg,int sens);
void format(dstring* ch);
char* creerBuffer(dstring* ch);
// void afficherBuffer(char* b);
void libererChaine(dstring* ch);
