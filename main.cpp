#include <iostream>
#include <Windows.h>
#include <string>
#include "juego.h"
#include "listaSudokus.h"
#include "listaJugadores.h"
using namespace std;
int MenuM();
int main() {
	int selector1 = 0;
	int selector2 = 0;
	int puntos;
	tListaSudokus ListaSudokus;
	tListaJugadores ListaJugadores;
	creaListaSudokus(ListaSudokus);
	cargarListaSudokus(ListaSudokus);
	creaListaVacia(ListaJugadores);
	cargar(ListaJugadores);
	do {
		selector1 = MenuM();
		switch (selector1) {
		case 1:
			selector2 = menuListaSudokus(ListaSudokus);
			puntos = JugarUnSudoku(ListaSudokus.array[selector2]);
			if (puntos != 0) {
				puntuarJugador(ListaJugadores, puntos);
				cout << "Felicidades has recibido " << puntos << " puntos" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			mostrar(ListaJugadores);
			system("pause");
			break;
		case 3:
			system("cls");
			mostrar(ordenarPorRanking(ListaJugadores));
			system("pause");
			break;
		case 4:
			system("cls");
			registrarSudoku(ListaSudokus);
			system("pause");
			break;

		}
	} while (selector1 != 0);
	system("pause");
	return 0;
}
int MenuM() {
	int selector = -1;

	while (selector < 0 || selector>4) {
		cout << "1.- Jugar" << endl;
		cout << "2.- Ver jugadores ordenados por identificador" << endl;
		cout << "3.- Ver jugadores ordenados por puntos" << endl;
		cout << "4.- Incorporar sudoku" << endl;
		cout << "0.- Salir" << endl;
		cin >> selector;

	}
	return selector;
}