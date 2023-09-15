#include "functions.h"

/* Gaussian */
void randn(double mean, double std, double* array, int len) {
  for (int i = 0; i < len; i++) {
    array[i] = ltqnorm((double)rand()/RAND_MAX)*std + mean;
  }
  return;
}

/* Poisson */
void randp(double mean, int* array, int len) {
  /* Knuth method */
  double L = exp(-1*mean);
  for (int i = 0; i < len; i++) {
    double p = 1;
    int k = 0;
    do {
      k++;
      p = p * (double)rand()/RAND_MAX;
    } while (p > L);
    array[i] = k - 1;
  }
  return;
}

double pdfp(double mean, int count) {
  return (pow(mean, (double)count))/(tgamma((double)count+1))*exp(-1*mean);
}

/* Argmax */
int argmax(double* array, int len) {
  double max = -1E9;
  int mi = 0;
  for (int i = 0; i < len; i++) {
    if (array[i] > max) {
      max = array[i];
      mi = i;
    }
  }
  return mi;
}

/* Softmax */
void softmax(double* pi, double* H, int len) {
  double Hb = 0;
  for (int i = 0; i < len; i++) Hb += exp(H[i]);
  for (int i = 0; i < len; i++) pi[i] = exp(H[i])/Hb;
  return;
}

/* Random decision */
int random_decision(double* pi, int len) {
  double d = 0, p = 0;
  d = (double)rand()/RAND_MAX;
  for (int i = 0; i < len; i++)
    if (d > p && d < (p+=pi[i])) return i;

  /* Should not reach here */
  return 0;
}
