#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <unit_testing.h>
#include <jacobi_method.h>
#include <harmonic_oscillator.h>
#include <stdlib.h>             /* NULL */
#include <stdio.h>              /* srand, rand */
#include <time.h>               /* time */
#include <armadillo>
#include <iomanip>
#include <matrix.h>

using namespace std;
using namespace arma;


double SL(double wr, int matrix_dim, bool interaction, bool time, bool groundstate, double rho_min, double rho_max);
void normalize(double ** R, int n);
void ground_states(int &a,int &b, int &c, double * A, int n);
void n_vs_iteration_SL_plot_generator(int start, int stop);
void n_vs_itr_general_matrix_plot_generator(int start, int stop, int n);
double rand_float(int start, int stop);
double rand_norm(double max);                         /* Returns a random float between -10e4 and 10e4 */
double time_arma(double wr, int n, bool interaction);
void groundstates_plot_generator();
void armadillo_vs_jacobi_time_plot_generator();
void regression_plot();
double lanczos_algorithm(matrix &A);
matrix SL_matrix_generator(double wr, int matrix_dim, bool interaction, double rho_min, double rho_max);

int main(){

    const int n = 350;
    matrix A(n,n);
    A = SL_matrix_generator(1.0,n,false,0.0,4.5);

    mat B(n,n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            B(i,j) = A(i,j);

    lanczos_algorithm(A);
    vec eigval;
    mat eigvec;
    eig_sym(eigval, eigvec, B);
    cout << endl;
    sort(eigval);                       // Finding the lowest eigenvalue
    cout << eigval(0) << endl;
    cout << eigval(n-1) << endl;
    
    /*//////////////////////////////////////*/
    /*      Uncomment to run.               */
    /*//////////////////////////////////////*/
    //regression_plot();
    //n_vs_iteration_SL_plot_generator(3,150);
    //armadillo_vs_jacobi_time_plot_generator();
    //groundstates_plot_generator();
    //srand(time(NULL));
    //n_vs_itr_general_matrix_plot_generator(2, 150, 100);
    //cout << time_arma(1.0, 300, false) << endl;
    //cout << SL(1.0, 300, false, true, false) << endl;

    return 0;
}



void normalize(double ** R, int n){
    for(int i=0;i<n;i++){
        double sum = 0;
        for(int j=0;j<n;j++)
            sum += R[j][i]*R[j][i];
        for(int j=0;j<n;j++)
            R[j][i] = R[j][i]/sqrt(sum);
    }
    return;
}

void ground_states(int &a, int &b, int &c, double * A, int n){
    a=b=c=0;
    double s1 = A[0];
    double s2 = A[0];
    double s3 = A[0];
    for(int i=0;i<n;i++)
        if(s1 > A[i]){
            c = b;
            b = a;
            a = i;
            s1 = A[i];
        }
        else if(s2 > A[i]){
            c = b;
            b = i;
            s2 = A[i];
        }
        else if(s3 > A[i]){
            c = i;
            s3 = A[i];
        }
    return;
}

double SL(double wr, int matrix_dim, bool interaction, bool time, bool groundstate,double rho_min, double rho_max){

    const int n = matrix_dim;
    double h = (rho_max-rho_min)/(n+1);

    double rho[n];
    for(int i=0;i<n;i++)
        rho[i] = rho_min + (i+1)*h;


    double V[n];
    double coulomb;
    for(int i=0;i<n;i++){
        coulomb = interaction ? 1.0/(rho[i]) : 0.0;
        V[i] = pow(wr*rho[i],2) + coulomb;
    }

    double ** A;
    double ** R;
    A = new double*[n];
    R = new double*[n];

    for(int i=0;i<n;i++){
        A[i] = new double[n];
        R[i] = new double[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) A[i][j] = 2.0/pow(h,2) + V[i];
            else if(i == j+1 || j==i+1) A[i][j] = -1.0/pow(h,2);
            else A[i][j] = 0.0;
        }
    }

    clock_t start, finish;
    start = clock();
    int iterations = jacobi_method(A,R,n);
    normalize(R,n);
    finish = clock();

    if(groundstate){
        double S[n];
        for(int i=0;i<n;i++)
            S[i]=A[i][i];

        int a,b,c;
        ground_states(a,b,c,S,n);


        ofstream outfile;
        stringstream convert;
        convert << wr;
        string filename("SL_for_wr_");
        filename.append(convert.str());

        if(interaction)
            filename.append("_coulomb");
        filename.append(".txt");
        outfile.open(filename.c_str());
        outfile << rho_min << "  " << 0.0 << endl;
        for(int i=0;i<n;i++){
            outfile << rho[i] << "  " <<  R[a][i] << endl;
        }
        outfile << rho_max << "  " << 0.0 << endl;
        sort(S,S+n);
        cout << "Lamda for wr = " << wr;
        if(interaction)
            cout << " with interaction: ";
        else
            cout <<  " without interaction: ";
        cout << S[0] << endl;
        outfile.close();
     //system("python plotscript.py");
    }
    //sort(S,S+n);

     //cout << S[0] << endl;
     //cout << S[1] << endl;
     //cout << S[2] << endl;




    for(int i=0;i<n;i++){
         delete A[i];
         delete R[i];
    }
    delete [] A;
    delete [] R;
    return (time ? (finish - start)/double(CLOCKS_PER_SEC) : iterations);
}

