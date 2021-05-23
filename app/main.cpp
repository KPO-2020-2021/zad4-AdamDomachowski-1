#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "matrix.hh"
#include "Cuboid.hh"
#include "scena.hh"
#include "../include/lacze_do_gnuplota.hh"

/*! \brief tu sie dzieje program*/


int main() {

  PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji rysunku prostokata
  int aktywne_obiekty = 0;
  double kat = 0, ile_razy = 1;
  char wybor;
  Vector3D wektor_przesuniecia, temp_srodek;
  Matrix3x3 tymczasowa_macierz;

  scena scena;

  std::vector <std::string>  schowek_vector;

  std::string schowek_string;

  schowek_vector.push_back("../datasets/cuboid.dat");

  Lacze.DodajNazwePliku(schowek_vector.at(0).c_str(),PzG::RR_Ciagly,2);

  Lacze.ZmienTrybRys(PzG::TR_3D);

  Lacze.UstawZakresY(-200,200);  
  Lacze.UstawZakresX(-200,200);
  Lacze.UstawZakresZ(-200,200); 


  scena[aktywne_obiekty].zapisz(schowek_vector.at(aktywne_obiekty).c_str());
  Lacze.Rysuj();

  std::cout << "Menu wyboru opcji:" << std::endl
    << "o - obrot bryly o zadana sekwencje katow" << std::endl
    << "p - przesuniecie bryly o zadany wektor " << std::endl
    << "m - wyswietl menu" << std::endl
    << "k - koniec dzialania programu" << std::endl << std::endl;

  while (1){
    std::cout << "Twoj wybor? (m - menu) > ";
    std::cin >> wybor;
  switch(wybor)
  {
  case 'o': /* Opcja pozwalajaca na zadanie sekwencji obrotu prostopadloscianu */
  tymczasowa_macierz.reset_matrix();
  std::cout << "Podaj oś względem któej chcesz obrocic (x,y,z), k - koniec " << std::endl; /* Okreslenie sekwencji obrotow prostopadloscianu */
  while (wybor !='k'){  
  std::cin >> wybor;
      switch(wybor){
                                
        case 'x':
        std::cin >> kat;
        if(std::cin.fail())
            throw std::invalid_argument("Podano bledna wartosc kata obrotu "); 
        else
        {
          tymczasowa_macierz = obrot_X(kat) * tymczasowa_macierz;
        }
        break;

                               
        case 'y':
        std::cin >> kat;
        if(std::cin.fail())
          throw std::invalid_argument(" Podano bledna wartosc kata obrotu ");
        else
        {
          tymczasowa_macierz = obrot_Y(kat) * tymczasowa_macierz;
        }
        break;


        case 'z':
        std::cin >> kat;
        if(std::cin.fail())
          throw std::invalid_argument(" Podano bledna wartosc kata obrotu ");
        else
        {
          tymczasowa_macierz = obrot_Z(kat) * tymczasowa_macierz;
        }
        break;
                                

        default:
        std::cout << " wybierz (x, y, z) lub k - koniec" << std::endl; 
        std::cin.ignore(10000,'\n');
        break;            
        }//2 switch 
      }// while

      while (true){
        std::cout << "Ile razy chcesz obrocic bryle"<< std::endl; /* Okreslenie ile razy wprowadzony obrot ma sie wykonac*/
        std::cin >> ile_razy; 
        if(std::cin.fail() || ile_razy < 0)
          throw std::invalid_argument(" Podano bledna wartosc mnoznika ");
        else   
          break;
       } 

      for (unsigned int i=0; i<ile_razy;++i)
          scena.macierz_rotacji(tymczasowa_macierz, aktywne_obiekty);

        scena.przesun(aktywne_obiekty); 
        scena[aktywne_obiekty].zapisz(schowek_vector.at(aktywne_obiekty).c_str());
        Lacze.Rysuj();
      break;




      case 'p': /* Opcja translacji o wektor */
      std::cout << "podaj wektor" << std::endl;
      std::cin >> wektor_przesuniecia;
      scena.wektor_przesuniecia(wektor_przesuniecia,aktywne_obiekty);
      scena.przesun(aktywne_obiekty);
      scena[aktywne_obiekty].zapisz(schowek_vector[aktywne_obiekty].c_str());
      Lacze.Rysuj();
      break;




      case 'm': /* Opcja wyswietlajaca dostepne w menu opcje */        
      std::cout << "Menu wyboru opcji:" << std::endl
      << "o - obrot bryly o zadana sekwencje katow" << std::endl
      << "p - przesuniecie bryly o zadany wektor " << std::endl
      << "m - wyswietl menu" << std::endl
      << "k - koniec dzialania programu" << std::endl << std::endl;
      break;




      case 'k': /* Opcja konczaca program */
      std::cout << "Koniec pracy programu" << std::endl;
      return 0;
      

    }
  }
}