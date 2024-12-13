#ifndef RENTAL_H
#define RENTAL_H

#include "structs.h"
int daysInMonth(int month, int year);
int dateDifference( Date d1, Date d2) ;
int  write_rbloc(TOF *tof, Rblock bloc, int position);
int read_rbloc(TOF *tof, Rblock *bloc, int position);
Rental createRental(Custumer s, Game i, Date f, Date l);
void insert_rent(Rentalf s, TOF *tof, Rblock bloc, int position);
Rentalf searchRental(TOF *tof,Index ren, int id);
void displayRental(const Rental *rental);
void displayRentals(TOF *tof, TOF *ctof, TOF *gtof,Index custindex,Index gameindex);
void addRental(TOF *rfile, TOF *cfile, TOF *gfile,Index cust,Index gami,Index b,char *a);

#endif // RENTAL_H
