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
	tListaJugadores Copia;
	creaListaSudokus(ListaSudokus);
	cargarListaSudokus(ListaSudokus);
	creaListaVacia(ListaJugadores);
	cargar(ListaJugadores);
	do {
		system("cls");
		selector1 = MenuM();
		system("cls");
		switch (selector1) {
			case 1:
			selector2 = menuListaSudokus(ListaSudokus);
			system("cls");
			puntos = JugarUnSudoku(ListaSudokus.array[selector2]);
			if (puntos != 0) {
				puntuarJugador(ListaJugadores, puntos);
				cout << "Felicidades has recibido " << puntos << " puntos" << endl;
			}
			system("pause");
			break;
		case 2:
			mostrar(ListaJugadores);
			system("pause");
			break;
		case 3:
			Copia = ordenarPorRanking(ListaJugadores);
			mostrar(Copia);
			borrarListaJugadores(Copia);
			system("pause");
			break;
		case 4:
			registrarSudoku(ListaSudokus);
			system("pause");
			break;
		case 5:
			annadirJugador(ListaJugadores);
			system("pause");
			break;
		case 6:
			BorrarSudoku(ListaSudokus);
			system("pause");
			break;

		}
	} while (selector1 != 0);
	borrarListaJugadores(ListaJugadores);
	system("pause");
	return 0;
}
int MenuM() {
	int selector = -1;

	while (selector < 0 || selector>6) {
		cout << "1.- Jugar" << endl;
		cout << "2.- Ver jugadores ordenados por identificador" << endl;
		cout << "3.- Ver jugadores ordenados por puntos" << endl;
		cout << "4.- Incorporar sudoku" << endl;
		cout << "5.- Añadir un jugador " << endl;
		cout << "6.- Borrar un sudoku" << endl;
		cout << "0.- Salir" << endl;
		cin >> selector;

	}
	return selector;
}