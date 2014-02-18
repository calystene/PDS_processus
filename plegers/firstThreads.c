#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* On crée un pointeur sur fonction qui prend en paramètre un pointeur sur void */
void
*toPrint
(void *message)
{
  pthread_exit((void *) message); /* On retourne le résultat de la fonction via pthread_exit */
  return NULL;
}


int
main
(void)
{
  pthread_t thread_id[2]; /* On crée un tableau de pthread_t */
  void *msg;
  
  /* On crée les threads, c'est à cette étape que comment l'éxécution des threads */
  pthread_create(&thread_id[0],NULL,toPrint,(void *) "Je suis A\n");
  pthread_create(&thread_id[1],NULL,toPrint,(void *) "Je suis B\n");
    
  /* On attend la fin de l'éxécution des threads fils, on récupère le résultat à l'aide du pointeur void msg, et on l'affiche ensuite sur stdout */
  pthread_join(thread_id[1],&msg);
  printf("%s", (char *) msg);
  pthread_join(thread_id[0],&msg);
  printf("%s", (char *) msg);

  /* L'intérêt d'attendre la fin de l'éxécution des fils est d'éviter que le programme main se termine avant eux */ 
  exit(0);
}
