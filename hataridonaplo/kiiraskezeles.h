#ifndef KIIRASKEZELES_H
#define KIIRASKEZELES_H

#include"listakezeles.h"

/**
Konzolosan bekeri az adatokat, nincs parametere
Ha hibas a formatuma("datumcheck" es "idopontcheck"), akkor azt hibauzenettel jelzi, es addig keri ujra az adatot
Amig jo formatumu nem lesz
A hely, nev es megjegyzes tartalmazhat szokozt is
Bovebben kommentelve a fuggvenynel
*/

Adatok* adat_beker();

/**
Menurendszer, nincs parametere
Egy szamot var el bemenetkent
Kiirja a menut, a program nevet, a "MENU" feliratot, a "Valassz az opciok kozul!" uzenetet, es az opciokat
Amik a következõk:
Fajlba iras(1)
Rekord torlese (2)
Rekordok kilistazasa (3)
Kereses a rekordok kozott (4)
Kilepes (5)
Hibasan bekert szam eseten ujrakeri, addig mig megfelelo a szam
*/

void menu();

/**
Kilistazza a fajlban levo adatokat, ev es honapok alapjan csoportositva, datum es idobeli sorrendben
(azonos datum es idopont eseten hozzaadas sorrendjeben kerul sorbarendezesre)
Egy parametere van, "Adatok* adat"
A fuggveny akkor fut le, ha van adat feltoltve a listaba
Bovebben kommentelve a fuggvenynel
*/

Adatok* datum_listazas(Adatok* adat);

#endif
