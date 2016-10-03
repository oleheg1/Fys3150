#include <iostream>
#include <matrix.h>
#include <iomanip>
#include <cmath>
double rand_norm(double max);
using namespace std;

matrix::matrix(){
    ptr = NULL;
}
matrix::matrix(const matrix& arg){
    rows = arg.rows;
    columns = arg.columns;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            ptr[i][j] = arg.ptr[i][j];
        }
    }
}

matrix::matrix(int n){
    rows = n;
    columns = n;
    ptr = new double *[n];
    for(int i=0;i<n;i++){
        ptr[i] = new double[n];
    }
}

matrix::matrix(int n, int m){
    rows = n;
    columns = m;
    ptr = new double *[n];
    for(int i=0;i<n;i++){
        ptr[i] = new double[m];
    }
}

matrix::~matrix(){
    for(int i=0;i<rows;i++){
        delete ptr[i];
    }
    delete [] ptr;
}

double& matrix::operator ()(int i, int j){
    return ptr[i][j];
}

matrix matrix::operator[](int i){
    matrix temp(1,rows);
    for(int k=0;k<rows;k++){
        temp.ptr[k][0] = ptr[k][i];
    }

    return temp;
}

matrix operator +(const matrix& lhs, const matrix& rhs){
    if(lhs.rows != rhs.rows || lhs.columns != rhs.columns){
        cout << "lhs.rows = " << lhs.rows << "     " << "rhs.rows = " << rhs.rows << endl;
        cout << "lhs.columns = " << lhs.columns << "     " << "rhs.columns = " << rhs.columns << endl;
        cout << "Matrix dimensions for addition are wrong, exit(1)." << endl;
        exit(1);
    }
    matrix temp(lhs.rows,lhs.columns);
    for(int i=0;i<lhs.rows;i++){
        for(int j=0; j<lhs.columns;j++){
            temp.ptr[i][j] = lhs.ptr[i][j] + rhs.ptr[i][j];
        }
    }

    return temp;
}

matrix operator -(const matrix& lhs, const matrix& rhs){
    if(lhs.rows != rhs.rows || lhs.columns != rhs.columns){
        cout << "lhs.rows = " << lhs.rows << "     " << "rhs.rows = " << rhs.rows << endl;
        cout << "lhs.columns = " << lhs.columns << "     " << "rhs.columns = " << rhs.columns << endl;
        cout << "Matrix dimensions for subtraction are wrong, exit(1)." << endl;
        exit(1);
    }
    matrix temp(lhs.rows,lhs.columns);
    for(int i=0;i<lhs.rows;i++){
        for(int j=0; j<lhs.columns;j++){
            temp.ptr[i][j] = lhs.ptr[i][j] - rhs.ptr[i][j];
        }
    }

    return temp;
}

void matrix::print(){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            cout << setw(15) << ptr[i][j];
        }
    cout << endl;
    }
}


void matrix::operator =(const matrix& rhs){
    rows = rhs.rows;
    columns = rhs.columns;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            ptr[i][j] = rhs.ptr[i][j];
        }
    }
}

void matrix::setDimensions(int n, int m){
    rows = n;
    columns = m;
    ptr = new double *[n];
    for(int i=0;i<n;i++){
        ptr[i] = new double[m];
    }
}

matrix matrix::T(){

    matrix temp(this->columns, this->rows);
    for(int i=0;i<this->columns;i++){
        for(int j=0;j<this->rows;j++){
        temp.ptr[i][j] = this->ptr[j][i];
        }
    }
    return temp;
}

void matrix::t(){


    double ** temp;
    temp = new double * [columns];
    for(int i=0;i<columns;i++)
        temp[i] = new double [rows];
    for(int i=0;i<columns;i++){
        for(int j=0;j<rows;j++){
        temp[i][j] = ptr[j][i];
        }
    }


   for(int i=0;i<rows;i++){
        delete ptr[i];
    }
    delete [] ptr;

    int placeholder;
    placeholder = columns;
    columns = rows;
    rows = placeholder;

    ptr = new double *[rows];
    for(int i=0;i<rows;i++)
        ptr[i] = new double [columns];

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
        ptr[i][j] = temp[i][j];
        }
    }


    for(int i=0;i<rows;i++){
        delete temp[i];
    }
    delete [] temp;



    return;
}

