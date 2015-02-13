/*
 * Dane.cpp
 *
 *  Created on: 8 gru 2014
 *      Author: M
 */

#include "Dane.h"

Dane::Dane(int skl,int prod) {
//	cout << "dane konstr poczatek" << endl;
	MAX_ILOSC_SKLEPOW = skl;
	MAX_ILOSC_PRODUKTOW = prod;
//	MAX_DLUGOSC_TABU = 300;

	macierz_odleglosci = new int* [MAX_ILOSC_SKLEPOW + 1];
	for (int i = 0; i < MAX_ILOSC_SKLEPOW + 1; i++) {
		macierz_odleglosci[i] = new int [MAX_ILOSC_SKLEPOW + 1];
		for (int j = 0; j < MAX_ILOSC_SKLEPOW + 1; j++) {
			macierz_odleglosci[i][j] = 0;
		}
	}
	macierz_cen = new int* [MAX_ILOSC_SKLEPOW];
	for (int i = 0; i < MAX_ILOSC_SKLEPOW; i++) {
		macierz_cen[i] = new int [MAX_ILOSC_PRODUKTOW];
		for (int j = 0; j < MAX_ILOSC_PRODUKTOW; j++) {
			macierz_cen[i][j] = 0;
		}
	}
	droga_startowa = new Punkt [MAX_ILOSC_SKLEPOW];
	for (int i = 0; i < MAX_ILOSC_SKLEPOW; i++) {
		droga_startowa[i] = Punkt(0, 0);
	}
//	cout << "dane konstr koniec" << endl;
}

Dane::~Dane () {
//	cout << "destruktor danych" << endl;
	for (int i = 0; i < MAX_ILOSC_SKLEPOW + 1; i++) {
		delete [] macierz_odleglosci[i];
		macierz_odleglosci[i] = NULL;
	}
	delete [] macierz_odleglosci;
	macierz_odleglosci = NULL;
	for (int i = 0; i < MAX_ILOSC_SKLEPOW + 1; i++) {
		delete [] macierz_cen[i];
		macierz_cen[i] = NULL;
	}
	delete [] macierz_cen;
	macierz_cen = NULL;
	delete [] droga_startowa;
	droga_startowa = NULL;
//	cout << "destruktor danych zakonczyl dzialanie" << endl;
}

void Dane::Wczytaj_Macierz (string nazwaPliku, int** tab, int wiersze, int kolumny) {
    std::ifstream plik;
    plik.open (nazwaPliku.c_str());
    if (plik.good()) {
    	for (int i = 0; i < wiersze; i++) {
    		for (int j = 0; j < kolumny; j++) {
    			plik >> tab[i][j];
    		}
    	}
    }
}

void Dane::Wczytaj_Macierz_Odleglosci (string plik) {
	Wczytaj_Macierz (plik, macierz_odleglosci, MAX_ILOSC_SKLEPOW + 1, MAX_ILOSC_SKLEPOW + 1);
}

void Dane::Wczytaj_Macierz_Cen (string plik) {
	Wczytaj_Macierz (plik, macierz_cen, MAX_ILOSC_SKLEPOW, MAX_ILOSC_PRODUKTOW);
}

void Dane::Wczytaj_Droge(string nazwaPliku) {
	int** temp;
	temp = new int* [MAX_ILOSC_SKLEPOW];
	for (int i = 0; i < MAX_ILOSC_SKLEPOW; i++) {
		temp[i] = new int [2];
		temp [i][0] = i;
		temp [i][1] = i;
	}
	Wczytaj_Macierz(nazwaPliku, temp, MAX_ILOSC_SKLEPOW, 2);
	for (int i = 0; i < MAX_ILOSC_SKLEPOW; i++) {
		droga_startowa[i].id_sklepu = temp[i][0];
		droga_startowa[i].id_prod = temp[i][1];
		delete [] temp[i];
		temp[i] = NULL;
	}
	delete [] temp;
}






