#ifndef impostazioni_H
#define impostazioni_H

#include "strutture.h"

// numero massimo di round da giocare
const int MAX_ROUND = 99;



// bottoni per ogni schermata
// NOME - MODE - CARICA - SIMBOLO - ANNULLA - ROUND - ESCI
AreaCliccabile bMenu[] = {{9, 30, 53},  {11, 31, 50}, {13, 34, 49}, {15, 32, 50}, {17, 30, 51}, {19, 30, 50}, {20, 69, 74}};
// G1 - G2 - ESCI
AreaCliccabile bNomi[] = {{12, 35, 46}, {16, 35, 46}, {18, 38, 44}};
// PERSONA - CPU - ESCI
AreaCliccabile bModo[] = {{13, 23, 32}, {13, 54, 58}, {16, 38, 44}};
// NOME - ESCI
AreaCliccabile bCarica[] = {{12, 40, 42}, {14, 38, 44}};
// G1 - G2 - ESCI
AreaCliccabile bSimb[] = {{12, 39, 42}, {16, 39, 42}, {18, 38, 44}};
// SI - NO
AreaCliccabile bAnnulla[] = {{13, 29, 33}, {13, 49, 53}};
// NOME - ROUND - ESCI
AreaCliccabile bRound[] = {{12, 37, 46}, {16, 40, 43}, {18, 38, 44}};


// vettore che carica i nomi delle schermate da visualizzare alla selezione
Stringa schermateImpostazioni[7] = {{"Impostazioni"}, {"NomiGiocatori"}, {"ModalitaDiGioco"},  {"CaricaPartita"}, {"SimboliGiocatori"}, {"AnnullaImpostazioni"}, {"PartitaERound"}};
  

// costante per il percorso delle interfacce delle impostazioni
const char PERCORSO_FILE[70] = "/home/Bale/GitHub/TTT/Interfacce/Impostazioni/%s.txt";

#endif