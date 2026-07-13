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
extern String get_game_name(Settings settings);
extern String get_previous_game(Settings settings);
#pragma endregion

// ----------------- GESTIONE FILE SALVATAGGI ------------------
#pragma region gestione file

int save_game(const Settings *settings, const Game *game)
{
  char path[PATH_LENGTH];
  FILE *fp;

  // Il nome del file e' il nome della partita
  sprintf(path, SAVE_FILE_PATH, get_game_name(*settings).data);
  fp = fopen(path, "wb");
  if (fp == NULL) {
    printf("Errore apertura file per il salvataggio: %s\n", path);
    return STATUS_ERROR;
  }
  fwrite(settings, sizeof(Settings), 1, fp);
  fwrite(game, sizeof(Game), 1, fp);
  fclose(fp);
  return STATUS_SUCCESS;
}

int load_game(Settings *settings, Game *game)
{
  char path[PATH_LENGTH];
  FILE *fp;

  // Il file da caricare e' specificato in previous_game
  sprintf(path, SAVE_FILE_PATH, get_previous_game(*settings).data);
  fp = fopen(path, "rb");
  if (fp == NULL) {
    printf("Errore apertura file per il caricamento: %s\n", path);
    return STATUS_ERROR;
  }
  fread(settings, sizeof(Settings), 1, fp);
  fread(game, sizeof(Game), 1, fp);
  fclose(fp);
  return STATUS_SUCCESS;
}

#pragma endregion
