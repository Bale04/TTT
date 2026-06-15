#ifndef salvataggio_H
#define salvataggio_H

#include "strutture.h"

// Salva lo stato della partita e delle impostazioni su file.
// Ritorna 1 in caso di successo, 0 altrimenti.
int salvaPartita(const Impostazioni *impostazioni, const Partita *partita);

// Carica lo stato della partita e delle impostazioni da file.
// Ritorna 1 in caso di successo, 0 altrimenti.
int caricaPartita(Impostazioni *impostazioni, Partita *partita);

#endif