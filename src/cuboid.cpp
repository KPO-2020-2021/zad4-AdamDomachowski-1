#include "Cuboid.hh"
#include "matrix.hh"
#include "matrix3x3.hh"

/*!
    \file
        \brief  metody klasy Cuboid
*/


/*!
    konstruktor bezparametryczny                                                                                                                                                     
    \return prostopadloscian zainicjowany samymi zerami       
 */
cuboid::cuboid ()
    {
        for (int i=0; i<8; i++){
            wierzcholki_globalne[i] = Vector3D();
        }
        srodek = Vector3D();
    }
    


/*!
    drugi konstruktor bezparametryczny                                                                                                                                                     
    \return informacja o srodku oraz wektorach wierzcholkow       
 */
cuboid::cuboid(Vector3D srodek_w_konstruktorze, Vector3D I, Vector3D II, Vector3D III, Vector3D IV, Vector3D V, Vector3D VI, Vector3D VII, Vector3D VIII)
     {
        srodek_w_konstruktorze = srodek;

        wierzcholki_lokalne[0] = I;
        wierzcholki_lokalne[1] = II;
        wierzcholki_lokalne[2] = III;
        wierzcholki_lokalne[3] = IV;
        wierzcholki_lokalne[4] = V;
        wierzcholki_lokalne[5] = VI;
        wierzcholki_lokalne[6] = VII;
        wierzcholki_lokalne[7] = VIII;

        for(int i=0; i < ILOSC_WIERZCHOLKOW; ++i)
        {
            wierzcholki_globalne[i] = wierzcholki_lokalne[i] + srodek;
        }
     }




/*!                                                                                                         
    \param[in] index - indeks wierzcholka                                             
                                                                   
    \return wypisuje wspolrzedne danego wierzcholka                
 */
const Vector3D & cuboid::operator [] (int row) const {
    if (row < 0 || row >= ILOSC_WIERZCHOLKOW) {
        throw std::runtime_error("Bledna wartosc");
    } 
    return wierzcholki_globalne[row];
}




/*!                                                                                                         
    \param[in] index - indeks wierzcholka                                             
                                                                   
    \return wypisuje wspolrzedne danego wierzcholka                
 */
 Vector3D & cuboid::operator[](int row) {
    return const_cast <Vector3D &> (const_cast <const cuboid *> (this)->operator[](row));
}




/*!  
    manipuluje pozycją prostopadłoscianu

    \param [in] wektor_przesuniecia - Wektor przesuniecia srodka prostopadloscianu.
    \param [in] macierz - Macierz rotacji. 
*/
void cuboid::translacja(Vector3D const & wektor_przesuniecia, Matrix3x3 const & macierz){
    Matrix3x3 matrix = macierz; 
    for(int i = 0; i < ILOSC_WIERZCHOLKOW; ++i)
        wierzcholki_globalne[i] = (matrix * wierzcholki_lokalne[i]) + srodek + wektor_przesuniecia;  
}




/*!  
    przeciarzenie operatora wejscia
    \param [in] in - strumien wejsciowy
    \param [in] rec - prostopadloscian 
*/
std::istream &operator>>(std::istream &in, cuboid &rec) {
    for (int i = 0; i < ILOSC_WIERZCHOLKOW; ++i){
            in >> rec[i];
    }
    return in;
}




/*!  
    przeciarzenie operatora wejscia
    \param [in] out - strumien wyjsciowy
    \param [in] rec - prostopadloscian 
*/
std::ostream &operator<<(std::ostream &out, const cuboid &rec) {
    for (int i = 0; i < ILOSC_WIERZCHOLKOW; ++i) {
            out << rec[i]<< std::endl; //warto ustalic szerokosc wyswietlania dokladnosci liczb
            if ((i+1)%2==0)
                out << std::endl;
    }
    return out;
}




/*!  
    zapisuje wierzcholki do pliku
    \param [in] sNazwaPliku - wskaznik na nazwe pliku
*/
void cuboid::zapisz(const char *sNazwaPliku) const{
    std::ofstream  plik;
    
    plik.open(sNazwaPliku);
    if (!plik.is_open()){
      throw std::runtime_error("operacja nie powiodła się");
    }

    plik <<  wierzcholki_globalne[6] << std::endl
             << wierzcholki_globalne[4] << std::endl
             << '#' << std::endl
             << std::endl;

    plik << wierzcholki_globalne[7] << std::endl
             << wierzcholki_globalne[5] << std::endl
             << '#' << std::endl
             << std::endl; 

    plik << wierzcholki_globalne[1] << std::endl
             << wierzcholki_globalne[3] << std::endl
             << '#' << std::endl
             << std::endl; 

    plik << wierzcholki_globalne[0] << std::endl
             << wierzcholki_globalne[2] << std::endl
             << '#' << std::endl
             << std::endl; 

    plik << wierzcholki_globalne[6] << std::endl
             << wierzcholki_globalne[4] << std::endl
             << '#' << std::endl
             << std::endl; 

    plik.close();
}

 
    

