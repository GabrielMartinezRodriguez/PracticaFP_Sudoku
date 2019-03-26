#include "Jugador.h"
string toString(const tJugador &jugador) {
	string Devolver;
	Devolver = jugador.Id;
	Devolver = Devolver + " "+(to_string(jugador.puntos));
	return Devolver;
}
void modificarJugador(tJugador & jugador, int puntos) {
	jugador.puntos += puntos;
}
bool menor(const tJugador & j1, const tJugador & j2) {
	if (j1.puntos>=j2.puntos) {
		if (j1.puntos == j2.puntos) {

		}
		else {
			return false;
		}
	}
	else {
		return true;
	}

}