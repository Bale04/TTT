#ifndef supporto_H
#define supporto_H

#include "strutture.h"

// bottoni del menu principale di supporto
static const AreaCliccabile bSupRegole = {10, 37, 44};
static const AreaCliccabile bSupManuale = {13, 36, 44};
static const AreaCliccabile bSupSuggerimenti = {16, 34, 47};
static const AreaCliccabile bSupEsci = {19, 38, 43};

// bottone ESCI per Regolamento e Manuale
static const AreaCliccabile bSubEsci = {18, 38, 43};

// bottoni per la navigazione dei suggerimenti
static const AreaCliccabile bSuggEsci = {22, 5, 10};
static const AreaCliccabile bSuggIndietro = {22, 30, 34};
static const AreaCliccabile bSuggAvantiP1 = {22, 46, 50};
static const AreaCliccabile bSuggAvanti = {22, 47, 51};

// percorso per i file d'interfaccia di supporto
static const char PERCORSO_SUPPORTO[70] = "/home/Bale/GitHub/TTT/Interfacce/Supporto/%s.txt";

// Dichiarazione funzione navigazione supporto
void navigaSupporto(void);

#endif /* supporto_H */
