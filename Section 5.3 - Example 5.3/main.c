#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

/* VOLK */
#define VK_USE_PLATFORM_XLIB_KHR
#define VOLK_IMPLEMENTATION
#include <volk/volk.h>

#include "functions.h"
#include "blackjack.h"
#include "monte_carlo_blackjack.h"
#include "volk_arrays.h"



/* Global (extern declaration in blackjack.h) */
int len = 52;
int deck_n[52] = {2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11};

char* deck_s[13] = {" 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"," J"," Q"," K"," A"};
int dealt_i = 0;
int already_dealt = 0;
int dealt[52] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int agent_wins = 0;
int dealer_wins = 0;
int mc_debug = 0;

/* Main */
int main (int argc, char** argv) {
  /* Control printf statements in monte_carlo_blackjack */
  if (argc > 1) mc_debug = atoi(argv[1]);

  /* Get number of episodes from commandline parameter */
  int episodes = 5000000; /* default */

  /* Set random seed */
  srand(time(NULL));

  /* Initialize matrices */
  /* Volk arrays */
  unsigned int alignment = volk_get_alignment(); /* required */
  double* Q = (double*)volk_malloc(sizeof(double)*(S0*S1*S2*A0), alignment); /* 4d array */
  double* R = (double*)volk_malloc(sizeof(double)*(S0*S1*S2*A0), alignment); /* 4d array */
  double* P = (double*)volk_malloc(sizeof(double)*(S0*S1*S2), alignment); /* 3d array */
  double* V = (double*)volk_malloc(sizeof(double)*(S0*S1*S2), alignment); /* 3d array */

  /* Initialize matrices to zero */
  for (int i = 0; i < S0*S1*S2*A0; i++) {
    Q[i] = 0.0f;
    R[i] = 1.0f;
    if (i < S0*S1*S2) { /* only 3d */
      P[i] = uniform_decision(2); /* random policy */
      V[i] = 0.0f;
    }
  }

  /* Mont carlo simulation */
  monte_carlo_blackjack(Q, R, P, V, episodes);

  /* Save P and V to file */
  FILE* fp = fopen("P.dat", "w");
  FILE* fv = fopen("V.dat", "w");
  int s2 = 1; /* 1: usable ace, 0: no usable ace */
  for (int s0 = 0; s0 < S0; s0++) {
    for (int s1 = 0; s1 < S1; s1++) {
      fprintf(fp, "%d ", (int)get_volk_3d(P, s0, s1, s2, S0*S1*S2));
      fprintf(fv, "%2.2f ", get_volk_3d(V, s0, s1, s2, S0*S1*S2));
    }
    fprintf(fp, "\n");
    fprintf(fv, "\n");
  }
  fclose(fp);
  fclose(fv);

  /* Free volk arrays */
  volk_free(Q);
  volk_free(R);
  volk_free(P);
  volk_free(V);

  return 0;
}
