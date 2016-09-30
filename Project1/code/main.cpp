#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <armadillo>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;
using namespace arma;

double Thomas_algorithm(double(*f1)(double),double(*f2)(double),int n);
double Ferrari(double(*f1)(double),int n);
double g(double x){return 100*exp(-10.0*x);}
double dfdx(double x){return (1-(1-exp(-10.0))*x-exp(-10.0*x));}
double LU_solver(double(*f1)(double),int n);

int main(int argc, char* argv[]){
	

	int N;
	(argv[1] != NULL) ? N = atoi(argv[1]) : N = 6;

	ofstream outfile;
	outfile.open("Time.txt");
	for(int i = 1; i<N+1; i++){
		int n;
		n = pow(10,i);
		outfile << "For 10^" << i << ":" << endl;
		outfile << "Time specalized algorithm:     " << showpoint(10) << setprecision(15) << Ferrari(g,n) << endl;
		outfile << "Time for the Thomas algorithm: " << showpoint(10) << setprecision(15) << Thomas_algorithm(g,dfdx,n) << endl;	
		//outfile << "Time for LU decomposition:     " << showpoint(10) << setprecision(15) << LU_solver(g,n) << endl;	
	}	
	outfile.close();

	system("python Relative_error_plot.py");
	return 0;
}



// LU func
double LU_solver(double(*f1)(double),int n){

		
	double *xi;
	xi = new double[n+2];
	double x0, xn;
	x0 = 0; xn = 1;	
	double h = (xn-x0)/(1+n);

	for(int i=0;i<n+2; i++)
        	xi[i] = x0 + i*h;

	
	mat L,U;
	mat A = zeros<mat>(n,n);
	vec x,y;
	vec f = vec(n);
	for(int i=0; i<n; i++) {
		A(i,i) = -2;
		f(i) = -f1(xi[i+1])*pow(h,2);
	    	}
	for(int i=0;i<n-1; i++)
	{
		A(i,i+1) = 1;
		A(i+1,i) = 1;
	}

	clock_t start, finish;
	start = clock();

	lu(L,U,A);
	y = solve(L,f);
	x = solve(U,y);

	finish = clock();

	ofstream outfile;
	stringstream convert;
	convert << n;
	string filename("LU");
	filename.append(convert.str() + ".txt");
	outfile.open(filename.c_str());
    	outfile << n << endl;
    	for(int i=0;i<n;i++){
        	outfile << left << setprecision(15) << setw(22) << x(i) << endl;
    	}
    	outfile.close();
	delete [] xi;
	return ((finish-start)/((double)CLOCKS_PER_SEC )); 
}

double Thomas_algorithm(double(*f1)(double),double(*f2)(double),int n){

	double *a, *b, *c, *f, *u, *x;
	a = new double[n];	
	b = new double[n];	
	c = new double[n];	
	f = new double[n];	
	u = new double[n+2];	
	x = new double[n+2];	

	for(int i = 0; i<n; i++){
		a[i] = -2;
		b[i] = 1;
		c[i] = 1;
	}
	
	double x0, xn;
	x0 = 0; xn = 1;	
	double h = (xn-x0)/(1+n);
	
	for(int i=0;i<n+2; i++)
        	x[i] = x0 + i*h;

	for(int i=0;i<n; i++)
        	f[i] = -f1(x[i+1])*pow(h,2);
	double timeused;
	clock_t start, finish;
	start = clock();

	// FWS
	for(int i = 1; i<n; i++){
		double p = c[i-1]/a[i-1];	
		a[i] = a[i]-b[i-1]*p;
		f[i] = f[i]-f[i-1]*p;
	}
	// BWS
	u[0] = 0;
	u[n+1] = 0;
	u[n] = f[n-1]/a[n-1];
	for(int i = n-1; i > 0; i--){
		u[i] = (f[i-1]-b[i-1]*u[i+1])/a[i-1];
	}
	finish = clock();
	
	stringstream convert;
	convert << n;
	string filename("Thomas_algorithm");
	filename.append(convert.str() + ".txt");
	
	ofstream outfile;

  	outfile.open(filename.c_str());

    	outfile << n << endl;
    	for(int i=0;i<n+2;i++){
        	outfile << left << setprecision(15) << setw(22) << u[i] << setw(22) << f2(x[i]) << setw(22) << x[i] << endl;
    	}
    	outfile.close();

	
	delete [] a;
	delete [] b;
	delete [] c;
	delete [] f;
	delete [] u;
	delete [] x;	

	//"python readfile.py"


	string cmdw("start readfile.py");
	cmdw.append(" ");
	cmdw.append(filename);
	string cmdl("python readfile.py");
	cmdl.append(" ");
	cmdl.append(filename);
	n == 10 ? cmdw.append(" 1") : cmdw.append(" 0");
	n == 10 ? cmdl.append(" 1") : cmdl.append(" 0");

	#ifdef OS_WINDOWS
		system(cmdw.c_str());
	#else
		system(cmdl.c_str());	
	#endif
	timeused = ((static_cast<double>(finish)-(static_cast<double>(start))/((double)CLOCKS_PER_SEC );
	//return ((finish-start)/((double)CLOCKS_PER_SEC ));
	return timeused;
}

double Ferrari(double(*f1)(double),int n){
	

	double * d;
	double * f;
	double * v;
	double * x;
	d = new double[n];
	f = new double[n];
	v = new double[n+2];
	x = new double[n+2];
	double x0, xn;
	x0 = 0; xn = 1;	
	double h = (xn-x0)/(1+n);
	
	for(int i=0;i<n+2; i++)
        	x[i] = x0 + i*h;

	
	for(int i=0;i<n; i++){
		d[i] = -(i+1.)/(i+2.);
        	f[i] = -f1(x[i+1])*pow(h,2);
	}

	clock_t start, finish;
	start = clock();
	
	//FW	
	for(int i = 1; i<n; i++){
		f[i] = f[i] - f[i-1]*d[i-1];
	}
	
	//BW
	v[0] = 0;
	v[n+1] = 0;
	v[n] = f[n-1]*d[n-1];
	for(int i = n-1; i > 0; i--){
		v[i] = (f[i]-v[i+1])*d[i-1];
	}
	finish = clock();

	ofstream outfile;
	stringstream convert;
	convert << n;
	string filename("Ferrari");
	filename.append(convert.str() + ".txt");
	outfile.open(filename.c_str());
    	outfile << n << endl;
    	for(int i=0;i<n+2;i++){
        	outfile << left << setprecision(15) << setw(22) << v[i] << endl;
    	}
    	outfile.close();
	
	delete [] x;
	delete [] d;
	delete [] f;
	delete [] v;	
	return ((finish-start)/((double)CLOCKS_PER_SEC ));	
}

