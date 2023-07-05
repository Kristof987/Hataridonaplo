#ifndef LISTAKEZELES_H
#define LISTAKEZELES_H

#include <time.h>

/**
"Adatok" nevu lancolt lista tipus, 9+1 parameterrel
ev (int): a datum evet tarolja
honap (int): a datum honapjat tarolja
nap (int): a datum napjat tarolja
ora (int): az idopont orajat tarolja
perc (int): a dz idopont percet tarolja
unixtimestamp (time_t): a datumot es idopontot tarolja "unix time" kodolassal
hely (string): az esemeny helyet tarolja, maximum 50 karakter hosszu
nev (string):  az esemeny nevet tarolja, maximum 50 karakter hosszu
megj (string):  az esemenyhez tartozo megjegyzest tarolja, max 100 karakter hosszu
*/

typedef struct Adatok { //láncolt lista létrehozása
    int ev;
    int honap;
    int nap;
    int ora;
    int perc;
    time_t unixido;
    char hely[51];
    char nev[51];
    char megj[101];
    struct Adatok* kov;
}Adatok;

/**
A fuggveny visszater az 1900 ota eltelt masodpercek szamaval, 1 parametere az "Adatok* adat"
Egy beepitett strukturat hasznal, ami a datumok es idopontok tipusait tartalmaz
Mindegyik egész típusú
Az év minimum 1900 kell, hogy legyen
A hónapokat 0-tól 11-ig számoljuk
Masodperc, nyari idoszamitas nem fontos...
*/

time_t unixkonverzio(Adatok* adat);

/**
A "hozzafuz" fuggveny osszefuz ket lancolt listat, 2 parametere van
"Adatok* adat" parameterhez hozzafuzi az "Adatok* uj" parametert
Lekezeli azokat az eseteket is, ha az "Adatok *adat" lista ures, vagy mar adatokkal rendelkezik
*/

Adatok* hozzafuz(Adatok* adat, Adatok* uj);

/**
Felszabaditja a listat, 1 parametere van, a felszabaditando "Adatok* adat"
Ha nem volt meg adat a listaban, akkor csak a hozzafuzendo "Adatok* uj"-jal ter vissza
Ha mar volt adat benne, akkor a vegehez hozzafuzi
*/

void lista_felszabadit(Adatok* adat);

/**
Rendezi a listat a unix time-ba konvertalt datum alapjan, 1 parametere van, az "Adatok *adat"
A fuggveny akkor fut le, ha van adat feltoltve a listaba
Lekezeli azokat az eseteket is, amikor az eppen rendezendo lista legelso eleme a legkisebb, es azt is ha nem
Bovebben a "listakezeles.c" reszben kommentekkel jelezve
*/

Adatok* datumszerint_rendez(Adatok* adat);

/**
Torli a lancolt lista egy elemet (amire nev alapjan keresunk ra), 1 parametere van, az "Adatok* adat"
A fuggveny akkor fut le, ha van adat feltoltve a listaba
A fuggveny eloszor beker a felhasznalotol egy maximum 50 karakterbol allo nevet
Ha a listaban van olyan nevu esemeny, akkor torli
Lekezeli azokat az eseteket is, ha a lancolt lista elso eleme a torlendo, es azt is ha nem
Ha tobb azonos nevu adat van megadva, akkor mindegyiket torli
Bovebben a "listakezeles.c" reszben kommentekkel jelezve
*/

Adatok* torol_fajlbol(Adatok* adat);

/**
Megkeresi a lancolt lista egy elemet (amire nev alapjan keresunk ra), 1 parametere van, az "Adatok* adat"
A fuggveny akkor fut le, ha van adat feltoltve a listaba
A fuggveny eloszor beker a felhasznalotol egy maximum 50 karakterbol allo nevet
Ha a listaban van olyan nevu esemeny, akkor kilistazza
Ha nincs, akkor jelzi uzenettel
Lekezeli azokat az eseteket is, amikor tobb esemeny azonos neven van mentve
*/

Adatok* nev_kereses(Adatok* adat);

#endif
