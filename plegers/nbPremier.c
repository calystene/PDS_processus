#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<stdlib.h>

#define nb 18446743979220271189ULL

unsigned int nbproc ;
pthread_t *threads ;

struct data_m 
{
  unsigned long long start ;
  unsigned long long end ;
  unsigned int current_thread_nb ;
} ;

typedef struct data_m data_t ;

void *
searchdivisor
(void * data)
{
  register unsigned long long i ;
  register unsigned long long end ;
  unsigned int j ;

  /* indicates that a cancellation request is acted immediately */
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE ,NULL) ;
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL) ;

  end = ((data_t *) data)->end ;

  for(i=((data_t*) data)->start; i<end; i++)
    if (!(nb % i))
      {
	printf(" %llu est un diviseur de %llu \n",i,nb) ;
	for(j=0;j<nbproc;j++) 
	  if(j!=((data_t *) data)->current_thread_nb)
	    if (pthread_cancel(threads[j])) 
	      printf("Incorrect cancellation\n");  
	return NULL;
      }
  return NULL ;
}

int
main
(void)
{
  unsigned long long sqrt_nb ;
  unsigned long long tmp ;
  void * status ;
  int i ; 
  data_t *data ;

  nbproc = sysconf(_SC_NPROCESSORS_ONLN) ;
  printf("%d computing unit available\n",nbproc) ;
  threads = (pthread_t *) malloc(nbproc*sizeof(pthread_t)) ;
  data = (data_t *) malloc(nbproc*sizeof(data_t)); 

  sqrt_nb = sqrt(nb) ; 
  tmp = sqrt_nb / nbproc ;

  for(i=0;i<nbproc;i++) 
    {
      data[i].start = 2+i*tmp ;
      data[i].end = data[i].start + tmp ;
      data[i].current_thread_nb = i ;
      pthread_create(&threads[i],NULL,searchdivisor,
		     (void *) &data[i]) ;
    } 
 
  for(i=0;i<nbproc;i++)
    { 
      pthread_join(threads[i],&status) ;
      if(status == PTHREAD_CANCELED ) printf(" thread %d canceled\n",i); 
    }
  return 0 ; 
}
