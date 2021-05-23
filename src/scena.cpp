#include "scena.hh"

/*!
    \file
        \brief  metody klasy scena
*/


/*!
    Konstruktor bezparametryczny   
    \return Scene zawierajaca przykladowy prostopadloscian. 
*/
scena::scena(){
    /*wspolrzedne srodka*/
    double wsp[]={20,30,10}; 
    Vector3D A(wsp);
    dodaj_obiekt(A,40,30,20);
}




/*!
    Przeciazenie operatora indeksujacego
    \param [in] index - Indeks 
    \return prsotopadloscian 
*/
const cuboid & scena::operator [] (unsigned int index) const{
    if (index>=obiekty_na_scenie.size())
        throw std::runtime_error("Bledna wartosc indeksu");
    return obiekty_na_scenie.at(index);
}




/*!
    Modyfikuje macierz obrotu konkretnego prostopadloscianu    
    \param [in] macierz - macierz o jaka macierz rotacji wewnatrz sceny ma zostac pomnozona.
    \param [in] index - Indeks prostopadloscianu.
*/
void scena::macierz_rotacji(Matrix3x3 const & macierz, unsigned int index){
    Matrix3x3 temporary = macierz;
    macierze_obrotu.at(index) = temporary * macierze_obrotu.at(index);
}




/*! 
    Modyfikuje wektor przesuniecia konkretnego prostopadloscianu
    \param [in] macierz - wektor dodawany do wekrora przesuniecia wewnatrz sceny.
    \param [in] index - Indeks prostopadloscianu.
*/
void scena::wektor_przesuniecia(Vector3D const & wektor, unsigned int index){
    Vector3D temporary = wektor;
    wektory_przesuniecia.at(index) = wektory_przesuniecia.at(index) + temporary;
}




/*!
    umożliwia manipulowanie pozycji prostopadloscianu na scenie
    \param [in] index - Indeks wskazanego prostopadloscianu.
*/
void scena::przesun(unsigned int index){
    obiekty_na_scenie.at(index).translacja(wektory_przesuniecia.at(index), macierze_obrotu.at(index));
}




/*!
    umozliwa dodawanie do sceny obiektu

    \param [in] A - wspolrzedne srodka
    \param [in] X - Dlugosc X. 
    \param [in] Y - Dlugosc Y. 
    \param [in] Z - Dlugosc Z. 

*/
void scena::dodaj_obiekt(Vector3D const & A, double const & X, double const & Y, double const & Z){
    Vector3D wspolrzedne[8], wektorX, wektorY, wektorZ;

    wektorX[0] = X/2;
    wektorY[1] = Y/2;
    wektorZ[2] = Z/2;

    wspolrzedne[0] = wspolrzedne[0] - wektorX - wektorY - wektorZ;
    wspolrzedne[1] = wspolrzedne[1] + wektorX - wektorY - wektorZ;
    wspolrzedne[2] = wspolrzedne[2] - wektorX + wektorY - wektorZ;
    wspolrzedne[3] = wspolrzedne[3] + wektorX + wektorY - wektorZ;
    wspolrzedne[4] = wspolrzedne[4] - wektorX + wektorY + wektorZ;
    wspolrzedne[5] = wspolrzedne[5] + wektorX + wektorY + wektorZ;
    wspolrzedne[6] = wspolrzedne[6] - wektorX - wektorY + wektorZ;
    wspolrzedne[7] = wspolrzedne[7] + wektorX - wektorY + wektorZ;

    cuboid obiekt(A,wspolrzedne[0],wspolrzedne[1],wspolrzedne[2],wspolrzedne[3],wspolrzedne[4],wspolrzedne[5],wspolrzedne[6],wspolrzedne[7]);

    obiekty_na_scenie.push_back(obiekt); 
    macierze_obrotu.push_back(Matrix3x3());
    wektory_przesuniecia.push_back(Vector3D());   
}