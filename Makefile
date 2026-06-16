# Makefile per compilare il gioco Tic-Tac-Toe (TTT) su Linux
CC = gcc
CFLAGS = -fdiagnostics-color=always -g
SRC = src/menu.c src/impostazioni.c src/gioco.c src/supporto.c src/salvataggio.c src/statistiche.c
OUT = TTT

all: $(OUT)

$(OUT):
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
