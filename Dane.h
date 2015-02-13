/*
 * Dane.h
 *
 *  Created on: 8 gru 2014
 *      Author: M
 */

#ifndef DANE_H_
#define DANE_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Punkt.h"

using namespace std;

class Dane {
public:
	int MAX_ILOSC_SKLEPOW;
	int MAX_ILOSC_PRODUKTOW;
//	int MAX_DLUGOSC_TABU;
	int** macierz_odleglosci;
	int** macierz_cen;
//	int** macierz_dostepnosci;
//    int* zapotrzebowanie;
//    int POJEMNOSC_AUTA;
    Punkt* droga_startowa;

    Dane (int, int);
    ~Dane();

    void Wczytaj_Macierz(string, int**, int, int);
    void Wczytaj_Macierz_Odleglosci(string);
    void Wczytaj_Macierz_Cen(string);
    void Wczytaj_Droge(string);
};


#endif /* DANE_H_ */
