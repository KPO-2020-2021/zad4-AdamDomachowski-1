
#include "matrix3x3.hh"

/*! \brief Funkcja przygotowujaca macierz obrout dla zadanego kata wzgledem osi X. 
    \param[in] kat - kat obrotu
    \return macierz przygotowana do obrotu    
*/
Matrix3x3 obrot_X (double const kat){
    Matrix3x3 macierz;
    double kat_radian = kat * M_PI / 180.0;
    macierz(0,0) = 1;
    macierz(0,1) = 0;
    macierz(0,2) = 0;
    macierz(1,0) = 0;
    macierz(1,1) = cos(kat_radian);
    macierz(1,2) = -sin(kat_radian);
    macierz(2,0) = 0;
    macierz(2,1) = sin(kat_radian);
    macierz(2,2) = cos(kat_radian);
    return macierz;
}




/*! \brief Funkcja przygotowujaca macierz obrout dla zadanego kata wzgledem osi Y. 
    \param[in] kat - kat obrotu
    \return macierz przygotowana do obrotu    
*/
Matrix3x3 obrot_Y (double const kat){
    Matrix3x3 macierz;
    double kat_radian = kat * M_PI / 180.0;
    macierz(0,0) = cos(kat_radian);
    macierz(0,1) = 0;
    macierz(0,2) = sin(kat_radian);
    macierz(1,0) = 0;
    macierz(1,1) = 1;
    macierz(1,2) = 0;
    macierz(2,0) = -sin(kat_radian);
    macierz(2,1) = 0;
    macierz(2,2) = cos(kat_radian);
    return macierz;
}




/*! \brief Funkcja przygotowujaca macierz obrout dla zadanego kata wzgledem osi Y. 
    \param[in] kat - kat obrotu
    \return macierz przygotowana do obrotu    
*/
Matrix3x3 obrot_Z (double const kat){
    Matrix3x3 macierz;
    double kat_radian = kat * M_PI / 180.0;
    macierz(0,0) = cos(kat_radian);
    macierz(0,1) = -sin(kat_radian);
    macierz(0,2) = 0;
    macierz(1,0) = sin(kat_radian);
    macierz(1,1) = cos(kat_radian);
    macierz(1,2) = 0;
    macierz(2,0) = 0;
    macierz(2,1) = 0;
    macierz(2,2) = 1;
    return macierz;
}
    