#ifndef menu_H
#define menu_H

#include "strutture.h"

// bottoni del menu principale (riga, colonna inizio, colonna fine)
// GIOCA - IMPOSTAZIONI - SUPPORTO - STATISTICHE - ESCI
static AreaCliccabile bMainMenu[] = {{10, 37, 43},{12, 34, 47},{14, 36, 45},{16, 35, 47},{18, 38, 43}};


// vettore delle schermate del menu principale
static Stringa schermateMenu[1] = {{"MenuPrincipale"}};

// costante per il percorso delle interfacce del menu
static const char PERCORSO_MENU[70] = "/home/Bale/GitHub/TTT/Interfacce/MainMenu/%s.txt";

#endif