// Calcola il determinante
template<typename T> double determinante(Matrix<T> mat)
{
	int n = mat.rows(); //la datarice è quadrata
	//Matrix<double> m = data; //matrice temporanea
	T piv; //pivot
	T temp; //variabile temporanea per lo scambio
	T d; //variabile temporanea per il determinante
	
	//controlla se la matrice è quadrata
	if(mat.rows() != mat.cols()) throw std::runtime_error("Matrix::determinant: matrix is not square");
	
	//accrocco perchè non c'è il casting nella classe
	Matrix<T> m(n,n,0);
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) m(i,j) = mat(i,j);
	
	// triangolarizza la matrice
	for(int i=0;i<n-1;i++){
		
		if(m(i,i) == 0){
			//cerca un valore massimo non nullo
			int k = i;
			while(k<n && m(k,i)==0) k++;
			//scambia le righe i e k
			for(int x=0;x<n;x++){
				temp = m(i,x);
				m(i,x) = m(k,x);
				m(k,x) = temp;
			}
			if(m(i,i) == 0){
				//la matrice è singolare
				//una riga è comb. lin. di un'altra
				return 0;
			}
		}
		//calcola i pivot per eliminare le componenti	
		for(int j=i+1;j<n;j++){
			if(m(j,i) != 0){
				piv = (double) m(j,i) / m(i,i);
				for(int k=i;k<n;k++){
					//somma per i pivot
					m(j,k) -= m(i,k) * piv;
				}
			}
		}
	}
	
	//calcola il determinante
	d = 1;
	for(int i=0;i<n;i++){
		d *= m(i,i);
	}
	
	//cout << endl << m ;
	
	return d;
}

