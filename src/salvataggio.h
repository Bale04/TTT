#ifndef SAVES_H
#define SAVES_H

#include "costanti.h"
#include "strutture.h"

// Salva lo stato della partita e delle impostazioni su file.
// Ritorna 1 in caso di successo, 0 altrimenti.
int save_game(const Settings *settings, const Game *game);

// Carica lo stato della partita e delle impostazioni da file.
// Ritorna 1 in caso di successo, 0 altrimenti.
int load_game(Settings *settings, Game *game);

// costante per il percorso delle interfacce del salvataggio
const char SAVE_FILE_PATH[] = "C:/Users/Bale/Desktop/git/TTT/Salvataggio/%s";

#endif
