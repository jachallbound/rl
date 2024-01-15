#ifndef VOLK_ARRAYS_H
#define VOLK_ARRAYS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "functions.h"
#include "blackjack.h"
#include "monte_carlo_blackjack.h"

/* Macros */
/* State space dimensions */
#define S0 10 /* 3D matrix dimension lengths */
#define S1 10
#define S2 2
#define A0 2 /* possible actions: 0: hit, 1: stick */

/* volk array functions */
void set_volk_3d(double* array, double value, int i0, int i1, int i2, int len);
void set_volk_4d(double* array, double value, int i0, int i1, int i2, int i3, int len);
double get_volk_3d(double* array, int i0, int i1, int i2, int len);
double get_volk_4d(double* array, int i0, int i1, int i2, int i3, int len);

#endif /* VOLK_ARRAYS_H */