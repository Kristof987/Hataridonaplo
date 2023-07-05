#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "listakezeles.h"
#include "kiiraskezeles.h"

/**
A fuggveny, visszaadja a keresett elem elotti elemet, ketto parametere van
Az "Adatok* elso" es az "Adatok* keresett"
Ez a fuggveny csak akkor hasznalhato, ha a keresett elem nem az elso
*/

Adatok* elozo_elem(Adatok* elso, Adatok* keresett);

Adatok* torol_fajlbol(Adatok* adat) { //fajlbol torles
    char nev[51];
    printf("Add meg a torlendo esemeny nevet!\n"); //bekerjuk a maximum 50 karakter hosszu nevet
    scanf(" %[^\n]", &nev); //szokozt is tartalmazhat
    if (adat == NULL) //ha nincs adat....
        return NULL;

    Adatok* lemarado = NULL;
    Adatok* mozgo = adat;

    bool volttorles = false; //kiirast segiti
    bool talaltelem = true; //tobb elem torleset segiti es teszi lehetove

    while (mozgo != NULL && talaltelem) //amig van meg a listaban a megadott nevu adat
    {
        while (mozgo != NULL && strcmp(mozgo->nev, nev) != 0) { //amig az adott elem neve nem egyezik meg a keresett elem nevevel
            lemarado = mozgo; //addig lepegetunk tovabb
            mozgo = mozgo->kov;
        }

        if (mozgo == NULL) //ha elertuk a lista veget es nem volt egyezes
        {
            if (!volttorles) //es ha nem volt torles egyaltalan
            {
                printf("Nincs '%s' nevvel elmentett rekord az adatok kozott!\n", &nev); //akkor azt jelezzuk a felhasznalonak
            }
            talaltelem = false; //es mivel nem volt talaltelem, false-ra allitjuk, es kilep a ciklusokbol
        }
        else //ha meg tart a lista
        {
            talaltelem = true;
            volttorles = true;
            if (lemarado == NULL) { //ha az elso elem a torlendo (ha csak egy elem van, akkor ez az eset ervenyesul nyilvanvaloan)
                printf("Elem sikeresen torolve: %4d.%02d.%02d. %02d:%02d \t%s \t%s \t%s \n",
                    mozgo->ev, mozgo->honap, mozgo->nap, mozgo->ora, mozgo->perc, mozgo->hely, mozgo->nev, mozgo->megj);
                Adatok* ujeleje = mozgo->kov;
                mozgo->kov = NULL;
                free(mozgo); //felszabaditas
                adat = ujeleje; //adatot "feltoltjuk"
            }
            else { //ha nem az elso elem
                printf("Elem sikeresen torolve: %4d.%02d.%02d. %02d:%02d \t%s \t%s \t%s \n",
                    mozgo->ev, mozgo->honap, mozgo->nap, mozgo->ora, mozgo->perc, mozgo->hely, mozgo->nev, mozgo->megj);
                lemarado->kov = mozgo->kov;
                mozgo->kov = NULL;
                free(mozgo); //felszabaditas
            }
        }
        lemarado = NULL;
        mozgo = adat;
    }
    return adat;
}

Adatok* nev_kereses(Adatok* adat) {
    if (adat == NULL) //fel kell hogy legyen toltve legalabb egy elemmel
        return NULL;

    Adatok* mozgo;
    mozgo = adat;
    char nev[51]; //esemeny neve
    printf("Add meg a keresendo esemeny nevet!\n");
    scanf(" %[^\n]", &nev);
    bool nemtalalt = true; //"nemtalalt" logikai valtozo
    for (mozgo = adat; mozgo != NULL; mozgo = mozgo->kov) {
        if (strcmp(mozgo->nev, nev) == 0) { //ha megtalaltuk az adott nevu esemenyt
            printf("Az adott rekord: %4d.%02d.%02d.#%02d:%02d#%s#%s#%s\n", //kiirjuk
                mozgo->ev, mozgo->honap, mozgo->nap, mozgo->ora, mozgo->perc, mozgo->hely, mozgo->nev, mozgo->megj);
            nemtalalt = false; //hamisra allitjuk, mivel van talalat
        }
    }
    if (nemtalalt) //ha nincs talalat...
    {
        printf("A megadott nevvel meg nincs mentve adat!\n");
    }
    return adat;
}

