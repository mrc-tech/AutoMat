/*****************************************************************************************************************

*****************************************************************************************************************/
#ifndef MRC_MATRIX_H
#define MRC_MATRIX_H

#ifndef _GLIBCXX_IOSTREAM
#include <iostream> //per stampare le matrici
#endif
#include <functional> //per passare le funzioni (membro map)
#include <vector>

#include <cmath> //per pow(,);
#include <exception> //per gestire gli errori

#include "vec128f.h"



class Matrix
{
	private:
		vec128f * data; // dati della matrice
		unsigned _rows;
		unsigned _cols;
		
	public:
		Matrix(); //inizializza la matrice nulla
		Matrix(unsigned rows); //inizializza un vettore
		Matrix(unsigned rows, unsigned cols); //inizializza la matrice con tutti zeri
		Matrix(unsigned rows, unsigned cols, const float& initial);
		Matrix(const Matrix& rhs); //copy constructor
		Matrix(std::initializer_list<std::initializer_list<float> > set); //initializer_list contructor
		virtual ~Matrix();
		
		// Operator overloading, for "standard" mathematical matrix operations
		const Matrix& operator = (const Matrix& rhs);
		
		// Matrix mathematical operations
		Matrix operator + (const Matrix& rhs);
		Matrix operator - (const Matrix& rhs);
		Matrix operator * (const Matrix& rhs);
		Matrix operator ^ (const Matrix& rhs); //prodotto interno (elemento per elemento)
		Matrix operator % (const Matrix& rhs); //prodotto diade (colonna per riga)
		Matrix& operator - (); //operatore di negazione
		Matrix& operator += (const Matrix& rhs);
		Matrix& operator -= (const Matrix& rhs);
		Matrix& operator *= (const Matrix& rhs);
		Matrix transpose(); //calcola la trasposta
		void map(std::function<float(float)> fun); //applica la funzione fun a tutti gli elementi della matrice
		Matrix mmap(std::function<float(float)> fun); //applica il map e ritorna senza modificare l'originale
		float tr(); //return trace of square matrix
		Matrix trace(); //return the diagonal vector of the square matrix
		//funzioni esterne
		float det(); //calcola il determinante
		Matrix inv(); //calcola l'inversa
		
		// Matrix/scalar operations
		Matrix operator + (const float& rhs);
		Matrix operator - (const float& rhs);
		Matrix operator * (const float& rhs);
		Matrix operator / (const float& rhs);
		Matrix& operator += (const float& rhs);
		Matrix& operator -= (const float& rhs);
		Matrix& operator *= (const float& rhs);
		Matrix& operator /= (const float& rhs);
		
		// Matrix/vector operations
//		Vector<T> operator*(const Vector<T>& rhs);
//		Vector<T> diag_vec();
		
		// Vector operation
		bool isVector(); //return true if matrix is a column or a row vector
		float norm(); //return the norm of the vector
		
		// Matrix vector conversion
		std::vector<float> MatrixToVector(); //flatten matrix into monodimensional array
		void VectorToMatrix(std::vector<float> vec); //create a column vector Matrix
		const Matrix& operator = (const std::vector<float>& rhs); //vectorToMatrix con l'operatore
		
		// Access the individual elements
		inline float& operator()(const unsigned& row, const unsigned& col) { return data[row*_cols + col]; };
		inline const float& operator()(const unsigned& row, const unsigned& col) const { return data[row*_cols + col]; };
		inline float& operator()(const unsigned& row) { return data[row]; }; //accesso per i vettori
		inline const float& operator()(const unsigned& row) const { return data[row]; }; //accesso per i vettori
		
		// Access the row and column sizes
		inline unsigned rows() const{ return _rows; };
		inline unsigned cols() const{ return _cols; };
		
		// Print matrix
		void print(std::ostream&);
//		friend std::ostream& operator << (std::ostream& stream, const Matrix<T>& rhs); //NON SO PERCHè NON FUNGE QUA (è un problema di templates se non sbaglio...)
};



