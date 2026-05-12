

#ifndef impostazioni_H
#define impostazioni_H

// Definizione della stringa di caratteri
typedef struct {
    char data[20];
} Stringa;

// struttura delle impostazioni della partita
typedef struct{
	Stringa nomeGiocatore1;  // nome del giocatore 1
	Stringa nomeGiocatore2;  // nome del giocatore 2
	int modoPartita;  // 1 - CPU,   0 - Giocatore
	Stringa partitaPrecedente;  // nome della partita da riprendere
	char simboloGiocatore1;  // simbolo giocatore 1
	char simboloGiocatore2;  // simbolo del giocatore 2
	int annullaImpostazioni;  // 1 - Default,  0 - Modificate
	int numeroRound;  // numero dei round
	Stringa nomePartita;  // nome della partita da giocare
}Impostazioni;


#endif