#include "functions.h"

void randn(double mean, double std, double* array, size_t len) {
  for (size_t i = 0; i < len; i++) {
    array[i] = ltqnorm((double)rand()/RAND_MAX)*std + mean;
  }
  return;
}

size_t argmax(double* array, size_t len) {
  double max = -1E9;
  size_t mi = 0;
  // printf("max: ");
  for (size_t i = 0; i < len; i++) {
    // printf("%2.2g ", max);
    if (array[i] > max) {
      max = array[i];
      mi = i;
    }
  }
  // printf("\n");
  return mi;
}

void softmax(double* pi, double* H, size_t len) {
  double Hb = 0;
  for (size_t i = 0; i < len; i++) Hb += exp(H[i]);
  for (size_t i = 0; i < len; i++) pi[i] = exp(H[i])/Hb;
  return;
}

size_t random_decision(double* pi, size_t len) {
  size_t A = 0;
  double d = 0, p = 0;
  d = (double)rand()/RAND_MAX;
  // printf("d: %0.2f ", d);
  for (size_t i = 0; i < len; i++) {
    // printf("p0: %0.2f, ", p);
    if (d > p && d < (p+=pi[i])) {
      // printf("p1: %0.2f, i: %zu\n", p, i);
      return i;
    }
  }
  return A;
}