#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int
main
(int argc, char *argv[], char *envp[])
{
  int pid;
  int exec;
  char *cmdArgve[] = {"gcc","-c",NULL};
  int i;
  /* char *envArgve[] = {"."}; */


  // création du fils
  pid = fork();  
  switch(pid)
    {
    case -1: exit(1); // exit si erreur
    case 0: {
      printf("le premier fils %d de parent : %d\n",getpid(),getppid());
      exit(execv("/bin/ls",argv)); // le fils éxécute ls avec les paramètres fourni par argv
    }
    default: {
      wait(&pid); //le père attend son fils et stock son resultat de retour dans pid
      
      if(pid || argc == 1) // si la commande ls à échouer ou qu'il y a qu'un seul argument (le nom de ce programme), alors erreur
	{
	  printf("error");
	} 
      else // Sinon on continu le traitement
	{
	  switch((pid=fork()))
	    {
	    case -1: printf("erreur 2\n");
	    case 0 : {
	      printf("le deuxième fils %d de parent :%d\n",getpid(),getppid());
	      
	      for(i=2;i<argc;i++) {
		cmdArgve[i] = argv[i-1];
	      }
	      cmdArgve[++i] = NULL;
	      
	      exit(execve("/usr/bin/gcc",cmdArgve,envp));
	    }
	    default : {	      
	      wait(&pid);
	      printf("Le père pid : %i \n",getpid());
	    }
	    }
	  
	}    
    }
      
    }
}
