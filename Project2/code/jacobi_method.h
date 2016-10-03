#ifndef JACOBI_METHOD
#define JACOBI_METHOD

double off(double **A, int &k, int &l, int n);
void rotate(double ** A, double ** R, int k, int l, int n);
int jacobi_method(double ** A, double ** R, int n);


#endif // JACOBI_METHOD


