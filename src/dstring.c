#include "chainesDeCaractères.h"
#define NBMOTSSPES 10

dstring* creerChaine(){
    dstring* ch = malloc(sizeof(dstring));
    ch->currentEl = NULL;
    ch->nbEl = 0;
    return ch;
}

typedef struct Dico{
    char* mot;
    unsigned id;
}dico;


void libererChaine(dstring* ch){
    noeud* arrivee = ch->currentEl->prec;
    while (ch->currentEl != arrivee){
        noeud* temp = ch->currentEl->suiv;
        free(ch->currentEl);
        ch->currentEl = temp;
    }
    free(arrivee);
    free(ch);
}

int lenCh(dstring* ch){
    noeud* arrivee = ch->currentEl->prec;
    int n=0;
    while (ch->currentEl != arrivee){

        ch->currentEl = ch->currentEl->suiv;
        n++;
    }
    return n;
}

void ajouterChar(dstring* pchaine,int c, int sens){
    noeud* nv = malloc(sizeof(noeud));
    nv->id = pchaine->nbEl;
    nv->val = c;
    pchaine->nbEl++;
    if (!pchaine->currentEl){
        pchaine->currentEl = nv;
        nv->prec = nv;
        nv->suiv = nv;
        return;
    }
    if (sens){
        nv->prec = pchaine->currentEl;
        nv->suiv = pchaine->currentEl->suiv;
        pchaine->currentEl->suiv = nv;
        nv->suiv->prec = nv;
        return;
    }
    nv->prec = pchaine->currentEl->prec;
    nv->suiv = pchaine->currentEl;
    pchaine->currentEl->prec = nv;
    nv->prec->suiv = nv;
}

void retirerEl(dstring* pchaine, int sens){
    
    if (pchaine->currentEl){
        noeud* temp;
        pchaine->nbEl--;
        if (pchaine->nbEl == 0){
            temp = pchaine->currentEl;
            pchaine->currentEl = NULL;
        }
        /*Cas de un élément ou plus*/
        else{
            if (sens){
                temp = pchaine->currentEl->suiv;
                pchaine->currentEl->suiv = temp->suiv;
                temp->suiv->prec = pchaine->currentEl;
            }
            else{
                temp = pchaine->currentEl->prec;
                pchaine->currentEl->prec = temp->prec;
                temp->prec->suiv = pchaine->currentEl;

            }
        }
        free(temp);
    }
}



void affichage(dstring* sg,int sens){
    if (sg->currentEl){
        if (sens){
            noeud* fin = sg->currentEl->prec;
            putchar('[');putchar(' ');
            while (fin != sg->currentEl){
                putchar(sg->currentEl->val);
                
                sg->currentEl = sg->currentEl->suiv;
            }
            putchar(sg->currentEl->val);
            putchar(']');putchar('\n');sg->currentEl = sg->currentEl->suiv;
        }
        else{
            noeud* fin = sg->currentEl->suiv;
            putchar('[');
            while (fin != sg->currentEl){
                putchar(sg->currentEl->val);
                
                sg->currentEl = sg->currentEl->prec;
            }
            putchar(sg->currentEl->val);
            putchar(']');putchar('\n');sg->currentEl = sg->currentEl->prec;       
        }
    }
    else{
        puts("Vide");
    }
}

int sautDeLigne(dstring* sg){
    noeud* depart = sg->currentEl;
    int val = -1;
    int verif = 0;
    sg->currentEl = sg->currentEl->prec;
    while (sg->currentEl->val != '\n'){
        if (sg->currentEl->val == '('){
            val++;
        }
        else if (sg->currentEl->val == ')'){
            val--;
        }
        else if (sg->currentEl->val == 'f' && val == 0){
            verif = (sg->currentEl->prec->val == 'i');
        }
        sg->currentEl = sg->currentEl->prec;
    }
    sg->currentEl = depart;
    return (val==0 && verif);
}

void passageLigneIf(dstring* sg,int nbtab){
    while (sg->currentEl->suiv->val >= 48 && sg->currentEl->suiv->val <= 57){
        retirerEl(sg,1);
    }
    sg->currentEl = sg->currentEl->suiv;
    for (int i=0;i<nbtab;i++){
        ajouterChar(sg,'\t',0);
    }
}

