/*
 * TabuList.cpp
 *
 *  Created on: 8 gru 2014
 *      Author: M
 */

#include "TabuList.h"

TabuList::TabuList (int dl = 250) {
//    cout << "tabu konst poczatek"<< endl;
	DLUGOSC = dl;
	Lista = new int* [2];
	Lista[0] = new int [DLUGOSC];
	Lista[1] = new int [DLUGOSC];
    for (int i = 0; i < DLUGOSC; i++) {
        Lista[0][i] = 0;
        Lista[1][i] = 0;
    }
//    cout << "tabu konst koniec"<< endl;
}

TabuList::~TabuList () {
//    cout << "tabu dest poczatek"<< endl;
    delete [] Lista[0];
    Lista[0] = NULL;
    delete [] Lista[1];
    Lista[1] = NULL;
    delete [] Lista;
    Lista = NULL;
//    cout << "tabu dest koniec"<< endl;
}

void TabuList::wstaw(int sklep, int prod) {
    for (int i = DLUGOSC - 1; i > 0; i--) {
        Lista[0][i] = Lista [0][i-1];
        Lista[1][i] = Lista [1][i-1];
    }
    Lista[0][0] = sklep;
    Lista[1][0] = prod;
}

bool TabuList::dozwolone(int k, int l) {
    for (int i = 0; i < DLUGOSC; i++) {
        if ((Lista[0][i] == k && Lista[1][i] == l) || (Lista[0][i] == l && Lista[1][i] == k))
            return false;
    }
    return true;
}



