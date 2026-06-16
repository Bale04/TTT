/*
 ============================================================================
 Name        : salvataggio.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 1.0
 Copyright   : Your copyright notice
 Description : file di gestione salvataggio e recupero delle partite
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salvataggio.h"

#pragma region funzioni esterne
// funzioni esterne da impostazioni.c
extern Stringa Get_nomePartita(Impostazioni impostazioni);
extern Stringa Get_partitaPrecedente(Impostazioni impostazioni);
#pragma endregion

// ----------------- GESTIONE FILE SALVATAGGI ------------------
#pragma region gestione file

int salvaPartita(const Impostazioni *impostazioni, const Partita *partita) {
  char percorso[LUNGHEZZA_PERCORSO];
  // Il nome del file è il nome della partita
  sprintf(percorso, PERCORSO_SALVATAGGIO_FILE, Get_nomePartita(*impostazioni).data);
  FILE *fp = fopen(percorso, "wb");
  if (fp == NULL) {
    printf("Errore apertura file per il salvataggio: %s\n", percorso);
    return ESITO_ERRORE;
  }
  fwrite(impostazioni, sizeof(Impostazioni), 1, fp);
  fwrite(partita, sizeof(Partita), 1, fp);
  fclose(fp);
  return ESITO_SUCCESSO;
}

int caricaPartita(Impostazioni *impostazioni, Partita *partita) {
  char percorso[LUNGHEZZA_PERCORSO];
  // Il file da caricare è specificato in partitaPrecedente
  sprintf(percorso, PERCORSO_SALVATAGGIO_FILE, Get_partitaPrecedente(*impostazioni).data);
  FILE *fp = fopen(percorso, "rb");
  if (fp == NULL) {
    printf("Errore apertura file per il caricamento: %s\n", percorso);
    return ESITO_ERRORE;
  }
  fread(impostazioni, sizeof(Impostazioni), 1, fp);
  fread(partita, sizeof(Partita), 1, fp);
  fclose(fp);
  return ESITO_SUCCESSO;
}

#pragma endregion