void n_vs_iteration_SL_plot_generator(int start, int stop){
    ofstream outfile;
    outfile.open("iterations_vs_matrix_dim.txt");
    for(int i = start; i<stop+1; i++)
        outfile << i << "  " << static_cast<int>(SL(1.0,i, false, false, false,0.0,4.5)) << endl;
    outfile.close();
    system("python iterations_vs_matrix_dim.py");
    return;
}

void regression_plot(){
    system("python mplot.py");
    return;
}

void n_vs_itr_general_matrix_plot_generator(int start, int stop, int n){

    srand (time(NULL));
    int range = stop - start;
    int * a = new int [n];
    for(int i = 0; i<n; i++){
        a[i] = static_cast<int>(rand() % range + start);
    }
    double ***A;
    A = new double ** [n];
    for(int i = 0; i<n; i++){
        A[i] = new double * [a[i]];
        for(int j=0; j<a[i]; j++)
            A[i][j] = new double [a[i]];
    }
    for(int i = 0; i<n; i++){
        for(int j = 0; j<a[i]; j++ ){
            A[i][j][j] = (rand() % 2 ? 1 : -1)*rand_norm(10e4);
            for(int k = a[i]-1; k>j; k--){
                    A[i][j][k] = A[i][k][j] = (rand() % 2 ? 1 : -1)*rand_norm(10e4);
            }
        }
    }
    /*        printing matrices          */
    /*
    for(int i = 0; i<n; i++){
    cout << "matrix nr: " << i << endl;
        for(int j = 0; j<a[i]; j++ ){
               for(int k = 0; k<a[i]; k++){
                    cout << A[i][j][k] << "  ";
            }
        cout << endl;
        }
    }
    */
    double *** R;
    R = new double ** [n];
    for(int i = 0; i<n; i++){
        R[i] = new double * [a[i]];
        for(int j=0; j<a[i]; j++)
            R[i][j] = new double [a[i]];
    }

    int * iterations;
    iterations =  new int[n];
    for(int i = 0; i<n; i++){
        iterations[i] = jacobi_method(A[i],R[i],a[i]);
    }
    ofstream outfile;
    outfile.open("RandMatData.txt");
    for(int i = 0; i<n; i++){
        outfile << a[i] << "  " << iterations[i] << endl;
    }
    outfile.close();
    for (int i = 0; i<n; i++) {
        for (int j = 0; j < a[i]; j++)
            delete [] A[i][j];
            delete [] A[i];
    }
    delete [] A;

    for (int i = 0; i<n; i++) {
        for (int j = 0; j < a[i]; j++)
            delete [] R[i][j];
            delete [] R[i];
    }
    delete [] R;
    system("python RandMatData.py");
    return;
}

double rand_float(int start, int stop){
    double a = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    a *= stop;
    a *= (rand() % 2 ? 1 : -1);
    a += start;
    return a;
}
double time_arma(double wr, int n, bool interaction){
    time_t start, finish;

    mat A(n,n);
    A.zeros();


        double rho_max = 4.5;
        double rho_min = 0;
        double h = (rho_max-rho_min)/(n+1);

        double V[n];
        double coulomb;
        for(int i=0;i<n;i++){
            coulomb = interaction ? 1.0/(rho_min+(i+1)*h) : 0.0;
            V[i] = pow(rho_min+wr*(i+1)*h,2) + coulomb;
        }


        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i==j) A(i,j) = 2.0/pow(h,2) + V[i];
                else if(i == j+1 || j==i+1) A(i,j) = -1.0/pow(h,2);
                else A(i,j) = 0.0;
            }
        }

    vec eigval;
    mat eigvec;
    start  = clock();
    eig_sym(eigval, eigvec, A);
    /* checking eigvals */
    /*sort(eigval);
    cout << eigval(0) << endl;
    cout << eigval(1) << endl;
    cout << eigval(2) << endl;*/
    finish = clock();

    return ((finish - start)/double(CLOCKS_PER_SEC));
}

