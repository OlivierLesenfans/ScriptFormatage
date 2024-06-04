#include "chainesDeCaractères.h"

void copy_to_clipboard(const char *text) {
    // Créez une commande pour xclip
    // Ouvrez un pipe vers xclip
    FILE *pipe = popen("xclip -selection clipboard", "w");
    if (pipe == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Écrivez le texte dans le pipe
    fwrite(text, sizeof(char), strlen(text), pipe);
    
    // Fermez le pipe
    if (pclose(pipe) == -1) {
        perror("pclose");
        exit(EXIT_FAILURE);
    }
}


int main(void){

    dstring* chaine = creerChaine();
    puts("Collez vore texte suivi de la combinaison '§§§', pour signifier\
 au programme la fin de la saisie.\nSachez que les commentaires ne seront pas conservés, mais signalés\
 avec le symbole '//'");

    int lock = 1;
    int cpt = 0;
    while (lock){
        int c = getchar();
        
        if (c == 194){ //Code du caractère '§'
            cpt++;
            if (cpt == 3){
                lock=0;
            }
            getchar(); //Comme ce n'est pas un caractère ascii, il est codé en deux fois, 194 et 167
        }
        else{
            cpt=0;
            if (c == 226){
                ajouterChar(chaine,1000,0);
            }
            else{
                if (c != 32 && c>=0 && c<=127 && c!='\t'){
                    ajouterChar(chaine,c,0);
                }              
            }     
        }
        /*Ajout dans une liste*/
    }

    format(chaine);
    char* buffer = creerBuffer(chaine);
    libererChaine(chaine);
    copy_to_clipboard(buffer);
    free(buffer);
    puts("copie effectuée");
    


    return 0;
}


/*On a pris ce caractère par convention, en supposant qu'il avait de très faibles 
probabilités d'apparaître dans un code*/