#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "ltqnorm.h"

void randn(double mean, double std, double* array, size_t len);
void softmax(double* pi, double* H, size_t len);
size_t argmax(double* array, size_t len);
size_t random_decision(double* pi, size_t len);

#endif /* FUNCTIONS_H */