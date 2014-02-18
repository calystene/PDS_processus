#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define TAB_SIZE 10

void *
triBulle
(void *tab)
{
  int switched;
  int a,b;
  int i;
  
  a = b = 0;
  switched=1;

  while(switched) {
    switched=0;

    for(i=0;i<(TAB_SIZE-1);i++) 
      {	
	a = ((int *)tab)[i];
	b = ((int *)tab)[i+1];
	
	if(a>b) 
	  {
	    ((int *)tab)[i] = b;
	    ((int *)tab)[i+1] = a;
	    switched=1;
	  }
      } 
  } 
}



void *
afficheTab
(void *tab)
{
  int i;

  while(1){
    for(i=0;i<TAB_SIZE;i++)
      {
	switch(i)
	  {
	  case 0: printf("[%d",((int *)tab)[i]);
	  case (TAB_SIZE): printf(";%d]\n",((int *)tab)[i]);
	  default: printf(";%d",((int *)tab)[i]);	  
	  }
      }

  }

}



/* Remarque : de l'éxécution, l'affichage affiche soit le tableau pas encore trié, soit le tableau entièrement trié. Il affiche rarement les étapes intermédiaire
 * Cela est du au fait que les deux threads accèdent à la même donnée, de ce fait un threads prend le monopole sur l'autre et libère la donné que lorsqu'il a finit son opération.
 */


int
main
(void)
{
  int i;
  int tab[TAB_SIZE];

  pthread_t threads_id[2];

  for(i=TAB_SIZE;i>0;i--)
    {
      tab[TAB_SIZE-i] = i;
    }

  /* On crée les threads qui vont s'éxécuter en parallèle, un pour l'affichage, un pour le tri */
  pthread_create(&threads_id[0],NULL,&afficheTab,(void *) tab);
  pthread_create(&threads_id[1],NULL,&triBulle,(void *) tab);

  /* Lorsque le treads de tri à fini son opération, on annule le threads d'affichage */
  pthread_join(threads_id[1],NULL);
  pthread_cancel(threads_id[0]);

  exit(0);
}
