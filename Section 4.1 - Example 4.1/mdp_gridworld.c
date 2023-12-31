#include "mdp_gridworld.h"

/* Calculate index of next state based on action taken */
size_t next_state_gw(pos Ss, pos Aa) {
  size_t sp = 0;
  pos Sp = {.x = Ss.x + Aa.x,
            .y = Ss.y + Aa.y};
  /* Prevent Overflow */
  Sp.x = (Sp.x > (W-1) ? (W-1) : Sp.x);
  Sp.y = (Sp.y > (H-1) ? (H-1) : Sp.y);
  /* Prevent Underflow */
  Sp.x = (Sp.x < 0 ? 0 : Sp.x);
  Sp.y = (Sp.y < 0 ? 0 : Sp.y);
  sp = Sp.x + Sp.y*W;
  return sp;
}



/* Gridworld in curses */
void draw(char c) {
  delch();
  insch(c);
  return;
}

void draw_gridworld(pos* S, size_t N) {
  /* Draw gridworld from array of states */
  /* Hardcoded to 4x4 for now, I think */
  /* 48 is '0' in ASCII */
  for (size_t i = 0; i < N; i++) {
    if (i < 10) {
      move(S[i].y*H_scale, S[i].x*W_scale+1);
      draw(48+i);
    } else if (i >= 10 && i < 100) {
      move(S[i].y*H_scale, S[i].x*W_scale);
      draw(48+i/10);
      move(S[i].y*H_scale, S[i].x*W_scale+1);
      draw(48+i-10*(i/10));
    } else {
      move(S[i].y*H_scale, S[i].x*W_scale);
      draw(48+i/100);
      move(S[i].y*H_scale, S[i].x*W_scale+1);
      draw(48+(i-100*(i/100))/10);
      move(S[i].y*H_scale, S[i].x*W_scale+2);
      draw(48+i%10);
    }
    refresh();
  }
  move((H-1)*H_scale,(W)*W_scale);
  return;
}

void move_gridworld(pos Ss) {
  move((Ss.y*H_scale)+1, Ss.x*W_scale);
  return;
}

