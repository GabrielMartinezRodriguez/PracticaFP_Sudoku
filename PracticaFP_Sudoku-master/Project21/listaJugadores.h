#include "main.h"
const int  MAX_JUGADORES = 10;
struct tListaJugadores {
	tJugador jugadores[MAX_JUGADORES];
	int contador;
};

void creaListaVacia(tListaJugadores & lista);
