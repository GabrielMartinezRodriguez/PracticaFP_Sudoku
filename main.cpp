#include "main.h"
using namespace std;

int main() {
	int selector1 = 0;
	int selector2 = 0;
	int puntos;
	tListaSudokus lista;
	
	do {
		selector1 = MenuM();
		if (selector1 == 1) {
			creaListaSudokus(lista);
			cargarListaSudokus(lista);
			selector2 = menuListaSudokus(lista);
			puntos=JugarUnSudoku(lista.array[selector2]);
			if (puntos != 0) {
				cout << "Felicidades has recibido " << puntos << " puntos" << endl;
			}
			system("pause");
			system("cls");
		}
	} while (selector1 == 1);
	system("pause");
	return 0;
}
int MenuM() {
	int selector = -1;

	while (selector < 0 || selector>1) {
		cout << "1-Jugar" << endl;
		cout << "0-Salir" << endl;
		cin >> selector;

	}
	return selector;
}
