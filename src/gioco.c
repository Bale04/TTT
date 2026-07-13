/*
 ============================================================================
 Name        : gioco.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Copyright   : Your copyright notice
 Description : file di gestione del gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gioco.h"
#include "mouse.h"

#pragma region funzioni esterne
// funzioni esterne da supporto.c
extern void navigate_support(void);

// funzioni esterne da salvataggio.c
extern int save_game(const Settings *settings, const Game *game);
extern int load_game(Settings *settings, Game *game);

// funzione esterna da statistiche.c
extern void save_game_stats(const char *player1_name, const char *player2_name, int result);

// funzioni esterne da impostazioni.c
extern String get_game_name(Settings settings);
extern String get_player1_name(Settings settings);
extern String get_player2_name(Settings settings);
extern int get_num_rounds(Settings settings);
extern char get_p1_symbol(Settings settings);
extern char get_p2_symbol(Settings settings);
extern int get_game_mode(Settings settings);
#pragma endregion

#pragma region dichiarazioni funzioni
// funzioni di accesso Game
void set_grid(Game *game, int row, int col, char symbol);
char get_grid(Game game, int row, int col);
void set_turn(Game *game, int turn);
int get_turn(Game game);
void set_round(Game *game, int round);
int get_round(Game game);
// funzioni di accesso Game - p1_stats
int get_p1_wins(Game game);
void set_p1_wins(Game *game, int v);
int get_p1_losses(Game game);
void set_p1_losses(Game *game, int v);
int get_p1_draws(Game game);
void set_p1_draws(Game *game, int v);
// funzioni di accesso Game - p2_stats
int get_p2_wins(Game game);
void set_p2_wins(Game *game, int v);
int get_p2_losses(Game game);
void set_p2_losses(Game *game, int v);
int get_p2_draws(Game game);
void set_p2_draws(Game *game, int v);

// funzioni di stampa
void print_game_screen(String s);
void print_game(Game game, Settings settings);

// funzione di navigazione
void navigate_game(Game *game, Settings *settings);

// funzioni di verifica stato round
char get_round_winner(Game game);
int is_grid_full(Game game);

// funzioni bot CPU
char get_grid_winner(char g[GRID_SIZE][GRID_SIZE]);
int is_grid_full_copy(char g[GRID_SIZE][GRID_SIZE]);
int calculate_score(char g[GRID_SIZE][GRID_SIZE], char bot_symbol, char opponent_symbol, int isMaximizing);
int bot_move(Game game, char bot_symbol, char opponent_symbol);

#pragma endregion

// ------------------------- FUNZIONI DI ACCESSO GAME -------------------------------
#pragma region funzioni di accesso

// ---------------------GRID---------------------------
void set_grid(Game *game, int row, int col, char symbol)
{
    game->grid[row][col] = symbol;
}

char get_grid(Game game, int row, int col)
{
    return game.grid[row][col];
}

// ---------------------TURN---------------------------
void set_turn(Game *game, int turn)
{
    game->turn = turn;
}

int get_turn(Game game)
{
    return game.turn;
}

// ---------------------ROUND---------------------------
void set_round(Game *game, int round)
{
    game->round = round;
}

int get_round(Game game)
{
    return game.round;
}

// ---------------------STATS P1---------------------------
void set_p1_wins(Game *game, int v)
{
    game->p1_stats.wins = v;
}

int get_p1_wins(Game game)
{
    return game.p1_stats.wins;
}

void set_p1_losses(Game *game, int v)
{
    game->p1_stats.losses = v;
}

int get_p1_losses(Game game)
{
    return game.p1_stats.losses;
}

void set_p1_draws(Game *game, int v)
{
    game->p1_stats.draws = v;
}

int get_p1_draws(Game game)
{
    return game.p1_stats.draws;
}

// ---------------------STATS P2---------------------------
void set_p2_wins(Game *game, int v)
{
    game->p2_stats.wins = v;
}

int get_p2_wins(Game game)
{
    return game.p2_stats.wins;
}

void set_p2_losses(Game *game, int v)
{
    game->p2_stats.losses = v;
}

int get_p2_losses(Game game)
{
    return game.p2_stats.losses;
}

void set_p2_draws(Game *game, int v)
{
    game->p2_stats.draws = v;
}

int get_p2_draws(Game game)
{
    return game.p2_stats.draws;
}

#pragma endregion

// ----------------------------- BOT CPU --------------------------------
#pragma region bot

// controlla il vincitore sulla copia della griglia usata dal bot
char get_grid_winner(char g[GRID_SIZE][GRID_SIZE])
{
    char winner = '\0';
    int r;
    int c;

    // Controlla righe
    r = 0;
    while (r < GRID_SIZE && winner == '\0') {
        if ((g[r][0] != ' ') &&
            (g[r][0] != '\0') &&
            (g[r][0] == g[r][1]) &&
            (g[r][1] == g[r][2])) {
            winner = g[r][0];
        }
        r = r + 1;
    }

    // Controlla colonne
    c = 0;
    while (c < GRID_SIZE && winner == '\0') {
        if ((g[0][c] != ' ') &&
            (g[0][c] != '\0') &&
            (g[0][c] == g[1][c]) &&
            (g[1][c] == g[2][c])) {
            winner = g[0][c];
        }
        c = c + 1;
    }

    // Controlla diagonale principale e secondaria
    if (winner == '\0') {
        if ((g[0][0] != ' ') &&
            (g[0][0] != '\0') &&
            (g[0][0] == g[1][1]) &&
            (g[1][1] == g[2][2])) {
            winner = g[0][0];
        } else if ((g[0][2] != ' ') &&
                   (g[0][2] != '\0') &&
                   (g[0][2] == g[1][1]) &&
                   (g[1][1] == g[2][0])) {
            winner = g[0][2];
        }
    }

    return winner;
}

// controlla se la griglia e' piena
int is_grid_full_copy(char g[GRID_SIZE][GRID_SIZE])
{
    int full = 1;
    int r;
    int c;

    r = 0;
    c = 0;

    // Scansiona le 9 celle
    while (r < GRID_SIZE && full == 1) {
        c = 0;
        while (c < GRID_SIZE && full == 1) {
            if (g[r][c] == ' ' || g[r][c] == '\0') {
                full = 0;
            }
            c = c + 1;
        }
        r = r + 1;
    }

    return full;
}

// algoritmo ricorsivo per il calcolo del punteggio della posizione
// isMaximizing == 1: turno del bot (massimizza)
// isMaximizing == 0: turno del giocatore (minimizza)
int calculate_score(char g[GRID_SIZE][GRID_SIZE], char bot_symbol, char opponent_symbol, int isMaximizing)
{
    int score;
    int r;
    int c;
    int p;
    int best;
    char winner;

    score = 0;
    winner = get_grid_winner(g);

    if (winner == bot_symbol) {
        score = SCORE_WIN;
    } else if (winner == opponent_symbol) {
        score = SCORE_LOSS;
    } else if (is_grid_full_copy(g)) {
        score = RESULT_DRAW;
    } else {
        if (isMaximizing) {
            best = MIN_SCORE;
            r = 0;
            c = 0;
            while (r < GRID_SIZE) {
                c = 0;
                while (c < GRID_SIZE) {
                    if (g[r][c] == ' ' || g[r][c] == '\0') {
                        g[r][c] = bot_symbol;
                        p = calculate_score(g, bot_symbol, opponent_symbol, 0);
                        g[r][c] = ' ';
                        if (p > best) {
                            best = p;
                        }
                    }
                    c = c + 1;
                }
                r = r + 1;
            }
            score = best;
        } else {
            best = MAX_SCORE;
            r = 0;
            c = 0;
            while (r < GRID_SIZE) {
                c = 0;
                while (c < GRID_SIZE) {
                    if (g[r][c] == ' ' || g[r][c] == '\0') {
                        g[r][c] = opponent_symbol;
                        p = calculate_score(g, bot_symbol, opponent_symbol, 1);
                        g[r][c] = ' ';
                        if (p < best) {
                            best = p;
                        }
                    }
                    c = c + 1;
                }
                r = r + 1;
            }
            score = best;
        }
    }

    return score;
}

// restituisce la cella migliore (0-8) per il bot, o -1 se nessuna mossa disponibile
int bot_move(Game game, char bot_symbol, char opponent_symbol)
{
    char g[GRID_SIZE][GRID_SIZE];
    int best = MIN_SCORE;
    int r;
    int c;
    int p;
    int move_cell = INVALID_CELL;

    // Copia lo stato della griglia
    r = 0;
    while (r < GRID_SIZE) {
        c = 0;
        while (c < GRID_SIZE) {
            g[r][c] = get_grid(game, r, c);
            c = c + 1;
        }
        r = r + 1;
    }

    // Ricerca la mossa migliore
    r = 0;
    while (r < GRID_SIZE) {
        c = 0;
        while (c < GRID_SIZE) {
            if (g[r][c] == ' ' || g[r][c] == '\0') {
                g[r][c] = bot_symbol;
                p = calculate_score(g, bot_symbol, opponent_symbol, 0);
                g[r][c] = ' ';
                if (p > best) {
                    best = p;
                    move_cell = r * GRID_SIZE + c;
                }
            }
            c = c + 1;
        }
        r = r + 1;
    }

    return move_cell;
}

#pragma endregion

// ----------------- STAMPA SCHERMATA ------------------
#pragma region stampa

void print_game_screen(String s)
{
    FILE *fp;
    int ch;
    char full_name[PATH_LENGTH];

    sprintf(full_name, GAME_PATH, s.data);
    fp = fopen(full_name, "r");
    if (fp == NULL) {
        printf("Errore caricamento schermata gioco: %s\n", full_name);
    } else {
        while ((ch = fgetc(fp)) != EOF) {
            putchar(ch);
        }
        fclose(fp);
    }
}

// mostra a schermo i dati della partita in corso
void print_game(Game game, Settings settings)
{
    int turn;
    int current_round;
    int r;
    int c;
    char symbol;

    turn = get_turn(game);
    current_round = get_round(game);

    // stampa il nome della partita
    goto_xy(GAME_TITLE_COL, GAME_TITLE_ROW);
    printf("%s", get_game_name(settings).data);

    // stampa il numero del round
    goto_xy(GAME_ROUND_COL, GAME_ROUND_ROW);
    printf("%d", current_round);

    // stampa il turno del giocatore
    goto_xy(GAME_TURN_COL, GAME_TURN_ROW);
    printf("%d", turn);

    // stampa il numero di vittorie correnti per giocatori in base ai round giocati
    goto_xy(WIN_COL, P1_WIN_ROW);
    printf("%d", get_p1_wins(game));
    goto_xy(WIN_COL, P2_WIN_ROW);
    printf("%d", get_p2_wins(game));

    fflush(stdout);

    // stampa i simboli al centro di ogni cella della griglia
    r = 0;
    while (r < GRID_SIZE) {
        c = 0;
        while (c < GRID_SIZE) {
            symbol = get_grid(game, r, c);
            goto_xy(GRID_CENTER_COL[c], GRID_CENTER_ROW[r]);
            if (symbol == ' ' || symbol == '\0') {
                printf(" ");
            } else {
                printf("%c", symbol);
            }
            c = c + 1;
        }
        r = r + 1;
    }
    fflush(stdout);
}

#pragma endregion

// --------------------- NAVIGAZIONE PARTITA -----------------------------
#pragma region navigazione

void navigate_game(Game *game, Settings *settings)
{
    int quit;
    int r;
    int c;
    int row;
    int col;
    int cell;
    int result;
    int confirmed;
    int full;
    char winner;
    char current_symbol;
    String winner_name;

    quit = 0;

    // Se c'e' una partita precedente specificata la carica
    if (strlen(settings->previous_game.data) > 0) {
        if (load_game(settings, game)) {
            // dopo aver caricato la partita pulisce il campo previous_game in modo che non venga caricata di nuovo ad ogni ciclo di while
            settings->previous_game.data[0] = '\0';
        } else {
            // Se fallisce il caricamento inizializza normalmente
            set_turn(game, 1);
            set_round(game, 1);
            set_p1_wins(game, 0);
            set_p1_losses(game, 0);
            set_p1_draws(game, 0);
            set_p2_wins(game, 0);
            set_p2_losses(game, 0);
            set_p2_draws(game, 0);
            r = 0;
            while (r < GRID_SIZE) {
                c = 0;
                while (c < GRID_SIZE) {
                    set_grid(game, r, c, ' ');
                    c = c + 1;
                }
                r = r + 1;
            }
        }
    } else {
        // Inizializza una nuova partita
        set_turn(game, 1);
        set_round(game, 1);
        set_p1_wins(game, 0);
        set_p1_losses(game, 0);
        set_p1_draws(game, 0);
        set_p2_wins(game, 0);
        set_p2_losses(game, 0);
        set_p2_draws(game, 0);
        // inizializza la griglia vuota
        r = 0;
        while (r < GRID_SIZE) {
            c = 0;
            while (c < GRID_SIZE) {
                set_grid(game, r, c, ' ');
                c = c + 1;
            }
            r = r + 1;
        }
    }

    // abilita il mouse tramite la libreria mouse.h
    enable_mouse();

    while (!quit) {
        // pulisce il terminale
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // stampa la schermata base del gioco
        print_game_screen(game_screens[0]);

        // stampa a schermo i dati della partita
        print_game(*game, *settings);
        goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
        fflush(stdout);

        // se modalita' CPU e turno del bot (giocatore 2), muove automaticamente
        if ((get_game_mode(*settings) == MODE_CPU) && (get_turn(*game) == PLAYER2_TURN)) {
            current_symbol = get_p2_symbol(*settings);
            cell = bot_move(*game, current_symbol, get_p1_symbol(*settings));
            if (cell != INVALID_CELL) {
                r = 0;
                c = 0;
                while (r * GRID_SIZE + c != cell) {
                    c = c + 1;
                    if (c == GRID_SIZE) {
                        c = 0;
                        r = r + 1;
                    }
                }
                set_grid(game, r, c, current_symbol);
                // controllo fine round
                winner = get_round_winner(*game);
                full = is_grid_full(*game);
                if ((winner != '\0') || (full == 1)) {
                    if (winner != '\0') {
                        if (winner == get_p1_symbol(*settings)) {
                            set_p1_wins(game, get_p1_wins(*game) + 1);
                            set_p2_losses(game, get_p2_losses(*game) + 1);
                        } else {
                            set_p2_wins(game, get_p2_wins(*game) + 1);
                            set_p1_losses(game, get_p1_losses(*game) + 1);
                        }
                    } else {
                        set_p1_draws(game, get_p1_draws(*game) + 1);
                        set_p2_draws(game, get_p2_draws(*game) + 1);
                    }
                    // aggiorna schermo con lo stato finale del round
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif
                    print_game_screen(game_screens[0]);
                    print_game(*game, *settings);
                    goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
                    fflush(stdout);

                    if (get_round(*game) >= get_num_rounds(*settings)) {
                        // fine partita
                        result = 0;
                        if (get_p1_wins(*game) > get_p2_wins(*game)) {
                            result = RESULT_PLAYER1_WIN;
                        } else if (get_p2_wins(*game) > get_p1_wins(*game)) {
                            result = RESULT_PLAYER2_WIN;
                        } else {
                            result = RESULT_DRAW;
                        }
                        save_game_stats(get_player1_name(*settings).data,
                                        get_player2_name(*settings).data,
                                        result);

                        confirmed = 0;
                        while (!confirmed) {
                            #ifdef _WIN32
                                system("cls");
                            #else
                                system("clear");
                            #endif
                            print_game_screen(game_screens[3]);
                            if (get_p1_wins(*game) > get_p2_wins(*game)) {
                                // nome vincitore e' giocatore 1
                                winner_name = get_player1_name(*settings);
                                goto_xy(WINNER_NAME_COL - 10, WINNER_NAME_ROW);
                                printf("                    ");
                                cell = WINNER_NAME_COL - (int)strlen(winner_name.data) / 2;
                                goto_xy(cell, WINNER_NAME_ROW);
                                printf("%s", winner_name.data);
                            } else if (get_p2_wins(*game) > get_p1_wins(*game)) {
                                winner_name = get_player2_name(*settings);
                                goto_xy(WINNER_NAME_COL - 10, WINNER_NAME_ROW);
                                printf("                    ");
                                cell = WINNER_NAME_COL - (int)strlen(winner_name.data) / 2;
                                goto_xy(cell, WINNER_NAME_ROW);
                                printf("%s", winner_name.data);
                            }
                            fflush(stdout);
                            goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
                            if (read_click(&row, &col)) {
                                if (is_area_clicked(btn_victory[0], row, col)) {
                                    confirmed = 1;
                                    quit = 1;
                                }
                            }
                        }
                    } else {
                        // round successivo
                        fflush(stdout);
                        while (!read_click(&row, &col))
                            ; /* wait for click */
                        set_round(game, get_round(*game) + 1);
                        set_turn(game, PLAYER1_TURN);
                        r = 0;
                        while (r < GRID_SIZE) {
                            c = 0;
                            while (c < GRID_SIZE) {
                                set_grid(game, r, c, ' ');
                                c = c + 1;
                            }
                            r = r + 1;
                        }
                    }
                } else {
                    // round non terminato: torna al turno del giocatore
                    set_turn(game, PLAYER1_TURN);
                }
            }
        } else {

        // legge il click del giocatore
        if (read_click(&row, &col)) {
        // rilevamento della cella cliccata tramite la funzione get_clicked_cell di gioco.h
        cell = get_clicked_cell(row, col);

        if (cell != INVALID_CELL) {
            r = 0;
            c = 0;
            while (r * GRID_SIZE + c != cell) {
                c = c + 1;
                if (c == GRID_SIZE) {
                    c = 0;
                    r = r + 1;
                }
            }

            // se la cella e' ancora libera
            if ((get_grid(*game, r, c) == ' ') || (get_grid(*game, r, c) == '\0')) {
                // simbolo del giocatore corrente letto dalle impostazioni
                if (get_turn(*game) == PLAYER1_TURN) {
                    current_symbol = get_p1_symbol(*settings);
                } else {
                    current_symbol = get_p2_symbol(*settings);
                }

                // piazza il simbolo nella cella
                set_grid(game, r, c, current_symbol);

                // controllo fine round
                winner = get_round_winner(*game);
                full = is_grid_full(*game);

                if ((winner != '\0') || (full == 1)) {
                    // Aggiorna punteggio se c'e' un vincitore del round
                    if (winner != '\0') {
                        if (winner == get_p1_symbol(*settings)) {
                            // Aggiorna vittorie giocatore 1 e sconfitte giocatore 2
                            set_p1_wins(game, get_p1_wins(*game) + 1);
                            set_p2_losses(game, get_p2_losses(*game) + 1);
                        } else {
                            // Aggiorna vittorie giocatore 2 e sconfitte giocatore 1
                            set_p2_wins(game, get_p2_wins(*game) + 1);
                            set_p1_losses(game, get_p1_losses(*game) + 1);
                        }
                    } else {
                        // Pareggio round
                        set_p1_draws(game, get_p1_draws(*game) + 1);
                        set_p2_draws(game, get_p2_draws(*game) + 1);
                    }

                    // Stampa l'ultimo stato grafico prima di procedere
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif
                    print_game_screen(game_screens[0]);
                    print_game(*game, *settings);
                    goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
                    fflush(stdout);

                    // Se siamo all'ultimo round, termina la partita e vai alla schermata vittoria
                    if (get_round(*game) >= get_num_rounds(*settings)) {
                        // Determina il risultato finale e salva le statistiche per-avversario
                        result = 0;
                        if (get_p1_wins(*game) > get_p2_wins(*game)) {
                            result = RESULT_PLAYER1_WIN; // vittoria G1
                        } else if (get_p2_wins(*game) > get_p1_wins(*game)) {
                            result = RESULT_PLAYER2_WIN; // vittoria G2
                        } else {
                            result = RESULT_DRAW; // pareggio
                        }
                        save_game_stats(get_player1_name(*settings).data,
                                        get_player2_name(*settings).data,
                                        result);

                        confirmed = 0;
                        while (!confirmed) {
                            #ifdef _WIN32
                                system("cls");
                            #else
                                system("clear");
                            #endif
                            print_game_screen(game_screens[3]);

                            // Calcola e scrivi il vincitore finale
                            if (get_p1_wins(*game) > get_p2_wins(*game)) {
                                // vittoria G1
                                winner_name = get_player1_name(*settings);
                                goto_xy(WINNER_NAME_COL - 10, WINNER_NAME_ROW);
                                printf("                    "); // ripulisce il puntino
                                cell = WINNER_NAME_COL - (int)strlen(winner_name.data) / 2;
                                goto_xy(cell, WINNER_NAME_ROW);
                                printf("%s", winner_name.data);
                            } else if (get_p2_wins(*game) > get_p1_wins(*game)) {
                                // vittoria G2
                                winner_name = get_player2_name(*settings);
                                goto_xy(WINNER_NAME_COL - 10, WINNER_NAME_ROW);
                                printf("                    "); // ripulisce il punto
                                cell = WINNER_NAME_COL - (int)strlen(winner_name.data) / 2;
                                goto_xy(cell, WINNER_NAME_ROW);
                                printf("%s", winner_name.data);
                            }
                            fflush(stdout);
                            goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);

                            if (read_click(&row, &col)) {

                            // Verifica click su btn_victory[0]
                            if (is_area_clicked(btn_victory[0], row, col)) {
                                confirmed = 1;
                                quit = 1;
                            }
                            }
                        }
                    } else {
                        fflush(stdout);

                        while (!read_click(&row, &col))
                            ; /* wait for click */

                        set_round(game, get_round(*game) + 1);
                        set_turn(game, PLAYER1_TURN);
                        // resetta la griglia per il prossimo round
                        r = 0;
                        while (r < GRID_SIZE) {
                            c = 0;
                            while (c < GRID_SIZE) {
                                set_grid(game, r, c, ' ');
                                c = c + 1;
                            }
                            r = r + 1;
                        }
                    }
                } else {
                    // Alterna il turno solo se il round non e' terminato
                    if (get_turn(*game) == PLAYER1_TURN) {
                        set_turn(game, PLAYER2_TURN);
                    } else {
                        set_turn(game, PLAYER1_TURN);
                    }
                }
            }
        } else if (is_area_clicked(btn_game_menu[0], row, col)) {
            // esce al menu principale
            quit = 1;
        } else if (is_area_clicked(btn_game_menu[1], row, col)) {
            // mostra la schermata di salvataggio e conferma
            confirmed = 0;
            while (!confirmed) {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
                print_game_screen(game_screens[1]);
                goto_xy(CURSOR_BASE.col, CURSOR_BASE.row);
                fflush(stdout);

                if (read_click(&row, &col)) {

                if (is_area_clicked(btn_save_confirm[0], row, col)) {
                    // salva la partita ed esci al menu principale
                    save_game(settings, game);
                    confirmed = 1;
                    quit = 1;
                } else if (is_area_clicked(btn_save_confirm[1], row, col) || is_area_clicked(btn_save_confirm[2], row, col)) {
                    // ritorna al gioco
                    confirmed = 1;
                }
                }
            }
        } else if (is_area_clicked(btn_game_menu[2], row, col)) {
            // apre il supporto del gioco
            enable_keyboard();
            navigate_support();
            enable_mouse();
        }
        }
        }
    }

    // ripristina terminale
    enable_keyboard();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Controlla se c'e' un vincitore del round. Ritorna il simbolo vincitore o '\0'.
