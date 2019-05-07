#include "listaJugadores.h"

void creaListaVacia(tListaJugadores & lista) {
	int contador = 0;
	lista.tamaño = 5;
	lista.jugadores = new tJugador[lista.tamaño];
	while (contador < lista.tamaño) {
		lista.contador = 0;
		lista.jugadores[contador].Id = "";
		lista.jugadores[contador].puntos = NULL;
		contador++;
	}
}

bool cargar(tListaJugadores & lista) {
	ifstream  fichero;
	fichero.open("listaJugadores.txt");
	int contador = 0;
	while (!fichero.eof()) {
		if (contador == lista.tamaño) {
			ampliar(lista);
		}
		fichero >> lista.jugadores[contador].Id;
		fichero >> lista.jugadores[contador].puntos;
		contador++;
	}
	lista.contador = contador-1;
	return true;
}
void mostrar(const tListaJugadores & lista) {
	int contador = 0;
	string mostrar;
	cout << "JUGADORES: " << endl;
	while (contador < lista.contador) {
		mostrar = toString(lista.jugadores[contador]);
		cout <<contador+1<<"- "<<mostrar<<endl;
		contador++;
	}
}

bool guardar(const tListaJugadores &lista) {
	int contador = 0;
	string jugador;
	ofstream fichero;
	fichero.open("listaJugadores.txt");
	if (fichero.is_open()) {
		while (contador < lista.contador) {
			jugador = toString(lista.jugadores[contador]);
			fichero << jugador << endl;
			contador++;
		}
	}
	else {
		return false;
	}
	return true;
}

void puntuarJugador(tListaJugadores & lista, int puntos) {
	string id;
	int pos,selector;
	bool Encontrado;
	tJugador Jugador;
	Jugador.puntos = 0;
	int Inicio = 0, Final = lista.contador - 1;
	cout << "Introduzca su Identificador de jugador para poder puntuarlo: ";
	cin >> id;
	Encontrado = buscar(lista, id, pos,Inicio,Final);

	if (Encontrado) {
		modificarJugador(lista.jugadores[pos], puntos);
	}
	else {
		if (lista.contador == lista.tamaño) {
			ampliar(lista);
		}
		Jugador.Id = id;
		modificarJugador(Jugador, puntos);
		InsertarJugador(lista, Jugador, pos);
	}
	guardar(lista);
}
bool buscar(const tListaJugadores & lista, string id, int &pos,int &Inicio,int &Final) {
	int Centro;
	bool Encontrado = false;
	
		Centro = (Inicio + Final) / 2;
		if (lista.jugadores[Centro].Id == id) {
			Encontrado = true;
			pos = Centro;
		}
		else if (id<lista.jugadores[Centro].Id){
			Final = Centro - 1;
		}
		else {
			Inicio = Centro + 1;
		}
		if (Inicio <= Final && !Encontrado) {
			Encontrado=buscar(lista, id, pos, Inicio, Final);
		}
		if (!Encontrado) {
			pos = Inicio;
		}
	return Encontrado;
}

void InsertarJugador(tListaJugadores &lista, const tJugador &Jugador, const int pos) {
	int contador = lista.contador - 1;
	if (lista.contador == lista.tamaño) {
		ampliar(lista);
	}
	while (contador >= pos) {
		lista.jugadores[contador + 1].Id = lista.jugadores[contador].Id;
		lista.jugadores[contador + 1].puntos = lista.jugadores[contador].puntos;
		contador--;
	}
	lista.jugadores[pos].Id = Jugador.Id;
	lista.jugadores[pos].puntos = Jugador.puntos;
	lista.contador++;
}

tListaJugadores ordenarPorRanking(const tListaJugadores &lista) {
	tListaJugadores CopiaLista;
	creaListaVacia(CopiaLista);
	tJugador Aux;
	int contador1;
	int contador2;
	int selector;
	bool Encontrado = false;
	cout << "Seleccione el metodo de ordenacion que desea: "<<endl;
	cout << "1-Inserccion" << endl;
	cout << "2-Metodo de la burbuja" << endl;
	cin >> selector;
	if (selector == 1) {
		CopiaLista.jugadores[0]=lista.jugadores[0];
		CopiaLista.contador++;
		contador1 = 1;
		contador2 = 0;
		while (contador1 < lista.contador) {
			while (contador2 < contador1 && !Encontrado) {
				if (!menor(lista.jugadores[contador1], CopiaLista.jugadores[contador2])) {
					Encontrado = true;
				}
				else {
					contador2++;
				}
			}
			InsertarJugador(CopiaLista, lista.jugadores[contador1], contador2);
			contador1++;
			contador2 = 0;
			Encontrado = false;
		}
	}
	else if (selector == 2) {
		CopiarLista(lista,CopiaLista);
		contador1 = CopiaLista.contador;
		contador2 = 0;
		while (contador1 > 0) {
			while (contador2 < contador1-1) {
				if (menor(CopiaLista.jugadores[contador2], CopiaLista.jugadores[contador2+1])) {
					Aux = CopiaLista.jugadores[contador2];
			        CopiaLista.jugadores[contador2] = CopiaLista.jugadores[contador2 + 1];
					CopiaLista.jugadores[contador2 + 1] = Aux;
				}
				contador2++;
			}
			contador1--;
			contador2 = 0;
		}
	}
	else {
		cout << "Seleccion no valida" << endl;
	}
	
	return CopiaLista;
}
void annadirJugador(tListaJugadores &lista) {
	tJugador NewPlayer;
	bool Encontrado;
	int pos;
	int Inicio=0,Final=lista.contador-1;
	NewPlayer.puntos = 0;
	if (lista.contador == lista.tamaño) {
		ampliar(lista);
	}
	cout << "Introduzca el id del jugador que quiere añadir: ";
	cin >> NewPlayer.Id;
	Encontrado = buscar(lista, NewPlayer.Id, pos,Inicio,Final);
	if (!Encontrado) {
		InsertarJugador(lista, NewPlayer, pos);
		cout << "Jugador añadido con exito" << endl;
		guardar(lista);
	}
	else {
		cout << "No se ha podido añadir el jugador, ya que ya existe un jugador con ese id" << endl;
	}
}

void CopiarLista(const tListaJugadores &lista,tListaJugadores &Copia) {
	int contador = 0;

	while (contador < lista.contador) {
		if (contador == Copia.tamaño) {
			ampliar(Copia);
		}
	
		Copia.jugadores[contador] = lista.jugadores[contador];
		contador++;
	}
	Copia.contador = lista.contador;
}
void ampliar(tListaJugadores & lista) {
	int contador = 0;
	tPtrJugador Copia;
	Copia = new tJugador[lista.tamaño];
	while (contador < lista.tamaño) {
		Copia[contador] = lista.jugadores[contador];
		contador++;
	}
	lista.tamaño = lista.tamaño * 2;
	borrarListaJugadores(lista);
	lista.jugadores = new tJugador[lista.tamaño];
	contador = 0;
	while (contador < lista.tamaño/2) {
		lista.jugadores[contador]=Copia[contador] ;
		contador++;
	}
	delete[] Copia;
}
void borrarListaJugadores(tListaJugadores & lista) {
	delete[] lista.jugadores;
}