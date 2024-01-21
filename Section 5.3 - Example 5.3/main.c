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

/* Function definitions */
void libvolkexample(void);

/* Macros */
#define RUN_LIBVOLKEXAMPLE 0 /* 1: run short libvolk example, 0: skip */
#define TRAIN_AGENT_OR_PLAY_BLACKJACK 1 /* 1: train agent, 0: play blackjack */

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
  
  #if RUN_LIBVOLKEXAMPLE 
    libvolkexample();
  #endif /* RUN_LIBVOLKEXAMPLE */

  /* 1: train agent as described in Example 5.1 */
  #if TRAIN_AGENT_OR_PLAY_BLACKJACK
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

  #else /* TRAIN_AGENT_OR_PLAY_BLACKJACK */
    /* 0: play blackjack */
    /*** BEGIN CURSES ***/
    WINDOW* wnd = initscr(); /* curses call to initialize window */
    cbreak(); /* curses call to set no waiting for Enter key */
    noecho(); /* curses call to set no echoing */
    clear(); /* curses call to clear screen, send cursor to position (0,0) */
    refresh(); /* curses call to implement all changes since last refresh */
    curs_set(0); /* display cursor or not */
    char c;
    
    hand agent;
    agent.id = AGENT;
    hand dealer;
    dealer.id = DEALER;
    do {
      /* Reset values */
      curses_reset_screen(wnd);
      hand_reset(&agent);
      hand_reset(&dealer);
      player winner = DEALER;
      deck_reset(); /* Reset deck */
      /* Deal two hands */
      hand_add_card(&agent);
      hand_add_card(&agent);
      hand_add_card(&dealer);
      curses_update_hands(wnd, &agent, &dealer);
      /* Get input and make decision to hit or stay */
      do {
        c = getch();
        /* Type 'h' to hit */
        if (c == 'h') {
          if (hand_add_card(&agent)) goto end_hand;
          // if (hand_calculate_value(&agent)) goto end_hand;
          curses_update_hands(wnd, &agent, &dealer);
        }
      } while (c == 'h'); /* Type anything else to stay */
      /* Deal second card to dealer */
      hand_add_card(&dealer);
      hand_calculate_value(&dealer);
      hand_dealer_decision(&dealer);
      /* Check who won */
      end_hand:
      curses_update_hands(wnd, &agent, &dealer);
      winner = hand_decide_winner(&agent, &dealer);
      /* Display results */
      curses_end_game(winner);
      getch();
    } while (c != 'q');
    endwin();
  #endif /* TRAIN_AGENT_OR_PLAY_BLACKJACK */

  return 0;
}

  void libvolkexample(void) {
    /* example of using arrays with libvolk */
    unsigned int N = 10;
    unsigned int alignment = volk_get_alignment();
    double* increasing = (double*)volk_malloc(sizeof(double)*N, alignment);
    double* decreasing = (double*)volk_malloc(sizeof(double)*N, alignment);
    double* out = (double*)volk_malloc(sizeof(double)*N, alignment);
    for(unsigned int ii = 0; ii < N; ++ii){
        increasing[ii] = (float)ii;
        decreasing[ii] = 10.f - (float)ii;
    }
    volk_64f_x2_multiply_64f(out, increasing, decreasing, N);
    for(unsigned int ii = 0; ii < N; ++ii){
        printf("out[%u] = %1.2F\n", ii, out[ii]);
    }

    FILE *gnuplot;
    gnuplot = popen("gnuplot -persist","w");
    fprintf(gnuplot, "plot '-'\n");
    for (unsigned int i = 0; i < N; i++)
        fprintf(gnuplot, "%F %F\n", increasing[i], decreasing[i]);
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);


    volk_free(increasing);
    volk_free(decreasing);
    volk_free(out);

    return;
  }