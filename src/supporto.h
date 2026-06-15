#ifndef supporto_H
#define supporto_H

#include "strutture.h"

// bottoni del menu principale di supporto
const AreaCliccabile bSupRegole = {10, 37, 44};
const AreaCliccabile bSupManuale = {13, 36, 44};
const AreaCliccabile bSupSuggerimenti = {16, 34, 47};
const AreaCliccabile bSupEsci = {19, 38, 43};

// bottone ESCI per Regolamento e Manuale
const AreaCliccabile bSubEsci = {18, 38, 43};

// bottoni per la navigazione dei suggerimenti
const AreaCliccabile bSuggEsci = {22, 5, 10};
const AreaCliccabile bSuggIndietro = {22, 30, 34};
const AreaCliccabile bSuggAvantiP1 = {22, 46, 50};
const AreaCliccabile bSuggAvanti = {22, 47, 51};

// percorso per i file d'interfaccia di supporto
const char PERCORSO_SUPPORTO[70] = "/home/Bale/GitHub/TTT/Interfacce/Supporto/%s.txt";

// Dichiarazione funzione navigazione supporto
void navigaSupporto(void);

#endif /* supporto_H */
