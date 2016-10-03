#include <iostream>
#include <cmath>
#include <jacobi_method.h>

using namespace std;


double off(double ** A, int &k, int &l, int n){
    double max = 0;
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(max < abs(A[i][j]))
            {
                max = abs(A[i][j]);
                k = i;
                l = j;
            }
        }
    }

    return max;
}

void rotate(double ** A, double ** R, int k, int l, int n){


    double s,c,t,tau;
    double a_kk, a_ll, a_kl, a_ik, a_il;


    a_kk = A[k][k];
    a_ll = A[l][l];
    a_kl = A[k][l];

    tau = (a_ll-a_kk)/(2*a_kl);
    //if(tau > 0) t = -tau + sqrt(1 + pow(tau,2));
    //else t = -tau - sqrt(1 + pow(tau,2));
    if(tau > 0) t = 1.0/(tau + sqrt(1 + tau*tau));
    else t = -1.0/(-tau + sqrt(1+tau*tau));
    if(t == 0){ c = 1.0; s=0.0;}
    else{
    c = 1.0/sqrt(1 + pow(t,2));
    s = t*c;}

    A[k][k] = a_kk*pow(c,2) - 2*a_kl*c*s + a_ll*pow(s,2);
    A[l][l] = a_ll*pow(c,2) + 2*a_kl*c*s + a_kk*pow(s,2);
    //A[k][l] = A[l][k] = 0.0;
    A[k][l] = A[l][k] = (a_kk-a_ll)*c*s + a_kl*(c*c -s*s);
    for(int i=0;i<n;i++){
        if( i != k && i != l){
            a_ik = A[i][k];
            a_il = A[i][l];
            A[i][k] = A[k][i] = a_ik*c - a_il*s;
            A[i][l] = A[l][i] = a_il*c + a_ik*s;
        }

    double r_ki = R[k][i];
    double r_li = R[l][i];
    R[k][i] = c*r_ki - s*r_li;
    R[l][i] = c*r_li + s*r_ki;

    }
    return;
}

int jacobi_method(double ** A, double ** R, int n){

    int counter = 0;
    int k, l;
    double eps = 1.0e-8;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            R[i][j] = ( i==j ? 1.0 : 0.0 );
        }
    }
    while(off(A,k,l,n) > eps){
        rotate(A,R,k,l,n);
        counter++;
    }
    //cout << "number of iterations: " << counter << endl;
    return counter;
}

