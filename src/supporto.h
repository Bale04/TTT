#ifndef supporto_H
#define supporto_H

#include "strutture.h"

// REGOLE - MANUALE - SUGGERIMENTI - ESCI
AreaCliccabile bSupporto[] = {{10, 37, 44}, {13, 36, 44}, {16, 34, 47}, {19, 38, 43}};

// ESCI
AreaCliccabile bManuale = {18, 38, 43};

// ESCI - INDIETRO - AVANTI
AreaCliccabile bSuggerimenti[] = {{22, 5, 10}, {22, 30, 34}, {22, 46, 50}};

// percorso per i file d'interfaccia di supporto
const char PERCORSO_SUPPORTO[70] = "C:/Users/Bale/Desktop/git/TTT/Interfacce/Supporto/%s.txt";

// Dichiarazione funzione navigazione supporto
void navigaSupporto(void);

#endif /* supporto_H */
