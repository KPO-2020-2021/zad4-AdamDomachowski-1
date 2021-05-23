#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <filesystem>
#include <vector>
#include "vector.hh"
#include "matrix.hh"
#include "Cuboid.hh"
#include "lacze_do_gnuplota.hh"


/*!
    \file
        \brief klasa scena
*/

class scena{
    private:
        /*! \brief pole przechowujace informacje o obiektach znajdujacych sie na scenie*/
        std::vector <cuboid> obiekty_na_scenie;
        
        /*! \brief pole przechowujace informacje o macierzach obrotu*/
        std::vector <Matrix3x3> macierze_obrotu;

        /*! \brief pole przechowujace informacje o wektorach przesuniecia*/
        std::vector <Vector3D> wektory_przesuniecia;

    public:
        /*! \brief konstruktor bezparametryczny*/
        scena();
        
        /*! \brief umozliwia przesuwanie obiektu na scenie*/
        void przesun(unsigned int index);
        
        /*! \brief przechowuje macierze rotacji*/
        void macierz_rotacji(Matrix3x3 const & macierz, unsigned int index);

        /*! \brief przechowuje wektory przesuniecia */
        void wektor_przesuniecia(Vector3D const & wektor,unsigned int index);
        
        /*! \brief Przeciazenie operatora indeksujacego */
        const cuboid & operator [] (unsigned int index) const;

        /*! \brief Metoda do odczytania macierzy obrotu*/
        Matrix3x3 get_matrix(unsigned int index);

        /*! \brief dodaje obiekt na scenę*/
        void dodaj_obiekt(Vector3D const & A, double const & X, double const & Y, double const & Z);
};
