/*
 * Algorytm.cpp
 *
 *  Created on: 8 gru 2014
 *      Author: M
 */

#include "Algorytm.h"
#include "widget.h"
#include <QThread>
#include<QObject>
#include<QProgressBar>
//bool Algorytm::wczytaj_plik(std::string nazwaPliku, int** tab, int wiersze, int kolumny){
//    std::ifstream plik;
//    plik.open( nazwaPliku.c_str() );
//    if( !plik.good()){
//    	return false;
//    }
//    for(int i = 0; i < wiersze; i++){
//    	for(int j = 0; j < kolumny; j++){
//            if(plik.good())
//            	plik >> tab[i][j];
//    	}
//    }
//    return true;
//}

Algorytm::Algorytm (int arg1, int arg2 , int arg3, int arg4) {
//	cout << "alg konst poczatek" << endl;

	ilosc_sklepow_arg = arg1;
	ilosc_produktow_arg = arg2;
	dlugosc_tabu_arg = arg3;
	ilosc_iteracji_arg = arg4;

	dane = new Dane (ilosc_sklepow_arg, ilosc_produktow_arg);

	tabu_prod = new TabuList(dlugosc_tabu_arg);
	tabu_sklep = new TabuList(dlugosc_tabu_arg);

	najlepsza_wartosc_f_celu = 10000;
	droga = new Punkt [dane->MAX_ILOSC_SKLEPOW];
	droga_najlepsza = new Punkt [dane->MAX_ILOSC_SKLEPOW];
	droga_nowa = new Punkt [dane->MAX_ILOSC_SKLEPOW];
	for (int i = 0; i < dane->MAX_ILOSC_SKLEPOW; i++) {
		droga[i] = Punkt (0, 0);
		droga_najlepsza[i] = Punkt(0, 0);
		droga_nowa[i] = Punkt(0, 0);
	}
//	cout << "alg konst koniec" << endl;
}

Algorytm::~Algorytm () {
//	cout << "destruktor algorytmu" << endl;

	delete tabu_prod;
	delete tabu_sklep;

	delete [] droga;
	droga = NULL;
	delete [] droga_najlepsza;
	droga_najlepsza = NULL;
	delete [] droga_nowa;
	droga_nowa = NULL;
//	cout << "destruktor algorytmu koniec" << endl;
}

int Algorytm::Wylicz_Funkcje_Celu(){  // pojemnosc auta nie jest uwzgledniona ani zapotrzebwanie
	int suma=0;
	int k=0, l=0, m=0;
	int i=0;
	if(droga[0].id_prod != 0)
		suma += dane->macierz_odleglosci[0][droga[0].id_sklepu];
	for(i = 0; i < dane->MAX_ILOSC_SKLEPOW-1; i++ ) {
		if (droga[i].id_prod != 0) {
			k = droga[i].id_sklepu;
			m = droga[i].id_prod;
            suma += dane->macierz_cen[k-1][m-1];//zmiana
		}
		if (droga[i+1].id_prod != 0){
			l = droga[i+1].id_sklepu;
			suma += dane->macierz_odleglosci[k][l];
		}
	}
	if (droga[dane->MAX_ILOSC_SKLEPOW-1].id_prod != 0){
		k = droga[i].id_sklepu;
		m = droga[i].id_prod;
		suma += dane->macierz_cen[i][m-1];
	}
	suma += dane->macierz_odleglosci[k][0];
	return suma;
}

void Algorytm::Zamien_Sklep(int i, int j){
    if (i!=j) {
    	Punkt tmp = droga[i];
    	droga[i] = droga[j];
    	droga[j] = tmp;
    }
}

void Algorytm::Zamien_Prod(int i, int j){
    if(i!=j){
    	int tmp = droga[i].id_prod;
    	droga[i].id_prod = droga[j].id_prod;
    	droga[j].id_prod = tmp;
    }
}

//void Algorytm::Zamien_Sklep_Kopia(int i, int j){
//    if(i!=j){
//    	Punkt tmp = droga_kopia[i];
//    	droga_kopia[i] = droga_kopia[j];
//    	droga_kopia[j] = tmp;
//    }
//}

