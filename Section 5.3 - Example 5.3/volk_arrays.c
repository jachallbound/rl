#include "volk_arrays.h"

/* volk array functions */
/* Dimension lengths are hardcoded and set at compile time */
/* 0th dimension length: S0 (unneeded in these functions) */
/* 1st dimension length: S1 */
/* 2nd dimension length: S2 */
/* 3rd dimension length: A0 */
void set_volk_3d(double* array, double value, int i0, int i1, int i2, int len) {
  #if VOLK_DEBUG
  printf("i0 = %2d, i1 = %2d, i2 = %2d | \n", i0, i1, i2);
  #endif /* VOLK_DEBUG */

  int index_3d = i0*S1*S2 + i1*S2 + i2; /* first line of real code */

  #if VOLK_CHECK_LENGTH
  if (index_3d < len) {
  #endif /* VOLK_CHECK_LENGTH */

    array[index_3d] = value; /* second line of real code */

  #if VOLK_CHECK_LENGTH
  } else {
    fprintf(stderr, "(3d) Attempted write beyond array length: %d > %d\n", index_3d, len);
    
    #if VOLK_EXIT_IF_OVER_LENGTH
    exit(1);
    #endif /* VOLK_EXIT_IF_OVER_LENGTH */

  }
  #endif /* VOLK_CHECK_LENGTH */
  return;
}

void set_volk_4d(double* array, double value, int i0, int i1, int i2, int i3, int len) {
  #if VOLK_DEBUG
  printf("i0 = %2d, i1 = %2d, i2 = %2d i3 = %2d | \n", i0, i1, i2, i3);
  #endif /* VOLK_DEBUG */

  int index_4d = i0*S1*S2*A0 + i1*S2*A0 + i2*A0 + i3; /* first line of real code */

  #if VOLK_CHECK_LENGTH
  if (index_4d < len) {
  #endif /* VOLK_CHECK_LENGTH */

    array[index_4d] = value; /* second line of real code */

  #if VOLK_CHECK_LENGTH
  } else {
    fprintf(stderr, "(4d) Attempted write beyond array length: %d > %d\n", index_4d, len);
    
    #if VOLK_EXIT_IF_OVER_LENGTH
    exit(1);
    #endif /* VOLK_EXIT_IF_OVER_LENGTH */

  }
  #endif /* VOLK_CHECK_LENGTH */
  return;
}

double get_volk_3d(double* array, int i0, int i1, int i2, int len) {
  #if VOLK_DEBUG
  printf("i0 = %2d, i1 = %2d, i2 = %2d | \n", i0, i1, i2);
  #endif /* VOLK_DEBUG */

  int index_3d = i0*S1*S2 + i1*S2 + i2; /* first line of real code */

  #if VOLK_CHECK_LENGTH
  if (index_3d < len) {
  #endif /* VOLK_CHECK_LENGTH */

    return array[index_3d]; /* second line of real code */

  #if VOLK_CHECK_LENGTH
  } else {
    fprintf(stderr, "(3d) Attempted write beyond array length: %d > %d\n", index_3d, len);
    
    #if VOLK_EXIT_IF_OVER_LENGTH
    exit(1);
    #endif /* VOLK_EXIT_IF_OVER_LENGTH */
    
  }
  #endif /* VOLK_CHECK_LENGTH */
}

double get_volk_4d(double* array, int i0, int i1, int i2, int i3, int len) {
  #if VOLK_DEBUG
  printf("i0 = %2d, i1 = %2d, i2 = %2d i3 = %2d | \n", i0, i1, i2, i3);
  #endif /* VOLK_DEBUG */

  int index_4d = i0*S1*S2*A0 + i1*S2*A0 + i2*A0 + i3; /* first line of real code */

  #if VOLK_CHECK_LENGTH
  if (index_4d < len) {
  #endif /* VOLK_CHECK_LENGTH */

    return array[index_4d]; /* second line of real code */

  #if VOLK_CHECK_LENGTH
  } else {
    fprintf(stderr, "(4d) Attempted write beyond array length: %d > %d\n", index_4d, len);
    
    #if VOLK_EXIT_IF_OVER_LENGTH
    exit(1);
    #endif /* VOLK_EXIT_IF_OVER_LENGTH */

  }
  #endif /* VOLK_CHECK_LENGTH */
}