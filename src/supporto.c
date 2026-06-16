/*
 ============================================================================
 Name        : supporto.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Copyright   : Your copyright notice
 Description : file di gestione delle schermate con il manuale di supporto sul gioco 
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supporto.h"
#include "mouse.h"

// ----------------- STAMPA SCHERMATA ------------------
#pragma region stampa

// Funzione interna per stampare un file di interfaccia (.txt)
void stampaSchermataSupporto(const char *nomeSchermata) {
  FILE *fp;
  int c;
  char nomeCompleto[256];

  sprintf(nomeCompleto, PERCORSO_SUPPORTO, nomeSchermata);
  fp = fopen(nomeCompleto, "r");
  if (fp == NULL) {
    printf("Errore caricamento schermata supporto: %s\n", nomeCompleto);
  } else {
    while ((c = fgetc(fp)) != EOF) {
      putchar(c);
    }
    fclose(fp);
    printf("\n");
  }
}

#pragma endregion

// --------------------- NAVIGAZIONE SUPPORTO -----------------------------
#pragma region navigazione

// Funzione principale di navigazione del supporto
void navigaSupporto(void) {
  int riga, colonna;
  int esciSupporto = 0;
  // schermata: PAGINA_SUPPORTO_MAIN = Supporto principale, PAGINA_SUPPORTO_REGOLAMENTO = Regolamento, PAGINA_SUPPORTO_MANUALE = Manuale, PAGINA_SUPPORTO_SUGGERIMENTI = Suggerimenti
  int schermata = PAGINA_SUPPORTO_MAIN;
  int pagSuggerimento = PAGINA_SUGGERIMENTO_INIZIALE;

  // abilita il mouse per la navigazione interattiva
  abilitaMouse();

  while (!esciSupporto) {
    // pulisce il terminale
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif

    // stampa la schermata corretta
    if (schermata == PAGINA_SUPPORTO_MAIN) {
      stampaSchermataSupporto("Supporto");
    } else if (schermata == PAGINA_SUPPORTO_REGOLAMENTO) {
      stampaSchermataSupporto("Regolamento");
    } else if (schermata == PAGINA_SUPPORTO_MANUALE) {
      stampaSchermataSupporto("Manuale");
    } else if (schermata == PAGINA_SUPPORTO_SUGGERIMENTI) {
      char nomeSuggerimento[LUNGHEZZA_NOME_SUGGERIMENTO];
      sprintf(nomeSuggerimento, "Suggerimenti%d", pagSuggerimento);
      stampaSchermataSupporto(nomeSuggerimento);
    }

    goTo(CURSORE_BASE.col, CURSORE_BASE.rig);
    fflush(stdout);

    // attende ed acquisisce il click del mouse
    if (!leggiClick(&riga, &colonna)) {
      continue;
    }

    // gestione della navigazione in base alla schermata corrente
    if (schermata == PAGINA_SUPPORTO_MAIN) {
      // Menu Principale del Supporto
      if (areaCliccata(bSupporto[0], riga, colonna)) {
        schermata = PAGINA_SUPPORTO_REGOLAMENTO;
      } else if (areaCliccata(bSupporto[1], riga, colonna)) {
        schermata = PAGINA_SUPPORTO_MANUALE;
      } else if (areaCliccata(bSupporto[2], riga, colonna)) {
        schermata = PAGINA_SUPPORTO_SUGGERIMENTI;
        pagSuggerimento = PAGINA_SUGGERIMENTO_INIZIALE;
      } else if (areaCliccata(bSupporto[3], riga, colonna)) {
        esciSupporto = 1;
      }
    } else if (schermata == PAGINA_SUPPORTO_REGOLAMENTO) {
      // Regolamento
      if (areaCliccata(bManuale, riga, colonna)) {
        schermata = PAGINA_SUPPORTO_MAIN;
      }
    } else if (schermata == PAGINA_SUPPORTO_MANUALE) {
      // Manuale
      if (areaCliccata(bManuale, riga, colonna)) {
        schermata = PAGINA_SUPPORTO_MAIN;
      }
    } else if (schermata == PAGINA_SUPPORTO_SUGGERIMENTI) {
      // Suggerimenti (pagine 1 a 5)
      if (areaCliccata(bSuggerimenti[0], riga, colonna)) {
        schermata = PAGINA_SUPPORTO_MAIN;
      } else if (pagSuggerimento > PAGINA_SUGGERIMENTO_INIZIALE && areaCliccata(bSuggerimenti[1], riga, colonna)) {
        pagSuggerimento = pagSuggerimento - 1;
      } else if (pagSuggerimento < PAGINA_SUGGERIMENTO_FINALE && areaCliccata(bSuggerimenti[2], riga, colonna)) {
        pagSuggerimento = pagSuggerimento + 1;
      }
    }
  }

  // ripristina la modalità terminale
  abilitaTastiera();
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

#pragma endregion
