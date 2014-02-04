
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILENAME "listeNbPremier"

int
main
(void) {
  int i;
  FILE *f;
  int c;
  int result;
 
  if((f=fopen(FILENAME,"r"))!=NULL)
    {
      /* Le père commence son travail */
      for(i=0;i<10;i++) 
	{
	  printf("%c",fgetc(f));
	}
      printf("\n");
      
      /* On crée le processus fils*/
      switch(fork()) 
	{
	  /* si Erreur à la création */
	case -1 : exit(1);

	case 0:
	  {
	    /* On fait attendre le fils 3 seconde avant qu'il fasse son travail */
	    sleep(3);
	    for(i=0;i<20;i++)
	      {
		printf("%c", fgetc(f));
	      }
	    printf("\n");
	    fclose(f);

	    /* On fait de nouveau attendre le fils 3 seconde avant qu'il se suicide */
	    sleep(3);
	    exit(1);
	  }

	default:
	  {
	    /* Le père attend la mort du fils */
	    wait(&result);
	    /* et il finit son travail */
	    while((c=fgetc(f))!=EOF) {
	      printf("%c", c);
	    }

	    fclose(f);
	    printf("\n");
	    return 0;
	  }
	}
    }
}


