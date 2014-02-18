#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int
main
(void)
{

    int             i, j;
    int             pid;
    FILE           *fd;
    int             resultat; /* on n'utilise pas cette variable. C'est pour
     * le wait */

    printf("Salut, je suis un processus et mon numero est %d\n", getpid());

    printf("Je vais afficher 10 nombres premiers issus du fichier listeNbPremier\n");

    fd = fopen("listeNbPremier", "r");

    if (fd == NULL)
    {
 perror("Impossible de lire le fichier listeNbPremier");
 return -1;
    }
    /* Le p\`ere lit des nombres premiers */
    for (j = 0; j < 10; j++)
    {
 fscanf(fd, "%d", &i);
 printf("%d\n", i);
    }

    printf("Maintenant, je vais creer un fils\n");
    /* cr\'eation d'un processus */
    pid = 0;
    pid = fork();

    if (pid == -1)
    {
 perror("impossible de creer un fils");
 exit(-1);
    } else if (pid == 0)
    {

 printf("Salut, je suis un processus et mon numero est %d\n", getpid());

 printf("J'attends 5 secondes avant de faire mon boulot\n");
 sleep(5);  /* on fait passer une seconde pour grouper les
     * messages */

 printf("Je vais afficher 10 nombres premiers issus du fichier listeNbPremier\n");
 /* Le fils lit des nombres premiers */
 for (j = 0; j < 10; j++)
 {
     fscanf(fd, "%d", &i);
     printf("%d\n", i);
 }
 fclose(fd);
 printf("J'attends 5 secondes avant de faire mon boulot\n");
 sleep(5);
 printf("Le fils se suicide\n");
 exit(1);
    } else
    {
 /* Le pere attend la mort de son fils */
 printf("Le pere attend la mort de son fils\n");

 wait(&resultat);

 printf("Le pere termine la lecture\n");

 /* Fin de la lecture des nombres premiers par le p\`ere */
 while (!feof(fd))
 {
     fscanf(fd, "%d", &i);
     printf("%d\n", i);
 }

 fclose(fd);

    }
    printf("Le pere se termine\n");
    return 0;
}
