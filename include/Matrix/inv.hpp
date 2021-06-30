// Calcola la matrice inversa
template<typename T> Matrix<T> inversa(const Matrix<T>& mat)
{
	int n = mat.rows(); //la datarice è quadrata
	//Matrix<double> m = data; //matrice temporanea
	T piv; //pivot
	T temp; //variabile temporanea per lo scambio
	T d; //variabile temporanea per il determinante
	
	//controlla se la matrice è quadrata
	if(mat.rows() != mat.cols()) throw std::runtime_error("Matrix::inverse: matrix is not square");
	
	//accrocco perchè non c'è il casting nella classe
	Matrix<T> m(n,n);
	Matrix<T> in(n,n,0); //matrice che da identità diventa inversa dopo la riduzione di Gauss
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) m(i,j) = mat(i,j);
	for(int i=0;i<n;i++) in(i,i) = 1; //inizialmente è la matrice identità
	
	// triangolarizza la matrice
	for(int i=0;i<n-1;i++){
//std::cout << "i=" << i << " n=" << n << std::endl;
		if(m(i,i) == 0){
			//cerca un valore massimo non nullo
//std::cout << "debug::inv::triangolazione: Ha trovato un elemento di pivon nullo" << std::endl;
			int k = i;
			while(k<n && m(k,i)==0) k++;
			//scambia le righe i e k
			for(int x=0;x<n;x++){
				temp = m(i,x);
				m(i,x) = m(k,x);
				m(k,x) = temp;
				//tutto cio che succede alla matrice di sinistra succede anche alla matrice di destra
				temp = in(i,x);
				in(i,x) = in(k,x);
				in(k,x) = temp;
			}
			if(m(i,i) == 0){
				//la matrice non deve essere singolare per fare l'inversa
				throw std::runtime_error("Matrix:inverse: matrix is singular");
				return Matrix<T>(0,0);
			}
		}
		//calcola i pivot per eliminare le componenti	
		for(int j=i+1;j<n;j++){
//std::cout << "pollo" << std::endl;
			if(m(j,i) != 0){
				piv = m(j,i) / m(i,i);
				for(int k=0;k<n;k++){
					//somma per i pivot
//std::cout << "debug::inv::triangolazione: " << i << " " << j << " " << k << std::endl;
					m(j,k) -= m(i,k) * piv;
					in(j,k) -= in(i,k) * piv;
				}
				//per risparmiare calcoli potrei fare che m calcola con k da i a n e in con k da 0 a n
			}
		}
//m.print(std::cout);
//in.print(std::cout);
	}
	
	for(int i=0;i<n;i++) if(m(i,i) == 0) throw std::runtime_error("Matrix:inverse: matrix is singular");
	
	// crea la matrice bandata
	for(int i=n-1;i>0;i--){
		//calcola i pivot per eliminare le componenti	
		for(int j=i-1;j>=0;j--){
			piv = m(j,i) / m(i,i);
			for(int k=0;k<n;k++){
				//somma per i pivot
//std::cout << "debug::inv::diagonalizzazione: " << i << " " << j << " " << k << std::endl;
				m(j,k) -= m(i,k) * piv;
				in(j,k) -= in(i,k) * piv;
			}
			//per risparmiare calcoli potrei fare che m calcola con k da i a n e in con k da 0 a n
		}
	}
	
	//rende la matrice bandata una matrice identità
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			in(i,j) /= m(i,i);
		}
	}
	
//m.print(std::cout);
//in.print(std::cout);
//std::cout << std::endl;
	
//std::cout << "debug::inv::fine." << std::endl;
	return in;
}

