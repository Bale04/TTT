/*
 ============================================================================
 Name        : impostazioni.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 1.0 
 Copyright   : Your copyright notice
 Description : file di gestione delle impostazioni di gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// struttura della gestione delle stringhe, impostazioni e aree cliccabili
#include "impostazioni.h"
#include "costanti.h"
// libreria condivisa per mouse e cursore
#include "mouse.h"

void reset_settings(Settings *settings);

// DEFINIZIONE FUNZIONI DI ACCESSO
#pragma region definizione funzioni di accesso
void set_game_mode(int m, Settings *settings);
int get_game_mode(Settings settings);
void set_player1_name(String n1, Settings *settings);
String get_player1_name(Settings settings);
void set_player2_name(String n2, Settings *settings);
String get_player2_name(Settings settings);
void set_p1_symbol(char s1, Settings *settings);
char get_p1_symbol(Settings settings);
void set_p2_symbol(char s2, Settings *settings);
char get_p2_symbol(Settings settings);
void set_previous_game(String p, Settings *settings);
String get_previous_game(Settings settings);
void set_undo_settings(int x, Settings *settings);
int get_undo_settings(Settings settings);
void set_num_rounds(int r, Settings *settings);
int get_num_rounds(Settings settings);
void set_game_name(String n, Settings *settings);
String get_game_name(Settings settings);
#pragma endregion

// DEFINIZIONE ALTRE FUNZIONI
#pragma region dichiarazione altre funzioni
void print_settings_screen(String s);
#pragma endregion

// dichiarazioni funzioni navigazione
#pragma region input
void navigate_settings(Settings *settings);
#pragma endregion

// ------------------------------ FUNZIONI DI ACCESSO ------------------------------------
#pragma region funzioni di accesso
// ---------------------GAME MODE---------------------------
void set_game_mode(int m, Settings *settings)
{
  settings->game_mode = m;
}

int get_game_mode(Settings settings)
{
  return settings.game_mode;
}

// ---------------------PLAYER NAMES---------------------------
void set_player1_name(String n1, Settings *settings)
{
  strncpy(settings->player1_name.data, n1.data,
          sizeof(settings->player1_name.data) - 1);
}

String get_player1_name(Settings settings)
{
  return settings.player1_name;
}

// ------------------------------------------------
void set_player2_name(String n2, Settings *settings)
{
  strncpy(settings->player2_name.data, n2.data,
          sizeof(settings->player2_name.data) - 1);
}

String get_player2_name(Settings settings)
{
  return settings.player2_name;
}

// --------------------PLAYER SYMBOLS----------------------------
void set_p1_symbol(char s1, Settings *settings)
{
  settings->p1_symbol = s1;
}

char get_p1_symbol(Settings settings)
{
  return settings.p1_symbol;
}

// ------------------------------------------------
void set_p2_symbol(char s2, Settings *settings)
{
  settings->p2_symbol = s2;
}

char get_p2_symbol(Settings settings)
{
  return settings.p2_symbol;
}

// ------------------PREVIOUS GAME------------------------------
void set_previous_game(String p, Settings *settings)
{
  strncpy(settings->previous_game.data, p.data,
          sizeof(settings->previous_game.data) - 1);
}

String get_previous_game(Settings settings)
{
  return settings.previous_game;
}

// ---------------------UNDO SETTINGS---------------------------
void set_undo_settings(int x, Settings *settings)
{
  settings->undo_settings = x;
  if (x == SETTINGS_DEFAULT) {
    set_player1_name((String){"giocatore1"}, settings);
    set_player2_name((String){"giocatore2"}, settings);
    set_game_mode(MODE_CPU, settings);
    set_previous_game((String){""}, settings);
    set_p1_symbol('X', settings);
    set_p2_symbol('O', settings);
    set_num_rounds(1, settings);
    set_game_name((String){"partita"}, settings);
  }
}

int get_undo_settings(Settings settings)
{
  return settings.undo_settings;
}

// ---------------------ROUNDS TO PLAY---------------------------
void set_num_rounds(int r, Settings *settings)
{
  if (r > MAX_ROUNDS) {
    settings->num_rounds = MAX_ROUNDS;
  } else {
    settings->num_rounds = r;
  }
}

int get_num_rounds(Settings settings)
{
  return settings.num_rounds;
}

// ---------------------GAME NAME---------------------------
void set_game_name(String n, Settings *settings)
{
  strncpy(settings->game_name.data, n.data,
          sizeof(settings->game_name.data) - 1);
}

String get_game_name(Settings settings)
{
  return settings.game_name;
}

#pragma endregion

// ALTRE FUNZIONI
#pragma region altre funzioni

// ---------------------RESET SETTINGS---------------------------
// reset delle impostazioni di default all'avvio

void reset_settings(Settings *settings)
{
  set_player1_name((String){"giocatore1"}, settings);
  set_player2_name((String){"giocatore2"}, settings);
  set_game_mode(MODE_CPU, settings);
  set_previous_game((String){""}, settings);
  set_p1_symbol('X', settings);
  set_p2_symbol('O', settings);
  set_undo_settings(SETTINGS_DEFAULT, settings);
  set_num_rounds(1, settings);
  set_game_name((String){"partita"}, settings);
}

void print_settings_screen(String s)
{
  FILE *fp_settings;
  int ch;
  char full_name[PATH_LENGTH];

  // apertura del file in lettura per caricare la schermata di impostazioni
  sprintf(full_name, FILE_PATH, s.data);
  fp_settings = fopen(full_name, "r");
  if (fp_settings == NULL) {
    printf("Errore Caricamento Schermata\n");
  } else {
    // finche' non raggiunge la fine del file legge i caratteri man mano e li stampa a schermo
    while ((ch = fgetc(fp_settings)) != EOF) {
      putchar(ch);
    }
    fclose(fp_settings);
    printf("\n");
  }
}

#pragma endregion

// FUNZIONI CURSORE E NAVIGAZIONE
#pragma region funzioni cursore

// ---------------------NAVIGATE SETTINGS---------------------------
void navigate_settings(Settings *settings)
{
  int row;
  int col;
  int page;
  int quit;
  String input_string;
  char new_symbol;

  row = 0;
  col = 0;
  page = SETTINGS_PAGE_MAIN;
  quit = 0;

  enable_mouse();

  while (!quit) {
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif
    print_settings_screen(settings_screens[page]);
    // stampa i dati nelle schermate scelte
    if (page == SETTINGS_PAGE_NAMES) {
      // pagina dei nomi
      goto_xy(btn_names[0].col1 + 1, btn_names[0].row);
      printf("%s]", get_player1_name(*settings).data);
      goto_xy(btn_names[1].col1 + 1, btn_names[1].row);
      printf("%s]", get_player2_name(*settings).data);
      fflush(stdout);
    } else if (page == SETTINGS_PAGE_LOAD) {
      // pagina del caricamento partita
      goto_xy(btn_load[0].col1 + 1, btn_load[0].row);
      printf("%s]", get_previous_game(*settings).data);
      fflush(stdout);
    } else if (page == SETTINGS_PAGE_SYMBOLS) {
      // pagina dei simboli
      goto_xy(btn_symbols[0].col1 + 1, btn_symbols[0].row);
      printf("%c", get_p1_symbol(*settings));
      goto_xy(btn_symbols[1].col1 + 1, btn_symbols[1].row);
      printf("%c", get_p2_symbol(*settings));
      fflush(stdout);
    } else if (page == SETTINGS_PAGE_ROUND) {
      // pagina del nome partita e round
      goto_xy(btn_round[0].col1 + 1, btn_round[0].row);
      printf("%s]", get_game_name(*settings).data);
      goto_xy(btn_round[1].col1 + 1, btn_round[1].row);
      printf("%d]", get_num_rounds(*settings));
      fflush(stdout);
    }

    goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
    fflush(stdout);

    // gestione del click nelle pagine
    if (!read_click(&row, &col)) {
      continue;
    }

    if (page == SETTINGS_PAGE_MAIN) {
      // pagina delle impostazioni
      if (is_area_clicked(btn_menu[0], row, col)) {
        // pagina dei nomi
        page = SETTINGS_PAGE_NAMES;
      } else if (is_area_clicked(btn_menu[1], row, col)) {
        // pagina modalita' partita
        page = SETTINGS_PAGE_MODE;
      } else if (is_area_clicked(btn_menu[2], row, col)) {
        // pagina avversario
        page = SETTINGS_PAGE_LOAD;
      } else if (is_area_clicked(btn_menu[3], row, col)) {
        // pagina simbolo
        page = SETTINGS_PAGE_SYMBOLS;
      } else if (is_area_clicked(btn_menu[4], row, col)) {
        // pagina annulla impostazioni
        page = SETTINGS_PAGE_UNDO;
      } else if (is_area_clicked(btn_menu[5], row, col)) {
        // pagina nome e round
        page = SETTINGS_PAGE_ROUND;
      } else if (is_area_clicked(btn_menu[6], row, col)) {
        // esci dalle impostazioni
        quit = 1;
      }
    } else if (page == SETTINGS_PAGE_NAMES) {
      // pagina dei nomi giocatori
      if (is_area_clicked(btn_names[0], row, col)) {
        // nome del primo giocatore
        goto_xy(btn_names[0].col1 + 1, btn_names[0].row);
        enable_keyboard();
        scanf("%19s", input_string.data);
        enable_mouse();
        set_player1_name(input_string, settings);
      } else if (is_area_clicked(btn_names[1], row, col)) {
        // nome del secondo giocatore
        goto_xy(btn_names[1].col1 + 1, btn_names[1].row);
        enable_keyboard();
        scanf("%19s", input_string.data);
        enable_mouse();
        set_player2_name(input_string, settings);
      } else if (is_area_clicked(btn_names[2], row, col)) {
        // esci dalla pagina dei nomi
        page = SETTINGS_PAGE_MAIN;
      }
    } else if (page == SETTINGS_PAGE_MODE) {
      // pagina della modalita' partita
      if (is_area_clicked(btn_mode[0], row, col)) {
        // partita tra giocatori
        set_game_mode(MODE_PLAYER, settings);
        page = SETTINGS_PAGE_MAIN;
      } else if (is_area_clicked(btn_mode[1], row, col)) {
        // partita giocatore-CPU
        set_game_mode(MODE_CPU, settings);
        page = SETTINGS_PAGE_MAIN;
      } else if (is_area_clicked(btn_mode[2], row, col)) {
        // esci dalla pagina della modalita'
        page = SETTINGS_PAGE_MAIN;
      }
    } else if (page == SETTINGS_PAGE_LOAD) {
      // pagina di caricamento partita
      if (is_area_clicked(btn_load[0], row, col)) {
        // nome della partita
        goto_xy(btn_load[0].col1 + 1, btn_load[0].row);
        enable_keyboard();
        scanf("%s", input_string.data);
        enable_mouse();
        set_previous_game(input_string, settings);
      } else if (is_area_clicked(btn_load[1], row, col)) {
        // esci
        page = SETTINGS_PAGE_MAIN;
      }
    } else if (page == SETTINGS_PAGE_SYMBOLS) {
      // pagina dei simboli
      if (is_area_clicked(btn_symbols[0], row, col)) {
        // simbolo del primo giocatore
        goto_xy(btn_symbols[0].col1 + 1, btn_symbols[0].row);
        enable_keyboard();
        scanf("%c", &new_symbol);
        enable_mouse();
        set_p1_symbol(new_symbol, settings);
      } else if (is_area_clicked(btn_symbols[1], row, col)) {
        // simbolo del secondo giocatore
        goto_xy(btn_symbols[1].col1 + 1, btn_symbols[1].row);
        enable_keyboard();
        scanf("%c", &new_symbol);
        enable_mouse();
        set_p2_symbol(new_symbol, settings);
      } else if (is_area_clicked(btn_symbols[2], row, col)) {
        // esci
        page = SETTINGS_PAGE_MAIN;
      }
    } else if (page == SETTINGS_PAGE_UNDO) {
      // pagina annulla impostazioni
      if (is_area_clicked(btn_undo[0], row, col)) {
        // annulla impostazioni
        reset_settings(settings);
        page = SETTINGS_PAGE_MAIN;
      } else if (is_area_clicked(btn_undo[1], row, col)) {
        // esci
        page = SETTINGS_PAGE_MAIN;
      }
    } else if (page == SETTINGS_PAGE_ROUND) {
      // pagina nome e round
      if (is_area_clicked(btn_round[0], row, col)) {
        // nome della partita
        goto_xy(btn_round[0].col1 + 1, btn_round[0].row);
        enable_keyboard();
        scanf("%19s", input_string.data);
        enable_mouse();
        set_game_name(input_string, settings);
      } else if (is_area_clicked(btn_round[1], row, col)) {
        // numero di round
        goto_xy(btn_round[1].col1 + 1, btn_round[1].row);
        enable_keyboard();
        scanf("%3s", input_string.data);
        enable_mouse();
        set_num_rounds(atoi(input_string.data), settings);
      } else if (is_area_clicked(btn_round[2], row, col)) {
        // esci
        page = SETTINGS_PAGE_MAIN;
      }
    }
  }

  // ripristina il terminale
  enable_keyboard();
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

#pragma endregion