Adatok* datumszerint_rendez(Adatok* adat) //hosszabb, osszetettebb fuggveny, tobb kommentel magyarazom
{
    Adatok* uj_elso = NULL; //a rendezett lancolt lista elso elemet
    Adatok* uj_aktualis = NULL; //es a rendezett lancolt lista aktualis elemet is nullazzuk
    if (adat != NULL) //akkor fut, ha van benne adat
    {
        Adatok* regi_elso = adat; //a regi_elso valtozo nyilvan az adatra mutat
        Adatok* elozoelem = NULL; //az elozoelemet nullazzuk
        Adatok* minimum = regi_elso; //minimumkereso fuggvenyhez az elso elemre allitjuk, hiszen onnan indul
        Adatok* aktualis = regi_elso->kov; //az aktualist a kovetkezo elemre allitjuk
        while (regi_elso != NULL) //amig a regi lista elemei tartanak
        {
            minimum = regi_elso; //mivel egy ciklus vegen valtozhat a regi_elso erteke, igy ujbol ertekul kell adni
            aktualis = regi_elso->kov; //ugyanez a kovetkezo elemevel is
            while (aktualis != NULL) //amig van aktualis elem
            {
                if (aktualis->unixido < minimum->unixido) //es ha kisebb...
                {
                    minimum = aktualis; //minimumkereso fuggveny
                }
                aktualis = aktualis->kov; //kovetkezo elemre allitjuk
            }
            if (minimum != regi_elso) //ha a minimum nem az elso elem
            {
                elozoelem = elozo_elem(regi_elso, minimum); //az "elozoelem"-et a minimum elotti elemre allitjuk
                elozoelem->kov = minimum->kov; //a kovetkezot pedig a minimum kovetkezoere
                if (uj_elso == NULL) //ha meg nem volt uj_elso
                {
                    uj_elso = minimum; //akkor a minimum odakerul
                    uj_elso->kov = NULL; //kovetkezo elemet nullazzuk
                    uj_aktualis = uj_elso; //aktualis pedig a minimumrmal elso elemmel) megegyezik
                }
                else //ha mar volt uj_elso
                {
                    uj_aktualis->kov = minimum; //akkor az uj_aktualis kovetkezo eleme lesz, hiszen mar van egy minimum, o "csak" a kovetkezo legkisebb lehet...
                    uj_aktualis = minimum;
                    uj_aktualis->kov = NULL; //nyilvan nullazzuk a kovetkezo elemet
                }
            }
            else //ha a minimum az elso elem
            {
                regi_elso = minimum->kov; //akkor a regi_elso a minimum kovetkezo eleme lesz
                if (uj_elso == NULL) //ugyanaz a magyarazat
                {
                    uj_elso = minimum;
                    uj_elso->kov = NULL;
                    uj_aktualis = uj_elso;
                }
                else //itt is ugyanaz
                {
                    uj_aktualis->kov = minimum;
                    uj_aktualis = minimum;
                    uj_aktualis->kov = NULL;
                }
            }
        }
    }
    return uj_elso;
}

void lista_felszabadit(Adatok* adat) { //a lista felszabaditasa
    Adatok* futo = adat;
    while (futo != NULL) {
        Adatok* lemarado = futo;
        futo = futo->kov;
        free(lemarado);
    }
}

Adatok* elozo_elem(Adatok* elso, Adatok* keresett)
{
    //feltetelezzük hogy a keresett elem nem az elso
    Adatok* aktualis = elso;
    while (aktualis->kov != keresett)
    {
        aktualis = aktualis->kov;
    }
    return aktualis;

}
Adatok* hozzafuz(Adatok* adat, Adatok* uj) { //a mar meglevo adatok (adat) vegehez fuzzuk hozza az uj adatokat (uj)
    if (adat == NULL)
        return uj;

    Adatok* mozgo = adat;

    while (mozgo->kov != NULL)
        mozgo = mozgo->kov;
    mozgo->kov = uj;
    return adat;
}

time_t unixkonverzio(Adatok* adat)
{
    struct tm t;
    time_t t_of_day;

    t.tm_year = adat->ev - 1900;    // ev - 1900
    t.tm_mon = adat->honap - 1;     // honap, ahol 0 = januar
    t.tm_mday = adat->nap;          // nap
    t.tm_hour = adat->ora;          //ora
    t.tm_min = adat->perc;          //perc
    t.tm_sec = 0;                   //masodperc, nem hasznaljuk, de a struktura miatt fontos
    t.tm_isdst = -1;                // nyari idoszamitas? 1 = igen, 0 = nem, -1 = nemtudjuk, a struktura miatt fontos
    return t_of_day = mktime(&t);

}
