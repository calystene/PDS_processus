

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main
(int argc, char **argv) {
  int result;

  switch(fork()) 
    {
    case -1:
      {
	perror("Erreur création fils");
	return -1;
      } 

    case 0:
      {
	printf("Le fils va procéder à l'éxécution de ls\n");
	sleep(3);
	exit(execl("/bin/ls",argv[1],NULL));
      }

    default:
      {
	wait(&result);
	printf("Maintenant le père récupère le résultat de ls et agit en conséquence\n");
	sleep(3);
	if(!result)
	  {
	    execl("/bin/rm", argv[1], NULL);
	  } 
	else 
	  {
	    execl("/bin/touch", argv[1], NULL);
	  }

	return 1;
      }
      
      exit(0);
    }
  
}
