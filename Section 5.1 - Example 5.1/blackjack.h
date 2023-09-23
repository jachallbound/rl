#ifndef BLACKJACK_H
#define BLACKJACK_H

/* Macros */
#define DECK_SIZE 52
#define UNIQUE_CARDS 13

/* 52 card deck, suit doesn't matter in blackjack */
int deck_n[52] = {2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11};

char deck_s[13][2] = {" 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"," J"," Q"," K"," A"};

#endif /* BLACKJACK_H */