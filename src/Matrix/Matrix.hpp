/*****************************************************************************************************************
Matrices class
------------------------------------------------------------------------------------------------------------------
Author:  Andrea Marchi - Ph.D student Structural Eng.
Version: v1.0 (28/06/2021)
------------------------------------------------------------------------------------------------------------------
TODO:
	- inserire funzione zero() che azzera tutti i valori (M -= M;)
	- perchè dovrei ritornare il valore sulle funzioni cumulate??
	- funzione interna che fa automaticamente il resize sella memoria...
	- funzioni per inserire vettori e colonne (prendere spunto da MatLab)
	- sistemare la classe in funzione anche di quanto dice SIDRA nel libro dedicato alla risoluzione di PDE con il C++
	- mettere come operatore di accesso [] invece di ()
	- funzioni esterne per fare scalare*Matrice (Matrice*scalare è interno alla classe). Come funzione friend
	- fare il controllo throw_error anche per l'accesso agli elementi della matrice (operator())
	- mi sa che la matrice di matrici non funziona....
	- la funzione che inverte la matrice certe volte fallisce!! (sembra che lo fa random)
	- la funzione "operator <<" funziona male con i templates (indagare meglio come fare)
	- le funzioni più semplici e che devono essere più veloci metterle come "inline"
------------------------------------------------------------------------------------------------------------------
CHANGELOG:
v1.1
	(29/06/2021):
	- separate le funzioni in header files separati
v1.0
	(28/06/2021):
	- creato il file dalla precedente libreria "Matrix.h"
	- uniti i files in un'unico file "Matrix.hpp"
	- cambiati i dati, da un vector bidimensionale ad un'array monodimensionale
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




template <typename T> 
class Matrix
{
	private:
		T * data; // dati della matrice
		unsigned _rows;
		unsigned _cols;
		
	public:
		Matrix(); //inizializza la matrice nulla
		Matrix(unsigned rows); //inizializza un vettore
		Matrix(unsigned rows, unsigned cols); //inizializza la matrice con tutti zeri
		Matrix(unsigned rows, unsigned cols, const T& initial);
		Matrix(const Matrix<T>& rhs); //copy constructor
		Matrix(std::initializer_list<std::initializer_list<T> > set); //initializer_list contructor
		virtual ~Matrix();
		
		// Operator overloading, for "standard" mathematical matrix operations
		Matrix<T>& operator=(const Matrix<T>& rhs);
		
		// Matrix mathematical operations
		Matrix<T> operator + (const Matrix<T>& rhs);
		Matrix<T> operator - (const Matrix<T>& rhs);
		Matrix<T> operator * (const Matrix<T>& rhs);
		Matrix<T> operator ^ (const Matrix<T>& rhs); //prodotto interno (elemento per elemento)
		Matrix<T> operator % (const Matrix<T>& rhs); //prodotto diade (colonna per riga)
		Matrix<T>& operator - (); //operatore di negazione
		Matrix<T>& operator += (const Matrix<T>& rhs);
		Matrix<T>& operator -= (const Matrix<T>& rhs);
		Matrix<T>& operator *= (const Matrix<T>& rhs);
		Matrix<T> transpose(); //calcola la trasposta
		void map(std::function<float(float)> fun); //applica la funzione fun a tutti gli elementi della matrice
		Matrix<T> mmap(std::function<float(float)> fun); //applica il map e ritorna senza modificare l'originale
		T tr(); //return trace of square matrix
		Matrix<T> trace(); //return the diagonal vector of the square matrix
		//funzioni esterne
		double det() const; //calcola il determinante
		Matrix<T> inv(); //calcola l'inversa
//		double max_eigenvalue(double err); //ritorna il massimo autovalore calcolato numericamente
//		double nearest_eigenvalue(double mu,double err); //ritorna il più vicino autovalore calcolato numericamente
//		Matrix<T> nearest_eigenvector(double mu,double err); //ritorna il più vicino autovettore calcolato numericamente
//		Matrix<T> identity(int n); //assegna la matrice identità di dimensione n                MODIFICARE
//		void random(int max); //modifica la matrice in una random con numeri interi compresi tra [0,max]      MODIFICARE
//		void randomf(float min,float max); //modifica la matrice in una random con numeri float compresi tra [min,max]       MODIFICARE
		
		// Matrix/scalar operations
		Matrix<T> operator + (const T& rhs);
		Matrix<T> operator - (const T& rhs);
		Matrix<T> operator * (const T& rhs);
		Matrix<T> operator / (const T& rhs);
		Matrix<T>& operator += (const T& rhs);
		Matrix<T>& operator -= (const T& rhs);
		Matrix<T>& operator *= (const T& rhs);
		Matrix<T>& operator /= (const T& rhs);
		
		// Matrix/vector operations
//		Vector<T> operator*(const Vector<T>& rhs);
//		Vector<T> diag_vec();
		
		// Vector operation
		bool isVector(); //return true if matrix is a column or a row vector
		double norm(); //return the norm of the vector
		
		// Matrix vector conversion
		std::vector<T> MatrixToVector(); //flatten matrix into monodimensional array
		void VectorToMatrix(std::vector<T> vec); //create a column vector Matrix
		Matrix<T>& operator=(const std::vector<T>& rhs); //vectorToMatrix con l'operatore
		
		// Access the individual elements
		inline T& operator()(const unsigned& row, const unsigned& col) { return data[row*_cols + col]; };
		inline const T& operator()(const unsigned& row, const unsigned& col) const { return data[row*_cols + col]; };
		inline T& operator()(const unsigned& row) { return data[row]; }; //accesso per i vettori
		inline const T& operator()(const unsigned& row) const { return data[row]; }; //accesso per i vettori
		
		// Access the row and column sizes
		inline unsigned rows() const{ return _rows; };
		inline unsigned cols() const{ return _cols; };
		
		// Rows/Cols operation
		inline void resize(unsigned row,unsigned col){ data.resize(row); for(unsigned i=0;i<data.size();i++)data[i].resize(col, 0); };
		Matrix<T> remove_row(int index); //rimuove la colonna numero index (numerazione parte da zero)
		Matrix<T> remove_col(int index); //rimuove la riga numero index (ritorna il vettore eliminato)
		Matrix<T> add_row(Matrix<T> row); //aggiunge una riga alla fine della matrice (fine inferiore)
		Matrix<T> add_col(Matrix<T> col); //aggiunge una colonna alla fine della matrice (fine destra)
		
		
		// Print matrix
		friend std::ostream& operator << (std::ostream& stream, const Matrix<double>& rhs); //NON SO PERCHè NON FUNGE QUA (è un problema di templates se non sbaglio...)
};



#include "utils.hpp" //funzionalità aggiuntive
#include "eigen.hpp" //funzioni per gli autovalori e autovettori
//funzioni che usano algoritmi lunghi (e varie alternative)
#include "det.hpp" // per calcolare il determinante
#include "inv.hpp" // per calcolare l'inversa


//FUNZIONI AGGIUNTE

template<typename T>
Matrix<T> operator * (T scalar,Matrix<T> mat) { return mat * scalar; }; //fa il prodotto scalare * Matrice





// ===============================================================================================================

// Parameter Constructor
template<typename T> Matrix<T>::Matrix(unsigned rows, unsigned cols, const T& initial)
{
	_rows = rows;
	_cols = cols;
	data = new T[rows * cols](); //alloca la memoria
}

// Null Constructor
template<typename T> Matrix<T>::Matrix() : Matrix(0,0,0) {} //crea una matrice nulla (se la dimensione è zero vuol dire che non è definita)

// Zero Constructor
template<typename T> Matrix<T>::Matrix(unsigned rows, unsigned cols) : Matrix(rows,cols,0) {}

// Vector Constructor
template<typename T> Matrix<T>::Matrix(unsigned rows) : Matrix(rows,1,0) {}

// List contructor
template<typename T> Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > list)
{
	_rows = list.size(); //numero di righe
	_cols = list.begin()[0].size(); //numero di colonne
	
	data = new T[_rows * _cols](); //alloca la memoria
	
	//assegna i valori
	for(int r=0;r<_rows;r++){
		for(int c=0;c<_cols;c++){
			if(list.begin()[r].size() != _cols) throw std::runtime_error("Matrix::contructor: given list is not a matrix");
			data[r*_cols + c] = list.begin()[r].begin()[c];
		}
	}
}


// Copy Constructor
template<typename T> Matrix<T>::Matrix(const Matrix<T>& rhs)
{
	data = rhs.data;
	_rows = rhs.rows();
	_cols = rhs.cols();
}

// (Virtual) Destructor
template<typename T> Matrix<T>::~Matrix()
{
	if(data) delete [] data;
}

// Assignment Operator
template<typename T> Matrix<T>& Matrix<T>::operator = (const Matrix<T>& rhs)
{
	if (&rhs == this) return *this; //risparmia un po di calcoli
	
	unsigned new_rows = rhs.rows();
	unsigned new_cols = rhs.cols();
	
	data = new T[new_rows * new_cols]();
	
	for (unsigned i=0; i<new_rows; i++) {
		for (unsigned j=0; j<new_cols; j++) {
			data[i*_cols + j] = rhs(i, j);
		}
	}
	_rows = new_rows;
	_cols = new_cols;
	
	return *this;
}

// Addition of two matrices
template<typename T> Matrix<T> Matrix<T>::operator + (const Matrix<T>& rhs)
{
	if(_cols != rhs.cols() || _rows != rhs.rows()) throw std::runtime_error("Matrix::addition: dimensions mismatch");
	
	Matrix result(_rows, _cols);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i][j] + rhs(i,j);
		}
	}
	
	return result;
}

// Cumulative addition of this matrix and another
template<typename T> Matrix<T>& Matrix<T>::operator += (const Matrix<T>& rhs)
{
	*this = *this + rhs;
	return *this; //perchè dovrei ritornare il valore???????????????????????????
}

// Subtraction of this matrix and another
template<typename T> Matrix<T> Matrix<T>::operator - (const Matrix<T>& rhs)
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

// Cumulative subtraction of this matrix and another
template<typename T> Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& rhs)
{
	*this = *this - rhs;
	return *this;
}

// Left multiplication of this matrix and another 
//vale anche per i vettori [M * v] (vettori sono matrici con una sola colonna)
template<typename T> Matrix<T> Matrix<T>::operator * (const Matrix<T>& rhs)
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

// Cumulative left multiplication of this matrix and another
template<typename T> Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& rhs)
{
	*this = *this * rhs;
	return *this;
}

// Element wise of this matrix and another (prodotto interno) [devono avere le stesse dimensioni]
template<typename T> Matrix<T> Matrix<T>::operator ^ (const Matrix<T>& rhs)
{
	if(cols() != rhs.cols() || rows() != rhs.rows()) throw std::runtime_error("Matrix::multiplication::operator^: dimensions mismatch");
	unsigned _rows = rows();
	unsigned _cols = cols();
	Matrix result(_rows, _cols);
		
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
 			result(i,j) += this->data[i][j] * rhs(i,j);
		}
	}
	
	return result;
}

// Prodotto diade tra due vettori da una matrice (vettore colonna per vettore riga)
template<typename T> Matrix<T> Matrix<T>::operator % (const Matrix<T>& rhs)
{
	if(cols() != 1 || rhs.rows() != 1) throw std::runtime_error("Matrix::multiplication::diadic: input is not vector");
	
	unsigned _rows = rows();
	unsigned _cols = rhs.cols();
	Matrix result(_rows, _cols);
		
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
 			result(i,j) += this->data[i][0] * rhs(0,j);
		}
	}
	
	return result;
}

// Calculate a transpose of this matrix
template<typename T> Matrix<T> Matrix<T>::transpose()
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

// Matrix/scalar addition
template<typename T> Matrix<T> Matrix<T>::operator + (const T& rhs)
{
 	Matrix result(_rows, _cols);
	
	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i][j] + rhs;
 		}
	}
	
	return result;
}

// Matrix/scalar subtraction
template<typename T> Matrix<T> Matrix<T>::operator - (const T& rhs)
{
	Matrix result(_rows, _cols);
	
 	for (unsigned i=0; i<_rows; i++) {
		for (unsigned j=0; j<_cols; j++) {
			result(i,j) = this->data[i][j] - rhs;
		}
	}
	
	return result;
}

// Operatore di Negazione
template<typename T> Matrix<T>& Matrix<T>::operator - ()
{
	for(unsigned r=0;r<_rows;r++){
		for(unsigned c=0;c<_cols;c++){
			this->data[r][c] = - this->data[r][c];
		}
	}
	return *this;
}

// Matrix/scalar multiplication
template<typename T> Matrix<T> Matrix<T>::operator*(const T& rhs)
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
template<typename T> Matrix<T> Matrix<T>::operator / (const T& rhs)
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
template<typename T> Matrix<T>& Matrix<T>::operator += (const T& rhs)
{
	*this = *this + rhs;
	return *this;
}

// Cumulative Matrix/scalar subtraction
template<typename T> Matrix<T>& Matrix<T>::operator -= (const T& rhs)
{
 	*this = *this - rhs;
	return *this;
}

// Cumulative Matrix/scalar multiplication
template<typename T> Matrix<T>& Matrix<T>::operator *= (const T& rhs)
{
	*this = *this * rhs;
	return *this;
}

// Cumulative Matrix/scalar division
template<typename T> Matrix<T>& Matrix<T>::operator /= (const T& rhs)
{
	*this = *this / rhs;
	return *this;
}

// Flatten Matrix into a monodimensional vector
template<typename T> std::vector<T> Matrix<T>::MatrixToVector() //METTERLO IN UN HEADER SEPARATO "Matrix_utils.h"
{
	std::vector<T> res;
	
	for(int r=0;r<_rows;r++){
		for(int c=0;c<_cols;c++){
			res.push_back(data[r*_cols + c]);
		}
	}
	
	return res;
}

// Create a column vector Matrix
template<typename T> void Matrix<T>::VectorToMatrix(std::vector<T> vec) //METTERLO IN UN HEADER SEPARATO "Matrix_utils.h"
{
	Matrix<T> temp(vec.size(),1);
	
	for(int i=0;i<vec.size();i++){
		temp(i,0) = vec[i];
	}
	
	*this = temp; //da ottimizzare meglio...
}

template<typename T> Matrix<T>& Matrix<T>::operator = (const std::vector<T>& rhs)
{
	//questa routine viene usata anche prima quindi la potrei mettere in una funzione private
	_rows = rhs.size();
	_cols = 1;
	data = new T[_rows]();
	for (unsigned i=0; i<rhs.size(); i++) { 
		data[i] = rhs[i];
	}
	
	return *this;
}

template<typename T> bool Matrix<T>::isVector()
{
	if(_rows == 1 || _cols == 1) return true; else return false;
}

template<typename T> double Matrix<T>::norm()
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
template<typename T> T Matrix<T>::tr()
{
	if(_rows != _cols) throw std::runtime_error("Matrix::trace: matrix is not square");
	
	T res = 0;
	
	for(int i=0;i<_rows;i++) res += data[i*_cols + i];
	
	return res;
}

// Return diagonal vector of square matrix (sarebbe meglio chiamarlo diag_vec() ?)
template<typename T> Matrix<T> Matrix<T>::trace()
{
	if(_rows != _cols) throw std::runtime_error("Matrix::trace: matrix is not square");
	
	Matrix<T> res(_rows,1);
	
	for(int i=0;i<_rows;i++) res(i,0) = data[i][i];
	
	return res;
}


// Remove a Row
template<typename T> Matrix<T> Matrix<T>::remove_row(int index) //METTERLO IN UN HEADER SEPARATO "Matrix_utils.h"
{
	//ritorna il vettore riga eliminato
	Matrix<T> res(1,_cols);
	
	for(int i=0;i<_cols;i++) res(0,i) = data[index*_cols + i];
	
	//matrice su cio copia i dati nuovi
	Matrix<T> temp(_rows-1,_cols);
	//copia i dati senza la riga index
	for(int r=0;r<index;r++){
		for(int c=0;c<_cols;c++){
			temp(r,c) = data[r*_cols + c];
		}
	}
	for(int r=index+1;r<_rows;r++){
		for(int c=0;c<_cols;c++){
			temp(r-1,c) = data[r*_cols + c];
		}
	}
	//assegna alla matrice attuale la matrice temp
	*this = temp;
	
	return res;
}

// Remove a Column
template<typename T> Matrix<T> Matrix<T>::remove_col(int index) //METTERLO IN UN HEADER SEPARATO "Matrix_utils.h"
{
	//ritorna il vettore colonna eliminato
	Matrix<T> res(_rows,1);
	
	for(int i=0;i<_rows;i++) res(i,0) = data[i*_cols + index];
	
	//matrice su cio copia i dati nuovi
	Matrix<T> temp(_rows,_cols-1);
	//copia i dati senza la colonna index
	for(int r=0;r<_rows;r++){
		for(int c=0;c<index;c++){
			temp(r,c) = data[r*_cols + c];
		}
	}
	for(int r=0;r<_rows;r++){
		for(int c=index+1;c<_cols;c++){
			temp(r,c-1) = data[r*_cols + c];
		}
	}
	//assegna alla matrice attuale la matrice temp
	*this = temp;
	
	return res;
}

// Insert a Row
template<typename T> Matrix<T> Matrix<T>::add_row(Matrix<T> row) //METTERLO IN UN HEADER SEPARATO "Matrix_utils.h"
{
	//controlla se la riga da inserire ha la dimensione corretta
	if(row.cols() != _cols) throw std::runtime_error("Matrix::add_row: row to insert has different dimension");
	//non controlla se la matrice row è effettivamente un vettore riga perchè comunque inserisce solo la prima riga
	
	Matrix<T> res(_rows+1,_cols); //matrice con una riga in più
	for(int r=0;r<_rows;r++){
		for(int c=0;c<_cols;c++){
			res(r,c) = data[r][c];
		}
	}
	//metto dentro la riga aggiuntiva
	for(int i=0;i<_cols;i++) res(_rows,i) = row(0,i);
	
	*this = res;
	
	return res;
}

template<typename T> std::ostream& operator<<(std::ostream& stream,const Matrix<T>& rhs)
{
	for(int r=0;r<rhs.rows();r++){
//		stream << "|";
		for(int c=0;c<rhs.cols()-1;c++){
			stream << rhs(r,c) << "  ";
		}
//		stream << rhs(r,rhs.cols()-1) << "|" << std::endl;
		stream << rhs(r,rhs.cols()-1) << std::endl;
	}
	return stream;
}

//template<typename T>
//void Matrix<T>::print(std::ostream& stream)
//{
//	for(int r=0;r<_rows;r++){
//		for(int c=0;c<_cols-1;c++){
//			stream << data[r*_cols + c] << " ";
//		}
//		stream << data[r*_cols + _cols-1] << std::endl;
//	}
//}

template<typename T> void Matrix<T>::map(std::function<float(float)> fun)
{
	for(int r=0;r<_rows;r++){
		for(int c=0;c<_cols;c++){
			data[r*_cols + c] = fun(data[r*_cols + c]);
		}
	}
}

//mappa e ritorna senza modificare
template<typename T> Matrix<T> Matrix<T>::mmap(std::function<float(float)> fun)
{
	Matrix<T> result(_rows,_cols);
	result.map(fun);
	
	return result;
}

// Calcola il determinante
template<typename T> double Matrix<T>::det() const
{
	return determinante(*this);
}

// Calcola la matrice inversa
template<typename T> Matrix<T> Matrix<T>::inv()
{
	return inversa(*this);
}






#endif
