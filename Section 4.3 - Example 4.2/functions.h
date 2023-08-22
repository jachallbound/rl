#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "ltqnorm.h"
#include "data_structures.h"

/* Macros */
#define max(x,y) (x > y ? x : y)
#define min(x,y) (x < y ? x : y)

/* Declarations */
void randn(double mean, double std, double* array, int len);
void randp(double mean, int* array, int len);
double pdfp(double mean, int count);
void softmax(double* pi, double* H, int len);
int argmax(double* array, int len);
int random_decision(double* pi, int len);

#endif /* FUNCTIONS_H */