void Algorytm::Przeszukaj_Otoczenie() {
//	int aktualna_wartosc_f_celu = Wylicz_Funkcje_Celu ();
    int nowa_wartosc_f_celu;
    int i_tabu, j_tabu;
	bool zamiana_prod = false;
	// przeszukiwanie otoczenia sklepow
	for (int i = 0; i < dane->MAX_ILOSC_SKLEPOW; i++) {
		for (int j = 0; j < dane->MAX_ILOSC_SKLEPOW; j++) {
			nowa_wartosc_f_celu = 100000;
                if (i != j) {
				Zamien_Sklep (i, j);
				int badana_wartosc_f_celu = Wylicz_Funkcje_Celu ();
				if (badana_wartosc_f_celu < nowa_wartosc_f_celu) {
					if (tabu_sklep->dozwolone(i, j)) {
						nowa_wartosc_f_celu = badana_wartosc_f_celu;
						i_tabu = i;
						j_tabu = j;
						for (int k = 0; k < dane->MAX_ILOSC_SKLEPOW; k++) {
							droga_nowa[k] = droga[k];
						}
					//kryterium aspiracji
					} else if (!tabu_sklep->dozwolone(i, j) && badana_wartosc_f_celu < najlepsza_wartosc_f_celu ) {
						nowa_wartosc_f_celu = badana_wartosc_f_celu;
						i_tabu = i;
						j_tabu = j;
						for (int k = 0; k < dane->MAX_ILOSC_SKLEPOW; k++) {
							droga_nowa[k] = droga[k];
						}
					}
				}
				Zamien_Sklep (i, j);
			}
		}
	}
	//przeszukiwanie otoczenia produktow
	for (int i = 0; i < dane->MAX_ILOSC_SKLEPOW; i++) {
		for (int j = 0; j < dane->MAX_ILOSC_SKLEPOW; j++) {
			if (i != j) {
				Zamien_Prod (i, j);
				int badana_wartosc_f_celu = Wylicz_Funkcje_Celu ();
				if (badana_wartosc_f_celu < nowa_wartosc_f_celu) {
					if (tabu_prod->dozwolone(i, j)) {
						nowa_wartosc_f_celu = badana_wartosc_f_celu;
						i_tabu = i;
						j_tabu = j;
						zamiana_prod = true;
						for (int k = 0; k < dane->MAX_ILOSC_SKLEPOW; k++) {
							droga_nowa[k] = droga[k];
						}
					//kreterium aspiracji
					} else if (!tabu_prod->dozwolone(i, j) && badana_wartosc_f_celu < najlepsza_wartosc_f_celu ) {
						nowa_wartosc_f_celu = badana_wartosc_f_celu;
						i_tabu = i;
						j_tabu = j;
						zamiana_prod = true;
						for (int k = 0; k < dane->MAX_ILOSC_SKLEPOW; k++) {
							droga_nowa[k] = droga[k];
						}
					}
				}
				Zamien_Prod (i, j);
			}
		}
	}
	//uaktualnienie najlepszego wyniku, jesli w danym ot zostal znaleniony lepszy
	if (nowa_wartosc_f_celu < najlepsza_wartosc_f_celu) {
		najlepsza_wartosc_f_celu = nowa_wartosc_f_celu;
		for (int k = 0; k < dane->MAX_ILOSC_SKLEPOW; k++) {
			droga_najlepsza[k] = droga_nowa[k];
		}
	}
	//okreslenie nowego rozw jako najlepsze z danego otoczenia (moze byc gorsze, niz poprzednie)
	for (int k = 0; k < dane->MAX_ILOSC_SKLEPOW; k++) {
		droga[k] = droga_nowa[k];
	}
	//uaktualnienie listy tabu
	if (zamiana_prod) {
		tabu_sklep->wstaw(0, 0);
		tabu_prod->wstaw(i_tabu, j_tabu);
	} else {
		tabu_sklep->wstaw(i_tabu, j_tabu);
		tabu_prod->wstaw(0, 0);
	}
}