//#include "utils.hpp" //funzionalità aggiuntive
//#include "eigen.hpp" //funzioni per gli autovalori e autovettori
////funzioni che usano algoritmi lunghi (e varie alternative)
//#include "det.hpp" // per calcolare il determinante
//#include "inv.hpp" // per calcolare l'inversa


//FUNZIONI AGGIUNTE
Matrix operator * (float scalar, Matrix mat) { return mat * scalar; }; //fa il prodotto scalare * Matrice





// ===============================================================================================================

// Parameter Constructor
Matrix::Matrix(unsigned rows, unsigned cols, const float& initial)
{
	_rows = rows;
	_cols = cols;
	data = new vec128f[(rows * cols)/NVARS]; //alloca la memoria dinamicamente
}

// Null Constructor
Matrix::Matrix() : Matrix(0,0,0) {} //crea una matrice nulla (se la dimensione è zero vuol dire che non è definita)

// Zero Constructor
Matrix::Matrix(unsigned rows, unsigned cols) : Matrix(rows,cols,0) {}

// Vector Constructor
Matrix::Matrix(unsigned rows) : Matrix(rows,1,0) {}

// List contructor
Matrix::Matrix(std::initializer_list<std::initializer_list<float> > list)
{
	_rows = list.size(); //numero di righe
	_cols = list.begin()[0].size(); //numero di colonne
	
	data = new vec128f[_rows * _cols]; //alloca la memoria dinamicamente
	
	//assegna i valori
	for(int r=0;r<_rows;r++){
		for(int c=0;c<_cols;c++){
			if(list.begin()[r].size() != _cols) throw std::runtime_error("Matrix::contructor: given list is not a matrix");
			data[r*_cols + c] = list.begin()[r].begin()[c];
		}
	}
}


// Copy Constructor
Matrix::Matrix(const Matrix& rhs)
	: _rows(rhs.rows()), _cols(rhs.cols()), data(new vec128f[(rhs.rows()*rhs.cols())/NVARS])
{
	for(int i=0;i<_rows;i++)
		for(int j=0;j<_cols;j++)
			data[i*_cols+j] = rhs(i,j);
}

// (Virtual) Destructor
Matrix::~Matrix()
{
	if(data) delete [] data;
}


// Assignment Operator
const Matrix& Matrix::operator = (const Matrix& rhs)
{
	if (&rhs == this) return *this; //risparmia un po di calcoli
	
	unsigned new_rows = rhs.rows();
	unsigned new_cols = rhs.cols();
	
	if(data) delete [] data; //cancella i vecchi dati della matrice (se presenti)
	data = new float[new_rows * new_cols]; //alloca dinamicamente lo spazio per i nuovi dati
	
	for (unsigned i=0; i<new_rows; i++)
		for (unsigned j=0; j<new_cols; j++)
			data[i*_cols + j] = rhs(i, j);
	
	_rows = new_rows;
	_cols = new_cols;
	
	return *this; //ritorna la reference a &Matrix<T>, in maniera tale da permettere uguaglianze concatenate (A = B = C)
}


// Addition of two matrices
Matrix Matrix::operator + (const Matrix& rhs)
{
	if(_cols != rhs.cols() || _rows != rhs.rows()) throw std::runtime_error("Matrix::addition: dimensions mismatch");
	
	Matrix result(_rows, _cols);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i*_cols + j] + rhs(i,j);
		}
	}
	
	return result;
}

// Subtraction of this matrix and another
Matrix Matrix::operator - (const Matrix& rhs)
{
	if(cols() != rhs.cols() || rows() != rhs.rows()) throw std::runtime_error("Matrix::subtraction: dimensions mismatch");
	
	unsigned _rows = rhs.rows();
	unsigned _cols = rhs.cols();
	Matrix result(_rows, _cols);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i*_cols + j] - rhs(i,j);
		}
	}
	
	//per risparmiare spazio potrei fare:
	//result = *this + (-1 * rhs);
	//usando le operazioni di moltiplicazione per uno scalare... ma poi non potrei usare i template...
	
	return result;
}

