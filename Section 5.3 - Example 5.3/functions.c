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

/* Uniform decision */
int uniform_decision(int len) {
  double pi = 1/(double)len;
  double d = 0, p = 0;
  d = (double)rand()/RAND_MAX;
  for (int i = 0; i < len; i++)
    if ((d > p) && (d < (p+=pi))) return i;

  /* Should not reach here */
  return 0;
}



/*
 * Lower tail quantile for standard normal distribution function.
 *
 * This function returns an approximation of the inverse cumulative
 * standard normal distribution function.  I.e., given P, it returns
 * an approximation to the X satisfying P = Pr{Z <= X} where Z is a
 * random variable from the standard normal distribution.
 *
 * The algorithm uses a minimax approximation by rational functions
 * and the result has a relative error whose absolute value is less
 * than 1.15e-9.
 *
 * Author:      Peter John Acklam
 * Time-stamp:  2002-06-09 18:45:44 +0200
 * E-mail:      jacklam@math.uio.no
 * WWW URL:     http://www.math.uio.no/~jacklam
 *
 * C implementation adapted from Peter's Perl version
 */



double ltqnorm(double p) {
	double q, r;

	errno = 0;

	if (p < 0 || p > 1)
	{
		errno = EDOM;
		return 0.0;
	}
	else if (p == 0)
	{
		errno = ERANGE;
		return -HUGE_VAL /* minus "infinity" */;
	}
	else if (p == 1)
	{
		errno = ERANGE;
		return HUGE_VAL /* "infinity" */;
	}
	else if (p < LOW)
	{
		/* Rational approximation for lower region */
		q = sqrt(-2*log(p));
		return (((((c[0]*q+c[1])*q+c[2])*q+c[3])*q+c[4])*q+c[5]) /
			((((d[0]*q+d[1])*q+d[2])*q+d[3])*q+1);
	}
	else if (p > HIGH)
	{
		/* Rational approximation for upper region */
		q  = sqrt(-2*log(1-p));
		return -(((((c[0]*q+c[1])*q+c[2])*q+c[3])*q+c[4])*q+c[5]) /
			((((d[0]*q+d[1])*q+d[2])*q+d[3])*q+1);
	}
	else
	{
		/* Rational approximation for central region */
    		q = p - 0.5;
    		r = q*q;
		return (((((a[0]*r+a[1])*r+a[2])*r+a[3])*r+a[4])*r+a[5])*q /
			(((((b[0]*r+b[1])*r+b[2])*r+b[3])*r+b[4])*r+1);
	}
}
