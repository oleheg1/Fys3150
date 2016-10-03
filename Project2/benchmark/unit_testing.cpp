#include <iostream>
#include <cmath>
#include <unit_testing.h>
#include <jacobi_method.h>
using namespace std;

void test2x2(){
    cout << "--------------------" << endl;
    cout << "Jacobi method test for 2x2 matrix: " << endl;
    const int n = 2;
    double ** A;
    double ** D;
    A = new double*[n];
    D = new double*[n];
    for(int i=0;i<n;i++){
        A[i] = new double[n];
        D[i] = new double[n];
    }
    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 2;
    A[1][1] = 1;

    jacobi_method(A,D,n);
    cout << "Eigenvector Matrix: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Eigenvalues: " << endl;
    for(int i=0;i<n; i++)
        cout << A[i][i] << endl;
        cout << "--------------------" << endl;

    for(int i=0;i<n;i++){
        delete A[i];
        delete D[i];
    }
    delete [] A;
    delete [] D;

    return;

}

void test_off(){
    cout << "off diagonal function test:" << endl;
    const int n = 3;
    double ** A;
    A = new double*[n];
    for(int i=0;i<n;i++)
        A[i] = new double[n];

    cout << "Matrix A:" << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i][j] = -i-j;
            cout << -i-j << "  ";
        }
        cout << endl;
    }
    int k,l;
    off(A,k,l,n);
    cout << "Max elemental off diagonal for matrix A: " << A[k][l] << endl;
    cout << "--------------------" << endl;

    for(int i=0;i<n;i++)
        delete A[i];
    delete [] A;

    return;
}

void test_orthogonal(){
    const int n = 2;
    double ** A;
    double ** D;
    A = new double*[n];
    D = new double*[n];
    for(int i=0;i<n;i++){
        A[i] = new double[n];
        D[i] = new double[n];
    }
    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 2;
    A[1][1] = 1;
    cout << "Ortogonality test:" << endl;
    cout << "Jacobi method gives: ";
    jacobi_method(A,D,n);

    cout << "Eigenvector Matrix: " << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << D[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "checking orthogonality by multiplication" << endl;
    cout << "D[0][0]*D[0][1] + D[1][0]*D[1][1] =  ";
    cout << D[0][0]*D[0][1] + D[1][0]*D[1][1] << endl;
    cout <<"--------------------" << endl;

    for(int i=0;i<n;i++){
        delete A[i];
        delete D[i];
    }
    delete [] A;
    delete [] D;

    return;
}

void test_all(){
    test2x2();
    test_off();
    test_orthogonal();
    test5x5();
    return;
}

void test5x5(){
    int n = 5;
    double ** A;
    double ** R;
    A = new double*[n];
    R = new double*[n];

    for(int i=0;i<n;i++){
        A[i] = new double[n];
        R[i] = new double[n];
    }
    // Eigenvalue for matrix A: [0 0 0 0 55]
    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[0][3] = 4;
    A[0][4] = 5;
    A[1][0] = 2;
    A[1][1] = 4;
    A[1][2] = 6;
    A[1][3] = 8;
    A[1][4] = 10;
    A[2][0] = 3;
    A[2][1] = 6;
    A[2][2] = 9;
    A[2][3] = 12;
    A[2][4] = 15;
    A[3][0] = 4;
    A[3][1] = 8;
    A[3][2] = 12;
    A[3][3] = 16;
    A[3][4] = 20;
    A[4][0] = 5;
    A[4][1] = 10;
    A[4][2] = 15;
    A[4][3] = 20;
    A[4][4] = 25;

    jacobi_method(A,R,n);
    cout << "Jacobi method test for 5x5 matrix: " << endl;
    for(int i=0;i<n;i++)
        cout << A[i][i] << endl;

    cout << "--------------------" << endl;

    for(int i=0;i<n;i++){
        delete A[i];
        delete R[i];
    }
    delete [] A;
    delete [] R;
}

/*
void test_for_matrix_and_vector_functions(){
    const int n = 2;
    double ** A;
    double * x;
    double * y;
    A = new double*[n];
    x = new double[n];
    for(int i=0;i<n;i++){
        A[i] = new double[n];
    }
    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;
    x[0] = 3;
    x[1] = 4;
    y = matrix_vector_multiplication(A,x,n);
    cout << y[0] << "\n" << y[1] << endl;
    cout << dot_product(x,y,n) << endl;

    for(int i=0;i<n;i++)
        delete A[i];

    delete [] A;
    delete [] x;
    delete [] y;

}*/
// Unit testing output //
//------------------------------------------------//
/*Debugging starts
number of iterations: 35784
2.33721
4.0852
5.51554
--------------------
Jacobi method test for 2x2 matrix:
number of iterations: 1
Eigenvector Matrix:
0.707107 0.707107
-0.707107 0.707107
Eigenvalues:
3
-1
--------------------
off diagonal function test:
Matrix A:
0  -1  -2
-1  -2  -3
-2  -3  -4
Max elemental off diagonal for matrix A: -3
--------------------
Ortogonality test:
Jacobi method gives: number of iterations: 1
Eigenvector Matrix:
0.707107  0.707107
-0.707107  0.707107
checking orthogonality by multiplication
D[0][0]*D[0][1] + D[1][0]*D[1][1] =  0
--------------------
Jacobi method test for 5x5 matrix:
2.22045e-16
1.77636e-15
-8.88178e-16
-1.77636e-15
55
--------------------
Debugging has finished */
//------------------------------------------------//


