#ifndef MATRIX_H
#define MATRIX_H

double rand_norm(double max);

class matrix
{
    public:
        matrix();
        matrix(int n);
        matrix(int n,int m);
        matrix(const matrix&  arg);
        int getRows();
        int getColumns();
        matrix getColumn(int n);
        matrix getRow(int n);
        void print();
        void setDimensions(int n, int m);
        void t();
        matrix T();
        matrix randu();
        matrix zeros();
        double norm(int column);
        friend matrix operator+(const matrix& lhs, const matrix& rhs);
        friend matrix operator-(const matrix& lhs, const matrix& rhs);
        friend matrix operator*(const matrix& lhs, const matrix& rhs);
        friend matrix operator*(const double& lhs, const matrix& rhs);
        friend matrix operator*(const matrix& lhs, const double& rhs);
        friend matrix operator/(const double& lhs, const matrix& rhs);
        friend matrix operator/(const matrix& lhs, const double& rhs);
        void operator=(const matrix& rhs);
        double& operator()(int i, int j);
        matrix operator[](int i);
        ~matrix();
    private:
        int rows;
        int columns;
        double ** ptr;
};


#endif // MATRIX_H
