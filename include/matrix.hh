#pragma once

#include "vector.hh"
#include <cmath>
#include <iostream>
#include "size.hh"
#include <cstdlib>

/*!
    \file
    \brief  klasa matrix odpowiada za wszystkie dzialania na macierzach
*/

template <int SIZE>
class Matrix{

private:
    /*! \brief zawiera dane macierzy*/
    double value[SIZE][SIZE];               

public:
    /*! \brief konstruktor bezparametryczny*/
    Matrix();                               

     /*! \brief konstruktor parametryczny*/
    Matrix(double [SIZE][SIZE]);            

     /*! \brief operator mnozenia macierzy przez wektor*/
    Vector<SIZE> operator * (Vector<SIZE> const &tmp);           

     /*! \brief operator mnozenia macierzy przez macierz*/
    Matrix<SIZE> operator * (Matrix<SIZE> const &tmp); 

     /*! \brief dodaje dwie macierze ze soba*/
    Matrix<SIZE> operator + (Matrix<SIZE> tmp);

     /*! \brief resetuje macierz do jednostkowej*/
    Matrix reset_matrix();

     /*! \brief operator przyrównania dwóch macierzy*/
    bool operator == (Matrix const &tmp);  

     /*! \brief operator indeksujacy*/
    double  &operator () (unsigned int row, unsigned int column);
    
    /*! \brief operator indeksujacy*/
    const double &operator () (unsigned int row, unsigned int column) const;

    /*! \brief za pomocą metody eliminacji gausa oblicza wyznacznik macierzy*/
    double oblicz_wyzn(); 
};
/*! \brief przeciarzany opearator wejscia*/
std::istream &operator>>(std::istream &in, Matrix<SIZE> &mat);

/*! \brief przeciazony operator wyjscia*/
std::ostream &operator<<(std::ostream &out, Matrix<SIZE> const &mat);




/*!
    metoda resetujaca macierz do jednostkowej                                                                                                                                          
    \return  Macierz jednostkowa                                      
*/
template <int SIZE>
Matrix<SIZE> Matrix<SIZE>::reset_matrix(){
    for ( int i = 0; i < SIZE; ++i){
        for ( int j = 0; j < SIZE; ++j){
            i == j ? value[i][j] = 1 : value[i][j] = 0;
        }
    }
    return *this;
}




/*!
    Konstruktor bezparametryczny klasy Matrix.                                                                                                                                                                              
    \return  Macierz jednostkowa.                 
*/
template <int SIZE>
Matrix<SIZE>::Matrix() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i==j){
                value[i][j] = 1;
            }
            else{
                value[i][j] = 0;
            }
        }
    }
}




/*!
    Konstruktor parametryczny klasy Matrix.                                                                                                    
    \param[in] tmp - dwuwymiarowa tablica z elementami typu double.                                                                            
    \return  Macierz wypelniona wartosciami podanymi w argumencie.                 
*/
template <int SIZE>
Matrix<SIZE>::Matrix(double tmp[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = tmp[i][j];
        }
    }
}




/*!
    Realizuje mnozenie macierzy przez wektor.                                                                                             
    \param[in] this - macierz, czyli pierwszy skladnik mnozenia,                     
    \param[in] tmp - wektor, czyli drugi skladnik mnozenia.                                                                                         
    \return  Iloczyn dwoch skladnikow przekazanych jako wektor.                    
*/
template <int SIZE>
Vector<SIZE> Matrix<SIZE>::operator * (Vector<SIZE> const &tmp) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}




/*!
    Realizuje mnozenie macierzy przez macierz.                                 
                                                                   
    \param[in] this - macierz, czyli pierwszy skladnik mnozenia,                     
    \param[in] tmp - macierz, czyli drugi skladnik mnozenia.                            
                                                                   
    \return  result - Iloczyn dwoch skladnikow przekazanych jako macierz.                    
*/
template < int SIZE>
Matrix<SIZE> Matrix<SIZE>::operator * (Matrix<SIZE> const &tmp){
    Matrix<SIZE> result;
    for( int i = 0; i < SIZE; ++i){
        for( int j = 0; j < SIZE; ++j){    
            result(i,j) = 0;
            for( int k = 0; k < SIZE; ++k){
                result(i,j) +=  value[i][k] * tmp(k,j);
            }
        }
    }
    return result; 
}




