#ifndef statistiche_H
#define statistiche_H

#include "strutture.h"

// numero massimo di avversari per pagina nella schermata StatisticheLista
const int AVVERSARI_PER_PAGINA = 5;

// Record avversario: associa un nome avversario alla struttura Statistiche
typedef struct {
    char nomeAvversario[20];
    Statistiche stats;
} RecordAvversario;

// bottoni della schermata StatisticheMenu (RICERCA, ESCI)
AreaCliccabile bStatMenu[] = {{14, 38, 42}, {18, 38, 43}};

// bottoni della schermata StatisticheLista (ESCI, INDIETRO, AVANTI)
AreaCliccabile bLista[] = {{18, 38, 43}, {20, 5, 9}, {20, 73, 76}};

// nomi delle schermate
Stringa schermateStatistiche[2] = {{"StatisticheMenu"}, {"StatisticheLista"}};

// percorso interfacce statistiche
const char PERCORSO_STATISTICHE[80] = "/home/Bale/GitHub/TTT/Interfacce/Statistiche/%s.txt";

// percorso file statistiche salvate
const char PERCORSO_STATS_SALVATE[80] = "/home/Bale/GitHub/TTT/StatisticheSalvate/%s";

// Dichiarazione funzioni
void navigaStatistiche(void);
void salvaStatistichePartita(const char *nomeG1, const char *nomeG2, int risultato);

#endif
