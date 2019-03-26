#include "listaJugadores.h"

void creaListaVacia(tListaJugadores & lista) {
	int contador = 0;

	while (contador < MAX_JUGADORES) {
		lista.contador = 0;
		lista.jugadores[contador].Id = "";
		lista.jugadores[contador].puntos = NULL;
		contador++;
	}
}
bool cargar(tListaJugadores & lista) {
	ifstream  fichero;
	int contador = 0;
	while (!fichero.eof()) {
		fichero >> lista.jugadores[contador].Id;
		fichero >> lista.jugadores[contador].puntos;
		contador++;
	}
	lista.contador = contador;
}
void mostrar(const tListaJugadores & lista) {
	int contador = 0;
	string mostrar;
	while (contador < lista.contador) {
		mostrar = toString(lista.jugadores[contador]);
		cout <<contador+1<<"- "<<mostrar<<endl;
		contador++;
	}
}