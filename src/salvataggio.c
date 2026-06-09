/*
 ============================================================================
 Name        : salvataggio.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 0.0 
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// gestione delle strutture per il salvataggio dati
#include "salvataggio.h"
// gestione del mouse e del terminale
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// #pragma region definizione funzioni di accesso
// void Set_griglia(Partita* partita, char grigliaDiGioco[3][3]);
// char Get_griglia(Partita partita);
// void Set_impostazioni(Partita* partita, Impostazioni impostazioni);
// Impostazioni Get_impostazioni(Partita partita);
// void Set_turno(Partita* partita, int turnoCorrente);
// int Get_turno(Partita partita);
// void Set_round(Partita* partita, int roundCorrente);
// int Get_round(Partita partita);

// #pragma endregion