// Left multiplication of this matrix and another 
//vale anche per i vettori [M * v] (vettori sono matrici con una sola colonna)
Matrix Matrix::operator * (const Matrix& rhs)
{
	if(_cols != rhs.rows()) throw std::runtime_error("Matrix::multiplication: dimensions mismatch");
	
	unsigned _rows = rows();
	unsigned _cols = rhs.cols();
	Matrix result(_rows, _cols);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			for (unsigned k=0; k<cols(); k++) {
 				result(i,j) += this->data[i*_cols + k] * rhs(k,j);
			}
		}
	}
	
	return result;
}

// Element wise of this matrix and another (prodotto interno) [devono avere le stesse dimensioni]
Matrix Matrix::operator ^ (const Matrix& rhs)
{
	if(cols() != rhs.cols() || rows() != rhs.rows()) throw std::runtime_error("Matrix::multiplication::operator^: dimensions mismatch");
	unsigned _rows = rows();
	unsigned _cols = cols();
	Matrix result(_rows, _cols);
		
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
 			result(i,j) += this->data[i*_cols + j] * rhs(i,j);
		}
	}
	
	return result;
}

// Prodotto diade tra due vettori da una matrice (vettore colonna per vettore riga)
Matrix Matrix::operator % (const Matrix& rhs)
{
	if(cols() != 1 || rhs.rows() != 1) throw std::runtime_error("Matrix::multiplication::diadic: input is not vector");
	
	unsigned _rows = rows();
	unsigned _cols = rhs.cols();
	Matrix result(_rows, _cols);
		
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
 			result(i,j) += this->data[i] * rhs(0,j);
		}
	}
	
	return result;
}

// Cumulative addition of this matrix and another
Matrix& Matrix::operator += (const Matrix& rhs)
{
	*this = *this + rhs;
	return *this; //perchè dovrei ritornare il valore???????????????????????????
}

// Cumulative subtraction of this matrix and another
Matrix& Matrix::operator -= (const Matrix& rhs)
{
	*this = *this - rhs;
	return *this; //perchè dovrei ritornare il valore???????????????????????????
}

// Cumulative left multiplication of this matrix and another
Matrix& Matrix::operator *= (const Matrix& rhs)
{
	*this = *this * rhs;
	return *this; //perchè dovrei ritornare il valore???????????????????????????
}

// Matrix/scalar addition
Matrix Matrix::operator + (const float& rhs)
{
 	Matrix result(_rows, _cols);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i*_cols + j] + rhs;
 		}
	}
	
	return result;
}

// Matrix/scalar subtraction
Matrix Matrix::operator - (const float& rhs)
{
	Matrix result(_rows, _cols);
	
 	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i*_cols + j] - rhs;
		}
	}
	
	return result;
}

// Operatore di Negazione
Matrix& Matrix::operator - ()
{
	for(unsigned r=0;r<_rows;r++){
		for(unsigned c=0;c<_cols;c++){
			this->data[r*_cols + c] = - this->data[r*_cols + c];
		}
	}
	return *this;
}

// Matrix/scalar multiplication
Matrix Matrix::operator * (const float& rhs)
{
	Matrix result(_rows, _cols);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i*_cols + j] * rhs;
		}
	}
	
	return result;
}

// Matrix/scalar division
Matrix Matrix::operator / (const float& rhs)
{
	Matrix result(_rows, _cols);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i*_cols + j] / rhs;
		}
	}
	
	return result;
}

// cumulative Matrix/scalar addition
Matrix& Matrix::operator += (const float& rhs)
{
	*this = *this + rhs;
	return *this;
}

// Cumulative Matrix/scalar subtraction
Matrix& Matrix::operator -= (const float& rhs)
{
 	*this = *this - rhs;
	return *this;
}

// Cumulative Matrix/scalar multiplication
Matrix& Matrix::operator *= (const float& rhs)
{
	*this = *this * rhs;
	return *this;
}

// Cumulative Matrix/scalar division
Matrix& Matrix::operator /= (const float& rhs)
{
	*this = *this / rhs;
	return *this;
}


// Calculate a transpose of this matrix
Matrix Matrix::transpose()
{
	Matrix result(_cols, _rows);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(j,i) = this->data[i*_cols + j];
		}
	}
	
	//*this = result; //cambia la matrice stessa!!
	
	return result;
}

