#pragma once

#include "size.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <cmath>

/*!
    \file
    \brief  klasa vector odpowiada za wszystkie dzialania na wektorach
*/

template <int SIZE>
class Vector{

private:
    /*! \brief Tablica wartosci wektora*/
    double size[SIZE];    

public:

    /*! \brief konstruktor bezparametryczny*/
    Vector();

    /*! \brief konstruktor parametryczny*/   
    Vector(double [SIZE]);


    bool operator == ( const Vector<SIZE> &v) const;

    /*! \brief realizuje dodawanie dwoch wektorow*/
    Vector<SIZE> operator + (const Vector<SIZE> &v);

    /*! \brief realizuje odejmowanie dwoch wektorow*/
    Vector<SIZE> operator - (const Vector<SIZE> &v);

     /*! \brief realizuje mnozenie dwoch wektorow*/
    Vector<SIZE> operator * (const double &tmp);

    /*! \brief realizuje dzielenie wektora przez skalar*/
    Vector<SIZE> operator / (const double &tmp);

    /*! \brief operator indeksujacy*/
    const double &operator [] (int index) const;

    /*! \brief operator indeksujacy*/
    double &operator [] (int index);

    /*! \brief oblicza dlugosc*/
    double length(const Vector<SIZE> &v);
};

/*! \brief przeciarzany opearator wejscia*/
std::ostream &operator << (std::ostream &out, Vector<SIZE> const &tmp);

/*! \brief przeciarzany opearator wyjscia*/
std::istream &operator >> (std::istream &in, Vector<SIZE> &tmp);




/*!
    Konstruktor bezparametryczny klasy Vector tworzacy wektor zerowy.                                              
    \return Tablice wypelniona wartoscia 0.                                       
*/
template <int SIZE>
Vector<SIZE>::Vector() {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = 0;
    }
}




/*!
    Konstruktor wieloparametryczny klasy Vector tworzacy wektor o zadanej dlugosci wypelniony warosciami pochodzacymi z parametru - tablicy wartosci typu double.                                                 
    \param [in] tmp - Jednowymiarowa tablica typu double.                                                                                    
    \return  Tablice wypelniona wartosciami podanymi w argumencie.                 
 */
template <int SIZE>
Vector<SIZE>::Vector(double tmp[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        size[i] = tmp[i];
    }
}



/*!
    Realizuje dodawanie dwoch wektorow.                                       
                                                                  
    \param [in]    this - pierwszy skladnik dodawania,                                   
    \param [in]    v - drugi skladnik dodawania.                                         
   Zwraca:                                                                   
    \return Sume dwoch skladnikow przekazanych jako wskaznik na parametr.                                                          
*/
template <int SIZE>
Vector<SIZE> Vector<SIZE>::operator + (const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] += v[i];
    }
    return result;
}



/******************************************************************************
 |  Realizuje przyrównanie dwoch wektorow.                                    |
 |  Argumenty:                                                                |
 |      v - drugi skladnik porównania.                                        |
 |  Zwraca:                                                                   |
 |      true or false                                                         |
 */
template <int SIZE>
 bool Vector<SIZE>::operator == ( const Vector<SIZE> &v) const {
    for (int i = 0; i < SIZE; ++i) {
        if (v[i] != size[i]) return false;
    }
    return true;
}

/*!
    Realizuje odejmowanie dwoch wektorow.                                     
                                                                  
    \param [in]    this - pierwszy skladnik odejmowania,                                 
    \param [in]    v - drugi skladnik odejmowania.                                       
                                                               
    \return   Roznice dwoch skladnikow przekazanych jako wskaznik na parametr.                                                          
 */
template <int SIZE>
Vector<SIZE> Vector<SIZE>::operator - (const Vector<SIZE> &v) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] -= v[i];
    }
    return result;
}




/*!
    Realizuje mnozenie wektora przez liczbe zmiennoprzecinkowa.                                                                           
    \param [in]    this - pierwszy skladnik mnozenia (wektor),                           
    \param [in]    v - drugi skladnik mnozenia (liczba typu double).                                                                                   
    \return Iloczyn dwoch skladnikow przekazanych jako wskaznik na parametr.                                                          
 */
template <int SIZE>
Vector<SIZE> Vector<SIZE>::operator * (const double &tmp) {
    Vector<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] *= tmp;
    }
    return result;
}




/*!
    Realizuje dzielenie wektora przez liczbe zmienno przecinkowa.                                                                                                   
    \param [in]    this - licznik dzielenia,                                             
    \param [in]    v - mianownik dzielenia.                                                                                                         
    \return Iloraz dwoch skladnikow przekazanych jako wskaznik na parametr.                                                          
*/
template <int SIZE>
Vector<SIZE> Vector<SIZE>::operator / (const double &tmp) {
    Vector<SIZE> result;

    if (tmp == 0)
        throw std::runtime_error("dzielenie przez 0");

    for (int i = 0; i < SIZE; ++i) {
        result[i] = size[i] / tmp;
    }

    return result;
}




/*!
    Funktor wektora.                                                                                                                            
    \param [in] index - index wektora.                                                                                                              
    \return Wartosc wektora w danym miejscu tablicy jako stala.                   
*/
template <int SIZE>
const double &Vector<SIZE>::operator [] (int index) const {
    if (index < 0 || index >= SIZE) {
       throw "Error: Wektor jest poza zasiegiem!";
    } 
    return size[index];
}



/*!
    Funktor wektora.                                                                                                                      
    \param [in] index - index wektora.                                                                                                                
    \return Wartosc wektora w danym miejscu tablicy.                              
 */
template <int SIZE>
double &Vector<SIZE>::operator[](int index) {
    if (index < 0 || index >= SIZE) {
   throw "Error: Wektor jest poza zasiegiem!" ;
    } // lepiej byłoby rzucić wyjątkiem stdexcept
    return const_cast<double &>(const_cast<const Vector<SIZE> *>(this)->operator[](index));
}




/*!
    przeciazenie operatora <<                                                      
    \param [in] out - strumien wejsciowy,                                             
    \param [in] tmp - wektor.   
    \return Wypisane wartosci wskazanego wektora, w odpowiedniej formie na wskazane wyjscie.                                                        
 */
template <int SIZE>
std::ostream & operator << (std::ostream &out, Vector<SIZE> const &tmp){
    for ( int i = 0; i < SIZE; ++i) {
        out << std::fixed << std::setprecision(10) << tmp[i]<< " ";
    }
    return out;
}




/*!
    przeciazenie operatora >>                                                                                                               
    \param [in]    in - strumien wyjsciowy,                                              
    \param [in]    tmp - wektor.    
    \return                                                      
 */
template <int SIZE>
std::istream &operator >> (std::istream &in, Vector<SIZE> &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}




/*!
    sprawdza dlugosc wektora
*/
template <int SIZE>
double Vector<SIZE>::length(const Vector<SIZE> &v)
{
return sqrt(pow(size[0]-v[0],2)+pow(size[1]-v[1],2));
} 