#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main
(int argc, char *argv[], char *envp[])
{
  int pid;
  int exec;
  char **cmdArgve;
  int i;
  char *tempo;
  /* char *envArgve[] = {"."}; */


  // création du fils
  pid = fork();  
  switch(pid)
    {
    case -1: exit(1); // exit si erreur
    case 0: {
      printf("Le premier fils vérifie l'éxistence des fichiers à l'aide de la commande ls\n...");
      sleep(2);
      exit(execv("/bin/ls",argv)); // le fils éxécute ls avec les paramètres fourni par argv
    }
    default: {
      wait(&pid); //le père attend son fils et stock son resultat de retour dans pid
      
      if(pid || argc == 1) // si la commande ls à échouer ou qu'il y a qu'un seul argument (le nom de ce programme), alors erreur
	{
	  printf("error : fichier(s) manquant(s)");
	} 
      else // Sinon on continu le traitement
	{
	  // Création d'un fils pour la compilation des fichiers objet à partir des sources
	  switch((pid=fork()))
	    {
	    case -1: printf("erreur 2\n");	    	    
	    case 0 : {	  
	      printf("Le deuxième fils compile les fichiers objets à l'aide des fichiers sources\n...");
	      sleep(2);

	      // on réserve de l'espace mémoire pour le tableau qui va contenir les arguments de execve
	      cmdArgve = malloc((2+argc)*sizeof(char)); // --> le nombre d'argument + 2 pour "gcc" et "-c"
	      cmdArgve[0] = malloc(3*sizeof(char));
	      cmdArgve[1] = malloc(2*sizeof(char));
	      
	      // On ajoute les commandes utiles pour execve
	      cmdArgve[0] = "gcc";
	      cmdArgve[1] = "-c";	      
	      
	      // On instancie le tableau par argve avec le reste des paramètres fourni sur la ligne de commande
	      for(i=2;i<argc+1;i++) {		
		cmdArgve[i] = malloc(sizeof(argv[i-1]));
		cmdArgve[i] = argv[i-1];
	      }
	      cmdArgve[++i] = NULL;	      	      
	      
	      // on execute gcc -c avec l'ensemble des fichiers sources à compiler en fichier objet
	      exit(execve("/usr/bin/gcc",cmdArgve,envp));
	    }
	    default : {	      
	      // Le père attend que son fils ait créée tout les fichiers objets
	      wait(&pid);
	      printf("Le père compile le programme à l'aide des fichiers objets\n...",getpid());
	      sleep(3);

	      if(!pid) {
		//gcc -o monProg fichier.o fichier2.o fichier3.o
		cmdArgve = malloc((3+argc)*sizeof(char));
		

		/* on reserve les espaces mémoires pour les arguments connus */
		cmdArgve[0] = malloc(3*sizeof(char));
		cmdArgve[0] = "gcc\0";

		cmdArgve[1] = malloc(2*sizeof(char));
		cmdArgve[1] = "-o\0";

		cmdArgve[2] = malloc(7*sizeof(char));
		cmdArgve[2] = "monProg\0";	       

		/* on reserve les espaces mémoires pour les arguments variables */
		for(i=3;i<argc+2;i++){
		  cmdArgve[i] = malloc(sizeof(argv[i-2]));		  
		  cmdArgve[i] = argv[i-2];
		  
		  // On récupère un pointeur sur 'c' de "arg.c" et on change en "arg.o"
		  tempo = strrchr(cmdArgve[i],'c');
		  *(tempo) = 'o';
		}

		cmdArgve[++i] = NULL;
	      }
	      
	      /* On éxécute la commande finale pour la compilation du programme avec l'ensemble des fichiers objet */
	      execve("/usr/bin/gcc", cmdArgve, envp);
	    }
	    }
	  
	}    
    }
      
    }
}
