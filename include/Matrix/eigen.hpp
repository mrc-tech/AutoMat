
//calcola l'autovalore massimo con il metodo delle potenze
template<typename T> double max_eigenvalue(Matrix<T> mat,double err)
{
	// metodo delle potenze
	/*
	funziona solo per matrici definite positive
	il metodo trova l'autovettore x dopo tante iterazioni (infinite in teoria)
	applicando la trasformazione x(new) = A * x
	alla fine x diventa l'autovettore di A
	se l'autovalore atteso è molto simile agli altri allora converge più lentamente
	*/
	//valore iniziale preso a caso
	Matrix<double> x(mat.rows(),1);
	for(int i=0;i<mat.rows();i++) x(i,0) = 1; 
	double lambda = (x.transpose() * mat * x)(0,0) / (x.transpose() * x)(0,0);
	double newlambda;
	double error = 10; // a caso
	while(error > err){
		x = mat * x;
		x = x / x.norm();
		newlambda = (x.transpose() * mat * x)(0,0) / (x.transpose() * x)(0,0);
		error = fabs(lambda - newlambda);
		lambda = newlambda;
	}
	
	return lambda;
}

//calcola l'autovalore più vicino con il metodo delle potenze inverse
template<typename T> double nearest_eigenvalue(Matrix<T> mat,double mu,double err)
{
	// metodo delle potenze inverse
	/*
	se la matrice è definita positiva ha tutti gli autovalori positivi
	quindi per matrici definite positive se pongo mu = 0 ottengo l'autovalore minore
	e l'autovalore minore sarebbe la Frequenza Fondamentale!! (quella più lenta)
	*/
	Matrix<T> id = identity<T>(mat.rows());
	Matrix<T> temp = (mat - (id * mu)).inv();
	//valore iniziale preso a caso
	Matrix<double> x(mat.rows(),1);
	for(int i=0;i<mat.rows();i++) x(i,0) = 1; 
	double lambda = (x.transpose() * mat * x)(0,0) / (x.transpose() * x)(0,0);
	double newlambda;
	double error = 10; // a caso
	while(error > err){
		x = temp * x;
		x = x / x.norm();
		newlambda = (x.transpose() * mat * x)(0,0) / (x.transpose() * x)(0,0);
		error = fabs(lambda - newlambda);
		lambda = newlambda;
//		x.print(std::cout);
//		std::cout << newlambda << std::endl;
	}
	
//	return x; //ritorna l'autovettore
	return lambda;
}

//calcola l'autovettore più vicino con il metodo delle potenze inverse
template<typename T> Matrix<T> nearest_eigenvector(Matrix<T> mat,double mu,double err)
{
	// metodo delle potenze inverse
	/*
	se la matrice è definita positiva ha tutti gli autovalori positivi
	quindi per matrici definite positive se pongo mu = 0 ottengo l'autovalore minore
	e l'autovalore minore sarebbe la Frequenza Fondamentale!! (quella più lenta)
	*/
	Matrix<T> id = identity<T>(mat.rows());
	Matrix<T> temp = mat - (id * mu);
	temp.inv();
	//valore iniziale preso a caso
	Matrix<double> x(mat.rows(),1);
	for(int i=0;i<mat.rows();i++) x(i,0) = 1; 
	double lambda = (x.transpose() * mat * x)(0,0) / (x.transpose() * x)(0,0);
	double newlambda;
	double error = 10; // a caso
	while(error > err){
		x = temp * x;
		x = x / x.norm();
		newlambda = (x.transpose() * mat * x)(0,0) / (x.transpose() * x)(0,0);
		error = fabs(lambda - newlambda);
		lambda = newlambda;
//		x.print(std::cout);
//		std::cout << newlambda << std::endl;
	}
	
	return x; //ritorna l'autovettore
}
