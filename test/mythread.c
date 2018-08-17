#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS  3
#define TCOUNT 10
#define COUNT_LIMIT 12

int     count = 0;
pthread_cond_t count_threshold_cv;

void *inc_count(void *t)
{


	sleep(10);
	printf("signal sending...\n");
      pthread_cond_signal(&count_threshold_cv);
 	 pthread_exit(NULL);
}

void *watch_count(void *t) 
{

	printf("wating for signal\n");
    pthread_cond_wait(&count_threshold_cv, &count_mutex);
	printf("Signal arrived succesfull\n");
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  int i, rc; 
  long t1=1, t2=2, t3=3;
  pthread_t threads[2];

  pthread_cond_init (&count_threshold_cv, NULL);

  /* For portability, explicitly create threads in a joinable state */
  pthread_create(&threads[0], NULL, watch_count, (void *)t1);
  pthread_create(&threads[1], NULL, inc_count, (void *)t2);

  /* Wait for all threads to complete */
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("Main(): Waited and joined with %d threads. Final value of count = %d. Done.\n", 
          NUM_THREADS, count);

  /* Clean up and exit */
  pthread_cond_destroy(&count_threshold_cv);
  pthread_exit (NULL);

}

