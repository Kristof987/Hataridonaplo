#ifndef FAJLKEZELES_H
#define FAJLKEZELES_H

#include"listakezeles.h"

/**
A fuggveny kiirja a lancolt lista elemeit egy "szoveg.txt" nevu fajlba, 1 parametere van, az "Adatok* adat"
Fontos, hogy a fuggveny csak akkor kerul meghivasra, ha a menuben torteno kulonbozo funkciok hasznalata utan
A felhasznalo ugy dont, hogy kilep a programbol
Ekkor kerul az adott lancolt lista kiirasra a fajlba
Ha nincs benne adat, akkor azt jelezzuk uzenettel
Tovabbi kommentek a fuggvenynel
*/

void fajlba_kiir(Adatok* adat);

/**
A fuggveny beolvassa a fajlbol a rekordokat es betolti a lancolt listaba
A fuggveny mar a program megnyitasakor meghivasra kerul, hiszen minden funkcio (kiveve a kilepes) hasznalatahoz
Szukseg van a fajlbol az adatok betoltesere

*/

Adatok* beolv();

#endif
