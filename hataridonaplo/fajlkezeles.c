#include <stdio.h>
#include <stdlib.h>

#include "debugmalloc.h"
#include "fajlkezeles.h"
#include "econio.h"

void fajlba_kiir(Adatok* adat) {//fileba iras
    econio_clrscr; //elotte a kepernyot toroljuk

    if (adat == NULL) { //ha nincs adat
        printf("Az adatallomany ures\n");
    }

    remove("szoveg.txt");

    FILE* f = fopen("szoveg.txt", "wb"); //file megnyitása írásra
    if (f == NULL) {
        perror("Fajl megnyitasa sikertelen!"); //hibauzenet
        return;
    }

    Adatok* a = adat;

    while (a != NULL) { //amig tart a lista
        fprintf(f, "%4d.%02d.%02d.#", a->ev, a->honap, a->nap); //rekordok kiírása a megfelelõ formátumban, #-el elvalasztva, egy sorban
        fprintf(f, "%02d:%02d#", a->ora, a->perc);
        fprintf(f, "%s#", a->hely);
        fprintf(f, "%s#", a->nev);
        fprintf(f, "%s\n", a->megj); //kovetkezo rekord, kovetkezo sor
        a = a->kov;
    }
    printf("A rekordok elmentesre kerultek.\n"); //ha sikeresen elmentettük, azt jelezzük
    fclose(f); // a fajlt lezarjuk
}

Adatok* beolv() { //fajlbol beolvas
    Adatok* adat = NULL;

    FILE* f = fopen("szoveg.txt", "rt"); //file megnyitasa olvasasra
    if (f == NULL) { //ha nem sikerult...
        return NULL;
    }
    char sor[301];
    while (fgets(sor, 301, f)) { //sor beolvasasa
        sor[strcspn(sor, "\n")] = 0; //de az fgets a sorvegi entert is beteszi a sztringbe, igy azt feltoljuk 0-val
        Adatok* uj = (Adatok*)malloc(sizeof(Adatok)); //dinamikus tomb foglalasa
        char* datas = strtok(sor, "#"); //a sor darabolasa #-ek menten
        sscanf(datas, "%4d.%02d.%02d.", &uj->ev, &uj->honap, &uj->nap); //eloszor a datumot olvassuk be
        datas = strtok(NULL, "#"); // darabolunk elso #-ig
        sscanf(datas, "%02d:%02d", &uj->ora, &uj->perc); //majd az idopontot
        uj->unixido = unixkonverzio(uj); //unixidore szuksegunk van, konvertalunk
        datas = strtok(NULL, "#"); //darabolas
        if (NULL != datas) //ha irtunk be adatot
        {
            sscanf(datas, "%[^\n]", &uj->hely); //beolvasunk
        }
        else
        {
            for (int i = 0; i < 51; i++) {
                uj->hely[i] = 0; //ha nincs adat 0-val feltoltjuk
            }
        }
        datas = strtok(NULL, "#");
        if (NULL != datas) //ha irtunk be adatot
        {
            sscanf(datas, "%[^\n]", &uj->nev); //beolvasunk
        }
        else
        {
            for (int i = 0; i < 51; i++) {
                uj->nev[i] = 0; //ha nincs adat 0-val feltoltjuk
            }
        }
        datas = strtok(NULL, "#");
        if (NULL != datas)//ha irtunk be adatot
        {
            sscanf(datas, "%[^\n]", &uj->megj); //beolvasunk
        }
        else
        {
            for (int i = 0; i < 101; i++) {
                uj->megj[i] = 0; //ha nincs adat 0-val feltoltjuk
            }
        }
        if (adat == NULL) //ha nincs adat a listaban
        {
            adat = (Adatok*)malloc(sizeof(Adatok)); //dinamikus tomb foglalasa
            adat->ev = uj->ev; //lenyegeben a beolvasott adat kerul a lancolt listaba
            adat->honap = uj->honap; //es igy tovabb
            adat->nap = uj->nap;
            adat->ora = uj->ora;
            adat->perc = uj->perc;
            adat->unixido = uj->unixido;
            strcpy(adat->nev, uj->nev);
            strcpy(adat->hely, uj->hely);
            strcpy(adat->megj, uj->megj);
            adat->kov = NULL;
            free(uj); //fontos hogy fel kell szabaditani a listat
        }
        else
        {
            hozzafuz(adat, uj); //ha mar volt adat a listaban, akkor utana fuzzuk hozza a beolvasott adatot
            uj->kov = NULL;
        }
    }
    fclose(f); //le kell zarni a fajlt
    return adat;
}
