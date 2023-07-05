#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#include "debugmalloc.h"
#include "fajlkezeles.h"
#include "kiiraskezeles.h"
#include "listakezeles.h"


int main(void)
{
    econio_clrscr(); //a kepernyot toroljuk
    Adatok* adat = NULL;
    Adatok* tmp = NULL;
    menu(); //meghivjuk a menurendszert
    int c;
    scanf("%d",&c); //bekerunk egy szamot (fontos, hogy szamot adjunk meg)
    adat = beolv(); //az adatokat beolvassuk fajlbol
    /**A funkcio vegrehajtasa utan egy karakter megadasaval juthatunk vissza a menube*/
    while (c != 5) { //switch-case 1-tol 5-ig
        switch (c) {
        case 1: //fajlba iras
            tmp = adat_beker(); //adatok bekerese konzolrol
            adat = hozzafuz(adat, tmp); //ket lista osszefuzese
            break;
        case 2: //fajlbol torles
            adat = torol_fajlbol(adat);
            break;
        case 3: //listazas
            adat = datumszerint_rendez(adat); //adatok rendezese datum (unix time) szerint
            econio_clrscr(); //esztetikus megjelenes miatt clear screen
            adat = datum_listazas(adat); //majd datum szerinti naptarszeru megjelenites
            break;
        case 4: //kereses a rekordok kozott
            adat = nev_kereses(adat);
            break;
        case 5: exit(0); //kilepes, erre kulon fuggveny felesleges...
            break;
        default: //ha rossz szamot ad meg, hibauzenettel jelezzuk es ujra bekerjuk a szamot
            printf("Hibas karakter\n");
            printf("1-6 kozotti szamokat adj meg!\n");
            printf("Nyomj meg egy gombot a menube valo visszatereshez!");
        }
        if (c != 5) {
            getch();
            econio_clrscr();
            menu();
            scanf("%d", &c);
        }
    }
    fajlba_kiir(adat); //ha a funkciok lefutottak, a fajlt frissitjuk, kiiratjuk oda a lista elemeit
    lista_felszabadit(adat); //fel kell szabaditanunk a listat
    return 0;
}
