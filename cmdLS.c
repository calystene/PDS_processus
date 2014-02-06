

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main
(int argc, char **argv) {
  int result;

  switch(fork()) 
    {
      /*
       * Erreur dans la création du fils
       */
    case -1:
      {
	perror("Erreur création fils");
	return -1;
      } 

      /*
       * Le fils éxécute la commande systeme ls avec l'argument passé en paramètre du programme
       */
    case 0:
      {
	printf("Le fils va procéder à l'éxécution de ls\n");
	sleep(3);
	exit(execl("/bin/ls","ls",argv[1],NULL));
      }
      
      /*
       * Le père suite au résultat du fils crée le fichier si il est absent, ou le supprime si il est présent
       */
    default:
      {
	wait(&result);
	printf("Maintenant le père récupère le résultat de ls et agit en conséquence\n");
	sleep(3);
	if(!result)
	  {
	    execl("/bin/rm","rm",argv[1],NULL);
	  } 
	else 
	  {
	    execl("/bin/touch","touch",argv[1],NULL);
	  }

	return 1;
      }
      
      exit(0);
    }
  
}
