/*
 * Algorytm.h
 *
 *  Created on: 8 gru 2014
 *      Author: M
 */

#ifndef ALGORYTM_H_
#define ALGORYTM_H_

#include "Dane.h"
#include "Punkt.h"
#include "TabuList.h"
#include <fstream>
#include<QObject>
#include <string>
#include<QProgressBar>
#include <QString>
class Algorytm{
public:
    QProgressBar *bar;
    Dane* dane;
    volatile int index;

    Punkt* droga;
    // pamiec dla najlepszego rozwiazania w otoczeniu (wykonany ruch)
    Punkt* droga_nowa;
    QString nazwa_pliczku;

    QString nazwa_macierz_odleglosci;
    QString nazwa_macierz_cen;
    QString nazwa_wektor_poczatkowy;

    // pamiec najlepszego rozwiazania
    int najlepsza_wartosc_f_celu;
    Punkt* droga_najlepsza;

    // ruchy zabronione, po przeszukaniu obie listy sa uaktualniane,
    // jesli nastapila zamiana sklepu 1 i 2, to na tabu_sklep idzie
    // punkt (1,2) a na tabu_prod idzie (0,0)
    TabuList *tabu_sklep;
    TabuList *tabu_prod;

	int ilosc_sklepow_arg;
	int ilosc_produktow_arg;
	int dlugosc_tabu_arg;
	int ilosc_iteracji_arg;

    Algorytm (int, int, int, int);
    virtual ~Algorytm ();
    int Wylicz_Funkcje_Celu ();
    void Zamien_Sklep(int, int);
    void Zamien_Prod(int, int);
    void Przeszukaj_Otoczenie ();
    void Start ();
    void Wczytaj_Droge_Startowa();
    int getIndex() { return index;}
    void setBar(QProgressBar *b){
        bar = b;
    }
    void setOutputName(QString nazwa){
        nazwa_pliczku = nazwa;
    }
    void setPricesName(QString nazwa){
        nazwa_macierz_cen = nazwa;
    }
    void setDistanceName(QString nazwa){
        nazwa_macierz_odleglosci = nazwa;
    }
    void setInputName(QString nazwa){
        nazwa_wektor_poczatkowy = nazwa;
    }

};


#endif /* ALGORYTM_H_ */
