#ifndef menu_H
#define menu_H

#include "strutture.h"

// bottoni per ogni schermata
// NOME - MODE - CARICA - SIMBOLO - ANNULLA - ROUND - ESCI
AreaCliccabile bMainMenu[] = {{9, 30, 53},  {11, 31, 50}, {13, 34, 49}, {15, 32, 50}, {17, 30, 51}, {19, 30, 50}, {20, 69, 74}};


// costante per il percorso delle interfacce delle impostazioni
const char PERCORSO_MENU[70] = "/home/Bale/GitHub/TTT/Interfacce/MainMenu/%s.txt";

#endif