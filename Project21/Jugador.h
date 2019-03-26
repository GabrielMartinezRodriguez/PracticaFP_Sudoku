#ifndef _Jugador
#define _Jugador
#include "main.h" 

struct tJugador {
	string Id;
	int puntos;
};
string toString(const tJugador &jugador);
void modificarJugador(tJugador & jugador, int puntos);
bool menor(const tJugador & j1, const tJugador & j2);
#endif