#ifndef STATS_H
#define STATS_H

#include "costanti.h"
#include "strutture.h"

// numero massimo di avversari per pagina nella schermata StatsList
const int OPPONENTS_PER_PAGE = 5;

// associa un nome avversario alla struttura Stats
typedef struct {
    char opponent_name[STRING_LENGTH];
    Stats stats;
} OpponentRecord;

// bottoni della schermata StatsMenu (RICERCA, ESCI)
ClickableArea btn_stat_menu[] = {{14, 38, 42}, {18, 38, 43}};

// ESCI - INDIETRO - AVANTI
ClickableArea btn_list[] = {{18, 38, 43}, {20, 5, 9}, {20, 73, 76}};

// nomi delle schermate
String stats_screens[] = {{"StatisticheMenu"}, {"StatisticheLista"}};

// percorso interfacce statistiche
const char STATS_PATH[] = "C:/Users/Bale/Desktop/git/TTT/Interfacce/Statistiche/%s.txt";

// percorso file statistiche salvate
const char SAVED_STATS_PATH[] = "C:/Users/Bale/Desktop/git/TTT/StatisticheSalvate/%s";

// Dichiarazione funzioni
void navigate_stats(void);
void save_game_stats(const char *p1_name, const char *p2_name, int result);

#endif
