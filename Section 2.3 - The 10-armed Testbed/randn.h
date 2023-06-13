#ifndef RANDN_H
#define RANDN_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "ltqnorm.h"

void randn(double mean, double std, double* array, size_t len);

size_t argmax(double* array, size_t len);

#endif /* RANDN_H */