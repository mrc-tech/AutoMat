#include <iostream>

#include "Matrix/Matrix.hpp"

using namespace std;


int main()
{
	Matrix<int> mat(3,1);
	
	mat(0,0) = 1;
	mat(1,0) = 2;
	mat(2,0) = 3;
	
	vector<int> vec = mat.MatrixToVector();
	
	for(int i=0;i<vec.size();i++) cout << vec[i] << " "; cout << endl;
	
	
	Matrix<int> mat2;
//	mat2.VectorToMatrix(vec);
	mat2 = vec;
	
//	cout << mat2.transpose();
	mat2.transpose().print(cout);
	if(mat2.isVector()) cout << "norma = " << mat2.norm() << endl;
	cout << endl;
	
	
	
	Matrix<double> mat1(3,3);
	
	mat1 = random_Matrix<double>(3,3, 3);
	
//	cout << mat1 << endl;
	mat1.print(cout); cout << endl;
	
	mat1 = {{1,2,3},{4,3,5},{1,2,1}};
//	cout << "matrice:\n" << mat1 << endl;
	cout << "matrice:\n"; mat1.print(cout); cout << endl;
	
	Matrix<double> inverse = mat1.inv();
//	Matrix<double> inverse = inversa(mat1);
	
//	cout << inverse << endl;
	inverse.print(cout); cout << endl;
	
	//list constructor
	Matrix<int> pollo = {{1,2,3},
						 {4,5,6}};
//	cout << pollo << endl;
	pollo.print(cout); cout << endl;
	pollo = identity<int>(3);
	cout << "traccia = " << pollo.tr() << endl;
	cout << endl;
	
	
	cout << "autovalore massimo  = " << max_eigenvalue(mat1,0.000001) << endl;
	cout << "autovalore \"minimo\" = " << nearest_eigenvalue(mat1,0,0.00001) << endl;
	cout << "autovettore associato:" << endl;
//	cout << nearest_eigenvector(mat1,0,0.00001);
	nearest_eigenvector(mat1,0,0.00001).print(cout);
	
	
	
	
	cout << endl;
	pollo = random_Matrix<int>(2,3, 3);
//	cout << pollo;
	pollo.print(cout);
	cout << "Rimuovo la seconda riga:" << endl;
	pollo.remove_row(1); //partendo da zero la seconda riga è quella numerata UNO
//	cout << pollo;
	pollo.print(cout);
	cout << "Rimuovo la prima colonna:" << endl;
	mat = pollo.remove_col(0);
//	cout << pollo;
	pollo.print(cout);
	cout << "Ho rimosso:" << endl;
//	cout << mat;
	mat.print(cout);
	
	
	
	
	
	
	
	
	
	
	
	
	
// BENCHMARK
//	
//	ofstream file;
//	file.open("dati.txt");
//	
//	clock_t t; //conta quanti cicli di clock sono passati
//	
//	for(int i=0;i<500;i++){
//		Matrix<int> mat(i,i,0);
//		mat.random(5);
//		t = clock();
//		cout << i << "x" << i << " \t det= " << mat.det();
//		t = clock() - t;
//		cout << " \t t= " << ((float)t)/CLOCKS_PER_SEC;
//		cout << endl;
//		
//		file << i << "\t" << ((float)t)/CLOCKS_PER_SEC << endl; 
//	}
//	
//	file.close();



	
	return 0;
}
