#include "Funcionalidades.h"

bool esNumero(char caracter, int &numero) {
int aux;
bool devolver = false;
aux = int(caracter);
aux -= 48;
if (aux >= 0 && aux <= 9) {
	numero = aux;
	devolver = true;
}
return devolver;
}