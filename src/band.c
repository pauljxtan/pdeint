#include <complex.h>
#include <stdlib.h>
#include "band.h"
#include "utils.h"

/* Solves the band matrix equation given by Ax = v (real version)
 * See docs for info on band storage format */
double * solve_band(double A[], double v[], int n,
                    int n_diag_above, int n_diag_below) {
    int i, j, k, m;
    int n_diags = 1 + n_diag_above + n_diag_below;
    double * A_tmp = malloc(n_diags * n * sizeof(double));
    double * x = malloc(n * sizeof(double));
    double norm;
    
    /* Copy A and v into A_tmp and x */
    for (i = 0; i < n_diags ; i++)
        for (j = 0; j < n ; j++)
            A_tmp[i * n + j] = A[i * n + j];
    for (i = 0; i < n; i++)
        x[i] = v[i];

    /* Do Gaussian elimination */
    for (i = 0; i < n; i++) {

        /* Get normalization factor */
        norm = A_tmp[n * n_diag_above + i];

        /* Normalize and update v */
        x[i] /= norm;
        for (j = 1; j < n_diag_below + 1; j++)
            if ((i + j) < n)
                x[i + j] -= A_tmp[n * (n_diag_above + j) + i] * x[i];

        /* Normalize pivot row and subtract it from lower rows */
        for (j = 0; j < n_diag_above; j++) {
            k = i + n_diag_above - j;
            if (k < n) {
                A_tmp[n * j + k] /= norm;
                for (m = 1; m < n_diag_below + 1; m++)
                    A_tmp[n * (j + m) + k] -= A_tmp[n * (n_diag_above + m) + i]
                                              * A_tmp[n * j + k];
            }
        }
    }

    /* Do back-substitution */
    for (i = n - 2; i >= 0; i--) {
        for (j = 0; j < n_diag_above; j++) {
            k = i + n_diag_above - j;
            if (k < n)
                x[i] -= A_tmp[n * j + k] * x[k];
        }
    }

    return x;
}

/* Solves the band matrix equation given by Ax = v (complex version)
 * See docs for info on band storage format */
complex double * solve_band_complex(complex double A[], complex double v[],
                                    int n, int n_diag_above,
                                    int n_diag_below) {
    int i, j, k, m;
    int n_diags = 1 + n_diag_above + n_diag_below;
    complex double * A_tmp = malloc(n_diags * n * sizeof(complex double));
    complex double * x = malloc(n * sizeof(complex double));
    complex double norm;
    
    /* Copy A and v into A_tmp and x */
    for (i = 0; i < n_diags ; i++)
        for (j = 0; j < n ; j++)
            A_tmp[i * n + j] = A[i * n + j];
    for (i = 0; i < n; i++)
        x[i] = v[i];

    /* Do Gaussian elimination */
    for (i = 0; i < n; i++) {

        /* Get normalization factor */
        norm = A_tmp[n * n_diag_above + i];

        /* Normalize and update v */
        x[i] /= norm;
        for (j = 1; j < n_diag_below + 1; j++)
            if ((i + j) < n)
                x[i + j] -= A_tmp[n * (n_diag_above + j) + i] * x[i];

        /* Normalize pivot row and subtract it from lower rows */
        for (j = 0; j < n_diag_above; j++) {
            k = i + n_diag_above - j;
            if (k < n) {
                A_tmp[n * j + k] /= norm;
                for (m = 1; m < n_diag_below + 1; m++)
                    A_tmp[n * (j + m) + k] -= A_tmp[n * (n_diag_above + m) + i]
                                              * A_tmp[n * j + k];
            }
        }
    }

    /* Do back-substitution */
    for (i = n - 2; i >= 0; i--) {
        for (j = 0; j < n_diag_above; j++) {
            k = i + n_diag_above - j;
            if (k < n)
                x[i] -= A_tmp[n * j + k] * x[k];
        }
    }

    return x;
}

/*
int main() {
    int n = 3;
    double * A = malloc(n * n * sizeof(double));
    double * v = malloc(n * sizeof(double));
    double * x = malloc(n * sizeof(double));

    A[0] = 0.0; A[1] = 3.4; A[2] = 5.6;
    A[3] = 7.8; A[4] = 9.1; A[5] = 2.3;
    A[6] = 4.5; A[7] = 6.7; A[8] = 0.0;

    v[0] = 9.7; v[1] = 6.4; v[2] = 3.1;

    x = solve_band(A, v, n, 1, 1);
    print_arr(A, n * n);
    print_arr(v, n);
    print_arr(x, n);
    
    return 0;
}
*/
