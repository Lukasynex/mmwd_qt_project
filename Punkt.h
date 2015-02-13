/*
 * Punkt.h
 *
 *  Created on: 8 gru 2014
 *      Author: M
 */

#ifndef PUNKT_H_
#define PUNKT_H_

#include "Dane.h"

class Punkt {
public:
    int id_sklepu;
    int id_prod;

    Punkt (int sklep = 0, int prod = 0){
        id_sklepu = sklep;
        id_prod = prod;
    }
    Punkt (const Punkt& pkt) {
    	id_sklepu = pkt.id_sklepu;
    	id_prod = pkt.id_prod;
    }
    Punkt & operator = (const Punkt& pkt) {
    	if (this == &pkt)
    		return *this;
    	id_sklepu = pkt.id_sklepu;
    	id_prod = pkt.id_prod;
    	return *this;
    }
};


#endif /* PUNKT_H_ */
