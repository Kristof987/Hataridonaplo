#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "econio.h"
#include "listakezeles.h"
#include "debugmalloc.h"
#include "kiiraskezeles.h"

/**
Harom parametere van
Az egyik az ev(int), a masik a honap(int), a harmadik a nap(int)
Ellenorzi, hogy megfelelo formatumu-e a bemenet, tehat megfelelo-e az ev, a honap es nap
Az ev 1900-nal nagyobb kell, hogy legyen, azert, mert valami also hatart szukseges szabni
A honap 0 es 11 kozott
A nap pedig 1 es 31 kozott
Ha megfelelo, akkor false-al ter vissza
Ha nem, akkor jelzi a rossz formatumot konzolosan, es true-val ter vissza
Az "adat_beker" fuggveny hivja meg
*/

bool datumcheck(int ev, int honap, int nap);

/**
Ket parametere van
Az egyik az ora(int), masik a perc(int)
Ellenorzi, hogy megfelelo formatumu-e a bemenet, tehat megfelelo-e az ora es a perc
Az ora 0 es 23 kozotti kell, hogy legyen
A perc 0 es 59 kozott
Ha megfelelo, akkor false-al ter vissza
Ha nem, akkor jelzi a rossz formatumot konzolosan, es true-val ter vissza
Az "adat_beker" fuggveny hivja meg
*/

bool idopontcheck(int ora, int perc);

Adatok* datum_listazas(Adatok* adat) { //naptarszeruen listazzuk az adatokat
    if (adat == NULL) //fel kell hogy legyen toltve legalabb egy elemmel
        return NULL;
    const char* honapok[] = { //a honapok nevei, hogy a naptarszeru kiiras esztetikusabb legyen
        "Januar" ,
        "Februar",
        "Marcius",
        "Aprilis",
        "Majus",
        "Junius",
        "Julius",
        "Augusztus",
        "Szeptember",
        "Oktober",
        "November",
        "December"
    };

    Adatok* mozgo;
    /**
    megjegyzes: fuggveny meghivasa elott a lancolt listat mar rendeztuk datum szerint
    */
    int aktualisev = adat->ev; //a legkisebb ev
    int aktualishonap = adat->honap;//es ahhoz tartozo legkisebb honap
    printf("***************************** Naptar ******************************\n"); //fejlec
    printf("\n\n***************************** %4d ********************************\n", aktualisev); //a rendezett lancolt litsa legelso eve
    printf("***************************** %s ********************************\n", honapok[aktualishonap - 1]);//honap szovegesen, a rendezett lancolt lista
    //legelso honapja [-1 azert szukseges, mivel a strukturankban a honapok szamozasa 0-val kezdodik]
    for (mozgo = adat; mozgo != NULL; mozgo = mozgo->kov) {
        if (mozgo->ev != aktualisev) //ha uj evbe lepunk
        {
            aktualisev = mozgo->ev;
            aktualishonap = mozgo->honap;
            printf("\n\n***************************** %4d ******************************\n", aktualisev); //ev
            printf("***************************** %s ******************************\n", honapok[aktualishonap - 1]); //honap szovegesen
        }
        else //ha nem lepunk uj evbe,
        {
            if (aktualishonap != mozgo->honap) //de uj honapba igen
            {
                aktualishonap = mozgo->honap;
                printf("***************************** %s ******************************\n", honapok[aktualishonap - 1]);//honap szovegesen
            }
        }
        printf("%4d.%02d.%02d.  %02d:%02d  \t%s \t%s \t%s \n",
            mozgo->ev, mozgo->honap, mozgo->nap, mozgo->ora, mozgo->perc, mozgo->hely, mozgo->nev, mozgo->megj);
    }
    return adat;

}

void menu() {
    printf("\n\t\t\t\t\t\tHATARIDONAPLO\n");
    printf("\t\t\t\t\t\t     MENU\n");
    printf("\t\t\t\t   Valassz az opciok kozul egy SZAM megadasaval!\n\n");
    printf("\t\t\t(1).Hozzaadas \t\t\t(2).Torles   \t\t\t(3).Kilistazas  \n\t\t\t(4).Kereses \t\t\t(5).Kilepes\n");
}

Adatok* adat_beker() { //adatok bekérése
    Adatok* uj = (Adatok*)malloc(sizeof(Adatok)); //dinamikus tomb foglalasa a bekerendo adatoknak
    bool helytelenadat = true;  //a "helytelenadat"-ot true-ra allitjuk
    while (helytelenadat) //amig a datum helytelen
    {
        printf("Adja meg a datumot!\n");
        fseek(stdin, 0, SEEK_END); //lenyegeben clear buffer
        scanf(" %4d.%02d.%02d.", &uj->ev, &uj->honap, &uj->nap); //adatok bekerese
        helytelenadat = datumcheck(uj->ev, uj->honap, uj->nap); //ha helytelen a datum, akkor false-al ter vissza, es a ciklusban marad
    }
    helytelenadat = true; //ha a datum helyes volt, akkor kilep a ciklusbol, ekkor ujra true-ra allitjuk a valtozot
    while (helytelenadat) //amig az idopont helytelen
    {
        printf("Adja meg az idopontot!\n");
        fseek(stdin, 0, SEEK_END); //lenyegeben clear buffer
        scanf(" %02d:%02d", &uj->ora, &uj->perc); //adatok bekerese
        helytelenadat = idopontcheck(uj->ora, uj->perc); //ha helytelen az idopont, akkor false-al ter vissza, es a ciklusban marad
    }
    printf("Adja meg a helyszint!\n"); //bekerjuk a helyszint, stb....
    scanf(" %[^\n]", &uj->hely);    //termeszetesen szokozt is tartalmazhatnak....
    printf("Adja meg az esemeny nevet!\n");
    scanf(" %[^\n]", &uj->nev);
    printf("Megjegyzes:\n");
    scanf(" %[^\n]", &uj->megj);
    uj->unixido = unixkonverzio(uj);  //az unixidot is...
    uj->kov = NULL; //az uj->kov-et NULL-ra allitjuk
    return uj;

}

bool datumcheck(int ev, int honap, int nap)
{
    if (ev > 1900 && honap > 0 && honap < 13 && nap > 0 && nap < 32 ) return false; ///megjegyzes: elso alkalommal azert irtam, hogy ev kisebb, mint 2030, mert
    printf("\nRossz datum formatum!\nA helyes datum formatum a kovetkezo: <yyyy.mm.dd.>\n");///utananeztem, es azt olvastam, hogy 2038-as ev felett tulcsordulas
    return true;                                                                               ///kovetkezik be, ahogy probalgattam, en ilyet nem tapasztaltam
}

bool idopontcheck(int ora, int perc)
{
    if (ora >= 0 && ora < 25 && perc >= 0 && perc < 60) return false;
    printf("\nRossz idopont formatum!\nA helyes idopont formatum a kovetkezo: <hh:mm>\n");
    return true;
}