void groundstates_plot_generator(){
    double rho_min = 0.0;
    double rho_max = 7.0;
    SL(0.01, 100, false, false, true,rho_min, rho_max);
    SL(0.01, 100, true, false, true,rho_min, rho_max);
    SL(0.5, 100, false, false, true,rho_min, rho_max);
    SL(0.5, 100, true, false, true,rho_min, rho_max);
    SL(1.0, 100, false, false, true,rho_min, rho_max);
    SL(1.0, 100, true, false, true,rho_min, rho_max);
    SL(5.0, 100, false, false, true,rho_min, rho_max);
    SL(5.0, 100, true, false, true,rho_min, rho_max);
    system("python groundstates.py");
    return;
}

void armadillo_vs_jacobi_time_plot_generator(){
    double wr = 1.0;



    ofstream outfile;
    outfile.open("time_table.txt");


    for(int i = 0; i<5; i++){
        outfile << setprecision(15) << 10*(i+2) << "   ";
        outfile << setprecision(15) << setw(15) << SL(wr,10*(i+2),false,true, false,0.0,4.5) << "   ";
        outfile << setprecision(15) << setw(15) << time_arma(wr,10*(i+2),false);
        outfile << endl;
    }
    outfile.close();

    return;
}

matrix SL_matrix_generator(double wr, int matrix_dim, bool interaction, double rho_min, double rho_max){
    int n = matrix_dim;
    matrix A(n,n);

    double h = (rho_max-rho_min)/(n+1);

    double rho[n];
    for(int i=0;i<n;i++)
        rho[i] = rho_min + (i+1)*h;

    double V[n];
    double coulomb;
    for(int i=0;i<n;i++){
        coulomb = interaction ? 1.0/(rho[i]) : 0.0;
        V[i] = pow(wr*rho[i],2) + coulomb;
    }




    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) A(i,j) = 2.0/pow(h,2) + V[i];
            else if(i == j+1 || j==i+1) A(i,j) = -1.0/pow(h,2);
            else A(i,j) = 0.0;
        }
    }
    return A;
}

double lanczos_algorithm(matrix& A){
    int maxit = 300;
    int n = A.getRows();
    int j = 0;
    matrix I(n,n);
    I.zeros();
    for(int i=0;i<n;i++)
        I(i,i) = 1;

    matrix r(n,1); r.randu();
    matrix b(1,maxit); b.zeros();
    matrix Q(n,maxit-1); Q.zeros();
    matrix a(1,maxit); a.zeros();
    matrix q1(n,1); q1.zeros();
    matrix q2(n,1); q2.zeros();

    clock_t start,finish;
    start = clock();

    b(0,0) = r.norm(0);

    while (abs(b(0,j)) > 1e-3 && j < maxit-1){
        q2 = r/b(0,j);
        j = j+1;
        a(0,j) = (q2.T()*A*q2)(0,0);            // beregne q^T*A*q;
        r = (A-a(0,j)*I)*q2 - b(0,j-1)*q1;
        //r = A*q2 - a(0,j)*q2 - b(0,j-1)*q1; // beregne (A-a[j]I)*q[j] - b[j-1]*q[j-1];
        b(0,j) = r.norm(0);
        q1 = q2;
        for(int i=0;i<n;i++){
            Q(i,j-1) = q2(i,0);
        }
    }
    //(Q.T()*Q).print();
    mat T(maxit-1,maxit-1);
    matrix temp(maxit,maxit); temp = Q.T()*A*Q;
    finish = clock();
    for(int i=0;i<maxit-1;i++)
        for(int j=0;j<maxit-1;j++)
            T(i,j) = temp(i,j);


    vec eigval;
    mat eigvec;
    eig_sym(eigval, eigvec, T);
    cout << endl;
    sort(eigval);                       // Finding the lowest eigenvalue
    cout << eigval(0) << endl;
    cout << eigval(maxit-2) << endl;
    return ((finish - start)/double(CLOCKS_PER_SEC));
}

