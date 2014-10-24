#ifndef BAND_H
#define BAND_H

double * solve_band(double A[], double v[], int n, int n_diag_above,
                    int n_diag_below);

complex double * solve_band_complex(complex double A[], complex double v[],
                                    int n, int n_diag_above, int n_diag_below);

#endif /* BAND_H */
