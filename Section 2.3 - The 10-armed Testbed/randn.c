#include "randn.h"

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