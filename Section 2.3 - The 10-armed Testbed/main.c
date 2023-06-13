#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "ltqnorm.h"
#include "randn.h"

/* Macros */
#define K 10
#define STEPS 1000
#define RUNS 2000
#define EPS 0.0 /* Exploratory value */


int main (void) {
  /* Set random seed */
  srand(time(NULL));
  /* Variables */
  double q[K]; /* q*(a) - true value function */
  double Q[K]; /* Q(a) - estimate value function */
  double Qn[K]; /* estimate value function numerator */
  double R; /* Reward value */
  double Rr[STEPS]; for(size_t i = 0; i < STEPS; i++) Rr[i] = 0;/* Average reward across runs */
  size_t At = 0; /* Action to take each step */
  size_t Ai[K]; /* Numbers of times each action taken */
  size_t exploitations = 0; /* Number times exploited */
  size_t explorations = 0; /* Number times explored */

  /* BEGIN TRAINING RUNS */
  for (size_t run = 0; run < RUNS; run++) {
    /* Initialize/reset values */
    /* Generate random q(a) */
    randn(0, 1, q, K);
    /* Set other arrays to zero */
    for (size_t i = 0; i < K; i++) {
      Q[i] = 0.0;
      Qn[i] = 0.0;
      Ai[i] = 0;
    }
    At = 0;

    /* Training steps */
    for (size_t t = 0; t < STEPS; t++) {
      /* First step (t = 0), always explore. Then start calculating value function when t > 0 */
      if (t > 0) {
        /* Generate reward of previous action */
        randn(q[At], 1, &R, 1);
        /* Estimate value function */
        Qn[At] += R; /* Q(a) numerator, sum of rewards for this action */
        Q[At] = Qn[At]/(double)(++Ai[At]); /* ++Ai[a] tracks sum of times action a was taken */
      }

      /* Choose whether to exploit or explore */
      if (t != 0 && rand() > EPS*(double)RAND_MAX) {
        /* Exploit */
        At = argmax(Q, K);
        exploitations++;
      } else {
        /* Explore */
        At = rand()%K;
        explorations++;
      }
      Rr[t] += R; /* Sum reward over all runs */
    }
  }

  /* Lazily change save file name based on epsilon */
  FILE* f2;
  if (EPS == 0.01) f2 = fopen("Rr_0.01.dat", "w");
  else if (EPS == 0.1) f2 = fopen("Rr_0.1.dat", "w");
  else if (EPS == 0.0) f2 = fopen("Rr_greedy.dat", "w");
  else f2 = fopen("Rr.dat", "w");
  
  /* Average summed rewards and save to file */
  for (size_t t = 0; t < STEPS; t++) {
    Rr[t] /= RUNS; 
    fprintf(f2, "%zu %g\n", t, Rr[t]);
  }
  fclose(f2);

  printf("Exploitations: %zu, Explorations: %zu\n", exploitations, explorations);
  return 0;
}
