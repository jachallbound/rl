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
#define EPS 0.1 /* Exploratory value */


int main (void) {
  /* Set random seed */
  srand(time(NULL));
  /* Variables */
  double q[K]; /* q*(a) - true value function */
  double Q[K]; /* Q(a) - estimate value function */
  double Qn[K]; /* estimate value function numerator */
  double R[K][STEPS]; /* All rewards, for insight */
  double Rt[STEPS]; /* Reward based on chosen action at each time step */
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
    /* Set arrays to zero */
    for (size_t i = 0; i < K; i++) {
      Q[i] = 0.0;
      Qn[i] = 0.0;
      Ai[i] = 0;
    }
    At = 0;

    /* Training steps */
    for (size_t t = 0; t < STEPS; t++) {
      /* Iterate through available actions */
      for (size_t a = 0; a < K; a++) {
        /* Reward for this action */
        randn(q[a], 1, &R[a][t], 1);
        if (t > 0) {
          /* Estimate value function */
          if (a == At) { /* Increment if a was last action taken */
            Qn[a] += R[a][t-1]; /* Q(a) numerator, sum of rewards for this action */
            Q[a] = Qn[a]/(double)(++Ai[a]); /* ++Ai[a] tracks sum of times action a was taken */
          }
        }
      }
      if (t != 0 && rand() > EPS*(double)RAND_MAX) {
        /* Exploit */
        At = argmax(Q, K);
        exploitations++;
      } else {
        /* Explore */
        At = rand()%K;
        explorations++;
      }
      Rt[t] = R[At][t]; /* Reward for this run */
      Rr[t] += Rt[t]; /* Sum reward over all runs */
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
