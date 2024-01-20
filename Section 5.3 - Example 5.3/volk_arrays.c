#include "volk_arrays.h"

/* volk array functions */
/* Dimension lengths are hardcoded and set at compile time */
/* 0th dimension length: S0 (unneeded in these functions) */
/* 1st dimension length: S1 */
/* 2nd dimension length: S2 */
/* 3rd dimension length: A0 */
void set_volk_3d(double* array, double value, int i0, int i1, int i2, int len) {
  int index_3d = i0*S1*S2 + i1*S2 + i2;

  if (index_3d < len) {
    array[index_3d] = value;
  } else {
    fprintf(stderr, "(3d) Attempted write beyond array length: %d > %d\n", index_3d, len);
    exit(1);
  }
  return;
}

void set_volk_4d(double* array, double value, int i0, int i1, int i2, int i3, int len) {
  int index_4d = i0*S1*S2*A0 + i1*S2*A0 + i2*A0 + i3;

  if (index_4d < len) {
    array[index_4d] = value;
  } else {
    fprintf(stderr, "(4d) Attempted write beyond array length: %d > %d\n", index_4d, len);
    exit(1);
  }
  return;
}

double get_volk_3d(double* array, int i0, int i1, int i2, int len) {
  int index_3d = i0*S1*S2 + i1*S2 + i2;

  if (index_3d < len) {
    return array[index_3d];
  } else {
    fprintf(stderr, "(3d) Attempted write beyond array length: %d > %d\n", index_3d, len);
    exit(1);
  }
}

double get_volk_4d(double* array, int i0, int i1, int i2, int i3, int len) {
  int index_4d = i0*S1*S2*A0 + i1*S2*A0 + i2*A0 + i3;

  if (index_4d < len) {
    return array[index_4d];
  } else {
    fprintf(stderr, "(4d) Attempted write beyond array length: %d > %d\n", index_4d, len);
    exit(1);
  }
}