/*
 ============================================================================
 Name        : statistiche.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Copyright   : Your copyright notice
 Description : file di gestione di salvataggio e recupero delle statistiche di gioco per giocatore
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statistiche.h"
#include "mouse.h"

// --------------------- FUNZIONI DI ACCESSO ---------------------
#pragma region funzioni di accesso

// ---------------------STATS---------------------------
int get_wins(Stats s)
{
  return s.wins;
}

void set_wins(Stats *s, int v)
{
  s->wins = v;
}

int get_losses(Stats s)
{
  return s.losses;
}

void set_losses(Stats *s, int v)
{
  s->losses = v;
}

int get_draws(Stats s)
{
  return s.draws;
}

void set_draws(Stats *s, int v)
{
  s->draws = v;
}

// ---------------------OPPONENT RECORD---------------------------
const char *get_opponent_name(const OpponentRecord *r)
{
  return r->opponent_name;
}

void set_opponent_name(OpponentRecord *r, const char *name)
{
  strncpy(r->opponent_name, name, STRING_LENGTH - 1);
  r->opponent_name[STRING_LENGTH - 1] = '\0';
}

#pragma endregion

// --------------------- STAMPA SCHERMATA ---------------------
#pragma region stampa

void print_stats_screen(const char *screen_name)
{
  FILE *fp;
  int ch;
  char full_name[PATH_LENGTH];

  sprintf(full_name, STATS_PATH, screen_name);
  fp = fopen(full_name, "r");
  if (fp == NULL) {
    printf("Errore caricamento schermata statistiche: %s\n", full_name);
  } else {
    while ((ch = fgetc(fp)) != EOF) {
      putchar(ch);
    }
    fclose(fp);
  }
}

#pragma endregion

// --------------------- GESTIONE FILE STATISTICHE ---------------------
#pragma region gestione file

// Aggiorna il file statistiche di un giocatore per il record vs un avversario
// tipo: 1 = vittoria, 2 = sconfitta, 0 = pareggio
static void update_player_file(const char *player_name, const char *opponent_name, int type)
{
    char path[PATH_LENGTH];
    OpponentRecord *list;
    int num_opponents;
    int found;
    FILE *fp;
    int i;
    OpponentRecord empty_record;

    sprintf(path, SAVED_STATS_PATH, player_name);

    list = NULL;
    num_opponents = 0;
    found = 0;

    // Prova a caricare il file esistente
    fp = fopen(path, "rb");
    if (fp != NULL) {
        fread(&num_opponents, sizeof(int), 1, fp);
        if (num_opponents > 0) {
            list = (OpponentRecord *)malloc(num_opponents * sizeof(OpponentRecord));
            fread(list, sizeof(OpponentRecord), num_opponents, fp);
        }
        fclose(fp);
    }

    // Cerca il record dell'avversario nella lista
    i = 0;
    while (i < num_opponents) {
        if (strcmp(get_opponent_name(&list[i]), opponent_name) == 0) {
            found = 1;
            if (type == RESULT_PLAYER1_WIN) {
                set_wins(&list[i].stats, get_wins(list[i].stats) + 1);
            } else if (type == RESULT_PLAYER2_WIN) {
                set_losses(&list[i].stats, get_losses(list[i].stats) + 1);
            } else {
                set_draws(&list[i].stats, get_draws(list[i].stats) + 1);
            }
        }
        i = i + 1;
    }

    if (!found) {
        num_opponents = num_opponents + 1;
        list = (OpponentRecord *)realloc(list, num_opponents * sizeof(OpponentRecord));
        empty_record.stats.wins = 0;
        empty_record.stats.losses = 0;
        empty_record.stats.draws = 0;
        list[num_opponents - 1] = empty_record;
        set_opponent_name(&list[num_opponents - 1], opponent_name);
        if (type == RESULT_PLAYER1_WIN) {
            set_wins(&list[num_opponents - 1].stats, 1);
        } else if (type == RESULT_PLAYER2_WIN) {
            set_losses(&list[num_opponents - 1].stats, 1);
        } else {
            set_draws(&list[num_opponents - 1].stats, 1);
        }
    }

    // Salva il file aggiornato
    fp = fopen(path, "wb");
    if (fp != NULL) {
        fwrite(&num_opponents, sizeof(int), 1, fp);
        fwrite(list, sizeof(OpponentRecord), num_opponents, fp);
        fclose(fp);
    }

    if (list != NULL) {
        free(list);
    }
}

// Salva le statistiche della partita per entrambi i giocatori
// result: 1 = vittoria G1, 2 = vittoria G2, 0 = pareggio
void save_game_stats(const char *p1_name, const char *p2_name, int result)
{
  if (result == RESULT_PLAYER1_WIN) {
    // G1 vittoria vs G2
    update_player_file(p1_name, p2_name, RESULT_PLAYER1_WIN);
    // G2 sconfitta vs G1
    update_player_file(p2_name, p1_name, RESULT_PLAYER2_WIN);
  } else if (result == RESULT_PLAYER2_WIN) {
    // G1 sconfitta vs G2
    update_player_file(p1_name, p2_name, RESULT_PLAYER2_WIN);
    // G2 vittoria vs G1
    update_player_file(p2_name, p1_name, RESULT_PLAYER1_WIN);
  } else {
    // pareggio per entrambi
    update_player_file(p1_name, p2_name, RESULT_DRAW);
    update_player_file(p2_name, p1_name, RESULT_DRAW);
  }
}

#pragma endregion

// --------------------- NAVIGAZIONE STATISTICHE ---------------------
#pragma region navigazione

void navigate_stats(void)
{
    int quit;
    int screen;
    int page;
    int num_opponents;
    int row;
    int col;
    int start;
    int i;
    char path[PATH_LENGTH];
    char searched_name[STRING_LENGTH];
    OpponentRecord *list;
    FILE *fp;

    quit = 0;
    screen = STATS_SCREEN_MENU;
    page = 0;
    list = NULL;
    num_opponents = 0;
    memset(searched_name, 0, sizeof(searched_name));

    enable_mouse();

    while (!quit) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        if (screen == STATS_SCREEN_MENU) {
            // ----- StatsMenu -----
            print_stats_screen(stats_screens[STATS_SCREEN_MENU].data);
            goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
            fflush(stdout);

            if (!read_click(&row, &col)) {
                continue;
            }

            if (is_area_clicked(btn_stat_menu[0], row, col)) {
                // [RICERCA] - input nome giocatore
                goto_xy(btn_stat_menu[0].col1 + 1, btn_stat_menu[0].row);
                enable_keyboard();
                scanf("%19s", searched_name);
                enable_mouse();

                // Cerca il file del giocatore nella cartella StatisticheSalvate
                sprintf(path, SAVED_STATS_PATH, searched_name);
                fp = fopen(path, "rb");
                if (fp != NULL) {
                    // File trovato: carica i dati
                    if (list != NULL) {
                        free(list);
                        list = NULL;
                    }
                    num_opponents = 0;
                    fread(&num_opponents, sizeof(int), 1, fp);
                    if (num_opponents > 0) {
                        list = (OpponentRecord *)malloc(num_opponents * sizeof(OpponentRecord));
                        fread(list, sizeof(OpponentRecord), num_opponents, fp);
                    }
                    fclose(fp);
                    screen = STATS_SCREEN_LIST;
                    page = 0;
                }
                // Se il file non esiste, non accade nulla (rimane su StatsMenu)
            } else if (is_area_clicked(btn_stat_menu[1], row, col)) {
                // [ESCI] - torna al menu principale
                quit = 1;
            }
        } else if (screen == STATS_SCREEN_LIST) {
            // ----- StatsList -----
            print_stats_screen(stats_screens[STATS_SCREEN_LIST].data);

            // Stampa il nome del giocatore cercato (riga 9, centrato)
            start = SCREEN_CENTER_COL - (int)strlen(searched_name) / 2;
            goto_xy(start, SEARCHED_NAME_ROW);
            printf("%s", searched_name);

            // Stampa gli avversari della pagina corrente (righe 12-16)
            start = page * OPPONENTS_PER_PAGE;
            i = 0;
            while (i < OPPONENTS_PER_PAGE && (start + i) < num_opponents) {
                // Stampa il nome dell'avversario
                goto_xy(TABLE_COL_START, TABLE_ROW_START + i);
                printf("%s", get_opponent_name(&list[start + i]));

                // Stampa il numero di vittorie a colonna 31
                goto_xy(31, TABLE_ROW_START + i);
                printf("%d", get_wins(list[start + i].stats));

                // Stampa i pareggi a colonna 50
                goto_xy(50, TABLE_ROW_START + i);
                printf("%d", get_draws(list[start + i].stats));

                // Stampa le sconfitte a colonna 69
                goto_xy(69, TABLE_ROW_START + i);
                printf("%d", get_losses(list[start + i].stats));

                i = i + 1;
            }
            goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
            fflush(stdout);

            if (!read_click(&row, &col)) {
                continue;
            }

            if (is_area_clicked(btn_list[0], row, col)) {
                // [ESCI] - torna a StatsMenu
                screen = STATS_SCREEN_MENU;
            } else if (is_area_clicked(btn_list[1], row, col)) {
                // [<--] - pagina precedente
                if (page > 0) {
                    page = page - 1;
                }
            } else if (is_area_clicked(btn_list[2], row, col)) {
                // [-->] - pagina successiva
                if ((page + 1) * OPPONENTS_PER_PAGE < num_opponents) {
                    page = page + 1;
                }
            }
        }
    }

    // Libera la memoria allocata
    if (list != NULL)
    {
        free(list);
    }

    // Ripristina il terminale
    enable_keyboard();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#pragma endregion