// Flatten Matrix into a monodimensional vector
std::vector<float> Matrix::MatrixToVector() //METTERLO IN UN HEADER SEPARATO "Matrix_utils.h"
{
	std::vector<float> res;
	
	for(int r=0;r<_rows;r++){
		for(int c=0;c<_cols;c++){
			res.push_back(data[r*_cols + c]);
		}
	}
	
	return res;
}

// Create a column vector Matrix
void Matrix::VectorToMatrix(std::vector<float> vec) //METTERLO IN UN HEADER SEPARATO "Matrix_utils.h"
{
	Matrix temp(vec.size(),1);
	
	for(int i=0;i<vec.size();i++){
		temp(i,0) = vec[i];
	}
	
	*this = temp; //da ottimizzare meglio...
}

const Matrix& Matrix::operator = (const std::vector<float>& rhs)
{
	//questa routine viene usata anche prima quindi la potrei mettere in una funzione private
	_rows = rhs.size();
	_cols = 1;
	if(data) delete [] data; //cancella i vecchi dati
	data = new float[_rows]; //alloca la memoria per i nuovi dati
	for (unsigned i=0; i<rhs.size(); i++) { 
		data[i] = rhs[i];
	}
	
	return *this;
}

bool Matrix::isVector()
{
	if(_rows == 1 || _cols == 1) return true; else return false;
}

double Matrix<T>::norm()
{
	double res = 0;
	
	if(_cols == 1){
		//column vector
		for(int i=0;i<_rows;i++) res += data[i*_cols] * data[i*_cols];
		return sqrt(res);
	} else if(_rows == 1){
		//row vector
		for(int i=0;i<_cols;i++) res += data[i] * data[i];
		return sqrt(res);
	} else {
		// non è un vettore
		//protrei implementare delle norme matriciali, ritornare -1 non è una mossa furba...
		return -1;
	}
}

//return trace of matrix
float Matrix::tr()
{
	if(_rows != _cols) throw std::runtime_error("Matrix::trace: matrix is not square");
	
	T res = 0;
	
	for(int i=0;i<_rows;i++) res += data[i*_cols + i];
	
	return res;
}

// Return diagonal vector of square matrix (sarebbe meglio chiamarlo diag_vec() ?)
//Matrix Matrix::trace()
//{
//	if(_rows != _cols) throw std::runtime_error("Matrix::trace: matrix is not square");
//	
//	Matrix res(_rows,1);
//	
//	for(int i=0;i<_rows;i++) res(i,0) = data[i][i];
//	
//	return res;
//}


template<typename T>
void Matrix<T>::print(std::ostream& stream)
{
	for(int r=0;r<_rows;r++){
		for(int c=0;c<_cols-1;c++){
			stream << data[r*_cols + c] << " ";
		}
		stream << data[r*_cols + _cols-1] << std::endl;
	}
}

//template<typename T> std::ostream& operator<<(std::ostream& stream,const Matrix<T>& rhs)
//{
//	for(int r=0;r<rhs.rows();r++){
////		stream << "|";
//		for(int c=0;c<rhs.cols()-1;c++){
//			stream << rhs(r,c) << "  ";
//		}
////		stream << rhs(r,rhs.cols()-1) << "|" << std::endl;
//		stream << rhs(r,rhs.cols()-1) << std::endl;
//	}
//	return stream;
//}

void Matrix::map(std::function<float(float)> fun)
{
	for(int r=0;r<_rows;r++){
		for(int c=0;c<_cols;c++){
			data[r*_cols + c] = fun(data[r*_cols + c]);
		}
	}
}

//mappa e ritorna senza modificare
Matrix Matrix::mmap(std::function<float(float)> fun)
{
	Matrix result(_rows,_cols);
	result.map(fun);
	
	return result;
}

// Calcola il determinante
float Matrix<T>::det()
{
//	return determinante(*this);
}

// Calcola la matrice inversa
Matrix Matrix::inv()
{
//	return inversa(*this);
}






#endif
