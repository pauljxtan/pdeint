/* Miscellaneous utility functions. */

#include <complex.h>
#include <stdio.h>

/* Print the elements of a double array arr of length n */
void print_arr(double arr[], int n) {
    int i;

    for (i = 0; i < n - 1; i++)
        printf("%f ", arr[i]);
    printf("%f\n", arr[n - 1]);
}

/* Print the elements of a complex double array arr of length n */
void print_arr_complex(complex double arr[], int n) {
    int i;

    for (i = 0; i < n - 1; i++)
//        printf("%f%+fi ", creal(arr[i]), cimag(arr[i]));
//    printf("%f%+fi\n", creal(arr[n - 1]), cimag(arr[n - 1]));
//        printf("%f ", creal(arr[i]));
//    printf("%f\n", creal(arr[n - 1]));
        printf("%f ", cabs(arr[i]));
    printf("%f\n", cabs(arr[n - 1]));
}
