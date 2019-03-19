
#include "Conjunto.h"


void cjto_vacio(tConjunto &c) {
	c.nElems = 0;
	for (int contador = 0; contador < DIMENSION; contador++) {
		c.elementos[contador] = false;
	}
}
void cjto_lleno(tConjunto & c) {
	c.nElems = 9;
	for (int contador = 0; contador < DIMENSION; contador++) {
		c.elementos[contador] = true;
	}
}
bool pertenece(const tConjunto &c, int e) {
	return c.elementos[e - 1];
}
void addElemento(tConjunto & c, int e) {
	if (!c.elementos[e - 1]) {
		c.elementos[e - 1] = true;
		c.nElems++;
	}
}
void delElemento(tConjunto & c, int e) {
	if (c.elementos[e - 1]) {
		c.elementos[e - 1] = false;
		c.nElems--;
	}
}
int numElems(const tConjunto & c) {
	return c.nElems;
}
bool esUnitario(const tConjunto & c, int &e) {
	int contador = 0;
	bool devolver=false;
	if (c.nElems == 1) {
		while (!c.elementos[contador]) {
			contador++;
		}
		devolver = true;
		e = contador + 1;
	}
	return devolver;
}
void mostrar(const tConjunto & c) {
	cout << "VALORES POSIBLES: " << endl;
	for (int contador = 0; contador < 9; contador++) {
	    if (c.elementos[contador]) {
			cout<<contador+1<<" ";
		}
		
	}
	cout << endl;
}
