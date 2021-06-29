#include <cstdlib> //per rand();
#include <time.h> //per time(0);


//assegna la matrice identità
template<typename T> Matrix<T> identity(unsigned int n)
{
	Matrix<T> mat(n,n,0);
	for(int i=0;i<n;i++) mat(i,i) = 1;
	return mat;
}

// Calcola la matrice random
template<typename T> Matrix<T> random_Matrix(int rows,int cols, int max)
{
	Matrix<T> mat(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			mat(i,j) = rand() % max;
		}
	}
	return mat;
}

// Calcola la matrice random con numeri a vigola mobile compresi tra min e max
template<typename T> Matrix<T> randomf_Matrix(int rows,int cols, float min,float max)
{
	Matrix<T> mat(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			mat(i,j) = ((float)rand()/RAND_MAX)*(max-min) + min;
		}
	}
	return mat;
}
