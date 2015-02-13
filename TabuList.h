/*
 * TabuList.h
 *
 *  Created on: 8 gru 2014
 *      Author: M
 */

#ifndef TABULIST_H_
#define TABULIST_H_

#include "Dane.h"

class TabuList {
public:
	int DLUGOSC;
    int** Lista;

    TabuList(int);
    ~TabuList();

    void wstaw (int, int);
    bool dozwolone (int, int);
};

#endif /* TABULIST_H_ */
