#include <iostream>
#include <Windows.h>
#include "juego.h"
#include "Jugador.h"
#include "listaSudokus.h"
int MenuMain() {
	int selector = -1;
	
	while (selector < 0 || selector>1) {
		cout << "1-Jugar" << endl;
		cout << "0-Salir" << endl;
		cin >> selector;

	}
	return selector;
}
