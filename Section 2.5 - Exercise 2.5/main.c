#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "ltqnorm.h"
#include "randn.h"

/* Macros */
#define K 10
#define STEPS 10000
#define RUNS 2000
#define EPS 0.1 /* Exploratory value */
#define ALPHA 0.1 /* Step-size parameter */


#define SAMPLE_AVERAGE 1 /* 0 = Equ (2.3) | 1 = Equ (2.5) */
#define STATIONARY 0 /* Choose q(a) to be stationary or non-stationary */

int main (void) {
  /* Set random seed */
  srand(time(NULL));
  /* Variables */
  double q[K]; /* q*(a) - true value function */
  double Q[K]; /* Q(a) - estimate value function */
  double R = 0; /* Reward value */
  double Rr[STEPS]; for(size_t i = 0; i < STEPS; i++) Rr[i] = 0;/* Average reward across runs */
  size_t A = 0; /* Action to take each step */
  size_t n[K]; /* Numbers of times each action taken */
  size_t exploitations = 0; /* Number times exploited */
  size_t explorations = 0; /* Number times explored */
  double M = 0; /* non-stationary initial mean */
  double S[K]; /* non-stationary random steps */

  /* BEGIN TRAINING RUNS */
  for (size_t run = 0; run < RUNS; run++) {
    /* Initialize/reset values */
    /* Generate random q(a) */
    #if STATIONARY
    randn(0, 1, q, K);
    #else
    randn(0, 1, &M, 1);
    for (size_t i = 0; i < K; i++) q[i] = 0;
    #endif
    
    /* Set other arrays to zero */
    for (size_t i = 0; i < K; i++) {
      Q[i] = 0.0;
      n[i] = 0;
    }
    A = 0;
    R = 0;

    /* Training steps */
    for (size_t t = 0; t < STEPS; t++) {
      #if !STATIONARY
      randn(0, 0.1, S, K);
      for (size_t i = 0; i < K; i++) q[i] += S[i];
      #endif
      /* First step (t = 0), always explore. Then start calculating value function when t > 0 */
      if (t > 0) {
        /* Generate reward of previous action */
        randn(q[A], 1, &R, 1);
        /* Estimate value function */
        /* 2.4 - Incremental Implementation, reduced memory computation */
        #if SAMPLE_AVERAGE
        Q[A] = Q[A] + (R - Q[A])/(double)(++n[A]); /* Equ (2.3), sample average */
        #else
        Q[A] = Q[A] + (R - Q[A])*ALPHA; /* Equ (2.5), weighted average */
        #endif
      }

      /* Choose whether to exploit or explore */
      if (t != 0 && rand() > EPS*(double)RAND_MAX) {
        /* Exploit */
        A = argmax(Q, K);
        exploitations++;
      } else {
        /* Explore */
        A = rand()%K;
        explorations++;
      }
      Rr[t] += R; /* Sum reward over all runs */
    }
  }

  /* Lazily change save file name based on epsilon */
  FILE* f2;
  #if SAMPLE_AVERAGE
  f2 = fopen("Rr_sample.dat", "w");
  #else
  f2 = fopen("Rr_weighted.dat", "w");
  #endif

  /* Average summed rewards and save to file */
  for (size_t t = 0; t < STEPS; t++) {
    Rr[t] /= RUNS; 
    // fprintf(f2, "%zu %g\n", t, Rr[t]);
    fprintf(f2, "%g\n", Rr[t]);
  }
  fclose(f2);

  printf("Exploitations: %zu, Explorations: %zu\n", exploitations, explorations);
  return 0;
}
