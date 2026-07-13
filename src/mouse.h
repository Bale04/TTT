/*
 ============================================================================
 Name        : mouse.h
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato
 Version     : V 1.0
 Description : Libreria condivisa per la gestione del mouse e del cursore del terminale.
 ============================================================================
 */

#ifndef MOUSE_H
#define MOUSE_H

#include "costanti.h"
#include "strutture.h"

#ifdef _WIN32
  #include <windows.h>
#else
  #include <termios.h>
  #include <unistd.h>
  #include <stdio.h>
#endif

// posizione base del cursore nel terminale (dopo ogni input)
#define CURSOR_BASE ((Cursor){1, 25})

// gestisce lo spostamento del cursore al click
void goto_xy(int x, int y);

// funzione di abilitazione del mouse
void enable_mouse(void);

// blocca finche' non riceve un click sinistro del mouse. Restituisce 1 se il click e' valido, 0 in caso di errore.
int read_click(int *row, int *col);

// abilita l'input da tastiera
void enable_keyboard(void);

// controlla se il click corrisponde all'area cliccabile
int is_area_clicked(ClickableArea area, int row, int col);

#endif
