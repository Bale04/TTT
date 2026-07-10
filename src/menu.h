#ifndef MENU_H
#define MENU_H

#include "costanti.h"
#include "strutture.h"

// bottoni del menu principale (riga, colonna inizio, colonna fine)
// PLAY - SETTINGS - SUPPORT - STATS - EXIT
ClickableArea btn_main_menu[] = {{10, 37, 43},{12, 34, 47},{14, 36, 45},{16, 35, 47},{18, 38, 43}};


// vettore delle schermate del menu principale
String menu_screens[] = {{"MenuPrincipale"}};

// costante per il percorso delle interfacce del menu
const char MENU_PATH[] = "C:/Users/Bale/Desktop/git/TTT/Interfacce/MainMenu/%s.txt";

#endif