void Algorytm::Wczytaj_Droge_Startowa() {
	for (int i = 0; i < dane->MAX_ILOSC_SKLEPOW; i++) {
		droga[i].id_sklepu = dane->droga_startowa[i].id_sklepu;
		droga[i].id_prod = dane->droga_startowa[i].id_prod;
	}
}

void Algorytm::Start () {
//    QFile plik_wyjsciowy;
//    outfile.setFileName("macierz_odleglosci_n.txt");
//    outfile.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream out(&outfile);
//    out << ui->EditDistanceMatrix->toPlainText() << endl;



    fstream plik_wyjsciowy;

    plik_wyjsciowy.open (nazwa_pliczku.toStdString().c_str(), ios::out);

    string p_macierz_odl = nazwa_macierz_odleglosci.toStdString().c_str();
    string p_macierz_cen = nazwa_macierz_cen.toStdString().c_str();
    string p_droga_start = nazwa_wektor_poczatkowy.toStdString().c_str();

    dane->Wczytaj_Macierz_Odleglosci(p_macierz_odl);
	dane->Wczytaj_Macierz_Cen(p_macierz_cen);
	dane->Wczytaj_Droge(p_droga_start);

//	tabu_sklep.DLUGOSC = dane.MAX_DLUGOSC_TABU;
//	tabu_prod.DLUGOSC = dane.MAX_DLUGOSC_TABU;		// tu jest problem!!!

	// jak chce przypisac cos do zmiennej tabu to sie program sypie!! dlaczego???? do naprawy
	Wczytaj_Droge_Startowa();
		cout << "Praca w toku." << endl;

	if (plik_wyjsciowy.good()) {
        cout<< "\nplik wyjsciowy sie robi\n";
        plik_wyjsciowy << "Tabu search v 1.0" << endl;
		plik_wyjsciowy << "\n";

		int ilosc_iteracji = ilosc_iteracji_arg;
		plik_wyjsciowy << "Ilosc iteracji: " << ilosc_iteracji << endl;
		plik_wyjsciowy << "Dlugosc listy tabu: " << tabu_sklep->DLUGOSC << endl;
		plik_wyjsciowy << "Ilosc sklepow: " << ilosc_sklepow_arg << endl;
		plik_wyjsciowy << "Ilosc produktow: " << ilosc_produktow_arg << endl;
		plik_wyjsciowy << "\n\n\n";
		plik_wyjsciowy << "Aktualna wartosc f celu: " << Wylicz_Funkcje_Celu() << endl;
		plik_wyjsciowy << "Aktualna droga: " << endl;
		for(int z = 0 ; z < dane->MAX_ILOSC_SKLEPOW; z++){
			plik_wyjsciowy << "\t("<< droga[z].id_sklepu << ", " << droga[z].id_prod << ")\n";
		}
		for (int i = 0; i < ilosc_iteracji; i++) {
			Przeszukaj_Otoczenie();
          //  parent->getBar().setValue( i/(ilosc_iteracji-1) );
          //  index  = ;

            index = 100*i/(ilosc_iteracji-1);
            bar->setValue(index);
            cout<< i<<endl;
            //->setValue(i/(ilosc_iteracji-1));
			plik_wyjsciowy << i <<"\t" << Wylicz_Funkcje_Celu() << endl;

		}
		plik_wyjsciowy << "Najlepsze rozwiazanie" << endl;
		plik_wyjsciowy << "Najlepsza wartosc f celu: " << najlepsza_wartosc_f_celu << endl;
		plik_wyjsciowy << "Najlepsza droga: " << endl;
		for(int z = 0 ; z < dane->MAX_ILOSC_SKLEPOW; z++){
			plik_wyjsciowy << "\t("<< droga_najlepsza[z].id_sklepu << ", " << droga_najlepsza[z].id_prod << ")\n";
		}
	} else {
		cout << "Blad otwarcia pliku wyjsciowego" << endl;
	}
	cout << "Gotowe! Zobacz plik wyjsciowy." << endl;
}

