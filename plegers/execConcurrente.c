#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAB_SIZE 100

int tab[TAB_SIZE];

/* Affiche le contenu du tableau */
void *
affiche
(void *arg)
{
  int i;
  i=0;

  while(i++<TAB_SIZE) {
    printf("case %d=%d | ",i,tab[i]);
    if ((i%10)==0 && i!=0)
      printf("\n");

    if(i==TAB_SIZE) 
      i=0;
  }  
  
  pthread_exit(0);
  
  return NULL;
}

/* Ajoute des un dans le tableaeu */
void *
ajouteUn
(void *arg)
{
  int i;
  i=0;

  while(i++<TAB_SIZE) {
    tab[i] = 1;

    if(i==TAB_SIZE)
      i=0;
  }
  pthread_exit(0);

  return NULL;
}

/* Ajoute des 2 dans le tableau */
void *
ajouteDeux
(void *arg)
{
  int i;
  i=0;

  while(i++<TAB_SIZE) {
    tab[i] = 2;
    if(i==TAB_SIZE)
      i=0;
  }
  
  pthread_exit(0);

  return NULL;
}


int
main
(void)
{
  pthread_t threads_id[3];
  void *res; 

  pthread_create(&threads_id[0],NULL,&affiche,NULL);
  pthread_create(&threads_id[1],NULL,&ajouteUn,NULL);
  pthread_create(&threads_id[2],NULL,&ajouteDeux,NULL);

  pthread_join(threads_id[2],&res);
  pthread_join(threads_id[1],&res);
  pthread_join(threads_id[0],&res);

  exit(0);
}
