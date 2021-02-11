#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <glob.h>

#define TAILLE_BUFFER 150

int main()
{
      char buffer[TAILLE_BUFFER];


    while(1)
    {
        printf("choisissez votre commande: ");
        fgets(buffer,TAILLE_BUFFER,stdin);
        buffer[strlen(buffer)-1]='\0';
        if (strcmp("exit",buffer)==0)
        {
            exit(0); //cette partie permet de mettre en place la commande exit qui va arr�ter le processus du programme
        }
        char *arg_list[32];
        char *p=strdup(buffer);
        char *tmp=strtok(p," "); //cr�ation du tableau permettant la cr�ation des bouts de ligne entre caract�res espaces
        int increment=0;
        while (tmp!=NULL)
        {
            char *p=strstr(tmp,"*");
            if (p==NULL)
            {
                arg_list[increment]=strdup(tmp);
                increment++;
            }
            else
            {
                glob_t     g;
                int retour_glob=glob(tmp,0,NULL,&g);
                if (retour_glob==0)
                {
                    int boucle;
                    for (boucle=0;boucle<g.gl_pathc;++boucle)
                    {
                        arg_list[increment]=strdup(g.gl_pathv[boucle]);
                        increment++;
                    }
                }
                globfree(&g);
            }
            tmp=strtok(NULL," ");
        }
        arg_list[increment]=NULL;
        pid_t process=fork(); //cr�ation du processus fils avec la commande fork
        if (process==0) //si le processus p�re est �gal � 0
        {
            int retour=execvp(arg_list[0],arg_list);
            if (retour==-1) printf("%s\n",strerror(errno)); //on se met dans le processus fils qui remplace le processus actuel par le contenu des param�tres pass�s et ex�cute celui-ci
            exit(0);
        }
        else
        {
            wait(&process); // si process = 0 on se met en attente de la fin du processus fils
        }
        increment=0;
        while (arg_list[increment]!=NULL)
        {
            free(arg_list[increment]); // � la fin du process on lib�re la m�moire du la liste d'argument
            increment++;
        }
        free(p);
    }
}
