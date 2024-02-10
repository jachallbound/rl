#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "functions.h"
#include "blackjack.h"
#include "monte_carlo_blackjack.h"

/* Global */
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

/* Main */
int main (void) {
  /* Set random seed */
  srand(time(NULL));

  /* Policy: hit for hand value < 20 */
  int pi = 20;

  /* number of states: S[0] agent's starting hand, S[1] dealer's showing card, S[2] usable ace */
  int S[3] = {S0, S1, S2};
  int episodes = 500000; /* number of episodes */

  /* Initialize states */
  int S_total = S[0]*S[1]*S[2];
  double V[S[0]][S[1]][S[2]]; zero_double_3d(V); /* state values */
  int    R[S[0]][S[1]][S[2]]; zero_int_3d(R); /* return count for averaging */
  
  monte_carlo_blackjack(V, R, pi, episodes);

  /* Check V */
  int iii = 1;
  FILE* f = fopen("V.dat", "w");
  for (int i = 0; i < S0; i++) {
    for (int ii = 0; ii < S1; ii++) {
      fprintf(f, "%2.5f ", V[i][ii][iii]/(double)(R[i][ii][iii]+1));
    }
    fprintf(f, "\n");
  }
  fclose(f);

  return 0;
}