matrix operator *(const matrix& lhs, const matrix& rhs){
    if(lhs.columns != rhs.rows){
        cout << "lhs.rows = " << lhs.rows << "     " << "rhs.rows = " << rhs.rows << endl;
        cout << "lhs.columns = " << lhs.columns << "     " << "rhs.columns = " << rhs.columns << endl;
        cout << "Matrix dimensions are wrong for multiplication, exit(1)." << endl;
        exit(1);
    }
    matrix temp(lhs.rows,rhs.columns);

    for(int i=0;i<lhs.rows;i++){
        for(int j=0;j<rhs.columns;j++){
            double sum = 0.0;
            for(int v=0;v<lhs.columns;v++){
                sum += lhs.ptr[i][v] * rhs.ptr[v][j];
            }
            temp.ptr[i][j] = sum;

        }
    }
    return temp;
}

matrix operator *(const double& lhs, const matrix& rhs){
    matrix temp(rhs.rows,rhs.columns);
    for(int i=0;i<rhs.rows;i++){
        for(int j=0;j<rhs.columns;j++){
            temp.ptr[i][j] = rhs.ptr[i][j]*lhs;
        }
    }
    return temp;
}
matrix operator *(const matrix& lhs, const double& rhs){
    matrix temp(lhs.rows,lhs.columns);
    for(int i=0;i<lhs.rows;i++){
        for(int j=0;j<lhs.columns;j++){
            temp.ptr[i][j] = lhs.ptr[i][j]*rhs;
        }
    }
    return temp;
}

matrix operator /(const double& lhs, const matrix& rhs){
    matrix temp(rhs.rows,rhs.columns);
    for(int i=0;i<rhs.rows;i++){
        for(int j=0;j<rhs.columns;j++){
            temp.ptr[i][j] = rhs.ptr[i][j]/lhs;
        }
    }
    return temp;
}
matrix operator /(const matrix& lhs, const double& rhs){
    matrix temp(lhs.rows,lhs.columns);
    for(int i=0;i<lhs.rows;i++){
        for(int j=0;j<lhs.columns;j++){
            temp.ptr[i][j] = lhs.ptr[i][j]/rhs;
        }
    }
    return temp;
}

int matrix::getRows(){
    return rows;
}

int matrix::getColumns(){
    return columns;
}

matrix matrix::randu(){
    matrix temp(rows, columns);
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            temp.ptr[i][j] = rand_norm(1.0);
            ptr[i][j] = temp.ptr[i][j];
        }
    }
    return temp;
}

matrix matrix::getColumn(int n){
    matrix temp(rows, 1);
    for(int i=0;i<rows;i++){
        temp.ptr[i][0]= ptr[i][n];
    }
    return temp;
}

matrix matrix::getRow(int n){
    matrix temp(n, columns);
    for(int i=0;i<rows;i++){
         temp.ptr[0][i]= ptr[n][i];
    }
        return temp;
}

matrix matrix::zeros(){
     matrix temp(rows, columns);
     for(int i=0;i<rows;i++){
         for(int j=0;j<columns;j++){
             temp.ptr[i][j] = 0.0;
             ptr[i][j] = 0.0;
         }
     }
     return temp;
}

double matrix::norm(int column){
    double sum = 0.0;
    for(int i=0;i<rows;i++){
        sum += ptr[i][column]*ptr[i][column];
    }
    return sqrt(sum);
}

double rand_norm(double max){  // Generates random numbers between [-1,1] or [-max,max]
    double a = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double b = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double s = max * static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    const double pi = 3.1415926535897;
    double z  = s*sqrt(-2*log(a))*cos(2*pi*b);
    return z;
}