/*!    
    Funktor macierzy.

    \param[in] row - numer wiersza.                                                  
    \param[in] column - numer kolumny.                                               

    \return Wartosc macierzy w danym miejscu tablicy.                             
*/
template <int SIZE>
double &Matrix<SIZE>::operator()(unsigned int row, unsigned int column) {

    if (row >= SIZE) {
        throw "Error: Macierz jest poza zasiegiem"; 
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= SIZE) {
        throw "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}




/*!    
    Funktor macierzy.

    \param[in] row - numer wiersza.                                                  
    \param[in] column - numer kolumny.                                               

    \return Wartosc macierzy w danym miejscu tablicy.                             
*/
template <int SIZE>
const double &Matrix<SIZE>::operator () (unsigned int row, unsigned int column) const {

    if (row >= SIZE) {
        throw "Error: Macierz jest poza zasiegiem";
        exit(0); 
    }

    if (column >= SIZE) {
        throw "Error: Macierz jest poza zasiegiem";
        exit(0);
    }

    return value[row][column];
}




/*!
    Przeciążenie operatora dodawania dwoch macierzy.                                                      
    \param[in] this - Macierz, czyli pierwszy skladnik dodawania.                    
    \param[in] tmp - Macierz, czyli drugi skladnik dodawania.                                                                                     
    \return  Macierz - suma dwóch podanych macierzy.                            
*/
template <int SIZE>
Matrix<SIZE> Matrix<SIZE>::operator + (Matrix<SIZE> tmp) {
    Matrix<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}




/*! 
    Funkcja realizujaca przeciazenia operatora >>.
    Funkcja sluzy do wczytywania ze wskazanego strumiena wejsciowego, wartosci wspolrzednych macierzy.      
    \param[in] in - Strumien wejsciowy.                                             
    \param[in] mat - Macierz.   
    \return wczytany obiekt - macierz.
*/
template <int SIZE>
std::istream &operator >> (std::istream &in, Matrix<SIZE> &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}




/*!  
    Funkcja realizujaca przeciazenia operatora <<.
    Funkcja sluzy do wypisywania na wskazany strumien wyjsciowy, wartosci wspolrzednych macierzy.      
    \param[in] out - Strumien wejsciowy.                                            
    \param[in] mat - Macierz.       
    \return Wypisane wspolrzende wskazanego prostopadloscianu, w odpowiedniej formie na wskazane wyjscie.                                                     
*/
template <int SIZE>
std::ostream &operator << (std::ostream &out, const Matrix<SIZE> &mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}




/*!
    Realizuje porownywanie wartosci w dwoch macierzach.                                                                                             
    \param[in]   this - macierz, czyli pierwszy skladnik porownania,                     
    \param[in]   tmp - macierz, czyli drugi skladnik porownania.                                                                                        
    \return  true - jesli macierze sa rowne.          
    \return  false - jesli macierze nie sa rowne.           
*/
template <int SIZE>
bool Matrix<SIZE>::operator == (Matrix const &tmp){
    for (unsigned int i = 0; i < SIZE ; ++i)
        for (unsigned int j = 0; j < SIZE ; ++j) 
            if(value[i][j] - tmp(i,j) < -MAKSYMALNA_ROZNICA_WYNIKOW || value[i][j] - tmp(i,j) > MAKSYMALNA_ROZNICA_WYNIKOW)   
                return false;   
    return true;    
}




// wykorzystując metodę gausa oblicza wyznacznik
 template <int SIZE>
 double Matrix<SIZE>::oblicz_wyzn(){
 double ratio, wyznacznik = 1;
	 for(int i=0;i<=SIZE-2;i++)
	 {
		  if(value[i][i] == 0.0)
		  {
			   throw "Mathematical Error!";
			   exit(0);
		  }
		  for(int j=i+1;j<=SIZE;j++)
		  {
			   ratio = value[j][i]/value[i][i];

			   for(int k=0;k<=SIZE;k++)
			   {
			  		value[j][k] = value[j][k] - ratio*value[i][k];
			   }
		  }
	 }

	
    for(int i=0; i<SIZE; i++){
        wyznacznik = wyznacznik * value[i][i];
    }

return wyznacznik;
}