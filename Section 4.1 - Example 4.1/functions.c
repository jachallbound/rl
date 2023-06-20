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
  for (size_t i = 0; i < len; i++) {
    if (array[i] > max) {
      max = array[i];
      mi = i;
    }
  }
  return mi;
}

void softmax(double* pi, double* H, size_t len) {
  double Hb = 0;
  for (size_t i = 0; i < len; i++) Hb += exp(H[i]);
  for (size_t i = 0; i < len; i++) pi[i] = exp(H[i])/Hb;
  return;
}

size_t random_decision(double* pi, size_t len) {
  double d = 0, p = 0;
  d = (double)rand()/RAND_MAX;
  for (size_t i = 0; i < len; i++)
    if (d > p && d < (p+=pi[i])) return i;

  /* Should not reach here */
  return 0;
}
