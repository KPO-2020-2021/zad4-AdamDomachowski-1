#pragma once

#include "matrix.hh"

/*!
    \file  
    \brief konkretyzacja szablonu matrix oraz funkcje odpwiedzialne za obrot prostopadloscianu
*/

/*! \brief Konkretyzacja szablonu klasy Matrix */
typedef Matrix<3> Matrix3x3;

/*! \brief Funkcja przygotowujaca macierz obrout dla zadanego kata wzgledem osi X. */
Matrix3x3 obrot_X (double const kat);  

/*! \brief Funkcja przygotowujaca macierz obrout dla zadanego kata wzgledem osi Y. */
Matrix3x3 obrot_Y (double const kat);  

/*! \brief Funkcja przygotowujaca macierz obrout dla zadanego kata wzgledem osi Z. */
Matrix3x3 obrot_Z (double const kat); 