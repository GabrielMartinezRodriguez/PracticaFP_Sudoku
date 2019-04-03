
#include "Conjunto.h"

//inicializa el conjunto c al conjunto vacío
void cjto_vacio(tConjunto &c) {
	c.nElems = 0; //el cardinal se deja a 0
	for (int contador = 0; contador < DIMENSION; contador++) {
		c.elementos[contador] = false;
	}
}

//crea un conjunto con elementos del 1 al 9
void cjto_lleno(tConjunto & c) {
	c.nElems = 9;
	for (int contador = 0; contador < DIMENSION; contador++) {
		c.elementos[contador] = true;
	}
}

/*recibe el conjunto y el numero que queremos comprobar
devuelve true o false en funcion de si pertenece o no a él*/
bool pertenece(const tConjunto &c, int e) {
	return c.elementos[e - 1];
}

//añade el número e [1-9] al conjunto c
void addElemento(tConjunto & c, int e) {
	if (!c.elementos[e - 1]) {
		c.elementos[e - 1] = true;
		c.nElems++;
	}
}

//retira el número e [1-9] del conjunto c
void delElemento(tConjunto & c, int e) {
	if (c.elementos[e - 1]) {
		c.elementos[e - 1] = false;
		c.nElems--;
	}
}

//devuelve el número de elementos que hay en el conjunto c
int numElems(const tConjunto & c) {
	return c.nElems;
}

/* si el conjunto tiene un único elemento, lo devolverá junto 
con un true. En caso contrario, será false*/
bool esUnitario(const tConjunto & c, int &e) {
	int contador = 0;
	bool devolver=false;
	if (c.nElems == 1) {

		/*mientras el boleano para la posición contador sea falso,
		este aumentará en uno*/
		while (!c.elementos[contador]) { 
			contador++;
		}

		/*una vez haya salido la posicion del elemento,
		este tendrá el valor del contador sumando 1*/
		devolver = true;
		e = contador + 1;
	}
	return devolver; //se devuelve true o false
}

//muestra en pantalla los elementos que hay en c
void mostrar(const tConjunto & c) {
	cout << "VALORES POSIBLES: " << endl;
	for (int contador = 0; contador < 9; contador++) {
	    if (c.elementos[contador]) {
			cout<<contador+1<<" ";
		}
		
	}
	cout << endl;
}