void effaceCommentaires(dstring* ch){
/*On part du prédicat que lorsque un commentaire commence, il termine*/
    unsigned int n=0;
    while (n < RAND_MAX){
        if (ch->currentEl->suiv->val == '*'){
            if (ch->currentEl->suiv->suiv->val == '/'){
                retirerEl(ch,1);
                return;
            }
        }
        retirerEl(ch,1);
        n++;
    }
    ch->currentEl = ch->currentEl->suiv; retirerEl(ch,0);
    ch->currentEl = ch->currentEl->prec;
}

int reconnaissanceMots(dico* t,char c){
    for (int i=0;i<NBMOTSSPES;i++){
        if (t[i].mot[t[i].id] == c){
            if (t[i].id == strlen(t[i].mot)-1){
                return 1;
            }
            else{
                (&t[i])->id++;
            }
        }
        else{
            (&t[i])->id = 0;
        }
    }
    return 0;
}

void format(dstring* ch){
    if (!ch->currentEl){
        return;
    }
    if (ch->currentEl->prec->val != '\n'){ajouterChar(ch,'\n',0);}

    dico tab[NBMOTSSPES] = {{"int",0},{"float",0},{"double",0},{"return",0},{"if",0},{"typedef",0},\
    {"struct",0},{"include",0},{"else",0},{"for",0}};

    int tabulations = 0;
    noeud* fin = ch->currentEl->prec;
    char lock = 1;
    while (lock){
        if (ch->currentEl->val == 1000){
            ch->currentEl->val = 34;
        }
        if(ch->currentEl->prec->val >= 48 && ch->currentEl->prec->val <= 57 && \
        ch->currentEl->prec->id == 0){
            retirerEl(ch,0);
        }
        if (ch->currentEl->val == ','){
            ajouterChar(ch,' ',1);
        }
        else if (ch->currentEl->val == '=' || ch->currentEl->val == '<' ||\
        ch->currentEl->val == '!' || ((ch->currentEl->val == '>' && ch->currentEl->prec->val != '-'))){
            if (ch->currentEl->suiv->val == '='){
               ajouterChar(ch,' ',0); 
            }
            else if (ch->currentEl->prec->val == '='||\
            ch->currentEl->prec->val == '!' || ch->currentEl->prec->val == '<' ||\
            ch->currentEl->prec->val == '>'){
                ajouterChar(ch,' ',1);
            }
            else{
                ajouterChar(ch,' ',1);
                ajouterChar(ch,' ',0);
            }
        }
        else if (ch->currentEl->val == '\n'){
            if (ch->currentEl->suiv->val >= 48 && ch->currentEl->suiv->val <= 57){
                retirerEl(ch,1);
                ch->currentEl = ch->currentEl->prec;
            }
            else{
                for (int n=0;n<tabulations;n++){
                    ajouterChar(ch,'\t',1);
                }
            }
 
            
        }
        else if (ch->currentEl->val == '*' && ch->currentEl->prec->val != '('\
        && ch->currentEl->suiv->val != '*'){
            ajouterChar(ch,' ',1);
        }
        else if (ch->currentEl->val == '{'){
            tabulations++;
        }
        else if (ch->currentEl->val == '}'){
            tabulations--;
            retirerEl(ch,0);

        }
        else if (ch->currentEl->val == ')' && ch->currentEl->suiv->val != '{' && sautDeLigne(ch)){
            if (ch->currentEl->suiv->val != '\n'){
                ajouterChar(ch,'\n',1);
            }
            ch->currentEl = ch->currentEl->suiv;
            passageLigneIf(ch,tabulations+1);

        }
        else if (ch->currentEl->val == '/' && ch->currentEl->suiv->val == '*'){
            effaceCommentaires(ch);
        }
        if (reconnaissanceMots(tab,ch->currentEl->val)){
            if (ch->currentEl->suiv->val != ' '){
                ajouterChar(ch,' ',1);
            }

        }
        /*Cette condition aurait du être dans le while, mais il faut que la boucle soit complète*/
        if (fin == ch->currentEl){
            lock = 0;
        }
        ch->currentEl = ch->currentEl->suiv;
    }
}

char* creerBuffer(dstring* ch){
    char* buffer = (char*)malloc((ch->nbEl+1)*sizeof(char));
    unsigned int i;
    for (i=0;i<ch->nbEl;i++){
        buffer[i] = ch->currentEl->val;
        ch->currentEl = ch->currentEl->suiv;
    }
    buffer[i] = '\0';
    return buffer;
}

void afficherBuffer(char* b){
    int i =0;
    putchar('[');
    while (b[i]){
        putchar(b[i]);putchar(' ');
        i++;
    }
    putchar(']');
}


