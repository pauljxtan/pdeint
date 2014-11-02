/* Integrating the quantum-mechanical "particle in a box", using a
 * Crank-Nicolson finite difference scheme.
 * Refer to the documentation for derivations. */

#include <complex.h>    // needs C99
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "band.h"
#include "constants.h"
#include "utils.h"

void print_usage();

int main(int argc, char *argv[]) {
    if (argc != 7) {
        print_usage();
        return 1;
    }

    /* Width of box [m] */
    const double L = atof(argv[1]);
    /* Number of grid steps */
    const int N = atoi(argv[2]);
    /* Grid spacing */
    const double a = L / (N - 1);
    /* Length of time-step */
    const double dt = atof(argv[3]);
    /* Number of time-steps */
    const int nsteps = atoi(argv[4]);

    /* Wavefunction constants */
    const double x0 = L / 2.0;
    const double sigma = atof(argv[5]);
    const double kappa = atof(argv[6]);

    /* Elements of the matrices A and B (see docs for derivation) */
    const complex double a1 = 1.0 + (dt * hbar) / (2.0 * m_e * a*a) * I;
    const complex double a2 = 0.0 - (dt * hbar) / (4.0 * m_e * a*a) * I;
    const complex double b1 = 1.0 - (dt * hbar) / (2.0 * m_e * a*a) * I;
    const complex double b2 = 0.0 + (dt * hbar) / (4.0 * m_e * a*a) * I;

    int i, j;
    complex double * A = malloc(3 * N * sizeof(complex double));
    double * x = malloc(N * sizeof(double));
    complex double * psi = malloc(N * sizeof(complex double));
    complex double * v = malloc(N * sizeof(complex double));
    
    /* Cast the tridiagonal matrix A in band storage format... */
    /* Construct the top diagonal */
    A[0] = 0.0 + 0.0 * I;
    A[1] = 0.0 + 0.0 * I;
    for (i = 2; i < N; i++)
        A[i] = a2;
    /* Construct the central diagonal */
    A[N] = 1.0 + 1.0 * I;
    for (i = N + 1; i < 2 * N - 1; i++)
        A[i] = a1;
    A[2 * N - 1] = 1.0 + 1.0 * I;
    /* Construct the bottom diagonal */
    for (i = 2 * N; i < 3 * N - 2 ; i++)
        A[i] = a2;
    A[3 * N - 2] = 0.0 + 0.0 * I;
    A[3 * N - 1] = 0.0 + 0.0 * I;

    /* Construct the x-axis */
    for (i = 0; i < N; i++)
        x[i] = i * a;

    /* Set the initial wavefunction */
    for (i = 0; i < N; i++)
        psi[i] = cexp(- pow(x[i] - x0, 2) / (2.0 * pow(sigma, 2)))
                 * cexp(kappa * x[i] * I);

    /* Set boundary conditions at psi(x=0) and psi(x=L) (i.e. box walls) */
    psi[0] = 0.0 + 0.0 * I;
    psi[N - 1] = 0.0 + 0.0 * I;

    /* Compute psi(x, t) at each time-step */
    for (i = 1; i < nsteps; i++) {

        /* Compute the vector v = B * psi (see docs for derivation) */
        for (j = 0; j < N; j++) {
            if (j == 0)
                //v[j] = b1 * psi[j] + b2 * psi[j + 1];
                v[j] = 0.0 + 0.0 * I;
            else if (j == (N - 1))
                //v[j] = b1 * psi[j] + b2 * psi[j - 1];
                v[j] = 0.0 + 0.0 * I;
            else
                v[j] = b1 * psi[j] + b2 * (psi[j + 1] + psi[j - 1]);
        }

        /* Now solve A * psi = v, where psi is the new wavefunction */
        psi = solve_band_complex(A, v, N, 1, 1);

        print_arr_complex(psi, N);
    }

    return EXIT_SUCCESS;
}

void print_usage() {
    printf("Usage: ./particle_box [box width] [grid steps] [time step] "
           "[number of steps] [sigma] [kappa]\n");
}
