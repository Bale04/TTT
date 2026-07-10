#ifndef SETTINGS_H
#define SETTINGS_H

#include "costanti.h"
#include "strutture.h"

// numero massimo di round da giocare
const int MAX_ROUNDS = 99;

// bottoni per ogni schermata
// NAME - MODE - LOAD - SYMBOL - UNDO - ROUND - EXIT
ClickableArea btn_menu[] = {{9, 30, 53},  {11, 31, 50}, {13, 34, 49}, {15, 32, 50}, {17, 30, 51}, {19, 30, 50}, {20, 69, 74}};
// P1 - P2 - EXIT
ClickableArea btn_names[] = {{12, 35, 46}, {16, 35, 46}, {18, 38, 44}};
// PLAYER - CPU - EXIT
ClickableArea btn_mode[] = {{13, 23, 32}, {13, 54, 58}, {16, 38, 44}};
// NAME - EXIT
ClickableArea btn_load[] = {{12, 40, 42}, {14, 38, 44}};
// P1 - P2 - EXIT
ClickableArea btn_symbols[] = {{12, 39, 42}, {16, 39, 42}, {18, 38, 44}};
// YES - NO
ClickableArea btn_undo[] = {{13, 29, 33}, {13, 49, 53}};
// NAME - ROUND - EXIT
ClickableArea btn_round[] = {{12, 37, 46}, {16, 40, 43}, {18, 38, 44}};

// vettore che carica i nomi delle schermate da visualizzare alla selezione
String settings_screens[] = {{"Impostazioni"}, {"NomiGiocatori"}, {"ModalitaDiGioco"},  {"CaricaPartita"}, {"SimboliGiocatori"}, {"AnnullaImpostazioni"}, {"PartitaERound"}};


// costante per il percorso delle interfacce delle impostazioni
const char FILE_PATH[] = "C:/Users/Bale/Desktop/git/TTT/Interfacce/Impostazioni/%s.txt";

#endif
