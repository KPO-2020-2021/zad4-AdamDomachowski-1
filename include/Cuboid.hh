#pragma once  

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iomanip>

#include "Vector3D.hh"
#include "matrix3x3.hh"
#include "matrix.hh"
#include "lacze_do_gnuplota.hh"
#include "size.hh"

/*!
    \file
    \brief  klasa cuboid przechowuje informacje o wierzcholkach (w formie wektorów) prostopadloscianu.
    W czesci prywatnej zawarte sa informacje o wektorach wierzcholkow oraz o wsporzednych srodka.
    W czesci publicznej znajduja sie konstruktory klasy oraz metody niezbedne do dzialania programu, wraz z przeciarzeniami.
*/
class cuboid {

private:
    /*! \brief przechowuje wspolrzedne srodka prostopadloscianu */
    Vector3D srodek;

    /*! \brief tablica wektorow dzieki ktorym uzyskujemy wspolrzedne wierzchowlkow ( w ukladzie lokalnym )*/
    Vector3D wierzcholki_lokalne[8];
    
    /*! \brief tablica wektorow dzieki ktorym uzyskujemy wspolrzedne wierzchowlkow ( w ukladzie globalnym )*/
    Vector3D wierzcholki_globalne[8];


public:
    /*! \brief konstruktor bezparametryczny*/
    cuboid ();

    /*! \brief konstruktor parametryczny*/
    cuboid(Vector3D srodek, Vector3D I, Vector3D II, Vector3D III, Vector3D IV, Vector3D V, Vector3D VI, Vector3D VII, Vector3D VIII);          

    /*! \brief przeciazany operator indeksujacy*/
    const Vector3D &operator[] (int row) const;

    /*! \brief przeciazany operator indeksujacy*/
    Vector3D  &operator[] (int row);

    /*! \brief odpowiada za zmiane polorzenia prostopadloscianu*/
    void translacja(Vector3D const & wektor_przes, Matrix3x3 const & macierz);

    /*! \brief zapisuje wierzcholki do pliku*/
    void zapisz(const char *sNazwaPliku) const;  
};
/*! \brief przeciarzany opearator wejscia*/
std::istream &operator>>(std::istream &in, cuboid &rec);

/*! \brief przeciazony operator wyjscia*/
std::ostream &operator<<(std::ostream &out, cuboid const &rec);




