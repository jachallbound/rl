#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "ltqnorm.h"
#include "functions.h"

/* Macros */
#define K 10
#define STEPS 10000
#define RUNS 2000
#define EPS 0.1 /* Exploratory value */
#define ALPHA 0.1 /* Step-size parameter */

#define SAMPLE_AVERAGE 0 /* 0 = Equ (2.3) | 1 = Equ (2.5) */
#define STATIONARY 1 /* Choose q(a) to be stationary or non-stationary */

int main (void) {
  /* Set random seed */
  srand(time(NULL));
  /* Variables */
  /* Arrays */
  double q[K]; /* q*(a) - true value function */
  double Ravg[K]; /* Rt(a) - average reward (previously Q(a)) */
  double pi[K]; /* pi(a) - probably of choosing action a */
  double H[K]; for(size_t i = 0; i < K; i++) H[i] = 0; /* H(a) - preference policy */
  size_t n[K]; /* Numbers of times each action taken */
  double S[K]; /* non-stationary random steps */
  double Rr[STEPS]; for(size_t i = 0; i < STEPS; i++) Rr[i] = 0;/* Average reward across runs */
  double Ar[STEPS]; for(size_t i = 0; i < STEPS; i++) Ar[i] = 0;/* Optimal action percent across runs */
  /* Values */
  size_t A = 0; /* Action to take each step */
  double R = 0; /* Reward value */
  size_t O = 0; /* Optimal action */
  double M = 0; /* non-stationary initial mean */
  double d = 0; /* denominator */
  

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

    /* Index of optimal action */
    O = argmax(q, K);
    
    /* Set other arrays to zero */
    for (size_t i = 0; i < K; i++) {
      Ravg[i] = 0.0;
      n[i] = 0;
      H[i] = 0;
      pi[i] = 0;
    }
    A = 0;
    R = 0;

    /* Training steps */
    for (size_t t = 0; t < STEPS; t++) {
      #if !STATIONARY
      randn(0, 0.1, S, K);
      for (size_t i = 0; i < K; i++) q[i] += S[i];
      #endif

      /********/
      /* H(t) */
      /********/
      /* Action probability, of previous H */
      softmax(pi, H, K);

      /* Pick previous action, based on previous H */
      A = (t > 0 ? random_decision(pi, K) : (size_t)rand()%K);

      /* Generate reward of previous action */
      randn(q[A], 1, &R, 1);
      /* Average reward */
      d = (SAMPLE_AVERAGE ? (double)(++n[A]) : 1/ALPHA);
      Ravg[A] = Ravg[A] + (R - Ravg[A])/d;

      /**********/
      /* H(t+1) */
      /**********/
      /* Update policy */
      // printf("A: %zu ", A);
      for (size_t a = 0; a < K; a++) {
        if (a == A) H[a] += ALPHA*(R - Ravg[a])*(1 - pi[a]);
        else H[a] -= ALPHA*(R-Ravg[a])*pi[a];
        // printf("H[%zu]=%0.2f, ", a, H[a]);
      }
      // printf("\n");

      /* Log performance */
      Rr[t] += R; /* Sum reward over all runs */
      if (A == O) Ar[t]++;
    }
    // return 0;
  }

  /* Lazily change save file name based on epsilon */
  FILE* f2;
  #if SAMPLE_AVERAGE
  f2 = fopen("Rr_sample.dat", "w");
  #else
  f2 = fopen("Rr_weighted.dat", "w");
  #endif

  /* Average over runs and save to file */
  for (size_t t = 0; t < STEPS; t++) {
    Ar[t] /= RUNS; 
    fprintf(f2, "%g\n", Ar[t]);
  }
  fclose(f2);

  return 0;
}
