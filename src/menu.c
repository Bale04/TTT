/*
 ============================================================================
 Name        : menu.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 1.0 
 Copyright   : Your copyright notice
 Description : file di gestione del menu principale
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// struttura della gestione delle stringhe, impostazioni e aree cliccabili
#include "strutture.h"
// libreria condivisa per mouse e cursore
#include "mouse.h"
#include "menu.h"

#pragma region funzioni esterne
// funzioni esterne da supporto.c
extern void navigate_support(void);

// funzioni esterne da impostazioni.c
extern void navigate_settings(Settings *settings);
extern void reset_settings(Settings *settings);
extern String get_game_name(Settings settings);

// funzioni esterne da gioco.c
extern void navigate_game(Game *game, Settings *settings);

// funzioni esterne da statistiche.c
extern void navigate_stats(void);
#pragma endregion

#pragma region dichiarazioni funzioni
// funzioni locali
void print_menu_screen(String s);
void navigate_menu(Settings *settings);
#pragma endregion

#pragma region main

int main()
{
  // le impostazioni vengono create una sola volta e persistono per tutto il programma
  Settings settings;
  reset_settings(&settings);

  // avvia la navigazione del menu principale
  navigate_menu(&settings);

  return EXIT_SUCCESS;
}

#pragma endregion

// ----------------- STAMPA SCHERMATA MENU ------------------
#pragma region stampa

void print_menu_screen(String s)
{
  FILE *fp;
  int ch;
  char full_name[PATH_LENGTH];

  sprintf(full_name, MENU_PATH, s.data);
  fp = fopen(full_name, "r");
  if (fp == NULL) {
    printf("Errore caricamento schermata menu: %s\n", full_name);
  } else {
    while ((ch = fgetc(fp)) != EOF) {
      putchar(ch);
    }
    fclose(fp);
  }
}

#pragma endregion

// --------------------- NAVIGAZIONE MENU PRINCIPALE -----------------------------
#pragma region navigazione

void navigate_menu(Settings *settings)
{
  int quit;
  int row;
  int col;
  Game game;

  quit = 0;

  // abilita il mouse tramite la libreria mouse.h
  enable_mouse();

  while (!quit) {
    // pulisce il terminale
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif

    // stampa la schermata del menu principale
    print_menu_screen(menu_screens[MAIN_MENU_INDEX]);
    goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
    fflush(stdout);

    // legge il click dell'utente
    if (!read_click(&row, &col)) {
      continue;
    }

    // gestione click sui bottoni del menu
    if (is_area_clicked(btn_main_menu[0], row, col)) {
      // tasto gioca
      enable_keyboard();
      navigate_game(&game, settings);
      // quando il gioco termina si torna al menu
      enable_mouse();
    } else if (is_area_clicked(btn_main_menu[1], row, col)) {
      // apre le impostazioni
      enable_keyboard();
      navigate_settings(settings);
      // quando si preme ESCI dalla schermata principale delle impostazioni si torna qui
      enable_mouse();
    } else if (is_area_clicked(btn_main_menu[2], row, col)) {
      // apre il supporto
      enable_keyboard();
      navigate_support();
      enable_mouse();
    } else if (is_area_clicked(btn_main_menu[3], row, col)) {
      // apre le statistiche
      enable_keyboard();
      navigate_stats();
      enable_mouse();
    } else if (is_area_clicked(btn_main_menu[4], row, col)) {
      // esce dal programma
      quit = 1;
    }
  }

  // ripristina il terminale
  enable_keyboard();
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
  printf("Arrivederci!\n");
}

#pragma endregion