char get_round_winner(Game game)
{
    int r;
    int c;

    // righe
    r = 0;
    while (r < GRID_SIZE) {
        if ((game.grid[r][0] != ' ') &&
            (game.grid[r][0] != '\0') &&
            (game.grid[r][0] == game.grid[r][1]) &&
            (game.grid[r][1] == game.grid[r][2])) {
            return game.grid[r][0];
        }
        r = r + 1;
    }
    // colonne
    c = 0;
    while (c < GRID_SIZE) {
        if ((game.grid[0][c] != ' ') &&
            (game.grid[0][c] != '\0') &&
            (game.grid[0][c] == game.grid[1][c]) &&
            (game.grid[1][c] == game.grid[2][c])) {
            return game.grid[0][c];
        }
        c = c + 1;
    }
    // diagonale principale
    if ((game.grid[0][0] != ' ') &&
        (game.grid[0][0] != '\0') &&
        (game.grid[0][0] == game.grid[1][1]) &&
        (game.grid[1][1] == game.grid[2][2])) {
        return game.grid[0][0];
    }
    // diagonale secondaria
    if ((game.grid[0][2] != ' ') &&
        (game.grid[0][2] != '\0') &&
        (game.grid[0][2] == game.grid[1][1]) &&
        (game.grid[1][1] == game.grid[2][0])) {
        return game.grid[0][2];
    }
    return '\0';
}

// Verifica se la griglia e' piena. Ritorna 1 se piena, 0 altrimenti.
int is_grid_full(Game game)
{
    int r;
    int c;

    r = 0;
    while (r < GRID_SIZE) {
        c = 0;
        while (c < GRID_SIZE) {
            if ((game.grid[r][c] == ' ') || (game.grid[r][c] == '\0')) {
                return 0;
            }
            c = c + 1;
        }
        r = r + 1;
    }
    return 1;
}

#pragma endregion
