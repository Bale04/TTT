/*
 ============================================================================
 Name        : salvataggio.c
 Author      : Mattia Emanuele Balestrucci, Vincenzo Basilio, Luigi Bonasia, Ruggiero Dicorato 
 Version     : V 1.0
 Copyright   : Your copyright notice
 Description : Gestione del salvataggio e caricamento dello stato del gioco
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salvataggio.h"

int salvaPartita(const Impostazioni *impostazioni, const Partita *partita) {
    char percorso[256];
    // Il nome del file è il nome della partita
    sprintf(percorso, "/home/Bale/GitHub/TTT/Salvataggio/%s", impostazioni->nomePartita.data);
    FILE *fp = fopen(percorso, "wb");
    if (fp == NULL) {
        printf("Errore apertura file per il salvataggio: %s\n", percorso);
        return 0;
    }
    fwrite(impostazioni, sizeof(Impostazioni), 1, fp);
    fwrite(partita, sizeof(Partita), 1, fp);
    fclose(fp);
    return 1;
}

int caricaPartita(Impostazioni *impostazioni, Partita *partita) {
    char percorso[256];
    // Il file da caricare è specificato in partitaPrecedente
    sprintf(percorso, "/home/Bale/GitHub/TTT/Salvataggio/%s", impostazioni->partitaPrecedente.data);
    FILE *fp = fopen(percorso, "rb");
    if (fp == NULL) {
        printf("Errore apertura file per il caricamento: %s\n", percorso);
        return 0;
    }
    fread(impostazioni, sizeof(Impostazioni), 1, fp);
    fread(partita, sizeof(Partita), 1, fp);
    fclose(fp);
    return 1;
}
