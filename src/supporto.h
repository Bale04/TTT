#ifndef SUPPORT_H
#define SUPPORT_H

#include "costanti.h"
#include "strutture.h"

// RULES - MANUAL - TIPS - EXIT
ClickableArea btn_support[] = {{10, 37, 44}, {13, 36, 44}, {16, 34, 47}, {19, 38, 43}};

// EXIT
ClickableArea btn_manual = {18, 38, 43};

// EXIT - BACK - FORWARD
ClickableArea btn_tips[] = {{22, 5, 10}, {22, 30, 34}, {22, 46, 50}};

// percorso per i file d'interfaccia di supporto
const char SUPPORT_PATH[] = "C:/Users/Bale/Desktop/git/TTT/Interfacce/Supporto/%s.txt";

// Dichiarazione funzione navigazione supporto
void navigate_support(void);

#endif
