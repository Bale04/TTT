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
void print_support_screen(const char *screen_name)
{
  FILE *fp;
  int ch;
  char full_name[PATH_LENGTH];

  sprintf(full_name, SUPPORT_PATH, screen_name);
  fp = fopen(full_name, "r");
  if (fp == NULL) {
    printf("Errore caricamento schermata supporto: %s\n", full_name);
  } else {
    while ((ch = fgetc(fp)) != EOF) {
      putchar(ch);
    }
    fclose(fp);
    printf("\n");
  }
}

#pragma endregion

// --------------------- NAVIGAZIONE SUPPORTO -----------------------------
#pragma region navigazione

// Funzione principale di navigazione del supporto
void navigate_support(void)
{
  int row;
  int col;
  int quit_support;
  int screen;
  int tip_page;
  char tip_name[HINT_NAME_LENGTH];

  quit_support = 0;
  screen = HELP_PAGE_MAIN;
  tip_page = TIP_PAGE_FIRST;

  // abilita il mouse per la navigazione interattiva
  enable_mouse();

  while (!quit_support) {
    // pulisce il terminale
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif

    // stampa la schermata corretta
    if (screen == HELP_PAGE_MAIN) {
      print_support_screen("Supporto");
    } else if (screen == HELP_PAGE_RULES) {
      print_support_screen("Regolamento");
    } else if (screen == HELP_PAGE_MANUAL) {
      print_support_screen("Manuale");
    } else if (screen == HELP_PAGE_TIPS) {
      sprintf(tip_name, "Suggerimenti%d", tip_page);
      print_support_screen(tip_name);
    }

    goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
    fflush(stdout);

    // attende ed acquisisce il click del mouse
    if (!read_click(&row, &col)) {
      continue;
    }

    // gestione della navigazione in base alla schermata corrente
    if (screen == HELP_PAGE_MAIN) {
      // Menu Principale del Supporto
      if (is_area_clicked(btn_support[0], row, col)) {
        screen = HELP_PAGE_RULES;
      } else if (is_area_clicked(btn_support[1], row, col)) {
        screen = HELP_PAGE_MANUAL;
      } else if (is_area_clicked(btn_support[2], row, col)) {
        screen = HELP_PAGE_TIPS;
        tip_page = TIP_PAGE_FIRST;
      } else if (is_area_clicked(btn_support[3], row, col)) {
        quit_support = 1;
      }
    } else if (screen == HELP_PAGE_RULES) {
      // Regolamento
      if (is_area_clicked(btn_manual, row, col)) {
        screen = HELP_PAGE_MAIN;
      }
    } else if (screen == HELP_PAGE_MANUAL) {
      // Manuale
      if (is_area_clicked(btn_manual, row, col)) {
        screen = HELP_PAGE_MAIN;
      }
    } else if (screen == HELP_PAGE_TIPS) {
      // Suggerimenti (pagine 1 a 5)
      if (is_area_clicked(btn_tips[0], row, col)) {
        screen = HELP_PAGE_MAIN;
      } else if (tip_page > TIP_PAGE_FIRST && is_area_clicked(btn_tips[1], row, col)) {
        tip_page = tip_page - 1;
      } else if (tip_page < TIP_PAGE_LAST && is_area_clicked(btn_tips[2], row, col)) {
        tip_page = tip_page + 1;
      }
    }
  }

  // ripristina la modalita' terminale
  enable_keyboard();
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

#pragma endregion
