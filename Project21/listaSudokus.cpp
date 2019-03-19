#include "listaSudokus.h"
bool cargarListaSudokus(tListaSudokus & lista) {
	int contador = 0;
	
	ifstream fichero;
	fichero.open("listaSudokus.txt");
	if (fichero.is_open()) {
	   
		while (!fichero.eof()) {
			fichero >> lista.array[contador].fichero;
		    fichero >> lista.array[contador].nivel;
		    contador++;
		}
		
		lista.cont = contador;
		return true;
	}
	else {
		return false;
	}
	
}
void mostrarListaSudokus(const tListaSudokus &lista) {
	int contador = 0;
	while (contador < lista.cont) {
		cout << contador + 1 << "-";
		cout << lista.array[contador].fichero<<" ";
		switch (lista.array[contador].nivel) {
			case 0:
				cout << "FACIL"<<endl;
				break;
			case 1:
				cout << "MEDIO" << endl;
				break;
			case 2:
				cout << "DIFICIL" << endl;
				break;
		}
		contador++;
	}
}
void creaListaSudokus(tListaSudokus & lista) {
	int contador = 0;
	lista.cont = 0;
	while (contador < MAX_SUDOKUS) {
		lista.array[contador].fichero = " ";
		contador++;
	}
}

int menuListaSudokus(const tListaSudokus &lista) {
	int selector = -1;
	
	while (selector<1 || selector>lista.cont) {
		mostrarListaSudokus(lista);
		cin >> selector;
	}
	selector--;
	return selector;
}

